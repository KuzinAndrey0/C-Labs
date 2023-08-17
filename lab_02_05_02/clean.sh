#!/bin/bash
#Очищает мусор
#Мусор - объектный файл, исполняемый файл, временный файл

for fileName in  ./*; do
    if [[ $fileName == *.o ]] || [[ $fileName == *.exe ]] || [[ $fileName == *.temp ]]; then
        rm "$fileName"
    fi
done