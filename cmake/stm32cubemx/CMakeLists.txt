cmake_minimum_required(VERSION 3.22)

# 设置项目名称
project(stm32cubemx)

# 启用 C 和 C++ 语言支持
enable_language(C ASM CXX)

# 创建一个接口库
add_library(stm32cubemx INTERFACE)

# 设置编译定义
target_compile_definitions(stm32cubemx INTERFACE 
    USE_HAL_DRIVER 
    STM32G030xx
    $<$<CONFIG:Debug>:DEBUG>
)

# 添加包含目录
target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
    ../../Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ../../Drivers/CMSIS/Include
    ../../Source
)

# 自动查找 source 和 core 目录下的所有 .c、.cpp 和 .s 文件
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

# 添加源文件到目标
target_sources(stm32cubemx INTERFACE ${CMAKE_PROJECT_NAME})

# 验证 C 标准是否符合要求
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()
