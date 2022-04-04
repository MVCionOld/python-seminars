build:
	gcc -c sum_utils.c -o sum_utils.o
	gcc -shared -fPIC sum_utils.o -o lib_sum_utils.so
test:
	python3 test.py
clean:
	rm -f sum_utils.o lib_sum_utils.so