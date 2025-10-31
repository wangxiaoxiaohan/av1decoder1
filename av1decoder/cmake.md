# 

cmake-gui 的cache在 where to build the binarie对应的目录下面

删除之后才可以重新配置

find_package

## find_package(Protobuf REQUIRED )

查找 Find.cmake 的文件

回去这里面找：

CMAKE_MODULE_PATH
CMAKE_ROOT

## find_package(Protobuf CONFIG REQUIRED )

是强制config模式，去查找名为`<PackageName>Config.cmake`或`<lower-case-package-name>-config.cmake`的模块文件

会去这里面找：

1._DIR

2.CMAKE_PREFIX_PATH、CMAKE_FRAMEWORK_PATH、CMAKE_APPBUNDLE_PATH的CMake变量或环境变量路径根目录(默认都为空)

3.PATH环境变量路径



## 指定路径

find_package(SomeLib REQUIRED
                 PATHS "/path/to/somelib"  

                                "/another/path" 

                                PATH_SUFFIXES lib/cmake/SomeLib 

# 可选：添加子目录后缀 )



## 设置DIR

set(SomeLib_DIR "/path/to/somelib/lib/cmake/SomeLib") 

find_package(SomeLib REQUIRED)

# pkg_check_modules

和find_package的区别是：find_package以来cmake，要用到.cmake文件

而依赖pkg-config的.pc文件

# target_link_libraries

连接的lib的路径通过以下途径获取

1.pkg_check_modules

2.find_package

3.手动指定路径​ ，没有通过以上两种方式指定路径的lib 会去一些默认的路径搜索：

link_directories(./) C:/mingw64/lib

# message

message(WARNING "FFMPEG_LIBRARIES: ${FFMPEG_LIBRARIES}")

find_package/pkg_check_modules 找到相关的lib之后，下面这些  “包名+后缀”的组合就是有效的

# 预定义宏：

### **一、包含路径相关​**​

1. ​**​`<Package>_INCLUDE_DIRS`​**​  
   第三方库的头文件目录路径列表，如 `OpenCV_INCLUDE_DIRS`

2. ​**​`<Package>_INCLUDE_PATH`​**​  
   环境变量，用于指定头文件的搜索路径，如 `CMAKE_INCLUDE_PATH`

---

### ​**​二、库文件相关​**​

3. ​**​`<Package>_LIBRARIES`​**​  
   库文件的完整路径列表（如 `.so`、`.dll`），如 `Protobuf_LIBRARIES`

4. ​**​`<Package>_LIBRARY_DIRS`​**​  
   库文件所在目录的路径列表，如 `Boost_LIBRARY_DIRS`

5. ​**​`CMAKE_FIND_LIBRARY_SUFFIXES`​**​  
   定义库文件的后缀名列表（如 `.so;.dll`），影响 `find_library()` 的行为
   
   SD

---

### ​**​三、编译与链接控制​**​

6. ​**​`<Package>_DEFINITIONS`​**​  
   预处理器定义（如宏），如 `Qt5Core_DEFINITIONS`

7. ​**​`<Package>_CFLAGS` / `<Package>_CXXFLAGS`​**​  
   编译选项，如 `Python3_CXXFLAGS`

---

### ​**​四、版本与状态​**​

8. ​**​`<Package>_FOUND`​**​  
   布尔变量，表示是否找到包，如 `GTest_FOUND`

9. ​**​`<Package>_VERSION`​**​  
   包的版本信息，如 `Protobuf_VERSION`

---

### ​**​五、工具与路径​**​

10. ​**​`<Package>_EXECUTABLE`​**​  
    包提供的命令行工具路径，如 `Protobuf_PROTOC_EXECUTABLE`

11. ​**​`CMAKE_INSTALL_PREFIX`​**​  
    安装路径前缀（如 `/usr/local`），影响 `make install` 的输出

### ​**​六、特殊用途​**​

12. ​**​`CMAKE_SHARED_LIBRARY_SUFFIX`​**​  
    共享库的标准后缀（如 `.dll`、`.so`），由操作系统决定

13. ​**​`CMAKE_STATIC_LIBRARY_SUFFIX`​**​  
    静态库的后缀（如 `.a`、`.lib`）

14. ​**​`CMAKE_MODULE_PATH`​**​  
    自定义 CMake 模块的搜索路径

# 
