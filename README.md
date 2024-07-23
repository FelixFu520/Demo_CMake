# [CMake教程](https://www.bookstack.cn/read/CMake-Cookbook/README.md)
## 1. 从可执行文件到库
- 1.1 将单个源文件编译为可执行文件
- 1.2 切换生成器
- 1.3 构建和链接静态库和动态库
- 1.4 用条件句控制编译
- 1.5 向用户显示选项
- 1.6 指定编译器
- 1.7 切换构建类型
- 1.8 设置编译器选项
- 1.9 为语言设定标准
- 1.10 使用控制流

## 2. 检测环境
- 2.1 检测操作系统
- 2.2 处理与平台相关的源代码
- 2.3 处理与编译器相关的源代码
- 2.4 检测处理器体系结构
- 2.5 检测处理器指令集
- 2.6 为Eigen库使能向量化

## 3. 检测外部库和程序
- 3.1 检测Python解析器
- 3.2 检测Python库
- 3.3 检测Python模块和包
- 3.4 检测BLAS和LAPACK数学库
- 3.5 检测OpenMP的并行环境
- 3.6 检测MPI的并行环境
- 3.7 检测Eigen库
- 3.8 检测Boost库
- 3.9 检测外部库: I. 使用pkg-config
- 3.10 检测外部库: II. 自定义find模块

## 4. 创建和运行测试
- 4.1 创建一个简单的单元测试
- 4.2 使用Catch2库进行单元测试
- 4.3 使用Google Test库进行单元测试
- 4.4 使用Boost Test进行单元测试
- 4.5 使用动态分析来检测内存缺陷
- 4.6 预测测试失败
- 4.7 使用超时测试运行时间过程的测试
- 4.8 并行测试
- 4.9 运行测试子集
- 4.10 使用测试固件

## 5. 配置时和构建时的操作
- 5.1 使用平台无关的文件操作
- 5.2 配置时运行自定义命令
- 5.3 构建时运行自定义命令: I. 使用add_custom_command
- 5.4 构建时运行自定义命令: II. 使用add_custom_target
- 5.5 构建时为特定目标运行自定义命令
- 5.6 探究编译和链接命令
- 5.7 探究编译器标志命令
- 5.8 探究可执行命令
- 5.9 使用生成器表达式微调配置和编译

## 6. 生成源码
- 6.1 配置时生成源码
- 6.2 使用Python在配置时生成源码
- 6.3 构建时使用Python生成源码
- 6.4 记录项目版本信息以便报告
- 6.5 从文件中记录项目版本
- 6.6 配置时记录Git Hash值
- 6.7 构建时记录Git Hash值

## 7. 构建项目
- 7.1 使用函数和宏重用代码
- 7.2 将Cmake源代码分成模块
- 7.3 编写函数来测试和设置编译器标志
- 7.4 用指定参数定义函数或宏
- 7.5 重新定义函数和宏
- 7.6 使用废弃函数、宏和变量
- 7.7 add_subdirectory的限定范围
- 7.8 使用target_sources避免全局变量

## 8. 超级构建模式
- 8.1 使用超级构建模式
- 8.2 使用超级构建管理依赖项: I. Boost库
- 8.3 使用超级构建管理依赖项: II. FFTW库
- 8.4 使用超级构建管理依赖项: III. Google Test框架
- 8.5 使用超级构建支持项目

## 9. 语言混合项目
- 9.1 使用C/C++库构建Fortran项目
- 9.2 使用Fortran库构建C/C++项目
- 9.3 使用Cython构建C++和Python项目
- 9.4 使用Boost Python构建C++和Python项目(没通过)
- 9.5 使用pybind11构建C++和Python项目(没通过)
- 9.6 使用Python CFFI混合C, C++, Fortran和Python

## 10. 编写安装程序
- 10.1 安装项目
- 10.2 生成输出头文件
- 10.3 输出目录
- 10.4 安装超级构建

## 11. 打包项目
- 11.1 生成源码和二进制包
- 11.2 通过PyPI发布使用CMake/pybind11构建的C++/Python项目(未测试)
- 11.3 通过P有PI发布使用CMake/CFFI构建C/Fortran/Python项目(未测试)
- 11.4 以Conda包的形式发布一个简单的项目(未测试)
- 11.5 将Conda包作为依赖项发布给项目(未测试)

## 12. 构建文档
- 12.1 使用Doxygen构建文档
- 12.2 使用Sphinx构建文档
- 12.3 结合Doxygen和Sphinx

## 13. 选择生成器和交叉编译
- 13.1 使用CMake构建Visual Studio 2017项目
- 13.2 交叉编译hello world示例
- 13.3 使用OpenMP并行化交叉编译Windows二进制文件

## 14. 测试面板
- 14.1 将测试部署到CDash
- 14.2 CDash显示测试覆盖率
- 14.3 使用AddressSanifier向CDash报告内存缺陷(未通过)
- 14.4 使用ThreadSaniiser向CDash报告数据争用(未通过)

## 15. 使用CMake构建已有项目
- 15.1 如何开始迁移项目
- 15.2 生成文件并编写平台检查
- 15.3 检测所需的链接和依赖关系
- 15.4 复制编译标志
- 15.5 移植测试
- 15.6 移植安装目标
- 15.7 进一步迁移的措施
- 15.8 项目转换为CMake的常见问题

## 语法学习
- [add_executable](https://blog.csdn.net/MacKendy/article/details/122549819)
- [add_custom_target]()
- [add_library](https://blog.csdn.net/LaineGates/article/details/108242803)
- [cmake_dependent_option](https://blog.csdn.net/sinat_31608641/article/details/124656282)
- [cmake_host_system_information](https://blog.csdn.net/fengbingchun/article/details/129108910)
- [configure_file](https://blog.csdn.net/qq_38410730/article/details/103741579)
- [check_cxx_compiler_flag]()
- [execute_process](https://blog.csdn.net/weixin_39766005/article/details/122857619)
- [find_file]()
- [find_library]()
- [find_package](https://blog.csdn.net/zhanghm1995/article/details/105466372)
- [find_path]()
- [find_program]()
- [get_source_file_property]()
- [include_directories]()
- [include]()
- [message](https://blog.csdn.net/Zhanganliu/article/details/99850603)
- [option](https://blog.csdn.net/lhl_blog/article/details/123553686)
- [pkg_search_module]()
- [set_source_files_properties]()
- [set_target_properties](https://blog.csdn.net/fengbingchun/article/details/128258041)
- [set](https://blog.csdn.net/sinat_31608641/article/details/123101969)
- [target_compile_options](https://blog.csdn.net/sinat_31608641/article/details/125417042)
- [target_compile_definitions](https://blog.csdn.net/fengbingchun/article/details/128273937)
- [target_sources](https://blog.csdn.net/guaaaaaaa/article/details/125601766)
- [target_include_directories]()




