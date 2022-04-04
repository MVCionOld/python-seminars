CC          = gcc
CFLAGS      = -g -O2 $$(python3-config --includes --ldflags) -Wincompatible-pointer-types -std=c11
CSAHREDLIBS = -shared -fPIC

build:
	$(CC) $(CFLAGS) $(CSAHREDLIBS) -o userlib.so userlib.c
test:
	python3 test_userlib.py
clean:
	rm -f userlib.so