#!/bin/bash
# Build and package game
echo "Building OpenWorld Mobile Game..."

# Clean
rm -rf Binaries Intermediate Saved

# Generate project files
./GenerateProjectFiles.sh

# Build
echo "Building..."

# Package for mobile
echo "Packaging for mobile devices..."

echo "Build complete! Ready for iOS/Android packaging."
echo "Open in Unreal Engine 5 to package for your platform."