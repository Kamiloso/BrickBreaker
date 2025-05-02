@echo off
setlocal enabledelayedexpansion

set totalLines=0

for %%f in (*.cpp *.h) do (
    for /f %%l in ('find /v /c "" ^< "%%f"') do (
        set /a totalLines+=%%l
    )
)

echo Suma znakow \n we wszystkich plikach .cpp i .h: %totalLines%
pause
