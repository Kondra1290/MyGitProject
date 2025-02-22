CC=gcc
CFLAGS=-fPIC -Wall
LDFLAGS=
AR=ar
ARFLAGS=rcs
RM=rm -f

GENERATES = prog prog-a prog-so README output_static.a liboutput.so test_output_*
TRASH = *.o *~

all: liboutput_static.a liboutput.so prog prog-a prog-so
fun.o: fun.c outlib.h
	$(CC) $(CFLAGS) -c fun.c -o fun.o
const.o: const.c outlib.h
	$(CC) $(CFLAGS) -c const.c -o const.o
prog.o: prog.c outlib.h
	$(CC) $(CFLAGS) -c prog.c -o prog.o
liboutput_static.a: fun.o const.o
	$(AR) $(ARFLAGS) liboutput_static.a fun.o const.o
liboutput.so: fun.o const.o
	$(CC) -shared -o liboutput.so fun.o const.o
prog: prog.o fun.o const.o
	$(CC) -o prog prog.o fun.o const.o
prog-a: prog.o liboutput_static.a
	$(CC) -o prog-a prog.o liboutput_static.a
prog-so: prog.o liboutput.so
	$(CC) -o prog-so prog.o -L. -loutput -Wl,-rpath,.
README: prog
	./$< 2> $@
.PHONY: test
test: prog prog-a prog-so
	./prog > test_output_prog_1 2>&1
	./prog-a > test_output_prog-a_1 2>&1
	./prog-so > test_output_prog-so_1 2>&1
	./prog arg1 > test_output_prog_2 2>&1
	./prog-a arg1 > test_output_prog-a_2 2>&1
	./prog-so arg1 > test_output_prog-so_2 2>&1
	./prog arg1 arg2 arg3 > test_output_prog_3 2>&1
	./prog-a arg1 arg2 arg3 > test_output_prog-a_3 2>&1
	./prog-so arg1 arg2 arg3 > test_output_prog-so_3 2>&1
	cmp test_output_prog_1 test_output_prog-a_1 || echo "Outputs differ"
	cmp test_output_prog_1 test_output_prog-so_1 || echo "Outputs differ"
	cmp test_output_prog_2 test_output_prog-a_2 || echo "Outputs differ"
	cmp test_output_prog_2 test_output_prog-so_2 || echo "Outputs differ"
	cmp test_output_prog_3 test_output_prog-a_3 || echo "Outputs differ"
	cmp test_output_prog_3 test_output_prog-so_3 || echo "Outputs differ"
.PHONY: clean distclean
clean:
	$(RM) $(TRASH) liboutput_static.a liboutput.so
distclean: clean
	$(RM) $(GENERATES)
