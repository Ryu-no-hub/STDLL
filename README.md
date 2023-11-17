Проект для сборки патчей для Морских Титанов
-----------------------------------

### Требуется
- Visual Studio 2019

### Как собрать :
1. Открыть проект plugin.sln в Visual Studio
2. Сборка -> Собрать решение (F7)

## Как активировать патчи
1. Положить d3drm.dll в игровую папку (1 раз, это механизм загрузки патчей).
2. Создать папку 'plugins' и положить туда STDLL.asi (после каждого изменения - это сам патч).

## Настроить автоматическое перекладывание результирующих файлов:
Проект -> Свойства: 'имя проекта' -> События сборки -> Событие после сборки -> Командная строка -> <Изменить> (по стрелке справа)

Вписать 2 строки:

copy "$(OutputPath)STDLL.asi" "C:\GOG Games\Submarine Titans\plugins"

copy "(Путь к папке с проектом)\STDLL\Release\d3drm.dll" "C:\GOG Games\Submarine Titans"


## Справочная информация
В файле ST.exe собраны адреса ключевых параметров.
