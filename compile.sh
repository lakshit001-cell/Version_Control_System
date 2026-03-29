#!/bin/bash

# Exit immediately if a command fails
set -e

# Clean old binary if exists
if [ -f filesystem ]; then
    echo "Cleaning old build..."
    rm filesystem
fi

# Compile
echo "Compiling..."
g++ -std=c++17 main.cpp -o filesystem

# If compilation succeeds
echo "Compilation successful."

# Run with commands.txt if it exists, else interactive mode
if [ -f commands.txt ]; then
    echo "Running with commands.txt..."
    ./filesystem < commands.txt
else
    echo "Running interactively..."
    ./filesystem
fi
