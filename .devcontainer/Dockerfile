FROM ubuntu:24.04 AS base

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

################################################################################

FROM base AS nvc-builder

ARG NVC_VERSION=1.19.1
ARG NVC_SIG_PUBLIC_KEY=BCDB295F74319F1A

ARG DEBIAN_FRONTEND=noninteractive
ENV LC_ALL=C.UTF-8

# Install neccessary build tools and dependencies.
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install \
        git \
        wget \
        gpg \
        make \
        automake \
        autoconf \
        check \
        flex \
        bison \
        libdw-dev \
        libffi-dev \
        pkg-config \
        zlib1g-dev \
        libzstd-dev \
        libreadline-dev
EOF

# Build NVC from signed tarball.
ARG NV_TARBALL=nvc-$NVC_VERSION.tar.gz
ARG NVC_GIT_URL=https://github.com/nickg/nvc
ARG NVC_TARBALL_URL=$NVC_GIT_URL/releases/download/r$NVC_VERSION/$NV_TARBALL
ARG NVC_SIG_URL=$NVC_GIT_URL/releases/download/r$NVC_VERSION/$NV_TARBALL.sig
RUN <<EOF
    set -e
    wget --progress=dot $NVC_TARBALL_URL
    wget --progress=dot $NVC_SIG_URL
    gpg --keyserver keyserver.ubuntu.com --recv-keys $NVC_SIG_PUBLIC_KEY
    gpg --verify $NV_TARBALL.sig $NV_TARBALL
    tar xvzf $NV_TARBALL
    mkdir ./nvc-$NVC_VERSION/build
    cd ./nvc-$NVC_VERSION/build
    ../configure --disable-llvm
    make -j$(nproc)
    make DESTDIR=/opt/nvc install
EOF

################################################################################

FROM base AS ghdl-builder

ARG GHDL_VERSION=v5.1.1

ARG DEBIAN_FRONTEND=noninteractive
ENV LC_ALL=C.UTF-8

# Install neccessary build tools and dependencies.
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install \
        make \
        gcc \
        gnat \
        libz-dev \
        git
EOF

# Build GHDL from source.
ARG GHDL_GIT_URL=https://github.com/ghdl/ghdl.git
RUN <<EOF
    set -e
    git clone $GHDL_GIT_URL -b $GHDL_VERSION --depth 1
    mkdir ghdl/build
    cd ghdl/build
    ../configure --prefix=/opt/ghdl
    make -j $(nproc)
    make install
EOF

################################################################################

FROM base

ARG DEBIAN_FRONTEND=noninteractive
ENV LC_ALL=C.UTF-8

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
        libclang-rt-dev \
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

# Import prebuilt NVC and install its runtime dependencies.
COPY --from=nvc-builder /opt/nvc /
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install --no-install-recommends \
        binutils \
        libdw1 \
        libzstd1 \
        libtcl8.6 \
        libreadline8
EOF

# Import prebuilt GHDL and install its runtime dependencies.
COPY --from=ghdl-builder /opt/ghdl /usr
RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    <<EOF
    set -e
    apt-get -q -y update
    apt-get -q -y install --no-install-recommends \
        libgnat-13
EOF
ENV GHDL_PREFIX=/usr/lib/ghdl

# Use ubuntu baseimage default non-root user.
ARG USERNAME=ubuntu
ARG USERHOME=/home/$USERNAME
USER $USERNAME
WORKDIR $USERHOME