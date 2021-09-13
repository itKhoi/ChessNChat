
CC		= gcc
DEBUG	= -g
CFLAGS	= -ansi -Wall -std=c99 -c

OBJS	= board.o main.o translate.o move.o

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

DESIGN = ChessGame
all: $(DESIGN)

ChessGame: $(OBJS)
	$(CC) -Wall $(OBJS) -o ChessGame
	
board.o: board.h board.c
	$(CC) $(CFLAGS) board.c -o board.o
	
translate.o: translate.h translate.c
	$(CC) $(CFLAGS) translate.c -o translate.o
	
move.o: move.h move.c
	$(CC) $(CFLAGS) move.c -o move.o
	
main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

database.o: database.c database.h
	$(CC) $(CFLAGS) database.c -o database.o

ChessGUI.o: ChessGUI.c ChessGUI.h move.h board.h translate.h
	gcc -c ChessGUI.c $(INC) -o ChessGUI.o
	 
ChessGUI: ChessGUI.o move.o board.o translate.o
	gcc ChessGUI.o move.o board.o translate.o $(LIBS) -o ChessGUI

LoginGUI.o: LoginGUI.c LoginGUI.h 
	gcc -c LoginGUI.c $(INC) -o LoginGUI.o

LoginGUI: LoginGUI.o 
	gcc  LoginGUI.o $(LIBS) -o LoginGUI

RegisterGUI.o: RegisterGUI.c RegisterGUI.h
	gcc -c RegisterGUI.c $(INC) -o RegisterGUI.o

RegisterGUI: RegisterGUI.o 
	gcc RegisterGUI.o $(LIBS) -o RegisterGUI 

	
databaseTest: database.c database.h
	gcc -ansi -Wall -std=c99 -g -DDEBUG database.c -o databaseTest
	./databaseTest

server_sockerTest: server_socket.c server_socket.h database.o
	gcc -pthread -ansi -Wall -std=c99 -g -DDEBUG server_socket.c database.o -o server_socketTest
	./server_socketTest

client_sockerTest: client_socket.c client_socket.h
	gcc -ansi -Wall -std=c99 -g -DDEBUG client_socket.c -o client_socketTest
	./client_socketTest

Socket_Communication_Demo: server_socket.c server_socket.h database.o client_socket.c client_socket.h
	echo "Starting Socket Communication Demo"
	echo "Notice that the Server is running in background!"
	gcc -pthread -ansi -Wall -std=c99 -g -DDEBUG server_socket.c database.o -o server_socketTest
	gcc -ansi -Wall -std=c99 -g -DDEBUG client_socket.c -o client_socketTest
	./server_socketTest &
	./client_socketTest

clean:
	rm -f *.o
	rm -f *.txt
	rm -f ChessGame
	rm -f ChessGUI
	rm -f client_socketTest
	rm -f server_socketTest
	rm -f RegisterGUI
	rm -f LoginGUI
