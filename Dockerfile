# Use an official Ubuntu runtime as a parent image
FROM ubuntu:latest

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Remove dist and build directories if they exist
RUN rm -rf /app/dist && \
    rm -rf /app/build

# Install necessary packages
RUN apt-get update && \
    apt-get install -y build-essential cmake git curl zip unzip tar ninja-build pkg-config make autoconf autoconf-archive && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install vcpkg
RUN export VCPKG_FORCE_SYSTEM_BINARIES=1 && \
    git clone https://github.com/microsoft/vcpkg.git && \
    ./vcpkg/bootstrap-vcpkg.sh && \
    ./vcpkg/vcpkg install --feature-flags=manifests

# Build the application using CMake
RUN export VCPKG_FORCE_SYSTEM_BINARIES=1 && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/app/vcpkg/scripts/buildsystems/vcpkg.cmake .. && \
    make

# Set the default command to run when the container starts
CMD ["/app/dist/CaveMUDServer"]
