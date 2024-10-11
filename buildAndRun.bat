:: Сборка проекта в релизную версию
cmake -S . -B build
cmake --build build --config Release

@echo off
:: Меняем текущую директорию на ту, где находится исполняемый файл
cd /d "%~dp0build\SpaceSTUGame\Release"

:: Запускаем программу
"SpaceSTUGame.exe" >nul 2>&1

pause