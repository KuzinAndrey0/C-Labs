#!/bin/bash
#Проводит позитивное тестирование исполняемого файла, ожидая нулевой код возврата и совпадение вывода с ожидаемым
#Ключи(2-3): Файл с исходными данными, файл с эталонными данными, [Доп. ключи для исполняемого файла] 

fileIn=$1 #Файл с исходными данными
fileOut=$2 #Файл для сравнения
fileTest="test.temp" #Временный файл для вывода
read -ra keys < "$3" #Доп. ключи
format=$4
cp "$fileIn" "fileIn.temp"

touch "$fileTest" #Создать временный файл, если его нет

vg=""
if [ -n "$USE_VALGRIND" ]; then #Делать в оболочке valgrind, если надо
    touch valgrind.temp
    vg="valgrind --quiet --log-file=valgrind.temp"
fi

if [ "${keys[0]}" == "p" ]; then
    ./t2b.exe "$format" "$fileIn" "fileIn.temp"
    $vg ../../app.exe "${keys[@]}" > "$fileTest"
          
fi

if [ "${keys[0]}" == "s" ]; then
    ./t2b.exe "$format" "$fileIn" "fileIn.temp"
    $vg ../../app.exe "${keys[@]}"
    ./b2t.exe "$format" "fileIn.temp" "$fileTest"
fi
./comparator.sh "$fileTest" "$fileOut"

returnCode="$?"
if [ -s "./valgrind.temp" ]; then
    if [ "$returnCode" == "0" ]; then
        returnCode="10"
    else
        returnCode="11"
    fi
fi

#echo RETCODE "$returnCode"
exit "$returnCode" #Возврат с кодом ошибки
