cmake_minimum_required(VERSION 3.10)

# Defina o nome do projeto
project(GBEmu)

# Defina o padrão de versão do C++
set(CMAKE_CXX_STANDARD 17)

# Coletar todos os arquivos .cpp recursivamente de src e subpastas
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

list(FILTER SOURCES EXCLUDE REGEX ".*/testes/.*")

# Adicionar o executável a ser gerado
add_executable(GBEmu ${SOURCES})

# Defina os diretórios de inclusão para os arquivos .hpp
target_include_directories(GBEmu PRIVATE ${CMAKE_SOURCE_DIR}/src/includes)

# Default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type specified, defaulting to Debug")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Set build type specific flags and output directory using set_target_properties
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring Debug build")
    message(STATUS "Out dir: ${CMAKE_BINARY_DIR}/bin/Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Debug"
    )
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")  # Debugging symbols, no optimization

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring Release build")
    message(STATUS "Out dir: ${CMAKE_BINARY_DIR}/bin/Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Release"
    )
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")  # High optimization, no debug symbols
endif()


###########################################3Catch2 tests
find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main

file(GLOB_RECURSE CORE_SOURCES ${CMAKE_SOURCE_DIR}/src/defs/*.cpp)
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/src/testes/*.cpp)

#list(FILTER SOURCES EXCLUDE REGEX ${CMAKE_SOURCE_DIR}/main.cpp) #Exclui o main.cpp / Classe principal da GBEmu

add_executable(GBEmuTests ${TEST_SOURCES} ${CORE_SOURCES})

target_link_libraries(GBEmuTests PRIVATE
    Catch2::Catch2WithMain
)

target_include_directories(GBEmuTests PRIVATE ${CMAKE_SOURCE_DIR}/src/includes)
target_include_directories(GBEmuTests PRIVATE ${CMAKE_SOURCE_DIR}/src/testes)

set_target_properties(GBEmuTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/Tests"
)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -g -O0")