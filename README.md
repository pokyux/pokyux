pokyux

Pokyux is the kernel of an OS named Pokyux OS.

### 工程结构

```shell
$ tree
├── build                    # 系统内核构建输出（按照架构存放）
│   ├── riscv64
│   │   ├── pokyux.bin       # 内核 ELF 文件
│   │   └── pokyux.elf       # 内核二进制文件（用于 QEMU 引导）
│   └── user                 # 用户程序构建输出（按照架构存放）
│       └── riscv64
├── kernel                   # 内核源码
│   ├── arch                 # 体系结构相关源码
│   │   ├── pkx_call.h       # 所有体系结构都要实现的接口
│   │   └── riscv64          # 体系结构
│   │       ├── boot.S       # pkx_entry 入口点（所有体系结构必须实现）
│   │       ├── linker.ld    # 内核内存布局（所有体系结构必须实现）
│   │       └── ...          # 其他源码，实现 pkx_call.h 中的接口
│   ├── component            # 内核功能组件，管理内存、任务等
│   ├── init
│   │   └──main.c            # 内核 C 语言入口点
│   ├── lib                  # 功能型函数
│   ├── syscall              # 系统调用
│   └── type.h               # 类型定义（u8 i32 等）
├── Makefile
├── README.md
├── tool                     # pkx 使用的外部成品工具
│   └── rustsbi-qemu.bin     # RustSBI（用于实现 RISCV M 模式的功能）
└── user                     # 用户程序
    ├── arch                 # 体系结构相关的标准库实现
    │   └── riscv64
    │       ├── lib
    │       ├── linker.ld    # 应用程序内存布局
    │       └── start.S      # CRT0（_start 所在地）
    ├── include              # 应用程序标准头文件（体系结构无关）
    └── Makefile
```



### 目前支持的架构

RISCV64

### 已经实现

加载程序

syscall: write

syscall: yield

物理分页管理（分配与回收）

### 运行

本项目需要在 WSL 或者 Linux 环境下运行。

**准备工作**

1. 安装 make
2. 安装 RISCV64 相关工具链（gcc、ld 等）
3. 安装 QEMU

**编译用户程序**

```shell
cd user
make hello
make app1-3
cd ..
```

**编译内核**

```shell
make build
```

**运行内核**

```shell
# 显示内核输出信息（默认）
make run

# 只显示应用输出信息（隐藏内核日志）
make run DEFINE=-DPKX_NO_PRINTK
```

