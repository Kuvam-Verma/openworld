@echo off
REM Build and run the game
echo Building OpenWorld Mobile Game...

REM Clean old builds
if exist Binaries rmdir /s /q Binaries
if exist Intermediate rmdir /s /q Intermediate
if exist Saved rmdir /s /q Saved

REM Generate project files
call GenerateProjectFiles.bat

echo.
echo ============================================
echo OpenWorld Mobile Game - BUILD INSTRUCTIONS
echo ============================================
echo.
echo STEP 1: Open Unreal Engine 5
echo STEP 2: Open the OpenWorld.uproject file
echo STEP 3: Cook & Package for your platform:
echo.
echo FOR iOS:
echo   - File > Package Project > iOS
echo.
echo FOR Android:
echo   - File > Package Project > Android (ARM64)
echo.
echo FOR Windows (Testing):
echo   - File > Package Project > Windows
echo.
echo STEP 4: Install on your mobile device
echo.
pause