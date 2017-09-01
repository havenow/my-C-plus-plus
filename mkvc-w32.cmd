
CLS
SET VSTools=""%VS100COMNTOOLS%\..\..\VC"
set PATH=D:\cygwin\bin;%path%
CALL "%DXSDK_DIR%\Utilities\bin\dx_setenv.cmd"
CALL "%VS100COMNTOOLS%\..\..\VC\vcvarsall.bat"

MAKE vc
ECHO _
ECHO FB Alpha Compilation done. [MSVC Tools Environment]
ECHO _
PAUSE