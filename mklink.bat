cd /d %~dp0
rd /s /q ..\qmk_firmware\keyboards\fan90
mklink /D ..\qmk_firmware\keyboards\fan90 %~dp0\fan90
pause