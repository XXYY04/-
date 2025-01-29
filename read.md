
#foot.sh脚本文件配置说明：包含自动配置task.json、launch.json、flash.cfg、CmakeLists.txt文件#

# 1.Foot.sh 里面已经配置好了task.josn,seting.json,flash.cfg和CmakeLists.txt文件，只需要运行./build.sh命令即可编译程序。 

# 2.可以自己配置task.josn,seting.json,flash.cfg和CmakeLists.txt文件·

    2.1.task.josn文件配置说明：
            例如·task.josn·文件内容如下：(任务配置)
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Download",   //任务名称
            "type": "shell",    //任务类型
            "command": "openocd",    //OPENOCD下载命令
            "args": [
                "-f",               
                "flash.cfg"         //flash.cfg配置文件路径
            ],
            "problemMatcher": [],
            "detail": "使用 flash.cfg 配置文件执行 OpenOCD 下载程序",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
    2.2.seting.json文件配置说明：
            例如·launch.json·文件内容如下：(调试配置)
{
    "version": "0.2.0",
    "configurations": [
        {
            "cwd": "\${workspaceFolder}",  
            "executable": "${project_dir}/build/Debug/${project_name}.elf",    //编译后的程序路径
            "name": "Debug with OpenOCD",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",     //调试器类型
            "configFiles": [
                "interface/stlink.cfg",   //stlink接口配置文件路径(调试器自定义)
                "target/stm32f1x.cfg"    //stm32f1x芯片配置文件路径(芯片型号自定义)
            ],
            "searchDir": [],
            "runToEntryPoint": "main",
            "showDevDebugOutput": "none"
        }
    ]
}
    2.3.flash.cfg文件配置说明：
            例如·flash.cfg·文件内容如下：(下载配置)
source [find interface/stlink.cfg]     //stlink接口配置文件路径(调试器自定义)
source [find target/stm32f1x.cfg]       //stm32f1x芯片配置文件路径(芯片型号自定义)
program ${project_dir}/build/Debug/${project_name}.elf verify reset exit    //编译文件路径

#    2.4.CmakeLists.txt文件配置说明：
            例如·CmakeLists.txt·文件内容如下：(编译配置)

cmake_minimum_required(VERSION 3.22)

// 设置项目名称
project(stm32cubemx)

//启用 C 和 C++ 语言支持
enable_language(C ASM CXX)

// 创建一个接口库
add_library(stm32cubemx INTERFACE)

// 设置编译定义
target_compile_definitions(stm32cubemx INTERFACE 
    USE_HAL_DRIVER 
    STM32G030xx
    $<$<CONFIG:Debug>:DEBUG>
)

// 添加包含目录
target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
    ../../Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ../../Drivers/CMSIS/Include
    ../../Source
)

// 自动查找 source 和 core 目录下的所有 .c、.cpp 和 .s 文件
file(GLOB_RECURSE CMAKE_PROJECT_NAME
    "../../Core/Src/*.c"
    "../../Core/Src/*.cpp"
    "../../Core/Src/*.s"
    
    "../../Drivers/STM32G0xx_HAL_Driver/Src/*.c"
    "../../startup_stm32g030xx.s"
#自定义文件
    "../../Source/*.cpp"
    "../../Source/*.c"
)

// 添加源文件到目标
target_sources(stm32cubemx INTERFACE \${CMAKE_PROJECT_NAME})

// 验证 C 标准是否符合要求
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()

# 3. 先用cubemx生成工程，然后在vscode中打开，cmake编译，git.bash运行Foot.sh命令，先Cmake，再运行脚本，目的是替换cmake/stm32cubemx/CMakeLists.txt文件，自动包含文件路径

# 4. 运行任务 ctrl+shift+p 输入task，点击run task，选择Download任务，即可下载程序到芯片。

# 5. 调试程序 ctrl+shift+d 选择Debug with OpenOCD调试配置，点击调试按钮，即可开始调试程序。

# 6. 查看寄存器需要svd文件，自行到stm32cube官网下载。

# 7.Cubemx会生成main.c,本项目用的是main.cpp，需要重命名.c文件为.cpp文件

# 8.具体Cmake，哔哩哔哩有教程，可以参考。