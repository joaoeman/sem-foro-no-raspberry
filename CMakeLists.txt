# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Configuração mínima necessária do CMake
cmake_minimum_required(VERSION 3.13)

# Definição dos padrões de linguagem
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == NÃO EDITE AS LINHAS ABAIXO para o funcionamento da extensão do VS Code para Raspberry Pi Pico ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

# Definição da placa (pico_w para Wi-Fi, ou apenas pico para a versão sem Wi-Fi)
set(PICO_BOARD pico CACHE STRING "Board type")

# Inclui o arquivo de importação do SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Nome do projeto
project(periodico C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Adiciona o executável (substitua "periodico.c" pelo nome do seu arquivo principal)
add_executable(periodico periodico.c)

# Define o nome e a versão do programa
pico_set_program_name(periodico "periodico")
pico_set_program_version(periodico "0.1")

# Habilitar saída via UART e USB
pico_enable_stdio_uart(periodico 1)
pico_enable_stdio_usb(periodico 1)

# Linka as bibliotecas necessárias
target_link_libraries(periodico
    pico_stdlib
    hardware_gpio
    hardware_timer
)

# Inclui diretórios adicionais (se necessário)
target_include_directories(periodico PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Gera arquivos extras (UF2, binário, etc.)
pico_add_extra_outputs(periodico)

