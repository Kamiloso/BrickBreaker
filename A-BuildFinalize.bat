@echo off
REM Tworzenie katalogu Release, jeśli nie istnieje
if not exist "Release" (
    mkdir "Release"
)

REM Usuwanie starych wersji folderów w Release
if exist "Release\GameData" (
    rmdir /S /Q "Release\GameData"
)
if exist "Release\Assets" (
    rmdir /S /Q "Release\Assets"
)
if exist "Release\Licenses" (
    rmdir /S /Q "Release\Licenses"
)

REM Kopiowanie folderu GameData
if exist "GameData" (
    xcopy "GameData" "Release\GameData" /E /I /Y
)

REM Kopiowanie folderu Assets
if exist "Assets" (
    xcopy "Assets" "Release\Assets" /E /I /Y
)

REM Kopiowanie folderu Licenses
if exist "Licenses" (
    xcopy "Licenses" "Release\Licenses" /E /I /Y
)

REM Usuwanie pliku BrickBreaker.pdb z Release
if exist "Release\BrickBreaker.pdb" (
    del "Release\BrickBreaker.pdb"
)

if exist "Release\GameData\progress.bin" del "Release\GameData\progress.bin"

echo Gotowe!
pause
