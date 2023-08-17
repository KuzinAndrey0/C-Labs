#!/bin/bash
#Тестирует файл app.exe используя файлы с входом/ожидаемым выходом из папки /func_tests/
#Названия файлов имеют следующую архитектуру:
#   Позитивные тесты: для входа pos_NN_in.txt, pos_NN_out.txt для ожидаемого выхода
#   Негативные тесты: для входа neg_NN_in.txt, 
#Ключи(1): -q - тихий режим


num="01" #Счетчик тестов
errors="0" #Счетчик проваленных тестов
errorsMem="0" #Счетчик проваленных тестов по памяти
silent="$1" #Тихий режим
if [ "$silent" == "-q" ]; then
    silent="1"
else
    silent="0"
fi

file="pos_""$num""_in.txt"
while test -f ../data/"$file"; do #Проверять все файлы с позитивными тестами

    fileOut="pos_""$num""_out.txt"
    fileKey="pos_""$num""_args.txt"
    if [ -f ../data/"$fileKey" ]; then
        key=$(<../data/"$fileKey")
    else
        key=""
    fi
    eval ./pos_case.sh ../data/"$file" ../data/"$fileOut" "$key";
    returnCode="$?"

    if [ $returnCode == "0" ]; then
        memoryPass="0"
        testPass="0"
    elif [ $returnCode == "1" ]; then
        memoryPass="0"
        testPass="1"
        errors=$((errors+1))
    elif [ $returnCode == "10" ]; then
        memoryPass="1"
        testPass="0"
        errorsMem=$((errorsMem+1))
    elif [ $returnCode == "11" ]; then
        memoryPass="1"
        testPass="1"
        errors=$((errors+1))   
        errorsMem=$((errorsMem+1))    
    fi



    if [ $silent == "0" ]; then #В интерактивном режиме выводить номер теста и результат

        if [ $testPass == "0" ]; then
            testStr="\033[32mPASSED\033[37m"
        else
            testStr="\033[31mFAILED\033[37m"
        fi

        if [ $memoryPass == "0" ]; then
            memoryStr="\033[32mPASSED\033[37m"
        else
            memoryStr="\033[31mFAILED\033[37m"
        fi


        outStr="POSITIVE TEST ""$num"": ""$testStr"
        if [ -n "$USE_VALGRIND" ]; then
            outStr="$outStr"" | MEMORY USAGE: ""$memoryStr"
        fi    
        echo -e "$outStr"
    fi


    num=$((num+1)) #Следующий тест
    if [ $num -lt "10" ]; then
        num="0"$num
    fi
    file="pos_""$num""_in.txt"    
done


if [ $silent == "0" ]; then
    outStr="Positive tests: correct "$((num-1-errors))" of "$((num-1))
         if [ -n "$USE_VALGRIND" ]; then
            outStr="$outStr"" | Memory Passed: "$((num-1-errorsMem))" of "$((num-1))
        fi       
    echo "$outStr"
fi
oldErrors=$errors
oldErrorsMem=$errorsMem

num="01" #Обнулить счетчик для негативных тестов

file="neg_""$num""_in.txt"
while test -f ../data/"$file"; do #Проверять все файлы с негативными тестами    


    fileKey="neg_""$num""_args.txt"
    if [ -f ../data/"$fileKey" ]; then
        key=$(<../data/"$fileKey")
    else
        key=""
    fi

    eval ./neg_case.sh ../data/"$file" "$key"

    returnCode="$?"

    if [ $returnCode == "0" ]; then
        memoryPass="0"
        testPass="0"
    elif [ $returnCode == "1" ]; then
        memoryPass="0"
        testPass="1"
        errors=$((errors+1))
    elif [ $returnCode == "10" ]; then
        memoryPass="1"
        testPass="0"
        errorsMem=$((errorsMem+1))
    elif [ $returnCode == "11" ]; then
        memoryPass="1"
        testPass="1"
        errors=$((errors+1))   
        errorsMem=$((errorsMem+1))    
    fi



    if [ $silent == "0" ]; then #В интерактивном режиме выводить номер теста и результат

        if [ $testPass == "0" ]; then
            testStr="\033[32mPASSED\033[37m"
        else
            testStr="\033[31mFAILED\033[37m"
        fi

        if [ $memoryPass == "0" ]; then
            memoryStr="\033[32mPASSED\033[37m"
        else
            memoryStr="\033[31mFAILED\033[37m"
        fi

        outStr="NEGATIVE TEST ""$num"": ""$testStr"

        if [ -n "$USE_VALGRIND" ]; then
            outStr="$outStr"" | MEMORY USAGE: ""$memoryStr"
        fi    
        echo -e "$outStr"
    fi


    num=$((num+1)) #Следующий тест
    if [ $num -lt "10" ]; then
        num="0"$num
    fi
    file="neg_""$num""_in.txt"    
done

#Код возврата - кол-во ошибок
if [ $silent == "0" ]; then

    outStr="Positive tests: correct "$((num-1-errors+oldErrors))" of "$((num-1))
         if [ -n "$USE_VALGRIND" ]; then
            outStr="$outStr"" | Memory Passed: "$((num-1-errorsMem+oldErrorsMem))" of "$((num-1))
        fi       
    echo "$outStr"

    #echo "Negative tests: correct "$((num-1-errors+oldErrors))" of "$((num-1))
fi
exit $errors