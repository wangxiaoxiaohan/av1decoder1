/*
;arm64  SIMD 汇编学习笔记
;指令 XX XX2 这样两个一组的指令，不带2的操作低位，带2的操作高位，这里的高位 低位针对的是 source寄存器
;
;arm 寄存器
;X/W寄存器：用于一般计算和整数运算。
;X是64位，W是对应的低32位。
;V寄存器：用于向量和浮点运算，128位宽。
;Q寄存器：也是用于向量运算，别名表示128位的V寄存器。
;D寄存器：用于64位的向量运算和浮点运算，表示V寄存器的低64位。
;
;也就说一般写的就是 
;
;X 和 V
;如果用到w ，则用作通用寄存器，传递参数等常规用途
;
;ld1 指令格式
;ld1 {Vt.<T>}[index], [Xn|SP], Xm
;.<T>
;举例
;.b - 8位无符号整数（Unsigned byte）
;.h - 16位无符号整数（Unsigned halfword）
;.s - 32位单精度浮点数（Single precision float） - 已经提及
;.d - 64位双精度浮点数（Double precision float）
;.8 或 .8b - 8位有符号/无符号整数，具体取决于上下文，通常用于表示8位整数向量
;.16 或 .16b - 16位有符号/无符号整数向量
;
;.4s - 4个32位单精度浮点数组成的向量
;.2d - 2个64位双精度浮点数组成的向量
;依次类推

*/


#define L(x) .L ## x

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



const idct_coeffs, align=4
        // idct4
        .short          2896, 2896*8, 1567, 3784
        // idct8
        .short          799, 4017, 3406, 2276
        // idct16
        .short          401, 4076, 3166, 2598
        .short          1931, 3612, 3920, 1189
        // idct32
        .short          201, 4091, 3035, 2751
        .short          1751, 3703, 3857, 1380
        .short          995, 3973, 3513, 2106
        .short          2440, 3290, 4052, 601
endconst

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
;接着使用 smlsl 指令，将 \s1 中每个16位数与 \c1 相乘后，所得的乘积从 \d0 寄存器当前的值中减去（即先乘后减），结果累加到 \d0 寄存器中。
        smlsl           \d0\().4s, \s1\().4h, \c1
.ifc \sz, .8h
        smull2          \d1\().4s, \s0\().8h, \c0
        smlsl2          \d1\().4s, \s1\().8h, \c1
.endif
.endm

;smlal  比 smull 多了累加操作
.macro smull_smlal d0, d1, s0, s1, c0, c1, sz
        smull           \d0\().4s, \s0\().4h, \c0 ;//使用 smull 指令，将 \s0 寄存器中的4个半字（16位）数据与 \c0 相乘，得到的结果是有符号的32位整数，并累加到 \d0 寄存器对应的低位元素中（.4s 表示四个32位数据）。
        smlal           \d0\().4s, \s1\().4h, \c1
.ifc \sz, .8h
        smull2          \d1\().4s, \s0\().8h, \c0 ;//smull2 和 smlal2 分别是 smull 和 smlal 的变体，用于处理寄存器中的高半部分数据。当 \sz 为 .8h 时，这意味着 \s0 和 \s1 被视为包含8个半字数据（.8h），前4个已经处理，这里处理后4个。结果累加到 \d1 寄存器中。
        smlal2          \d1\().4s, \s1\().8h, \c1
.endif
.endm

.macro sqrshrn_sz d0, s0, s1, shift, sz
        sqrshrn         \d0\().4h, \s0\().4s, \shift ;//按照 \shift 指定的位数右移并饱和处理（确保结果仍在数据类型的范围内），最后将结果转换为16位并存入 \d0 寄存器的低四位
.ifc \sz, .8h
        sqrshrn2        \d0\().8h, \s1\().4s, \shift
.endif
.endm



;t0 = ((in0 + in2) * 181 + 128) >> 8;
;t1 = ((in0 - in2) * 181 + 128) >> 8;
;t2 =  (in1 *  1567         - in3 *  3784         + 2048) >> 12
;t3 =  (in1 *  3784         + in3 *  1567         + 2048) >> 12
;c[0 * stride] = CLIP(t0 + t3);
;;c[1 * stride] = CLIP(t1 + t2);
;c[2 * stride] = CLIP(t1 - t2);
;c[3 * stride] = CLIP(t0 - t3);

;2896, 2896*8, 1567, 3784 这里的2896*8 应该是 v0.h[1] 似乎没有用上 那干嘛写这个

.macro idct_4 r0, r1, r2, r3, sz
        smull_smlal     v6,  v7,  \r1, \r3, v0.h[3], v0.h[2], \sz ;//加////r1内的值 乘以 v0.h[3]， r3内的值 乘以 v0.h[2]
        smull_smlsl   v4,  v5,  \r1, \r3, v0.h[2], v0.h[3], \sz ;'//减//' 
        smull_smlal     v2,  v3,  \r0, \r2, v0.h[0], v0.h[0], \sz ;'//加//'
        sqrshrn_sz      v6,  v6,  v7,  #12, \sz ;'//移位//' 
        sqrshrn_sz     v7,  v4,  v5,  #12, \sz ;'//移位// ' 
                     ;//这里将 V6 V7 V4 V5计算出来的中间值经过移位后存在了 V6 V7 里面
                     ;//此时V4 V5 存的中间已经使用过了，所以修改也没有关系，所以再次作为中间值存储寄存器使用 
        smull_smlsl   v4,  v5,  \r0, \r2, v0.h[0], v0.h[0], \sz ;//减// 
        sqrshrn_sz     v2,  v2,  v3,  #12, \sz ; //移位// 
        sqrshrn_sz     v3,  v4,  v5,  #12, \sz ; //移位// 
                    ;//这一段将 V2 V3 V5 V5 计算出来的中间值经过移位存储在 V2 V3 中


        ;进行蝶形变换的  clip 操作 ，此时 只使用  V6 V7 V2 V3 中经过移位的中间值
        sqadd           \r0\sz,  v2\sz,   v6\sz  ;//clip//
        sqsub           \r3\sz,  v2\sz,   v6\sz  ;//clip//
        sqadd          \r1\sz,  v3\sz,   v7\sz  ;//clip// 
        sqsub          \r2\sz,  v3\sz,   v7\sz  ;//clip// 
.endm

;思路是 同时四行的数据进行同样的操作，每次完成四行的每一行的蝶形变换的一个步骤:中间值计算、移位、clip
function inv_dct_4h_x4_neon, export=1
        movrel          x16, idct_coeffs
        ld1             {v0.4h}, [x16]
        idct_4          v16, v17, v18, v19, .4h
        ret
endfunc

function inv_txfm_add_4x4_neon
        ; v31 仅仅是存数据？
        movi            v31.8h,  #0
        ld1             {v16.4h,v17.4h,v18.4h,v19.4h}, [x2]  ;从 X2存的地址位置 开始加载 16个 16 位 到 V16 V17 V18 V19中，每个加载四个
        st1             {v31.8h}, [x2], #16              //将 V31的中8个16位存到 X2指向的地址，每存一个，X2值增加16位

        blr             x4      ;调用 X4指向的函数 ，，这就是一次一维变换 ，和下面X5组成完整的二维逆变换
                                ;注意是 所有四行的一维变换，不是一次一行 
        st1             {v31.8h}, [x2], #16
        transpose_4x4h  v16, v17, v18, v19, v20, v21, v22, v23

        blr             x5   ;调用 X5指向的函数 

        ;这一段 把 X0 数据加载到V0 V1,修改v16 v18高64位的值(从V17 V19插过来，然后视为8个16位，每个右移4位)
        ld1             {v0.s}[0], [x0], x1 ;从X0所指地址开始加载 一个32位，这里是加载到V0的第一个32位中，之后地址 增加 X1的值
        ld1             {v0.s}[1], [x0], x1 ;同上，只不过加载到第二个32位中
        ins             v16.d[1], v17.d[0] ;将v17的低64位插入到v16的高64位
        ins             v18.d[1], v19.d[0]
        ld1             {v1.s}[0], [x0], x1
        ld1             {v1.s}[1], [x0], x1
        srshr           v16.8h,  v16.8h,  #4
        srshr           v18.8h,  v18.8h,  #4

L(itx_4x4_end): ;展开为 .L itx_4x4_end  这一段 把V0 ,V1的数据 分别加上 V16,v18的数据自之后，存到X0指向的地址里面
        sub             x0,  x0,  x1, lsl #2
        uaddw           v16.8h,  v16.8h,  v0.8b
        sqxtun          v0.8b,   v16.8h  ;sqx指令 主要功能是从更宽的带有符号的整数向量中提取并转换为无符号的较窄整数
        uaddw           v18.8h,  v18.8h,  v1.8b  ;uaddw它的基本作用是将两个无符号整数向量相加，并将结果的宽度拓宽一倍，以容纳可能的溢出
        st1             {v0.s}[0], [x0], x1   
        sqxtun          v1.8b,   v18.8h
        st1             {v0.s}[1], [x0], x1
        st1             {v1.s}[0], [x0], x1
        st1             {v1.s}[1], [x0], x1

        ret             x15  ;因为这里返回了 ，所以inv_txfm_add_dct_dct_4x4_8bpc_neon 后续的代码也不会继续执行了，如果没这一句则会继续
endfunc



function inv_txfm_add_dct_dct_4x4_8bpc_neon, export=1
        mov             x15, x30


.ifc dct_dct, dct_dct   这个case ;是专门用来 做dc 系数的变换的,在解码器的代码中
        cbnz            w3,  1f ;如果W3 不为0 则 调到标签1，相当于 goto，w3中存储的是eob，当其为0的时候 ，则表示只有dc系数，这种情况分析下才不会跳到1f去
        mov             w16, #2896*8
        ld1r            {v16.8h}, [x2] ;从地址x2加载8个16位元素的向量到寄存器v16，并且所有元素都等于该地址处的值。
        dup             v4.8h,   w16 ;复制寄存器w16的内容到向量寄存器v4的所有8个16位元素中。
        strh            wzr, [x2] ;存储零到地址x2指向的位置，使用半字（16位）存储，这里是清零操作。

        ;使用sqrdmulh指令执行平方然后乘以某个系数的操作（在这个例子中是与v4.h[0]相乘，即利用之前加载并复制的系数）。
        ;通过ld1指令逐步从地址x0（并根据x1的值递增地址）加载32位浮点数到向量寄存器v0和v1的不同元素中。
        ;srshr指令执行右移并饱和操作，这里用于除以16（即右移4位，对应于#4），并保持结果在有效范围内。

        ;这一段也是把x0的值加载到V0,V1, 修改V16,V18的值，和 inv_txfm_add_4x4_neon里面做了类似的操作
        sqrdmulh        v16.8h,  v16.8h,  v4.h[0]
        ld1             {v0.s}[0], [x0], x1
        sqrdmulh        v20.8h,  v16.8h,  v4.h[0] 
        ld1             {v0.s}[1], [x0], x1
        srshr           v16.8h,  v20.8h,  #4
        ld1             {v1.s}[0], [x0], x1
        srshr           v18.8h,  v20.8h,  #4
        ld1             {v1.s}[1], [x0], x1

        b               L(itx_4x4_end) //在inv_txfm_add_4x4_neon ;函数里面 这里如果跳了 后面就不再执行 
1:
.endif
        adr             x4,  inv_dct_4h_x4_neon ;这里不是调用函数 而是 把函数地址存到X4 X5 中 ，以方便调用
        adr             x5,  inv_dct_4h_x4_neon
        b               inv_txfm_add_4x4_neon
endfunc