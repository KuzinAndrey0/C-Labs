#!/bin/bash
#Сравнивает строки между двумя файлами
#Ключи(2): пути к двум файлам для сравнения

#Файлы для сравнения

str1="$(cat "$1")"
str2="$(cat "$2")"

if [ "$str1" == "$str2" ]; then
    exit "0" #Пройдено
else
    exit "1" #Не пройдено
fi
