set (wakitest_SOURCES)

include(${CMAKE_CURRENT_LIST_DIR}/tokenizer/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_executable(wakitest ${wakitest_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
add_test(NAME wakitest COMMAND wakitest)
