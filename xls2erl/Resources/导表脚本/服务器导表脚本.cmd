@echo off
cd "%~dp0"
set epath=..\xls2erl\dist
set /p name="Please input config name (input all for all export): "
%epath%\xls2erl.exe --specs game_server.spec %name%
pause

