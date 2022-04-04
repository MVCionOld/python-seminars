CC          = gcc
CFLAGS      = -g -O2 $$(python3-config --includes --ldflags) -Wincompatible-pointer-types -std=c11
CSAHREDLIBS = -shared -fPIC

build_testlib_dummy:
	$(CC) $(CFLAGS) $(CSAHREDLIBS) -o testlib.so testlib_dummy.c
test_testlib_dummy:
	python3 test_testlib_dummy.py

build_testlib:
	$(CC) $(CFLAGS) $(CSAHREDLIBS) -o testlib.so testlib.c
test_testlib:
	python3 test_testlib.py

clean:
	rm -f testlib_dummy.so testlib.so