@echo off
echo Compiling DCT Steganography Project...
gcc main.c dct.c -o stego.exe

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed.
    pause
    exit /b
)

echo Running the program...
stego.exe

pause
