#!/bin/bash
#Создает релизную сборку .c файла из папки, где находится этот скрипт

for fileName in  *.c; do
    if [ "$fileName" != "*.c" ]; then
        newName="${fileName/.c/.o}" #Имя, которое будет у объектного файла
        gcc -std=c99 -Werror -Wall -Wpedantic -Wextra -c "$fileName" #исходный код -> объектный файл
        gcc -o "app.exe" "$newName" -lm #объектный файл -> исполняемый файл
    fi
done