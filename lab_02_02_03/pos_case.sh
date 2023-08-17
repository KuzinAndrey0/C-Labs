#!/bin/bash
#Проводит позитивное тестирование исполняемого файла, ожидая нулевой код возврата и совпадение вывода с ожидаемым
#Ключи(3-4): Файл с исходными данными, файл с эталонными данными, тип компаратора для сравнения, [Доп. ключи для исполняемого файла] 

fileIn=$1 #Файл с исходными данными
fileOut=$2 #Файл для сравнения
fileTest="test.temp" #Временный файл для вывода
mode=$3 #0 - числа, 1 - строки
keys=$4 #Доп. ключи

touch "$fileTest" #Создать временный файл, если его нет

valgrind=""
if [ "$USE_VALGRIND" == "1" ]; then #Делать в оболочке valgrind, если надо
    valgrind="valgrind"
fi

if $valgrind ./app.exe "$keys" < "$fileIn" > "$fileTest"; then
    if [ "$mode" == "0" ]; then #Компаратор для чисел
        ./comparator.sh "$fileTest" "$fileOut"
    elif [ "$mode" == "1" ]; then #Компаратор для строк
        ./comparator2.sh "$fileTest" "$fileOut"
    else
        echo "WRONG COMPARATOR" #Не выдан ключ для компаратора, что-то пошло не так
        exit "1"
    fi

    exit "$?" #Возврат с кодом ошибки, который вернет компаратор
else
    exit "1" #Программа выдала ненулевой код ошибки при позитивном тесте
fi