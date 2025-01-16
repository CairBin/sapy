#!/usr/bin/env bash

set -e

usage() {
    echo "Usage: $0 [build_type]"
    echo "  build_type: Release or Debug (default: Release)"
    exit 1
}

# Default build type
BUILD_TYPE="Release"


if [ $# -gt 1 ]; then
    usage
elif [ $# -eq 1 ]; then
    case "$1" in
        Release|release)
            BUILD_TYPE="Release"
            ;;
        Debug|debug)
            BUILD_TYPE="Debug"
            ;;
        *)
            echo "Invalid build type: $1"
            usage
            ;;
    esac
fi

echo "Selected build type: ${BUILD_TYPE}"

# Define build directories
CONAN_BUILD_FOLDER="build"
GENERATED_FOLDER="${CONAN_BUILD_FOLDER}/build/Release/generators"

# Run Conan install
echo "Running Conan install..." 
conan install . --output-folder="${CONAN_BUILD_FOLDER}" --build=missing
cd "${GENERATED_FOLDER}"


echo "Configuring CMake..."
cmake ../../../../ \
    -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE}


echo "Building the project..."
cmake --build . --config ${BUILD_TYPE}  

echo "Build completed successfully in ${BUILD_TYPE} mode."
