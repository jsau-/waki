set (wakitest_SOURCES)

# TODO: Can we skip double-defining these?
# Likely defining the compiler as a static library too?
set (waki_SOURCES)
include(${CMAKE_CURRENT_LIST_DIR}/../src/emitter/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/../src/modules/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/../src/parser/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/../src/tokenizer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/../src/typechecker/CMakeLists.txt)

include(${CMAKE_CURRENT_LIST_DIR}/parser/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/tokenizer/CMakeLists.txt)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../include)

add_executable(wakitest ${waki_SOURCES} ${wakitest_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
add_test(NAME wakitest COMMAND wakitest)
