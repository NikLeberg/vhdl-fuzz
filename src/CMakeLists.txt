# SPDX-License-Identifier: MIT

# Create library for VHDL2019 generator.
add_library(gen19 SHARED gen19.cc gen19.h)
target_include_directories(gen19 INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(gen19 PRIVATE -fsanitize=fuzzer)
target_link_libraries(gen19 PRIVATE proto)
target_link_libraries(gen19 INTERFACE main)

add_executable(gen19e gen19.cc gen19.h)
target_compile_definitions(gen19e PRIVATE GEN_MAIN)
target_link_libraries(gen19e PRIVATE proto)
target_link_libraries(gen19e INTERFACE main)

# Create executable for proto based fuzzer.
add_executable(fuzz fuzz.cc fuzz.h)
target_include_directories(fuzz INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_options(fuzz PRIVATE -fsanitize=fuzzer)
target_link_libraries(fuzz PRIVATE proto gen19 mutator)
target_link_libraries(fuzz INTERFACE main mutator)

# Create paths for the fuzzing process.
file(MAKE_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/corpus
    ${CMAKE_CURRENT_BINARY_DIR}/merged
)

# Target to run fuzzer.
add_custom_target(run
    COMMAND ./fuzz ./corpus -exact_artifact_path=./crash
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS fuzz
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/corpus
)

# Target to merge fuzzer corpus.
add_custom_target(merge
    COMMAND ./fuzz -merge=1 ./merged ./corpus
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS fuzz
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/merged
)
