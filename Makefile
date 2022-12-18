CC = gcc 
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g \
         -Wstrict-prototypes -Wold-style-definition
CFILES = game.c pacman.c enemy.c main.c
HFILES = game.h pacman.h enemy.h
OFILES = game.o pacman.o enemy.o main.o
OBJNAME = main
LINKS = -lncurses

%.o: %.c $(HFILES)
	$(CC) -c $< -o $@

main: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(OBJNAME) $(LINKS)
clean:
	rm -f *.o
	rm -f main 


%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@


hw9:
	$(CC) main.c list.c $(CFLAGS) -o hw9

