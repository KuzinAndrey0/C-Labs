#!/bin/bash
#Очищает мусор
#Мусор - объектный файл, исполняемый файл, временный файл

find . -type f -name "*.temp" -delete
find . -type f -name "*.o" -delete
find . -type f -name "*.exe" -delete