#!/bin/bash 

./build/TEST test.dat > test.dat-expected.txt; # вывод скрипта в файл test-expected.txt
# diff_out = diff test.dat-expected.txt test.ans # сравнение полученного файла с ответами
diff test.dat-expected.txt test.ans
if [ $? -eq 0 ]
then
    exit 0
    echo "All tests were successful"
else
    exit 1
    # echo "$diff_out"
fi
# if diff_out = 0; 
#     echo "All tests were successful"
# else
#     echo "$diff_out";
# fi