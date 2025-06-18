ffmpeg中 调用 omx 接口的 编码器

const FFCodec ff_h264_omx_encoder = {

    .p.name           = "h264_omx",

    CODEC_LONG_NAME("OpenMAX IL H.264 video encoder"),

    .p.type           = AVMEDIA_TYPE_VIDEO,

    .p.id             = AV_CODEC_ID_H264,

    .priv_data_size   = sizeof(OMXCodecContext),

    .init             = omx_encode_init,

    FF_CODEC_ENCODE_CB(omx_encode_frame),

    .close            = omx_encode_end,

    CODEC_PIXFMTS_ARRAY(omx_encoder_pix_fmts),

    .color_ranges     = AVCOL_RANGE_MPEG, /* FIXME: implement tagging */

    .p.capabilities   = AV_CODEC_CAP_DELAY,

    .caps_internal    = FF_CODEC_CAP_INIT_CLEANUP,

    .p.priv_class     = &omx_h264enc_class,

};

应用层使用的接口：

ffmpeg omx.c 中 使用到的：

**OMX_Init**

**OMX_Deinit**

**OMX_GetHandle**

**OMX_FreeHandle**

**OMX_GetComponentsOfRole**

**OMX_GetRolesOfComponent**

**OMX_EmptyThisBuffer**

**OMX_FillThisBuffer**

**OMX_SetParameter**

**OMX_SendCommand**

**OMX_UseBuffer**

**OMX_AllocateBuffer**

**OMX_FreeBuffer**

=======================================================

libomxil-bellagio/
├── src/                   # 核心实现文件
│   ├── omxcore.c          # IL 核心功能实现
│   ├── component_loader.c # 组件加载器实现
│   └── ...                # 其他核心文件
├── components/            # 各类组件实现
│   ├── audio/             # 音频组件
│   ├── video/             # 视频组件
│   └── ...                # 其他组件
├── test/                  # 测试应用
│   ├── omxvolcontroltest/ # 音量控制测试
│   ├── omxaudiomixertest/ # 音频混音器测试
│   └── ...                # 其他测试
├── include/               # 头文件
├── README                 # 项目说明
└── configure.ac           # 构建配置

libomxil-bellagio

源码解析：

openmax对外提供的所有接口

# omxcore.c

### **宏定义函数接口（#define OMX_XXXXXX）​**

​这些宏函数的具体实现在 componets 中，事实上 宏的定义中就是引用compoent：

以这个为例：

#define OMX_EmptyThisBuffer(                                \

        hComponent,                                         \

        pBuffer)                                            \

    ((OMX_COMPONENTTYPE*)hComponent)->EmptyThisBuffer(      \

        hComponent,                                         \

        pBuffer)

**(OMX_COMPONENTTYPE*)hComponen** ：这里 就是使用compoent中的函数指针

**omx_base_compoent.c**中

omx_base_component_Constructor 中把要用到的这些函数指向实际的实现

例如以EmptyThisBuffer 为例子：

openmaxStandComp->EmptyThisBuffer = omx_base_component_EmptyThisBuffer;

omx_base_component_EmptyThisBuffer

                                                                      ===》  Port_SendBufferFunction//输入缓冲区传递给指定组件的输入端口进行处理,(empty)

                                                                                                                    ===》base_port_SendBufferFunction //将缓冲区提交到指定端口的队列中，触发组件对缓冲区的处理（empty）

| 宏名称                       | 参数                                                                            | 功能描述                           |
| ------------------------- | ----------------------------------------------------------------------------- | ------------------------------ |
| `OMX_GetComponentVersion` | `hComponent, pComponentName, pComponentVersion, pSpecVersion, pComponentUUID` | 获取组件版本信息，包括组件名称、版本号、规范版本和UUID。 |
| `OMX_SendCommand`         | `hComponent, Cmd, nParam, pCmdData`                                           | 向组件发送命令（如状态切换、端口刷新、启用/禁用端口等）。  |
| `OMX_GetParameter`        | `hComponent, nParamIndex, pComponentParameterStructure`                       | 获取组件的当前参数配置。                   |
| `OMX_SetParameter`        | `hComponent, nParamIndex, pComponentParameterStructure`                       | 设置组件的参数配置。                     |
| `OMX_GetConfig`           | `hComponent, nConfigIndex, pComponentConfigStructure`                         | 获取组件的当前配置信息。                   |
| `OMX_SetConfig`           | `hComponent, nConfigIndex, pComponentConfigStructure`                         | 设置组件的配置信息。                     |
| `OMX_GetExtensionIndex`   | `hComponent, cParameterName, pIndexType`                                      | 将厂商特定的配置或参数字符串转换为OMX结构索引。      |
| `OMX_GetState`            | `hComponent, pState`                                                          | 获取组件的当前状态。                     |
| `OMX_UseBuffer`           | `hComponent, ppBufferHdr, nPortIndex, pAppPrivate, nSizeBytes, pBuffer`       | 请求组件使用已分配的缓冲区。                 |
| `OMX_AllocateBuffer`      | `hComponent, ppBuffer, nPortIndex, pAppPrivate, nSizeBytes`                   | 分配新的缓冲区并关联到组件的端口。              |
| `OMX_FreeBuffer`          | `hComponent, nPortIndex, pBuffer`                                             | 释放由组件分配的缓冲区。                   |
| `OMX_EmptyThisBuffer`     | `hComponent, pBuffer`                                                         | 向组件的输入端口发送数据缓冲区以供处理。           |
| `OMX_FillThisBuffer`      | `hComponent, pBuffer`                                                         | 向组件的输出端口发送空缓冲区以接收数据。           |
| `OMX_UseEGLImage`         | `hComponent, ppBufferHdr, nPortIndex, pAppPrivate, eglImage`                  | 使用EGL图像作为缓冲区（用于图形处理组件）。        |

---

### ​**​普通函数接口（非宏定义）​**​

| 函数名称                      | 参数                                              | 返回类型            | 功能描述                                 |
| ------------------------- | ----------------------------------------------- | --------------- | ------------------------------------ |
| `OMX_Init`                | `void`                                          | `OMX_ERRORTYPE` | 初始化OMX核心库。                           |
| `OMX_Deinit`              | `void`                                          | `OMX_ERRORTYPE` | 反初始化OMX核心库，释放资源。                     |
| `OMX_ComponentNameEnum`   | `cComponentName, nNameLength, nIndex`           | `OMX_ERRORTYPE` | 枚举系统中所有可用的组件名称。                      |
| `OMX_GetHandle`           | `pHandle, cComponentName, pAppData, pCallBacks` | `OMX_ERRORTYPE` | 根据组件名称创建组件实例句柄。                      |
| `OMX_FreeHandle`          | `hComponent`                                    | `OMX_ERRORTYPE` | 销毁组件实例并释放资源。                         |
| `OMX_SetupTunnel`         | `hOutput, nPortOutput, hInput, nPortInput`      | `OMX_ERRORTYPE` | 在两个组件的端口之间建立数据隧道。                    |
| `OMX_GetContentPipe`      | `hPipe, szURI`                                  | `OMX_ERRORTYPE` | 根据URI协议（如`file://`、`inet://`）创建内容管道。 |
| `OMX_GetComponentsOfRole` | `role, pNumComps, compNames`                    | `OMX_ERRORTYPE` | 获取支持指定角色的所有组件名称。                     |
| `OMX_GetRolesOfComponent` | `compName, pNumRoles, roles`                    | `OMX_ERRORTYPE` | 获取指定组件支持的所有角色。                       |

---

### ​**​说明**

### 关键函数解析

#### 1. `BOSA_AddComponentLoader()`

- ​**​功能​**​  
  动态添加组件加载器到系统。
- ​**​流程​**​
  - 使用`realloc`扩展加载器数组。
  - 将新加载器指针加入数组末尾。
  - 若内存不足，返回`OMX_ErrorInsufficientResources`。
- ​**​用途​**​  
  支持插件式扩展，允许第三方或动态加载的组件集成到OpenMAX环境中。

#### 2. `OMX_Init()`

- ​**​功能​**​  
  初始化OpenMAX核心环境。
- ​**​流程​**​
  - 若未初始化，调用`createComponentLoaders()`创建默认加载器（如静态库组件）。
  - 遍历所有加载器，调用其`BOSA_InitComponentLoader`方法。
- ​**​关键点​**​
  - 依赖`createComponentLoaders()`初始化默认加载器。
  - 任一加载器初始化失败会导致整个初始化失败。

#### 3. `OMX_Deinit()`

- ​**​功能​**​  
  反初始化，释放所有资源。
- ​**​流程​**​
  - 遍历加载器，调用`BOSA_DeInitComponentLoader`并释放内存。
  - 重置全局变量，防止内存泄漏。

#### 4. `OMX_GetHandle()`

- ​**​功能​**​  
  根据组件名创建组件实例句柄。
- ​**​流程​**​
  - 遍历所有加载器，调用`BOSA_CreateComponent`尝试创建组件。
  - 返回第一个成功创建的组件句柄。
- ​**​规范约束​**​  
  OpenMAX要求组件名唯一，故找到即返回，否则返回`OMX_ErrorComponentNotFound`。

#### 5. `OMX_FreeHandle()`

- ​**​功能​**​  
  销毁组件实例并释放资源。
- ​**​流程​**​
  - 遍历加载器，调用`BOSA_DestroyComponent`销毁指定句柄。
  - 成功销毁后返回`OMX_ErrorNone`。

#### 6. `OMX_ComponentNameEnum()`

- ​**​功能​**​  
  枚举系统中所有可用组件名称。
- ​**​实现逻辑​**​
  - 按加载器顺序，遍历每个加载器的组件列表。
  - 使用双重循环：外层遍历加载器，内层遍历单个加载器的组件。
  - 通过累加索引整合所有加载器的组件列表，对外呈现统一索引。

#### 7. `OMX_SetupTunnel()`

- ​**​功能​**​  
  在两个组件的端口间建立隧道连接。
- ​**​关键步骤​**​
  1. 输出端口组件协商隧道参数（缓冲区供应商、标志等）。
  2. 输入端口组件确认参数，若失败则回滚输出端口的配置。
  3. 使用`OMX_TUNNELSETUPTYPE`传递协商结果。
- ​**​错误处理​**​  
  任一端口拒绝隧道则返回错误，需确保回滚操作的可靠性。

#### 8. `OMX_GetRolesOfComponent()`

- ​**​功能​**​  
  查询组件支持的角色列表（如解码器、编码器）。
- ​**​流程​**​
  - 遍历加载器，调用`BOSA_GetRolesOfComponent`获取角色信息。
  - 返回首个成功查询的结果。

#### 9. `OMX_GetComponentsOfRole()`

- ​**​功能​**​  
  根据角色查询支持该角色的所有组件。
- ​**​实现细节​**​
  - 分两次遍历：首次统计总数，第二次填充名称数组。
  - 动态分配临时内存存储中间结果，避免覆盖调用者传入的缓冲区。

#### 10. `OMX_GetContentPipe()`

- ​**​功能​**​  
  根据URI协议（如`file://`、`inet://`）创建内容管道。
- ​**​实现​**​
  - 调用协议对应的构造函数（如`file_pipe_Constructor`）。
  - 返回管道句柄供组件读取数据。

# compoentloader.c

# base

# compoents

## audio_effect

## clock_src

## video_scheduler

# core_extension

# dynamic_loader
