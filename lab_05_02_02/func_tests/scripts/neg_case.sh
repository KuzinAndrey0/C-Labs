#!/bin/bash
#Проводит негативное тестирование исполняемого файла, ожидая ненулевой код возврата
#Ключи(1-2): Файл с исходными данными, [Доп. ключи для исполняемого файла]

fileIn=$1 #Файл с исходными данными
keys=$2 #Доп. ключи

cp "$fileIn" "fileIn.temp"

vg=""
if [ -n "$USE_VALGRIND" ]; then #Делать в оболочке valgrind, если надо
    touch valgrind.temp
    vg="valgrind --quiet --log-file=valgrind.temp"
fi

$vg ../../app.exe "$keys" > /dev/null;

returnCode="$?"

if [ -s "./valgrind.temp" ]; then
    if [ "$returnCode" == "0" ]; then
        returnCode="11"
    else
        returnCode="10"
    fi
elif [ "$returnCode" == "0" ]; then
    returnCode="1"
else
    returnCode="0"
fi

#echo RETCODE "$returnCode"
exit "$returnCode" #Возврат с кодом ошибки
