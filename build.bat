
:: Entry
SET _arg1="build_and_run"
GOTO SETUP_ENV_VARS

:: Load env variables which will eventually be able to pick up any VS installation
:SETUP_ENV_VARS
    pushd "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build"
        call .\vcvarsall.bat x64
    popd
    GOTO PATH_SELECTION

: Currently only support build and run
:PATH_SELECTION
    GOTO build

: Run simple build command
:build
    SET _include=-IInclude
    SET _libPath=-Llib
    SET _libs=-lglfw3.lib
    SET _preProc=-DUNICODE
    clang %_preProc% %_include% -fms-compatibility .\main.cpp %_libPath% %_libs% -omain.exe
    GOTO run

: Execute program with clear screen
:run
    .\main.exe

exit /B 1