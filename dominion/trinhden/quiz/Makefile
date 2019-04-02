CFLAGS = -Wall -fpic -coverage -lm -std=c99

test: testme.c
	gcc -o testme -g testme.c $(CFLAGS)

clean:
	rm -f *.gcno *.gcda testme
