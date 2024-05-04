HEADERS = common.h chunk.h debug.h
OBJECTS = main.o chunk.o memory.o debug.o value.o vm.o compiler.o scanner.o
PROGRAM = main

default: $(PROGRAM)

%.o: %.c $(HEADERS)
		gcc -c $< -o $@

main: $(OBJECTS)
		gcc $(OBJECTS) -o $@

clean:
		-rm -f $(OBJECTS) $(PROGRAM)