project(server)

add_library(${PROJECT_NAME}
     server.cpp
     environment.cpp
     )

target_link_libraries(${PROJECT_NAME}
     ${Fcgi_LIBRARIES}
     )

if(BUILD_TESTING)
     set(UNIT_TEST_NAME ${PROJECT_NAME}-test)
     add_definitions(-DBOOST_TEST_MAIN -DBOOST_TEST_DYN_LINK)
     add_executable(${UNIT_TEST_NAME}
          test/environment_test.cpp
          )
     target_link_libraries(${UNIT_TEST_NAME} ${PROJECT_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
     add_test(${PROJECT_NAME} ${UNIT_TEST_NAME})
endif()