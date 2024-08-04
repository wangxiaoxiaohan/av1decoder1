本仓库中的 dav1d 是学习版本 某些地方加了注释，某些地方做了修改，仅做学习之用
待做：
1.根据过程 ，整理规划变量 ，添加新的上下文 *
2.编译问题 
3. 分配内存，size确定 *
4.确定 所有 memcpy的size *
5 .6.10.25. Assign mv semantics 里面有一个 is_mv_vaild函数 
6. sort函数 *
7.确定所有 memcpy 多维数组的时候 ，是否内存连续 *
8. 7.11.3.3
9.结构体分配内后 memset
10. 所有return ERROR_CODE的地方是否正确 *
11.大量 数组作为二级/三级 指针传递问题！！！ 大量函数内定义 临时 二级 三级指针却没有分配内存 
        解决方法：一定要用 new或者malloc 分配，这样子传给给函数可以使用 [][]访问 *
12.BLOCKDATA 内存2还没没分配！*
13. cdf 数组和frameheader 在 framecontext和av1context之间的转换逻辑
14. 注意动态分配的多维数组的内存 memset的时候也必须 循环给子数组 memset
15 . decode.cpp 5071 行到底有什么问题？
16 .initSymbol 的时候 就出错了 sz 错误

!!问题在 init symbol上面

-------从头开始 用 gdb 一步一步的查
验证某个 obu 读取的 size 和 它的 obu_size是否 对得上

解决 readbits 某些情况下 会有符号的问题

DAV1D obu.c1387 开始 将 getbis 指针引用 转移到熵解码上下文中
dav1d decode.c 3548 拷贝数据


从 skip segment id 开始就不对了？
symbol填数据 仔细看看 有什么问题

*releaseDecodeContext 释放内存 函数没有调用
* 把new/delete 换成 malloc/free

疑难问题1:
问题： delete array16的时候出现double free，原因:使用 array的时候没有使用 (* x)[]这种方法访问
而是直接x[],这没有访问到数据，反而修改到x指向的内存地址，导致delete的时候出现问题。
疑难问题2:
  delete [] palette_delta_y出现问题 并不是必现，为什么删除的时候 判断都为空？
  gdb 調試发现，has_palette_x 的值为 255，应该是某处 memset 或者内存操作越界,?
  解决方法，构建BLOCKDATA结构体之后 ,内存置为0;



对比 DAV1D ： 第二个partition的restoration_type 就有问题，对比 一直有问题 ，巧合?
对比 coef中解码的 参数 数量 ，值

最后一次解码 coeff_br 和DAV1d对不上

read_lr_unit    decode_signed_subexp_with_ref_bool 读了一次 ，dav1d 读了两次。对不上


eob 512?--
*检查 get_coeff_base_ctx
*检查 进入 错误的 block之后 sbCtx->SymbolValue 出现问题

Quant的数据 不对，赋值的时候 是正常的
b decode.cpp 2029 2100

//printf("|@%d %d %d %d %d %d %d %d %d",i,j,upsampleAbove,dx,idx,base,shift,(*b_data->AboveRow)[base],(*b_data->AboveRow)[base + 1]);
//printf("|&%d %d %d %d %d %d %d %d %d",i,j,upsampleLeft,dx,idx,base,shift,(*b_data->LeftCol)[base],(*b_data->LeftCol)[base + 1]);

拿不准的时候 数据类型设置为有符号



看起来还是预测就没对 

以下面这个块为例：


*问题8, 右边界异常
residual b_data->MiCol:176 b_data->MiRow :16 subX:0 subY:0
predict_intra 内在给aboverow数组赋值的时候访问了未赋值的内存，值为0  拉低了所有分量的值 所以发绿



		        154 122 135
152 123 134		135 107 118
				residual b_data->MiCol:176 b_data->MiRow :16 
				
				
		        123  119 139
				
91 119 134(4*4) 107 106 130(8 * 8)
**  **  **(4*4)			
				
				residual b_data->MiCol:56 b_data->MiRow :16
				
				
				第二排第三个 partition是 发绿 和异常的起源 ，右边界除外


residual b_data->MiCol:36 b_data->MiRow :24

  最终输出数据 亮度和 预测 残差叠加值复合 色度 变成了 255 或者 0。


  三個沒有按照spec的地方，
  1.残差和帧内叠加的时候的取值范围限制在了255
  2.predict_chroma_from_luma 未使用
  3 predict_palette 未使用

按照 spec的 写法，loopfilter 几乎一定会把原来的像素值给放大？ 这不是有问题吗？
下一步思路 ，现在 重建出来的帧似乎有问题，帧后面马赛克过多。先把这个问题查了
然后查 环路滤波算法
然后查 cdef等 
然后查 帧间的问题

inverseIdentityTransform4
inverseIdentityTransform16
inverseADST4 等等 排查算法中所有乘以一个几千的常数的地方

重建出来的图像，每个partition中 都有一个十字条纹，肯定是有问题的
64 *64 块 才会出现 十字伪影，检查这一点 是否因为 Dequant 32 * 32 尺寸问题？
dav1d的 inv_dct4_1d_internal_c  和spec对不上   

8 * 8	      56	  24	  32					//angle
cos	        799	  3406	2896					
sin	        4017	2276	2896		


  16 * 16	  60	28	  44	  12   //angle
  cos	      401	3166	1931	3920
  sin	     4076	2598	3612	1189


  目前问题就是 nummvfound 的问题 也刚好就是spec写法意义不明那两个地方

 目前问题： 1.out7.obu 帧间第二帧开始出现问题 所以帧间的过程还有问题 : cdf 初始化的问题
           2. out15.obu 2s.obu 的loopRestoration 出现问题 
               2s.obu loopRestoration 之后的图像可以作为 查找 loopRestoration 问题的方向 很有规律
               但是out7.obu loopRestoration之后没有问题,为什么
        3.目前所有视频的环路滤波都有问题  先看这个问题==>不是 loop filter问题 ，是后面其他过程 或者就是解码过程中有什么问题 ,确定是 变换出来的数据有问题
*标记这个问题 ，现象是 解码出来的 图有一道道小印痕 最开始 是 第八列行 第八行 之后呈现以 16 * 16 块为单位 分布
是变换数据有问题 ：16 * 16 块以及以下完全没问题  块的宽高达到了 32 ，那么那个方向上的一维反变换就有问题
  ===》问题解决 ，是 还是一个循环上限写错了 
   排查 问题过程: 把 dav1d 正确 参数数据拿来作对比 ，发现 16 * 16 以下的都没问题，所以排查 32 ，就发现了


   需要重构当前的 cdf 机制 ，考虑一帧内多个tile的情况


在AV1和H.265/H.264中，虽然都使用了熵编码技术，但是它们的具体实现和解码过程中的一些细节上有一些区别。

AV1 中的算术编码（CDF）
AV1使用了一种称为CDF（Cumulative Distribution Function）的算术编码技术，用于对符号进行熵编码。与CABAC相比，AV1中的CDF算术编码在解码过程中有以下区别：

解码过程的算法不同：

在AV1中，解码过程使用了一种称为逆CDF（Inverse CDF）的算法，通过查找CDF表的逆来进行解码。这个过程不同于CABAC中的算法，因为CDF编码和CABAC编码在数学上是不同的。
状态更新方式不同：

在AV1中，CDF的状态更新是通过积分编码器（Integral Encoder）来实现的。解码器根据已解码的符号，通过逆CDF查找以更新状态，以便解码下一个符号。而在CABAC中，状态更新是通过根据解码过程中的上下文信息动态调整状态概率来实现的。
上下文模型的不同：

在AV1中，上下文模型是通过累积概率分布函数来表示的，这些概率是在编码过程中动态地进行估计和更新的。而在CABAC中，上下文模型是通过预定义的一组上下文模型来表示的，这些模型是固定的，并在编码器和解码器之间共享。
解码器的复杂性：

由于AV1中使用了CDF算术编码，解码器需要实现逆CDF查找等算法，这可能使得解码器的复杂性略高于使用CABAC的H.265/H.264解码器。
总的来说，尽管AV1和H.265/H.264都使用了熵编码技术，但它们在具体的编码方法和解码过程中存在一些差异。AV1中使用的CDF算术编码相对于H.265/H.264中的CABAC来说，有着不同的解码算法、状态更新方式以及上下文建模方式。



single_ref_p* 这些的 ctx  后面几个根本没有计算！

板子 toolchain 地址 https://mirrors.tuna.tsinghua.edu.cn/armbian-releases/_toolchain/
应该是CMAKE 的原因，在arm 板子上编译同样有 __MACH__ 问题
应该是没链接上 成功编译了 使用nm 查看函数列表也有

檢查 .8b .16b等等 以及使用X0的地方
确认为什么某些地方要多一次mov

add_dest_addsub combine

def_dct64_func

搞清楚这个函数
应该是在这个函数内把 src数据搬运到 sp上
function inv_txfm_dct\suffix\()_8h_x64_neon

以及为什么spec中系数最多是32X32