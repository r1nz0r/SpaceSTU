# Space Shoot'em Up

### Описание игры

Space Shoot'em Up (SpaceSTU) - это 2D скролл-шутер, в котором игрок управляет космическим кораблем и противостоит инопланетному вторжению.
Игра полностью написана на языке ```C++``` и использует следующие библиотеки:
* [SFML](https://www.sfml-dev.org/) 
* [Box2D](https://box2d.org/)

Игра поддерживает такие платформы как Windows, MacOS, Linux.

### Скриншоты

<image src="screenshots/1.png" width=200> <image src="screenshots/2.png" width=200>
<image src="screenshots/3.png" width=200> <image src="screenshots/4.png" width=200>

### Как установить
Для настройки проекта и зависимостей используется ```cmake```.  Убедитесь, что на вашем компьютере установлены ```cmake``` и компилятор ```gcc/g++/MSVC```:
|Инструменты сборки   	|Версия|
|-----------------------|------|
|cmake:       			|3.29.4|
|C++:        			|C++17 |

Процесс сборки стандартный:

1. Откройте папку проекта через командную строку и выполните команду для настройки с помощью cmake:
```
cmake -S . -B build
```
2. Соберите проект:
```
cmake --build build --config Release
```
3. Запустите игру:
```
.\build\SpaceSTUGame\Release\SpaceSTUGame.exe
```
Также можно запустить скрипт ```buildAndRun.bat```, который выполнит все шаги автоматически.

### Технические детали

Игра состоит из двух основных проектов:

* SpaceSTUEngine
* SpaceSTUGame

```SpaceSTUEngine``` - это минималистичный игровой движок, построенный на базе SFML и Box2D.
```SpaceSTUGame``` — это сама игра, созданная с использованием движка ```SpaceSTUEngine```.
