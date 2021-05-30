project(tools)
add_library(${PROJECT_NAME} url_escape.cpp)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})