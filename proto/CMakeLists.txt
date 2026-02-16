# SPDX-License-Identifier: MIT

# Include and find Googles Protocol Buffer library.
include(FindProtobuf)
find_package(Protobuf REQUIRED)

# Compile proto files to C++ header and implementation.
protobuf_generate_cpp(proto_src proto_hdr vhdl2008.proto vhdl2019.proto)

# Create library from proto files.
add_library(proto SHARED ${proto_src} ${proto_hdr})
get_filename_component(PROTO_HDR_DIR "${proto_hdr}" DIRECTORY)
target_include_directories(proto INTERFACE ${PROTOBUF_INCLUDE_DIR} ${PROTO_HDR_DIR})
target_link_libraries(proto PUBLIC ${Protobuf_LIBRARIES})
target_link_libraries(proto INTERFACE main)

# Include and find libprotobuf-mutator library.
find_package(libprotobuf-mutator REQUIRED)
add_library(mutator INTERFACE)
target_link_libraries(mutator INTERFACE
    main
    libprotobuf-mutator::protobuf-mutator
    libprotobuf-mutator::protobuf-mutator-libfuzzer
)
