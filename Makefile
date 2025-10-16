cc = gcc
srcs = main.c
cflags = -Wall -Wextra -Iinclude
ldflags = -Llib -lraylib
target = program 

default:
	$(cc) $(cflags) -o $(target) $(srcs) $(ldflags)
	./$(target)

clean:
	rm -rf $(target)
