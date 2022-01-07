@echo off
cd %~dp0
:start
echo SC-CL example.c
echo Press ENTER to launch
pause > nul
cls
"../../bin/SC-CL.exe" -platform=PS3 -emit-asm -target=GTAV -out-dir="GTAV/PS3/bin/" example.c ../../include/common.c -- -I "../../include/"
goto start

