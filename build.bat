PATH=E:\cygwin\dingux\bin;E:\cygwin\bin;C:\WINDOWS\system32;
SET DINGUX_TOOLCHAIN=/dingux
SET PATH=%PATH%;%MIPSTOOLS%/bin;%DINGUX_TOOLCHAIN%
make -f makefile 2>&1 |tee err.txt
pause