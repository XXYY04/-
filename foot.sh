#!/bin/bash

# ��ȡ��ǰ����Ŀ¼�ľ���·����תΪ Git Bash ��ʽ
project_dir=$(pwd | sed 's|^/c|C:|')
project_name=$(basename "$project_dir")

# ����.vscodeĿ¼
mkdir -p .vscode

# ���� tasks.json
cat > .vscode/tasks.json << EOF
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Download",
            "type": "shell",
            "command": "openocd",
            "args": [
                "-f", 
                "flash.cfg"
            ],
            "problemMatcher": [],
            "detail": " OpenOCD Download Program",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
EOF

# ���� launch.json
cat > .vscode/launch.json << EOF
{
    "version": "0.2.0",
    "configurations": [
        {
            "cwd": "\${workspaceFolder}",
            "executable": "${project_dir}/build/Debug/${project_name}.elf",
            "name": "Debug with OpenOCD",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",
            "configFiles": [
                "interface/stlink.cfg",
                "target/stm32f1x.cfg"
            ],
            "searchDir": [],
            "runToEntryPoint": "main",
            "showDevDebugOutput": "none"
        }
    ]
}
EOF

# ���� flash.cfg
cat > flash.cfg << EOF
source [find interface/stlink.cfg]
source [find target/stm32f1x.cfg]
program ${project_dir}/build/Debug/${project_name}.elf verify reset exit
EOF

# ���� CMakeLists.txt
cat > cmake/stm32cubemx/CMakeLists.txt << EOF
cmake_minimum_required(VERSION 3.22)

# ������Ŀ����
project(stm32cubemx)

# ���� C �� C++ ����֧��
enable_language(C ASM CXX)

# ����һ���ӿڿ�
add_library(stm32cubemx INTERFACE)

# ���ñ��붨��
target_compile_definitions(stm32cubemx INTERFACE 
    USE_HAL_DRIVER 
    STM32G030xx
    $<$<CONFIG:Debug>:DEBUG>
)

# ��Ӱ���Ŀ¼
target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
    ../../Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ../../Drivers/CMSIS/Include
    ../../Source
)

# �Զ����� source �� core Ŀ¼�µ����� .c��.cpp �� .s �ļ�
file(GLOB_RECURSE CMAKE_PROJECT_NAME
    "../../Core/Src/*.c"
    "../../Core/Src/*.cpp"
    "../../Core/Src/*.s"
    
    "../../Drivers/STM32G0xx_HAL_Driver/Src/*.c"
    "../../startup_stm32g030xx.s"
#�Զ����ļ�
    "../../Source/*.cpp"
    "../../Source/*.c"
)

# ���Դ�ļ���Ŀ��
target_sources(stm32cubemx INTERFACE \${CMAKE_PROJECT_NAME})

# ��֤ C ��׼�Ƿ����Ҫ��
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
EOF