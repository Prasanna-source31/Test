cmake_minimum_required(VERSION 3.9)  # CMake version check
project(Deployment-toolbox)               # Create project "CIS-Inventory-Start"
set(CMAKE_CXX_STANDARD 11)          # Enable c++14 standard
SET(CMAKE_C_COMPILER C:/msys64/mingw32/bin/gcc.exe)
set(CMAKE_CXX_COMPILER g++)
# set(BUILD_SHARED_LIBS OFF)
 set(CMAKE_EXE_LINKER_FLAGS "-static")
#Static start
#Static Libs
#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
# Add main.cpp file of project root directory as source file
set(SOURCE_FILES Main.cpp Services.cpp Configurations.cpp Logging.cpp)
# Add executable target with source files listed in SOURCE_FILES variable   
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/Curl/libcurl.a ws2_32.dll Wldap32.dll)
set (INCLUDE_DIRS  ${CMAKE_CURRENT_LIST_DIR}/Curl/)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
