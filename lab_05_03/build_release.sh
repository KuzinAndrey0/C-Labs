#!/bin/bash
#Создает релизную сборку .c файла из папки, где находится этот скрипт

fileNameStr="$(find . -type f -name "*.c" | tr '\n' ' ')"
read -r -a fileNameArr <<< "$fileNameStr"
newNameStr="${fileNameStr//.c/.o}"
read -r -a newNameArr <<< "$newNameStr"

gcc -std=c99 -Werror -Wall -Wpedantic -Wextra -c "${fileNameArr[@]}"
gcc -o "app.exe" "${newNameArr[@]}" -lm