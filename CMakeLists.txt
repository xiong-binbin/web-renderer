cmake_minimum_required (VERSION 3.8)

#项目名称
project(osr)
set(PROJECT_OSR osr)
set(PREFIX /usr/local/mdc)

#使用c++17标准
set(CMAKE_CXX_STANDARD 17)

#引入头文件
include_directories(
    ${PREFIX}/
    ${PREFIX}/include
    ${PREFIX}/include/libcef
    ${CMAKE_CURRENT_SOURCE_DIR}/app/include
)

#引入源文件
file(GLOB SRC_LIST "app/src/*.cpp")

#生成可执行文件
add_executable(${PROJECT_OSR} ${SRC_LIST}) 

#链接静态库和动态库
target_link_libraries(
    ${PROJECT_OSR}
    -Wl,--start-group
    pthread
    ${PREFIX}/lib/libcef_dll_wrapper.a
    ${PREFIX}/lib/libcef.so
    -Wl,--end-group
)

