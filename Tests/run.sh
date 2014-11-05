if [ $# -eq 1 ]
then
	clear;g++ -o test test.cpp -I ../Handbook/ && ./test && rm test
else
	clear;g++ -g -o test test.cpp -I ../Handbook/ && gdb ./test #&& rm test
fi
