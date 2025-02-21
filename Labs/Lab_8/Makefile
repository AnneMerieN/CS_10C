.PHONY: test
main: a.out sample.txt
	./a.out < sample.txt

test: test_hash
	./test_hash

a.out: main.cpp HashTable.cpp WordEntry.cpp HashTable.h WordEntry.h
	c++ -std=c++14 main.cpp HashTable.cpp WordEntry.cpp

sample.txt: movieReviews.txt
	python3 sample.py

test_hash: test.cpp HashTable.cpp WordEntry.cpp HashTable.h WordEntry.h
	c++ -std=c++14 test.cpp HashTable.cpp WordEntry.cpp -o test_hash
