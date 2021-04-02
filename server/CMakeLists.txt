project(server)

add_library(${PROJECT_NAME}
     server.cpp
     environment.cpp
     )

target_link_libraries(${PROJECT_NAME}
     ${Fcgi_LIBRARIES}
     )