@echo off
cd "%~dp0"
set ipath=..\..\doc\branches\banshu\
set opath=..\..\project\branches\banshu\RE_Client_Code\Assets\Data\Scripts\game\data\config\
set epath=..\xls2lua\dist\
set names=buff skill role story item section
set /p name="Please input config name (input all for all export): "

if "%name%"=="all" (
	for %%i in (%names%) do call :ExportLua %%i
) else (
	call :ExportLua %name%
)
pause
goto:eof

:ExportLua
	echo Export data_%1.lua
	%epath%xls2lua.exe --ifile %ipath%RE0_%1.xlsm --sheet data_%1 --ofile data_%1.lua --label 3 --begin 5
	copy data_%1.lua %opath%data_%1.lua
	del data_%1.lua
goto:eof
