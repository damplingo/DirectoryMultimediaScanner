# DirectoryMultimediaScaner

## Назначение

Данное приложение предназначено для анализа рабочей директории на предмет наличия мультимедийных файлов. Собранная информация о файлах мультимедиа доступна по Get-запросу
на адрес http://localhost:1234/media_files

## Инструменты

для написания http-сервера был использован фреймворк userver версии 2.6


## Сборка и запуск

Используется система сборки cmake
Для сборки из корневой директории проекта:
```
cmake -B build -S .
cmake --build ./build -j(nproc)
```
Запуск из корневой директории проекта:

```
./build/DirectoryMultimediaScanner *interval* *path* --config configs/static_config.yaml
```
*interval* - временной интервал в секундах
*path* - путь к директории

Например,
```
./build/DirectoryMultimediaScanner 1 ~/pictures --config configs/static_config.yaml
```
