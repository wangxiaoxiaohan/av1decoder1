DAV1D 并行机制分析

DAV1D 支持帧级并行解码 和 伪wpp

Dav1dContext 中的 n_fc 代表 帧级并行数量

​				n_tc代表 最大并行 行数量



现在先分析不支持帧级并行 ，只支持 wpp的情况

先看 dav1d_decode_frame 这个函数



```
int dav1d_decode_frame(Dav1dFrameContext *const f) {`

​    `assert(f->c->n_fc == 1);` //不支持帧级并行的时候才走这里

​    `// if n_tc > 1 (but n_fc == 1), we could run init/exit in the task`

​    `// threads also. Not sure it makes a measurable difference.`

​    `int res = dav1d_decode_frame_init(f);`

​    `if (!res) res = dav1d_decode_frame_init_cdf(f);`

​    `// wait until all threads have completed`

​    `if (!res) {`

​        `if (f->c->n_tc > 1) {`

​            `res = dav1d_task_create_tile_sbrow(f, 0, 1);`

​            `pthread_mutex_lock(&f->task_thread.ttd->lock);`

​            `pthread_cond_signal(&f->task_thread.ttd->cond);`

​            `if (!res) {`
					//task_counter 大于0，即还有未开始的线程的时候，wait
​                `while (!f->task_thread.done[0] ||`

​                       `atomic_load(&f->task_thread.task_counter) > 0)`

​                `{`

​                    `pthread_cond_wait(&f->task_thread.cond,`

​                                      `&f->task_thread.ttd->lock);`

​                `}`

​            `}`

​            `pthread_mutex_unlock(&f->task_thread.ttd->lock);`

​            `res = f->task_thread.retval;`

​        `} else {`
				//不支持wpp的时候 直接串行解码

​            `res = dav1d_decode_frame_main(f);`
				//更新cdf

​            `if (!res && f->frame_hdr->refresh_context && f->task_thread.update_set) {`

​                `dav1d_cdf_thread_update(f->frame_hdr, f->out_cdf.data.cdf,`

​                                        `&f->ts[f->frame_hdr->tiling.update].cdf);`

​            `}`

​        `}`

​    `}`

​    `dav1d_decode_frame_exit(f, res);`

​    `f->n_tile_data = 0;`

​    `return res;`

`}


dav1d_worker_task 内的 case DAV1D_TASK_TYPE_TILE_ENTROPY，DAV1D_TASK_TYPE_TILE_RECONSTRUCTION
会解码一行并通知一行解码完成
```







