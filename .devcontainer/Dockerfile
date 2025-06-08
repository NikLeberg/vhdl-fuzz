FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
ENV LC_ALL=C.UTF-8

# Update ca-certificates to fix failing git server certificate verification.
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    rm -f /etc/apt/apt.conf.d/docker-clean
    apt-get -q -y update
    apt-get -q -y install --no-install-recommends \
        apt-transport-https ca-certificates
    update-ca-certificates
EOF

# Install basic build tools.
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install --no-install-recommends \
        git \
        libc-dev \
        gcc \
        llvm \
        clang \
        make \
        cmake
EOF

# Install packages for libFuzzer fuzzing with protocol buffers support.
ARG PROTOBUF_MUTATOR_CLONE_URL=https://github.com/google/libprotobuf-mutator.git
ARG PROTOBUF_MUTATOR_CLONE_TAG=v1.5

RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install --no-install-recommends \
        protobuf-compiler \
        libprotobuf-dev \
        liblzma-dev \
        libz-dev
    cd /tmp
    git clone $PROTOBUF_MUTATOR_CLONE_URL -b $PROTOBUF_MUTATOR_CLONE_TAG --depth 1
    cd ./libprotobuf-mutator && mkdir ./build && cd ./build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DLIB_PROTO_MUTATOR_TESTING=OFF
    make install
    rm -rf /tmp/libprotobuf-mutator
EOF

# Install packages for Python support.
ARG PYTHON_VERSION=3.12

RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install --no-install-recommends \
        python3=$PYTHON_VERSION* \
        python3-pip
    update-alternatives --install \
        /usr/bin/python python /usr/bin/python$PYTHON_VERSION 1
    update-alternatives --set \
        python /usr/bin/python$PYTHON_VERSION
EOF
