
# all: main

# main: main.c list.c
# 	gcc -o main main.c list.c

# clean:
# 	rm -f main

all: test

test: s-talk.c list.o
	gcc s-talk.c list.o -o test -pthread

clean:
	rm -f test
