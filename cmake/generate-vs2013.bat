@echo off
REM Enter the path to your CMake executable here
SET CMAKE_EXECUTABLE="C:/Program Files (x86)/CMake 2.8/bin/cmake.exe"
REM Enter the path to your HIPAcc executable
SET HIPACC_EXECUTABLE_PATH="Z:/Projects/Hipacc_install/bin/hipacc.exe"
REM Enter the path to your ISPC executable
SET ISPC_EXECUTABLE_PATH="Z:/ispc/ispc-v1.8.2-windows/ispc.exe"

SET CMAKE_ARGUMENTS=-DHIPACC_EXECUTABLE_PATH:PATH="%HIPACC_EXECUTABLE_PATH%" -DISPC_EXECUTABLE_PATH:PATH="%ISPC_EXECUTABLE_PATH%"

ECHO.
ECHO Generate the 32-bit solution ...
ECHO.

mkdir "%~dp0..\vs2013_cmake_x86"
cd "%~dp0..\vs2013_cmake_x86"
%CMAKE_EXECUTABLE% %~dp0 %CMAKE_ARGUMENTS% -G "Visual Studio 12"
if NOT ["%errorlevel%"]==["0"] (
 pause 
)

ECHO.
ECHO ... done!
ECHO.



ECHO.
ECHO Generate the 64-bit solution ...
ECHO.

mkdir "%~dp0\..\vs2013_cmake_x64"
cd "%~dp0\..\vs2013_cmake_x64"
%CMAKE_EXECUTABLE% %~dp0 %CMAKE_ARGUMENTS% -G "Visual Studio 12 Win64"
if NOT ["%errorlevel%"]==["0"] (
 pause 
)

ECHO.
ECHO ... done!
ECHO.
