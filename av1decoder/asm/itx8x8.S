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

/*定义 数组转置宏 用于完成某个方向的一维idct后 ，转换数组元素的位置以进行另一个方向的一维变换*/
.macro transpose_8x8h r0, r1, r2, r3, r4, r5, r6, r7, d0, d1, d2, d3, d4, d5, d6, d7
        vswp            \d0,  \d4
        vswp            \d1,  \d5
        vswp            \d2,  \d6
        vswp            \d3,  \d7

        vtrn.32         \r0,  \r2
        vtrn.32         \r1,  \r3
        vtrn.32         \r4,  \r6
        vtrn.32         \r5,  \r7

        vtrn.16         \r0,  \r1
        vtrn.16         \r2,  \r3
        vtrn.16         \r4,  \r5
        vtrn.16         \r6,  \r7
.endm



.macro  movrel rd, val, offset=0
#if defined(__APPLE__)
  .if \offset < 0
        adrp            \rd, \val@PAGE
        add             \rd, \rd, \val@PAGEOFF
        sub             \rd, \rd, -(\offset)
  .else
        adrp            \rd, \val+(\offset)@PAGE
        add             \rd, \rd, \val+(\offset)@PAGEOFF
  .endif
#elif defined(PIC) && defined(_WIN32)
  .if \offset < 0
        adrp            \rd, \val
        add             \rd, \rd, :lo12:\val
        sub             \rd, \rd, -(\offset)
  .else
        adrp            \rd, \val+(\offset)
        add             \rd, \rd, :lo12:\val+(\offset)
  .endif
#elif defined(PIC)
        adrp            \rd, \val+(\offset)
        add             \rd, \rd, :lo12:\val+(\offset)
#else
        ldr             \rd, =\val+\offset
#endif
.endm             




.macro smull_smlsl d0, d1, s0, s1, c0, c1, sz
        smull           \d0\().4s, \s0\().4h, \c0
/* 接着使用 smlsl 指令，将 \s1 中每个16位数与 \c1 相乘后，所得的乘积从 \d0 寄存器当前的值中减去（即先乘后减），结果累加到 \d0 寄存器中。 */
        smlsl           \d0\().4s, \s1\().4h, \c1
.ifc \sz, .8h
        smull2          \d1\().4s, \s0\().8h, \c0
        smlsl2          \d1\().4s, \s1\().8h, \c1
.endif
.endm

/* smlal  比 smull 多了累加操作 */
.macro smull_smlal d0, d1, s0, s1, c0, c1, sz
        smull           \d0\().4s, \s0\().4h, \c0 /*使用 smull 指令，将 \s0 寄存器中的4个半字（16位）数据与 \c0 相乘，得到的结果是有符号的32位整数，并累加到 \d0 寄存器对应的低位元素中（.4s 表示四个32位数据）。 */
        smlal           \d0\().4s, \s1\().4h, \c1
.ifc \sz, .8h
        smull2          \d1\().4s, \s0\().8h, \c0 /*smull2 和 smlal2 分别是 smull 和 smlal 的变体，用于处理寄存器中的高半部分数据。当 \sz 为 .8h 时，这意味着 \s0 和 \s1 被视为包含8个半字数据（.8h），前4个已经处理，这里处理后4个。结果累加到 \d1 寄存器中。*/
        smlal2          \d1\().4s, \s1\().8h, \c1
.endif
.endm

.macro sqrshrn_sz d0, s0, s1, shift, sz
        sqrshrn         \d0\().4h, \s0\().4s, \shift /*按照 \shift 指定的位数右移并饱和处理（确保结果仍在数据类型的范围内），最后将结果转换为16位并存入 \d0 寄存器的低四位 */
.ifc \sz, .8h
        sqrshrn2        \d0\().8h, \s1\().4s, \shift
.endif
.endm


/*************
定义8X8系列变换函数
****/
/*
    const int in1 = c[1 * stride], in3 = c[3 * stride];
    int t4a, t5a, t6a, t7a;
    if (tx64) {
        t4a = (in1 *   799 + 2048) >> 12;//cos
        t5a = (in3 * -2276 + 2048) >> 12;//sin
        t6a = (in3 *  3406 + 2048) >> 12;//cos
        t7a = (in1 *  4017 + 2048) >> 12;//sin
    } else {
        const int in5 = c[5 * stride], in7 = c[7 * stride];

        t4a = ((in1 *   799         - in7 * (4017 - 4096) + 2048) >> 12) - in7;
        t5a =  (in5 *  1703         - in3 *  1138         + 1024) >> 11;
        t6a =  (in5 *  1138         + in3 *  1703         + 1024) >> 11;
        t7a = ((in1 * (4017 - 4096) + in7 *  799          + 2048) >> 12) + in1;
    }
    const int t4  = CLIP(t4a + t5a);
              t5a = CLIP(t4a - t5a);
    const int t7  = CLIP(t7a + t6a);
              t6a = CLIP(t7a - t6a);

    const int t5  = ((t6a - t5a) * 181 + 128) >> 8;
    const int t6  = ((t6a + t5a) * 181 + 128) >> 8;

    const int t0 = c[0 * stride];
    const int t1 = c[2 * stride];
    const int t2 = c[4 * stride];
    const int t3 = c[6 * stride];

    c[0 * stride] = CLIP(t0 + t7);
    c[1 * stride] = CLIP(t1 + t6);
    c[2 * stride] = CLIP(t2 + t5);
    c[3 * stride] = CLIP(t3 + t4);
    c[4 * stride] = CLIP(t3 - t4);
    c[5 * stride] = CLIP(t2 - t5);
    c[6 * stride] = CLIP(t1 - t6);
    c[7 * stride] = CLIP(t0 - t7); 

 */       /*  v16, v17, v18, v19, v20, v21, v22, v23 */
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

/*
    load 加载目标
     shift 需要移位目标 这个是最后的 colshit
     addsrc adddst 扩宽 src/dst
     narrowsrc narrowdst 缩窄 src/dst
     store 存储目标
    uaddw sqxtun应该不需要？
*/
.macro load_add_store load, shift, addsrc, adddst, narrowsrc, narrowdst, store, dst, src, shiftbits=4
.ifnb \load
        ld1             {\load},  [\src], x1
.endif
.ifnb \shift
        srshr           \shift,  \shift,  #\shiftbits
.endif
.ifnb \addsrc
        uaddw           \adddst, \adddst, \addsrc
.endif
.ifnb \narrowsrc
        sqxtun          \narrowdst, \narrowsrc
.endif
.ifnb \store
        st1             {\store},  [\dst], x1
.endif
.endm

/*这一段 V2-V7 的 .8b改成了 .8h*/
.macro load_add_store_8x8 dst, src, shiftbits=4
        mov             \src, \dst
        load_add_store  v2.8h, v16.8h,      ,       ,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v3.8h, v17.8h,      ,       ,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v4.8h, v18.8h, v2.8h, v16.8h,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v5.8h, v19.8h, v3.8h, v17.8h, v16.8h, v2.8h,      , \dst, \src, \shiftbits
        load_add_store  v6.8h, v20.8h, v4.8h, v18.8h, v17.8h, v3.8h, v2.8h, \dst, \src, \shiftbits
        load_add_store  v7.8h, v21.8h, v5.8h, v19.8h, v18.8h, v4.8h, v3.8h, \dst, \src, \shiftbits
        load_add_store  v2.8h, v22.8h, v6.8h, v20.8h, v19.8h, v5.8h, v4.8h, \dst, \src, \shiftbits
        load_add_store  v3.8h, v23.8h, v7.8h, v21.8h, v20.8h, v6.8h, v5.8h, \dst, \src, \shiftbits
        load_add_store       ,       , v2.8h, v22.8h, v21.8h, v7.8h, v6.8h, \dst, \src, \shiftbits
        load_add_store       ,       , v3.8h, v23.8h, v22.8h, v2.8h, v7.8h, \dst, \src, \shiftbits
        load_add_store       ,       ,      ,       , v23.8h, v3.8h, v2.8h, \dst, \src, \shiftbits
        load_add_store       ,       ,      ,       ,       ,      , v3.8h, \dst, \src, \shiftbits
.endm

function inv_adst_8h_x8_neon, export=1
        iadst_8         v16, v17, v18, v19, v20, v21, v22, v23, .8h
        ret
endfunc

function inv_flipadst_8h_x8_neon, export=1
        iadst_8         v23, v22, v21, v20, v19, v18, v17, v16, .8h
        ret
endfunc

function inv_identity_8h_x8_neon, export=1
        sqshl           v16.8h,  v16.8h,  #1
        sqshl           v17.8h,  v17.8h,  #1
        sqshl           v18.8h,  v18.8h,  #1
        sqshl           v19.8h,  v19.8h,  #1
        sqshl           v20.8h,  v20.8h,  #1
        sqshl           v21.8h,  v21.8h,  #1
        sqshl           v22.8h,  v22.8h,  #1
        sqshl           v23.8h,  v23.8h,  #1
        ret
endfunc


function inv_dct_8h_x8_neon, export=1
        movrel          x16, idct_coeffs
        ld1             {v0.8h}, [x16]
        idct_8          v16, v17, v18, v19, v20, v21, v22, v23, .8h, .16b
        ret
endfunc


.macro def_fn_8x8_base variant
function inv_txfm_\variant\()add_8x8_neon
        movi            v28.8h,  #0
        movi            v29.8h,  #0
        movi            v30.8h,  #0
        movi            v31.8h,  #0
        ld1             {v16.8h,v17.8h,v18.8h,v19.8h}, [x2] /*加载前四行*/
        st1             {v28.8h,v29.8h,v30.8h,v31.8h}, [x2], #64 /*把v28-V31存到X2,其实就是置0，最后偏移64字节*/
        ld1             {v20.8h,v21.8h,v22.8h,v23.8h}, [x2] /*加载后四行*/
        st1             {v28.8h,v29.8h,v30.8h,v31.8h}, [x2] /*这里不增加地址 因为X2不用了*/

.ifc \variant, identity_
        // The identity shl #1 and downshift srshr #1 cancel out
.else
        blr             x4
/*rowshift*/
        srshr           v16.8h,  v16.8h,  #1
        srshr           v17.8h,  v17.8h,  #1
        srshr           v18.8h,  v18.8h,  #1
        srshr           v19.8h,  v19.8h,  #1
        srshr           v20.8h,  v20.8h,  #1
        srshr           v21.8h,  v21.8h,  #1
        srshr           v22.8h,  v22.8h,  #1
        srshr           v23.8h,  v23.8h,  #1
.endif

        transpose_8x8h  v16, v17, v18, v19, v20, v21, v22, v23, v24, v25

        blr             x5

        load_add_store_8x8 x0, x7
        ret             x15
endfunc
.endm

def_fn_8x8_base
def_fn_8x8_base identity_

/**************************/
/*定义8X8系列变换的入口*/

.macro def_fn_8x8 txfm1, txfm2
function inv_txfm_add_\txfm1\()_\txfm2\()_8x8_8bpc_neon, export=1
        mov             x15, x30


.ifc \txfm1\()_\txfm2, dct_dct
        idct_dc         8,   8,   1
.endif
        adr             x5,  inv_\txfm2\()_8h_x8_neon
.ifc \txfm1, identity
        b               inv_txfm_identity_add_8x8_neon
.else
        adr             x4,  inv_\txfm1\()_8h_x8_neon
        b               inv_txfm_add_8x8_neon
.endif
endfunc
.endm

def_fn_8x8 dct, dct
def_fn_8x8 identity, identity
def_fn_8x8 dct, adst
def_fn_8x8 dct, flipadst
def_fn_8x8 dct, identity
def_fn_8x8 adst, dct
def_fn_8x8 adst, adst
def_fn_8x8 adst, flipadst
def_fn_8x8 flipadst, dct
def_fn_8x8 flipadst, adst
def_fn_8x8 flipadst, flipadst
def_fn_8x8 identity, dct
def_fn_8x8 adst, identity
def_fn_8x8 flipadst, identity
def_fn_8x8 identity, adst
def_fn_8x8 identity, flipadst