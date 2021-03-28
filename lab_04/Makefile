CFLAGS = -std=c99 -Wall -Werror -pedantic
CC = gcc

ifeq ($(mode), debug)
	CFLAGS += -g3
endif

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG -g0
endif

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< 	
	
app.exe: array_stack.o arr_stack.o list_stack.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o