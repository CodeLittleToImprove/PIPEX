cmake_minimum_required(VERSION 3.25)
project(PIPEX C)

set(CMAKE_C_STANDARD 99)

# Add the library file
add_library(libft STATIC IMPORTED)
set_target_properties(libft PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libft/libft.a)

add_executable(PIPEX pipex.c error.c utils.c)

# Link the executable with the libft library
target_link_libraries(PIPEX libft)
