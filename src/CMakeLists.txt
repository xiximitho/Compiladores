set(SOURCE_FILES main.cpp mainwindow.cpp mainwindow.h lexico.cpp lexico.h sintatico.cpp sintatico.h)

message(STATUS "----- GTKMM4_INCLUDE_DIRS: ${GTKMM_INCLUDE_DIRS}")
message(STATUS "----- GTKMM4_LIBRARIES: ${GTKMM_LIBRARIES}")
message(STATUS "----- GTKMM4_LINK_LIBRARIES: ${GTKMM_LINK_LIBRARIES}")

add_executable(GTKMM_Analisador ${SOURCE_FILES})
link_directories(GTKMM_Analisador PRIVATE ${GTKMM_LIBRARY_DIRS})
include_directories(GTKMM_Analisador PRIVATE ${GTKMM_INCLUDE_DIRS})

target_link_libraries(GTKMM_Analisador PRIVATE ${GTKMM_LIBRARIES})
#Instalação
#install(TARGETS GTKMM_Analisador DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
#message(STATUS "Localizacao binario: ${CMAKE_INSTALL_PREFIX}/bin/")