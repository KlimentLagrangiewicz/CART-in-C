cmake_minimum_required(VERSION 3.25)

project(CART-on-C LANGUAGES C)

set(CMAKE_C_STANDARD 90)

add_executable(CART-on-C  src/main.c src/help.h src/help.c src/cart.h src/cart.c)

target_link_libraries(CART-on-C m)

install(TARGETS CART-on-C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
