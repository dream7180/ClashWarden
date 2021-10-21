@echo off
%~dp0wget.exe --timeout=5 --tries=3 --no-check-certificate "https://download.maxmind.com/app/geoip_download?edition_id=GeoLite2-Country&license_key=oeEqpP5QI21N&suffix=tar.gz"  -O %~dp0GeoLite2-Country.tar.gz
if not exist %~dp0GeoLite2-Country.tar.gz exit
%~dp07za.exe e %~dp0GeoLite2-Country.tar.gz -o%~dp0
%~dp07za.exe e %~dp0GeoLite2-Country.tar -r "GeoLite2-Country*\GeoLite2-Country.mmdb" -o.\profile -aoa
del .\profile\Country.mmdb /f /q
ren .\profile\GeoLite2-Country.mmdb Country.mmdb
del "%~dp0GeoLite2-Country*" /f /q