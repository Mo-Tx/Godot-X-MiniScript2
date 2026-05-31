#!/bin/bash
# GDXMS2 build orchestration script (definitely not stolen from miniscript2 build.sh)

set -e  # Exit on any error

##RUN THIS IN PROJECT ROOT

PROJECT_ROOT="$(dirname "$0")"

echo "=== GDXMS2 Build Script ==="
echo "Project root: $(pwd)"

# Parse command line arguments
TARGET="${1:-all}"

case "$TARGET" in
    #"setup")
    #    echo "Setting up development environment..."
    #    mkdir -p build/{cs,cpp,temp}
    #    mkdir -p generated
    #    echo "Setup complete."
    #    ;;

    "cs")
        echo "Building MS2 C# version..."
        cd miniscript2 && tools/build.sh cs
        #echo "building C# wrapper"
        #TODO: ADD C# BUILD FOR WRAPPER
        #echo "C# build complete."
        ;;

    "transpile")
        echo "Transpiling C# to C++ in MS2..."
        cd miniscript2 && tools/build.sh transpile
        echo "MS2 Transpile completed successfully."
        ;;

    "cpp")
        echo "Building MS2 C++ version and GDExtension wrapper..."
        cd ../gdxms2-cpp && scons && cd ..
        echo "C++ build complete."
        ;;

    "all")
        echo "Building all targets..."
        $0 cs
        $0 transpile
        $0 cpp
        echo "All builds complete."
        ;;

    "clean")
        echo "Cleaning all MS2 build artifacts..."
        cd miniscript2
        rm -rf build/cs/* build/cpp/* build/temp/*
        rm -rf generated/*.g.h generated/*.g.cpp
        cd cs && dotnet clean
        if [ -f cpp/Makefile ]; then
            make -C cpp clean
        fi
        echo "MS2 Clean complete."
        cd ..
        cd gdxms2-cpp
        scons -c
        echo "GDXMS2 Clean complete."
        ;;

    *)
        echo "Usage: $0 {cs|transpile|cpp|all|clean} [options]"
        echo ""
        echo "Build Commands:"
        echo "  cs          - Build MS2 C# version"
        echo "  transpile   - Transpile all MS2 C# files to C++"
        echo "  cpp         - Build MS2 and GDXMS2 (GDExtension) C++ versions"
        echo "  all         - Build everything"
        echo "  clean       - Clean build artifacts for everything"
        echo ""
        exit 1
        ;;
esac

echo "Build script completed successfully."
