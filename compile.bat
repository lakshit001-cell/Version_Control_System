@echo off
setlocal enabledelayedexpansion

echo ===========================
echo Cleaning old build...
echo ===========================
if exist filesystem.exe del filesystem.exe

echo ===========================
echo Compiling...
echo ===========================
g++ -std=c++17 main.cpp -o filesystem.exe

if %errorlevel% neq 0 (
    echo ---------------------------
    echo Compilation failed!
    echo ---------------------------
    exit /b %errorlevel%
)

echo ===========================
echo Compilation successful.
echo ===========================

if exist commands.txt (
    echo Running with commands.txt...
    filesystem.exe < commands.txt
) else (
    echo Running interactively...
    filesystem.exe
)

endlocal
