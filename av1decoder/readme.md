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


右边界异常
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

