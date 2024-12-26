# Use an official Ubuntu runtime as a parent image
FROM ubuntu:24.04

# Set environment variable for vcpkg
ENV VCPKG_FORCE_SYSTEM_BINARIES=1

# Install necessary packages and LLVM/Clang 19
RUN apt-get update && \
    apt-get install -y \
        cmake \
        git \
        curl \
        zip \
        unzip \
        tar \
        ninja-build \
        pkg-config \
        make \
        autoconf \
        autoconf-archive \
        wget \
        gnupg \
        software-properties-common \
        lsb-release && \
    wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh 19 && \
    apt-get install -y clang-19 && \
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-19 100 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-19 100 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set Clang++ as the default C++ compiler
ENV CC=clang-19
ENV CXX=clang++-19

# Set the working directory
WORKDIR /app

# Install vcpkg first (this rarely changes)
RUN git clone https://github.com/microsoft/vcpkg.git && \
    ./vcpkg/bootstrap-vcpkg.sh

# Copy only vcpkg.json first to leverage layer caching for dependencies
COPY vcpkg.json .

# Install dependencies using vcpkg manifest
RUN ./vcpkg/vcpkg install --feature-flags=manifests

# Copy CMake files next (these change less frequently than source code)
COPY CMakeLists.txt .

# Copy the rest of the source code
COPY . .

# Remove dist and build directories if they exist
RUN rm -rf dist build

# Build the application using CMake with Clang++
RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake \
          -DCMAKE_C_COMPILER=clang-19 \
          -DCMAKE_CXX_COMPILER=clang++-19 .. && \
    make

# Set the default command to run when the container starts
CMD ["/app/dist/CaveMUDServer"]
