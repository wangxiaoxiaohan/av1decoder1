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

function idct_dc_w8_neon
1:
        ld1             {v0.8b}, [x0], x1
        ld1             {v1.8b}, [x0], x1
        ld1             {v2.8b}, [x0], x1
        uaddw           v20.8h,  v16.8h, v0.8b
        ld1             {v3.8b}, [x0], x1
        sub             x0,  x0,  x1, lsl #2
        subs            w4,  w4,  #4
        uaddw           v21.8h,  v16.8h, v1.8b
        sqxtun          v0.8b,   v20.8h
        uaddw           v22.8h,  v16.8h, v2.8b
        sqxtun          v1.8b,   v21.8h
        uaddw           v23.8h,  v16.8h, v3.8b
        st1             {v0.8b}, [x0], x1
        sqxtun          v2.8b,   v22.8h
        st1             {v1.8b}, [x0], x1
        sqxtun          v3.8b,   v23.8h
        st1             {v2.8b}, [x0], x1
        st1             {v3.8b}, [x0], x1
        b.gt            1b
        ret
endfunc

/*定义 数组转置宏 用于完成某个方向的一维idct后 ，转换数组元素的位置以进行另一个方向的一维变换*/
.macro transpose_8x8h r0, r1, r2, r3, r4, r5, r6, r7, t8, t9
        trn1            \t8\().8h,  \r0\().8h,  \r1\().8h
        trn2            \t9\().8h,  \r0\().8h,  \r1\().8h
        trn1            \r1\().8h,  \r2\().8h,  \r3\().8h
        trn2            \r3\().8h,  \r2\().8h,  \r3\().8h
        trn1            \r0\().8h,  \r4\().8h,  \r5\().8h
        trn2            \r5\().8h,  \r4\().8h,  \r5\().8h
        trn1            \r2\().8h,  \r6\().8h,  \r7\().8h
        trn2            \r7\().8h,  \r6\().8h,  \r7\().8h

        trn1            \r4\().4s,  \r0\().4s,  \r2\().4s
        trn2            \r2\().4s,  \r0\().4s,  \r2\().4s
        trn1            \r6\().4s,  \r5\().4s,  \r7\().4s
        trn2            \r7\().4s,  \r5\().4s,  \r7\().4s
        trn1            \r5\().4s,  \t9\().4s,  \r3\().4s
        trn2            \t9\().4s,  \t9\().4s,  \r3\().4s
        trn1            \r3\().4s,  \t8\().4s,  \r1\().4s
        trn2            \t8\().4s,  \t8\().4s,  \r1\().4s

        trn1            \r0\().2d,  \r3\().2d,  \r4\().2d
        trn2            \r4\().2d,  \r3\().2d,  \r4\().2d
        trn1            \r1\().2d,  \r5\().2d,  \r6\().2d
        trn2            \r5\().2d,  \r5\().2d,  \r6\().2d
        trn2            \r6\().2d,  \t8\().2d,  \r2\().2d
        trn1            \r2\().2d,  \t8\().2d,  \r2\().2d
        trn1            \r3\().2d,  \t9\().2d,  \r7\().2d
        trn2            \r7\().2d,  \t9\().2d,  \r7\().2d
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



.macro idct_4 r0, r1, r2, r3, sz
        smull_smlal     v6,  v7,  \r1, \r3, v0.h[3], v0.h[2], \sz /*加////r1内的值 乘以 v0.h[3]， r3内的值 乘以 v0.h[2] */
        smull_smlsl   v4,  v5,  \r1, \r3, v0.h[2], v0.h[3], \sz /*/减//' */
        smull_smlal     v2,  v3,  \r0, \r2, v0.h[0], v0.h[0], \sz /*//加//'*/
        sqrshrn_sz      v6,  v6,  v7,  #12, \sz /*移位//' */
        sqrshrn_sz     v7,  v4,  v5,  #12, \sz /*移位// ' */
                     /*这里将 V6 V7 V4 V5计算出来的中间值经过移位后存在了 V6 V7 里面*/
                     /*此时V4 V5 存的中间已经使用过了，所以修改也没有关系，所以再次作为中间值存储寄存器使用 */
        smull_smlsl   v4,  v5,  \r0, \r2, v0.h[0], v0.h[0], \sz /*;//减// */
        sqrshrn_sz     v2,  v2,  v3,  #12, \sz /* //移位// */
        sqrshrn_sz     v3,  v4,  v5,  #12, \sz /* //移位// */
                    /*这一段将 V2 V3 V5 V5 计算出来的中间值经过移位存储在 V2 V3 中*/


        /*进行蝶形变换的  clip 操作 ，此时 只使用  V6 V7 V2 V3 中经过移位的中间值*/
        sqadd           \r0\sz,  v2\sz,   v6\sz  /*//clip// */
        sqsub           \r3\sz,  v2\sz,   v6\sz  /*//clip//*/
        sqadd          \r1\sz,  v3\sz,   v7\sz  /*//clip// */
        sqsub          \r2\sz,  v3\sz,   v7\sz  /*/clip// */
        
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

/*这一段 V2-V7 的 .8b改成了 .8h*/
.macro load_add_store_8x8 dst, src, shiftbits=4
        mov             \src, \dst
        load_add_store  v2.8h, v16.8h,      ,       ,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v3.8h, v17.8h,      ,       ,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v4.8h, v18.8h, v2.8h, v16.8h,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v5.8h, v19.8h, v3.8h, v17.8h,       ,      ,      , \dst, \src, \shiftbits
        load_add_store  v6.8h, v20.8h, v4.8h, v18.8h,       ,      , v2.8h, \dst, \src, \shiftbits
        load_add_store  v7.8h, v21.8h, v5.8h, v19.8h,       ,      , v3.8h, \dst, \src, \shiftbits
        load_add_store  v2.8h, v22.8h, v6.8h, v20.8h,       ,      , v4.8h, \dst, \src, \shiftbits
        load_add_store  v3.8h, v23.8h, v7.8h, v21.8h,       ,      , v5.8h, \dst, \src, \shiftbits
        load_add_store       ,       , v2.8h, v22.8h,       ,      , v6.8h, \dst, \src, \shiftbits
        load_add_store       ,       , v3.8h, v23.8h,       ,      , v7.8h, \dst, \src, \shiftbits
        load_add_store       ,       ,      ,       ,       ,      , v2.8h, \dst, \src, \shiftbits
        load_add_store       ,       ,      ,       ,       ,      , v3.8h, \dst, \src, \shiftbits
.endm

.macro iadst_8 o0, o1, o2, o3, o4, o5, o6, o7, sz
        movrel          x16, iadst8_coeffs
        ld1             {v0.8h, v1.8h}, [x16]

        smull_smlal     v2,  v3,  v23, v16, v0.h[0], v0.h[1], \sz
        smull_smlsl     v4,  v5,  v23, v16, v0.h[1], v0.h[0], \sz
        smull_smlal     v6,  v7,  v21, v18, v0.h[2], v0.h[3], \sz
        sqrshrn_sz      v16, v2,  v3,  #12, \sz  // t0a
        sqrshrn_sz      v23, v4,  v5,  #12, \sz  // t1a
        smull_smlsl     v2,  v3,  v21, v18, v0.h[3], v0.h[2], \sz
        smull_smlal     v4,  v5,  v19, v20, v0.h[4], v0.h[5], \sz
        sqrshrn_sz      v18, v6,  v7,  #12, \sz  // t2a
        sqrshrn_sz      v21, v2,  v3,  #12, \sz  // t3a
        smull_smlsl     v6,  v7,  v19, v20, v0.h[5], v0.h[4], \sz
        smull_smlal     v2,  v3,  v17, v22, v0.h[6], v0.h[7], \sz
        sqrshrn_sz      v20, v4,  v5,  #12, \sz  // t4a
        sqrshrn_sz      v19, v6,  v7,  #12, \sz  // t5a
        smull_smlsl     v4,  v5,  v17, v22, v0.h[7], v0.h[6], \sz
        sqrshrn_sz      v22, v2,  v3,  #12, \sz  // t6a
        sqrshrn_sz      v17, v4,  v5,  #12, \sz  // t7a

        sqadd           v2\sz,   v16\sz,  v20\sz // t0
        sqsub           v3\sz,   v16\sz,  v20\sz // t4
        sqadd           v4\sz,   v23\sz,  v19\sz // t1
        sqsub           v5\sz,   v23\sz,  v19\sz // t5
        sqadd           v6\sz,   v18\sz,  v22\sz // t2
        sqsub           v7\sz,   v18\sz,  v22\sz // t6
        sqadd           v18\sz,  v21\sz,  v17\sz // t3
        sqsub           v19\sz,  v21\sz,  v17\sz // t7

        smull_smlal     v16, v17, v3,  v5,  v1.h[3], v1.h[2], \sz
        smull_smlsl     v20, v21, v3,  v5,  v1.h[2], v1.h[3], \sz
        smull_smlsl     v22, v23, v19, v7,  v1.h[3], v1.h[2], \sz

        sqrshrn_sz      v3,  v16, v17, #12, \sz  // t4a
        sqrshrn_sz      v5,  v20, v21, #12, \sz  // t5a

        smull_smlal     v16, v17, v19, v7,  v1.h[2], v1.h[3], \sz

        sqrshrn_sz      v7,  v22, v23, #12, \sz  // t6a
        sqrshrn_sz      v19, v16, v17, #12, \sz  // t7a

        sqadd           \o0\()\sz, v2\sz, v6\sz  // out0
        sqsub           v2\sz,     v2\sz, v6\sz  // t2
        sqadd           \o7\()\sz, v4\sz, v18\sz // out7
        sqsub           v4\sz,     v4\sz, v18\sz // t3
        sqneg           \o7\()\sz, \o7\()\sz     // out7

        sqadd           \o1\()\sz, v3\sz, v7\sz  // out1
        sqsub           v3\sz,     v3\sz, v7\sz  // t6
        sqadd           \o6\()\sz, v5\sz, v19\sz // out6
        sqsub           v5\sz,     v5\sz, v19\sz // t7
        sqneg           \o1\()\sz, \o1\()\sz     // out1

        smull_smlal     v18, v19, v2,  v4,  v1.h[0], v1.h[0], \sz // -> out3 (v19 or v20)
        smull_smlsl     v6,  v7,  v2,  v4,  v1.h[0], v1.h[0], \sz // -> out4 (v20 or v19)
        smull_smlsl     v20, v21, v3,  v5,  v1.h[0], v1.h[0], \sz // -> out5 (v21 or v18)
        sqrshrn_sz      v2,  v18, v19, #12, \sz // out3
        smull_smlal     v18, v19, v3,  v5,  v1.h[0], v1.h[0], \sz // -> out2 (v18 or v21)
        sqrshrn_sz      v3,  v20, v21, #12, \sz // out5
        sqrshrn_sz      \o2, v18, v19, #12, \sz // out2 (v18 or v21)
        sqrshrn_sz      \o4, v6,  v7,  #12, \sz // out4 (v20 or v19)

        sqneg           \o3\()\sz, v2\sz     // out3
        sqneg           \o5\()\sz, v3\sz     // out5
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
        ld1             {v16.8h,v17.8h,v18.8h,v19.8h}, [x2] /*加载前四行 列？*/
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