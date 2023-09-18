#!/bin/bash 

rm -rf test_build
mkdir test_build
cd test_build
cmake ..
make

../test_build/TEST ../tests.dat > test.dat-expected.txt;

diff test.dat-expected.txt ../test.ans

# if [ $? -eq 0 ]
# then
#     exit 0
#     # echo "All tests were successful"
# else
#     exit 1
#     # echo "$diff_out"
# fi
