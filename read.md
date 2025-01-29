
#foot.sh�ű��ļ�����˵���������Զ�����task.json��launch.json��flash.cfg��CmakeLists.txt�ļ�#

# 1.Foot.sh �����Ѿ����ú���task.josn,seting.json,flash.cfg��CmakeLists.txt�ļ���ֻ��Ҫ����./build.sh����ɱ������ 

# 2.�����Լ�����task.josn,seting.json,flash.cfg��CmakeLists.txt�ļ���

    2.1.task.josn�ļ�����˵����
            ���硤task.josn���ļ��������£�(��������)
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Download",   //��������
            "type": "shell",    //��������
            "command": "openocd",    //OPENOCD��������
            "args": [
                "-f",               
                "flash.cfg"         //flash.cfg�����ļ�·��
            ],
            "problemMatcher": [],
            "detail": "ʹ�� flash.cfg �����ļ�ִ�� OpenOCD ���س���",
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
    2.2.seting.json�ļ�����˵����
            ���硤launch.json���ļ��������£�(��������)
{
    "version": "0.2.0",
    "configurations": [
        {
            "cwd": "\${workspaceFolder}",  
            "executable": "${project_dir}/build/Debug/${project_name}.elf",    //�����ĳ���·��
            "name": "Debug with OpenOCD",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",     //����������
            "configFiles": [
                "interface/stlink.cfg",   //stlink�ӿ������ļ�·��(�������Զ���)
                "target/stm32f1x.cfg"    //stm32f1xоƬ�����ļ�·��(оƬ�ͺ��Զ���)
            ],
            "searchDir": [],
            "runToEntryPoint": "main",
            "showDevDebugOutput": "none"
        }
    ]
}
    2.3.flash.cfg�ļ�����˵����
            ���硤flash.cfg���ļ��������£�(��������)
source [find interface/stlink.cfg]     //stlink�ӿ������ļ�·��(�������Զ���)
source [find target/stm32f1x.cfg]       //stm32f1xоƬ�����ļ�·��(оƬ�ͺ��Զ���)
program ${project_dir}/build/Debug/${project_name}.elf verify reset exit    //�����ļ�·��

#    2.4.CmakeLists.txt�ļ�����˵����
            ���硤CmakeLists.txt���ļ��������£�(��������)

cmake_minimum_required(VERSION 3.22)

// ������Ŀ����
project(stm32cubemx)

//���� C �� C++ ����֧��
enable_language(C ASM CXX)

// ����һ���ӿڿ�
add_library(stm32cubemx INTERFACE)

// ���ñ��붨��
target_compile_definitions(stm32cubemx INTERFACE 
    USE_HAL_DRIVER 
    STM32G030xx
    $<$<CONFIG:Debug>:DEBUG>
)

// ��Ӱ���Ŀ¼
target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc
    ../../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
    ../../Drivers/CMSIS/Device/ST/STM32G0xx/Include
    ../../Drivers/CMSIS/Include
    ../../Source
)

// �Զ����� source �� core Ŀ¼�µ����� .c��.cpp �� .s �ļ�
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

// ���Դ�ļ���Ŀ��
target_sources(stm32cubemx INTERFACE \${CMAKE_PROJECT_NAME})

// ��֤ C ��׼�Ƿ����Ҫ��
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()

# 3. ����cubemx���ɹ��̣�Ȼ����vscode�д򿪣�cmake���룬git.bash����Foot.sh�����Cmake�������нű���Ŀ�����滻cmake/stm32cubemx/CMakeLists.txt�ļ����Զ������ļ�·��

# 4. �������� ctrl+shift+p ����task�����run task��ѡ��Download���񣬼������س���оƬ��

# 5. ���Գ��� ctrl+shift+d ѡ��Debug with OpenOCD�������ã�������԰�ť�����ɿ�ʼ���Գ���

# 6. �鿴�Ĵ�����Ҫsvd�ļ������е�stm32cube�������ء�

# 7.Cubemx������main.c,����Ŀ�õ���main.cpp����Ҫ������.c�ļ�Ϊ.cpp�ļ�

# 8.����Cmake�����������н̳̣����Բο���