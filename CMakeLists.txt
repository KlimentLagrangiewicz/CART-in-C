cmake_minimum_required(VERSION 3.25)

project(CART-in-C LANGUAGES C)

set(CMAKE_C_STANDARD 90)
add_compile_options(-O3)

add_executable(CART-in-C  src/main.c src/help.h src/help.c src/cart.h src/cart.c)

target_link_libraries(CART-in-C m)

install(TARGETS CART-in-C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
