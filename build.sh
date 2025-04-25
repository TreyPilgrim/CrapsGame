#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Set the build directory and output binary directory
BUILD_DIR="build"
BIN_DIR="bin"

# Create the build directory if it doesn't exist
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Run CMake configuration
cmake -DCMAKE_RUNTIME_OUTPUT_DIRECTORY="../$BIN_DIR" ..

# Build the project
cmake --build .

# Optionally, run the program right after building
echo "Build complete. Running program..."
../$BIN_DIR/Debug/CrapsGame.exe
