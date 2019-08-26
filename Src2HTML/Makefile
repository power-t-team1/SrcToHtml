SRC:= $(wildcard *.c)
OBJ:= $(patsubst %.c, %.o, $(SRC))

lex.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o *.exe

run:
	make && ./lex.exe
