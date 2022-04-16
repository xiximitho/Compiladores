cmake_minimum_required(VERSION 3.21)
project(GTKMM_Analisador)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
find_package(PkgConfig REQUIRED)
endif()

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

add_subdirectory(src)

#install
#headers = /usr/local/include/<PACOTE>
#targets = /usr/local/lib/<PACOTE>
