@echo off

set CURRENT_PATH=%cd%

rem set user env
call SetUserEnv.bat

rem open the Visual Studio 2017
devenv
