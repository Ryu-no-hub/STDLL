Проект для сборки патчей для Морских Титанов
-----------------------------------

### Требуется
- Visual Studio 2019

### Как собрать патч :
1. Открыть проект plugin.sln в Visual Studio
2. Сборка -> Собрать решение (F7)

## Как активировать патчи
1. Положить d3drm.dll в игровую папку (1 раз, это механизм загрузки патчей).
2. Создать папку 'plugins' и положить туда STDLL.asi (после каждого изменения - это сам патч).

## Настроить автоматическое перекладывание результирующих файлов в папки игры (опционально):
Проект -> Свойства: 'имя проекта' -> События сборки -> Событие после сборки -> Командная строка -> <Изменить> (по стрелке справа)

Вписать 2 строки, внеся изменения в пути:

copy "$(OutputPath)STDLL.asi" "C:\GOG Games\Submarine Titans\plugins"

copy "(Путь к папке с проектом)\STDLL\Release\d3drm.dll" "C:\GOG Games\Submarine Titans"


## Справочная информация
В эксель файле ST.xlsx собраны адреса начала областей с параметрами юнитов и др. в .exe игры.

Без IDA PRO можно менять значения, которые уже есть в проекте. С ней возможно увидеть адрес недостающей переменной, ориентируясь по эксель файлу, и добавить её.
