@echo off

set QTDIR=C:\Programs\Qt\5.11.1
set BOOST_DIR=C:\work\dev\3rdparty\boost

set CURR_DIR=%cd%
set SRC_DIR=%CURR_DIR%\..\..\src\
set BIN_DIR=%CURR_DIR%\..\..\bin\

rem Comment out this block to enable Visual Studio 2017 Development Environment
rem -----------------------------------------------------------------------------------------
if (%VSCOMNTOOLS%)==() (
	set VSCOMNTOOLS="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\Common7\Tools\"
	set VSEnvBatchRelPath="VsDevCmd.bat"
)
rem -----------------------------------------------------------------------------------------

rem Set Visual studio paths
if (%VSEnvBatchRelPath%)==() (

call "%VSCOMNTOOLS:"=%..\..\VC\vcvarsall.bat" amd64
echo "%VSCOMNTOOLS:"=%..\..\VC\vcvarsall.bat" amd64

) else (

call "%VSCOMNTOOLS:"=%\%VSEnvBatchRelPath%"
echo "%VSCOMNTOOLS:"=%\%VSEnvBatchRelPath%"

)