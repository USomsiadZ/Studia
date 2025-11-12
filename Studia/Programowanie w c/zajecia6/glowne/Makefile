#Makefile
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

OBJS = main.o data.o analysis.o display.o

orion: $(OBJS)
	$(CC) $(CFLAGS) -o orion $(OBJS)

main.o: main.c data.h analysis.h display.h
data.o: data.c data.h
analysis.o: analysis.c analysis.h data.h
display.o: display.c display.h data.h analysis.h





clean:
	rm -f $(OBJS) orion