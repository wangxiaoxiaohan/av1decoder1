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


.macro  transpose_4x4h  r0, r1, r2, r3, t4, t5, t6, t7
        trn1            \t4\().4h,  \r0\().4h,  \r1\().4h
        trn2            \t5\().4h,  \r0\().4h,  \r1\().4h
        trn1            \t6\().4h,  \r2\().4h,  \r3\().4h
        trn2            \t7\().4h,  \r2\().4h,  \r3\().4h

        trn1            \r0\().2s,  \t4\().2s,  \t6\().2s
        trn2            \r2\().2s,  \t4\().2s,  \t6\().2s
        trn1            \r1\().2s,  \t5\().2s,  \t7\().2s
        trn2            \r3\().2s,  \t5\().2s,  \t7\().2s
.endm

.macro scale_input sz, c, r0, r1, r2 r3, r4, r5, r6, r7
        sqrdmulh        \r0\sz,  \r0\sz,  \c
        sqrdmulh        \r1\sz,  \r1\sz,  \c
        sqrdmulh        \r2\sz,  \r2\sz,  \c
        sqrdmulh        \r3\sz,  \r3\sz,  \c
.ifnb \r4
        sqrdmulh        \r4\sz,  \r4\sz,  \c
        sqrdmulh        \r5\sz,  \r5\sz,  \c
        sqrdmulh        \r6\sz,  \r6\sz,  \c
        sqrdmulh        \r7\sz,  \r7\sz,  \c
.endif
.endm

.macro load_add_store load, shift, addsrc, adddst, narrowsrc, narrowdst, store, dst, src, shiftbits=4
.ifnb \load
        ld1             {\load},  [\src], x1
.endif
.ifnb \shift
        srshr           \shift,  \shift,  #\shiftbits
.endif
/*
.ifnb \addsrc
        uaddw           \adddst, \adddst, \addsrc
.endif
*/
/*
改为使用sqadd 由于少了一个步骤，所有需要交换dst和src
*/

.ifnb \addsrc
        sqadd           \addsrc, \addsrc, \adddst
.endif
/* 不再需要
.ifnb \narrowsrc
        sqxtun          \narrowdst, \narrowsrc
.endif
*/

.ifnb \store
        st1             {\store},  [\dst], x1
.endif
.endm


.macro load_add_store_8x4 dst, src
        mov             \src, \dst
        load_add_store  v2.8b, v16.8h,      ,       ,       ,      ,      , \dst, \src
        load_add_store  v3.8b, v17.8h,      ,       ,       ,      ,      , \dst, \src
        load_add_store  v4.8b, v18.8h, v2.8b, v16.8h,       ,      ,      , \dst, \src
        load_add_store  v5.8b, v19.8h, v3.8b, v17.8h,       ,      ,      , \dst, \src
        load_add_store       ,       , v4.8b, v18.8h,       ,      , v2.8b, \dst, \src
        load_add_store       ,       , v5.8b, v19.8h,       ,      , v3.8b, \dst, \src
        load_add_store       ,       ,      ,       ,       ,      , v4.8b, \dst, \src
        load_add_store       ,       ,      ,       ,       ,      , v5.8b, \dst, \src
.endm

.macro load_add_store4 load, inssrc, insdst, shift, addsrc, adddst, narrowsrc, narrowdst, store, dst, src
.ifnb \load
        ld1             {\load}[0],  [\src], x1
.endif
.ifnb \inssrc
        ins             \insdst\().d[1],   \inssrc\().d[0]
.endif
.ifnb \shift
        srshr           \shift,  \shift,  #4
.endif
.ifnb \load
        ld1             {\load}[1],  [\src], x1
.endif
.ifnb \addsrc
        uaddw           \adddst, \adddst, \addsrc
.endif
.ifnb \store
        st1             {\store}[0],  [\dst], x1
.endif
.ifnb \narrowsrc
        sqxtun          \narrowdst, \narrowsrc
.endif
.ifnb \store
        st1             {\store}[1],  [\dst], x1
.endif
.endm

.macro load_add_store_4x8 dst, src
        mov             \src, \dst
        load_add_store4 v0.s, v17, v16,       ,      ,       ,       ,      ,     , \dst, \src
        load_add_store4 v1.s, v19, v18,       ,      ,       ,       ,      ,     , \dst, \src
        load_add_store4 v2.s, v21, v20, v16.8h,      ,       ,       ,      ,     , \dst, \src
        load_add_store4 v3.s, v23, v22, v18.8h, v0.8b, v16.8h,       ,      ,     , \dst, \src
        load_add_store4     ,    ,    , v20.8h, v1.8b, v18.8h, v16.8h, v0.8b,     , \dst, \src
        load_add_store4     ,    ,    , v22.8h, v2.8b, v20.8h, v18.8h, v1.8b, v0.s, \dst, \src
        load_add_store4     ,    ,    ,       , v3.8b, v22.8h, v20.8h, v2.8b, v1.s, \dst, \src
        load_add_store4     ,    ,    ,       ,      ,       , v22.8h, v3.8b, v2.s, \dst, \src
        load_add_store4     ,    ,    ,       ,      ,       ,       ,      , v3.s, \dst, \src
.endm

.macro idct_8 r0, r1, r2, r3, r4, r5, r6, r7, sz, szb
        idct_4          \r0, \r2, \r4, \r6, \sz

        smull_smlsl     v2,  v3,  \r1, \r7, v0.h[4], v0.h[5], \sz // -> t4a
        smull_smlal     v4,  v5,  \r1, \r7, v0.h[5], v0.h[4], \sz // -> t7a
        smull_smlsl     v6,  v7,  \r5, \r3, v0.h[6], v0.h[7], \sz // -> t5a
        sqrshrn_sz      \r1, v2,  v3,  #12, \sz                   // t4a
        sqrshrn_sz      \r7, v4,  v5,  #12, \sz                   // t7a
        smull_smlal     v2,  v3,  \r5, \r3, v0.h[7], v0.h[6], \sz // -> t6a
        sqrshrn_sz      \r3, v6,  v7,  #12, \sz                   // t5a
        sqrshrn_sz      \r5, v2,  v3,  #12, \sz                   // t6a

        sqadd           v2\sz,   \r1\sz,  \r3\sz // t4
        sqsub           \r1\sz,  \r1\sz,  \r3\sz // t5a
        sqadd           v3\sz,   \r7\sz,  \r5\sz // t7
        sqsub           \r3\sz,  \r7\sz,  \r5\sz // t6a

        smull_smlsl     v4,  v5,  \r3, \r1, v0.h[0], v0.h[0], \sz // -> t5
        smull_smlal     v6,  v7,  \r3, \r1, v0.h[0], v0.h[0], \sz // -> t6
        sqrshrn_sz      v4,  v4,  v5,  #12, \sz // t5
        sqrshrn_sz      v5,  v6,  v7,  #12, \sz // t6

        sqsub           \r7\sz,  \r0\sz,  v3\sz // out7
        sqadd           \r0\sz,  \r0\sz,  v3\sz // out0
        sqadd           \r1\sz,  \r2\sz,  v5\sz // out1
        sqsub           v6\sz,   \r2\sz,  v5\sz // out6
        sqadd           \r2\sz,  \r4\sz,  v4\sz // out2
        sqsub           \r5\sz,  \r4\sz,  v4\sz // out5
        sqadd           \r3\sz,  \r6\sz,  v2\sz // out3
        sqsub           \r4\sz,  \r6\sz,  v2\sz // out4
        mov             \r6\szb, v6\szb         // out6
.endm

.macro iadst_8x4 o0, o1, o2, o3
        movrel          x16, iadst4_coeffs
        ld1             {v0.8h}, [x16]

        ssubl           v2.4s,   v16.4h,  v18.4h
        ssubl2          v3.4s,   v16.8h,  v18.8h
        smull           v4.4s,   v16.4h,  v0.h[0]
        smlal           v4.4s,   v18.4h,  v0.h[1]
        smlal           v4.4s,   v19.4h,  v0.h[2]
        smull2          v5.4s,   v16.8h,  v0.h[0]
        smlal2          v5.4s,   v18.8h,  v0.h[1]
        smlal2          v5.4s,   v19.8h,  v0.h[2]
        saddw           v2.4s,   v2.4s,   v19.4h
        saddw2          v3.4s,   v3.4s,   v19.8h
        smull           v6.4s,   v16.4h,  v0.h[2]
        smlsl           v6.4s,   v18.4h,  v0.h[0]
        smlsl           v6.4s,   v19.4h,  v0.h[1]
        smull2          v7.4s,   v16.8h,  v0.h[2]
        smlsl2          v7.4s,   v18.8h,  v0.h[0]
        smlsl2          v7.4s,   v19.8h,  v0.h[1]

        mul             v18.4s,  v2.4s,   v0.s[2]
        mul             v19.4s,  v3.4s,   v0.s[2]

        smull           v2.4s,   v17.4h,  v0.h[3]
        smull2          v3.4s,   v17.8h,  v0.h[3]

        add             v16.4s,  v4.4s,   v2.4s // out0
        add             v17.4s,  v5.4s,   v3.4s

        add             v4.4s,   v4.4s,   v6.4s // out3
        add             v5.4s,   v5.4s,   v7.4s

        add             v6.4s,   v6.4s,   v2.4s // out1
        add             v7.4s,   v7.4s,   v3.4s

        sub             v4.4s,   v4.4s,   v2.4s // out3
        sub             v5.4s,   v5.4s,   v3.4s

        sqrshrn         v18.4h,  v18.4s, #12
        sqrshrn2        v18.8h,  v19.4s, #12

        sqrshrn         \o0\().4h, v16.4s, #12
        sqrshrn2        \o0\().8h, v17.4s, #12

.ifc \o2, v17
        mov             v17.16b,   v18.16b
.endif

        sqrshrn         \o1\().4h, v6.4s,  #12
        sqrshrn2        \o1\().8h, v7.4s,  #12

        sqrshrn         \o3\().4h, v4.4s,  #12
        sqrshrn2        \o3\().8h, v5.4s,  #12
.endm

//这里的 4h_x8 4h 的h 代表16 位，不是高度
function inv_dct_4h_x8_neon, export=1
        movrel          x16, idct_coeffs
        ld1             {v0.8h}, [x16]
        idct_8          v16, v17, v18, v19, v20, v21, v22, v23, .4h, .8b
        ret
endfunc
function inv_adst_4h_x8_neon, export=1
        iadst_8         v16, v17, v18, v19, v20, v21, v22, v23, .4h
        ret
endfunc

function inv_flipadst_4h_x8_neon, export=1
        iadst_8         v23, v22, v21, v20, v19, v18, v17, v16, .4h
        ret
endfunc
function inv_identity_4h_x8_neon, export=1
        sqshl           v16.4h,  v16.4h,  #1
        sqshl           v17.4h,  v17.4h,  #1
        sqshl           v18.4h,  v18.4h,  #1
        sqshl           v19.4h,  v19.4h,  #1
        sqshl           v20.4h,  v20.4h,  #1
        sqshl           v21.4h,  v21.4h,  #1
        sqshl           v22.4h,  v22.4h,  #1
        sqshl           v23.4h,  v23.4h,  #1
        ret
endfunc


function inv_txfm_add_8x4_neon
        movi            v30.8h,  #0
        movi            v31.8h,  #0
        mov             w16, #2896*8
        dup             v0.4h,   w16
        ld1             {v16.4h,v17.4h,v18.4h,v19.4h}, [x2]
        st1             {v30.8h,v31.8h}, [x2], #32
        ld1             {v20.4h,v21.4h,v22.4h,v23.4h}, [x2]
        st1             {v30.8h,v31.8h}, [x2]

        scale_input     .4h, v0.h[0], v16, v17, v18, v19, v20, v21, v22, v23

        blr             x4

        transpose_4x4h  v16, v17, v18, v19, v4,  v5,  v6,  v7
        transpose_4x4h  v20, v21, v22, v23, v4,  v5,  v6,  v7
        ins             v16.d[1], v20.d[0]
        ins             v17.d[1], v21.d[0]
        ins             v18.d[1], v22.d[0]
        ins             v19.d[1], v23.d[0]

        blr             x5

        load_add_store_8x4 x0, x7
        ret             x15
endfunc

function inv_txfm_add_4x8_neon
        movi            v28.8h,  #0
        movi            v29.8h,  #0
        movi            v30.8h,  #0
        movi            v31.8h,  #0
        mov             w16, #2896*8
        dup             v0.4h,   w16
        ld1             {v16.8h,v17.8h,v18.8h,v19.8h}, [x2]
        st1             {v28.8h,v29.8h,v30.8h,v31.8h}, [x2]

        scale_input     .8h, v0.h[0], v16, v17, v18, v19

        blr             x4

        transpose_4x8h  v16, v17, v18, v19, v4,  v5,  v6,  v7
        ins             v20.d[0], v16.d[1]
        ins             v21.d[0], v17.d[1]
        ins             v22.d[0], v18.d[1]
        ins             v23.d[0], v19.d[1]

        blr             x5

        load_add_store_4x8 x0, x7
        ret             x15
endfunc

.macro def_fn_48 w, h, txfm1, txfm2
function inv_txfm_add_\txfm1\()_\txfm2\()_\w\()x\h\()_8bpc_neon, export=1
        mov             x15, x30

.ifc \txfm1\()_\txfm2, dct_dct
        idct_dc         \w,  \h,  0
.endif
        adr             x4,  inv_\txfm1\()_\h\()h_x\w\()_neon
        adr             x5,  inv_\txfm2\()_\w\()h_x\h\()_neon
        b               inv_txfm_add_\w\()x\h\()_neon
endfunc
.endm

.macro def_fns_48 w, h
def_fn_48 \w, \h, dct, dct
def_fn_48 \w, \h, identity, identity
def_fn_48 \w, \h, dct, adst
def_fn_48 \w, \h, dct, flipadst
def_fn_48 \w, \h, dct, identity
def_fn_48 \w, \h, adst, dct
def_fn_48 \w, \h, adst, adst
def_fn_48 \w, \h, adst, flipadst
def_fn_48 \w, \h, flipadst, dct
def_fn_48 \w, \h, flipadst, adst
def_fn_48 \w, \h, flipadst, flipadst
def_fn_48 \w, \h, identity, dct
def_fn_48 \w, \h, adst, identity
def_fn_48 \w, \h, flipadst, identity
def_fn_48 \w, \h, identity, adst
def_fn_48 \w, \h, identity, flipadst
.endm

def_fns_48 4, 8
def_fns_48 8, 4