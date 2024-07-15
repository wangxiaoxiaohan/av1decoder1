#define L(x) .L ## x


/*定义function 宏*/
.macro function name, export=0, align=2
    .macro endfunc
#ifdef __ELF__
        .size   \name, . - \name
#endif
#if HAVE_AS_FUNC
        .endfunc
#endif
        .purgem endfunc
    .endm
        .text
        .align \align
    .if \export
        .global EXTERN\name
#ifdef __ELF__
        .type   EXTERN\name, %function
        .hidden EXTERN\name
#elif defined(__MACH__)
        .private_extern EXTERN\name
#endif
#if HAVE_AS_FUNC
        .func   EXTERN\name
#endif
EXTERN\name:
    .else
#ifdef __ELF__
        .type \name, %function
#endif
#if HAVE_AS_FUNC
        .func \name
#endif
    .endif
\name:
#if ARCH_AARCH64
    .if \export
         AARCH64_VALID_CALL_TARGET
    .endif
#endif
.endm


/*这一坨是 定义const 宏*/
.macro  const   name, export=0, align=2
    .macro endconst  /*内部宏 endconst 的主要作用是标记常量定义的结束位置*/
#ifdef __ELF__
        .size   \name, . - \name  /*这部分是针对ELF格式的目标文件，在宏结束的地方计算并设置符号\name的大小。.表示当前地址，所以. - \name计算的是从符号开始到当前位置的距离，即数据的实际大小。*/
                                  /*这里应该是计算当前位置到 /NAME 的 size，也就是 整个const 宏的最后面那里 */                                                              
#endif
        .purgem endconst   /*.purgem 是一个汇编指令，用于从当前汇编环境中移除（清除）之前定义的宏*/
    .endm
/*数据段*/
#if defined(_WIN32)
        .section        .rdata
#elif !defined(__MACH__)
        .section        .rodata
#else
        .const_data
#endif
        .align          \align
/*外部可见*/
    .if \export
        .global EXTERN\name
#ifdef __ELF__
        .hidden EXTERN\name              /*使用.hidden标记符号为外部链接但不在符号表中显示，以减少链接时的可见性。*/
#elif defined(__MACH__)
        .private_extern EXTERN\name
#endif
EXTERN\name:
    .endif
\name:
.endm

/*定义idct 数组，spec中的 COS128XXX */
const idct_coeffs, align=4
        /*  idct4 */
        .short          2896, 2896*8, 1567, 3784
        /*  idct8 */
        .short          799, 4017, 3406, 2276
        /*  idct16 */
        .short          401, 4076, 3166, 2598
        .short          1931, 3612, 3920, 1189
        /*  idct32 */
        .short          201, 4091, 3035, 2751
        .short          1751, 3703, 3857, 1380
        .short          995, 3973, 3513, 2106
        .short          2440, 3290, 4052, 601
endconst

const iadst8_coeffs, align=4
        .short          4076, 401, 3612, 1931
        .short          2598, 3166, 1189, 3920
        // idct_coeffs
        .short          2896, 0, 1567, 3784, 0, 0, 0, 0
endconst

.macro idct_dc w, h, shift
        cbnz            w3,  1f
        mov             w16, #2896*8
        ld1r            {v16.8h}, [x2]
        dup             v0.4h,   w16
        sqrdmulh        v16.8h,  v16.8h,  v0.h[0]
        strh            wzr, [x2]
.if (\w == 2*\h) || (2*\w == \h)
        sqrdmulh        v16.8h,  v16.8h,  v0.h[0]
.endif
.if \shift > 0
        srshr           v16.8h,  v16.8h,  #\shift
.endif
        sqrdmulh        v16.8h,  v16.8h,  v0.h[0]
        srshr           v16.8h,  v16.8h,  #4
        mov             w4,  #\h
        b               idct_dc_w\w\()_neon
1:
.endm



function inv_txfm_add_16x16_neon
        mov             x15, x30
        sub             sp,  sp,  #512
        ldrh            w12, [x13], #2
.irp i, 0, 4, 8, 12
        add             x6,  sp,  #(\i*16*2)
.if \i > 0
        mov             w8,  #(16 - \i)
        cmp             w3,  w12
        b.lt            1f
.if \i < 12
        ldrh            w12, [x13], #2
.endif
.endif
        add             x7,  x2,  #(\i*4)
        mov             x8,  #16*4
        bl              inv_txfm_horz_16x4_neon
.endr
        b               3f
1:
        movi            v4.8h,  #0
        movi            v5.8h,  #0
        movi            v6.8h,  #0
        movi            v7.8h,  #0
2:
        subs            w8,  w8,  #4
.rept 2
        st1             {v4.8h, v5.8h, v6.8h, v7.8h}, [x6], #64
.endr
        b.gt            2b
3:
.irp i, 0, 8
        add             x6,  x0,  #(\i*2)
        add             x7,  sp,  #(\i*2)
        mov             x8,  #32
        bl              inv_txfm_add_vert_8x16_neon
.endr

        add             sp,  sp,  #512
        ret             x15
endfunc

const eob_16x16
        .short 10, 36, 78, 256
endconst

const eob_16x16_identity
        .short 4, 8, 12, 256
endconst


.macro def_fn_16x16 txfm1, txfm2
function inv_txfm_add_\txfm1\()_\txfm2\()_16x16_16bpc_neon, export=1
.ifc \txfm1\()_\txfm2, dct_dct
        idct_dc         16,  16,  2
.endif
        adr             x4,  inv_\txfm1\()_4s_x16_neon
        movrel          x5,  X(inv_\txfm2\()_8h_x16_neon)
.ifc \txfm1, identity
.ifc \txfm2, identity
        movrel          x13, eob_16x16
.else
        movrel          x13, eob_16x16_identity
.endif
.else
.ifc \txfm2, identity
        movrel          x13, eob_16x16_identity
.else
        movrel          x13, eob_16x16
.endif
.endif
        b               inv_txfm_add_16x16_neon
endfunc
.endm

def_fn_16x16 dct, dct
def_fn_16x16 identity, identity
def_fn_16x16 dct, adst
def_fn_16x16 dct, flipadst
def_fn_16x16 dct, identity
def_fn_16x16 adst, dct
def_fn_16x16 adst, adst
def_fn_16x16 adst, flipadst
def_fn_16x16 flipadst, dct
def_fn_16x16 flipadst, adst
def_fn_16x16 flipadst, flipadst
def_fn_16x16 identity, dct
