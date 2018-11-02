CMAKE_MINIMUM_REQUIRED(VERSION 3.4)
PROJECT(shell_console_library)

set(source_dir ${CMAKE_CURRENT_SOURCE_DIR})

add_library(shell_readinput ${source_dir}/readinput.h ${source_dir}/readinput_utilities.cpp ${source_dir}/readinput.cpp)

add_library(shell_console_lib ${source_dir}/shell_console_base.h ${source_dir}/shell_console_base.cpp)

if(NOT WIN32)
    find_library(readline_lib NAMES libreadline.a PATHS /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib NO_DEFAULT_PATH)
    find_library(history_lib NAMES libhistory.a PATHS /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib NO_DEFAULT_PATH)
    find_library(ncurses_lib NAMES libncurses.a PATHS /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib NO_DEFAULT_PATH)
    
    if (readline_lib AND history_lib AND ncurses_lib)
       # # rl=(GNU) readline
       add_library(shell_readinput_rl ${source_dir}/readinput.h ${source_dir}/readinput_utilities.cpp ${source_dir}/readinput_rl.cpp)

       TARGET_LINK_LIBRARIES(shell_readinput_rl ${readline_lib} ${history_lib} ${ncurses_lib})
   endif()
endif()


