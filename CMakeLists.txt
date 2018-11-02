CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(shell-console-example)

add_subdirectory(shell_console_lib)
set(source_dir ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(shell_console_test ${source_dir}/main.cpp)
TARGET_LINK_LIBRARIES(shell_console_test shell_console_lib shell_readinput)

if(TARGET shell_readinput_rl)
   add_executable(shell_console_test_rl ${source_dir}/main.cpp)
   TARGET_LINK_LIBRARIES(shell_console_test_rl shell_console_lib shell_readinput_rl)
endif()


