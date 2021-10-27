@echo off
chcp 65001
set /p url=<%~dp0subscription
%~dp0wget.exe  --timeout=5 --tries=3 --no-check-certificate -nv %url%  -O %~dp0clash.yaml
if not exist %~dp0clash.yaml exit
FOR /f "delims=" %%i in ("%~dp0clash.yaml") do (
IF %%~zi lss 1024 (
del %~dp0clash.yaml 
exit))
for /F %%i in ('%~dp0sed64.exe -n "1,/proxies:/=" %~dp0clash.yaml') do (set commitid=%%i)
set /a divnum=%commitid%-1
%~dp0sed64.exe -i 1,%divnum%d %~dp0clash.yaml
%~dp0sed64.exe -i $,${/"socks-port: 7891"/d;} %~dp0clash.yaml
type %~dp0configtun %~dp0clash.yaml>.\profile\configtun.yaml
type %~dp0configdefault %~dp0clash.yaml>.\profile\config.yaml
del %~dp0clash.yaml
