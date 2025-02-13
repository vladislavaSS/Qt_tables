cmake_minimum_required(VERSION 3.5)

add_library(CommonLib STATIC
    buttons.cpp
    transform.cpp
    сreate.cpp
)

target_include_directories(CommonLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../AD_9122
    ${CMAKE_CURRENT_SOURCE_DIR}/../LMK_1000
)
