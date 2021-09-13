CC		= gcc
DEBUG	= -g
CFLAGS	= -ansi -Wall -std=c99 -c

OBJS	= board.o main.o translate.o move.o Chat.o ChatGui.o

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

DESIGN = ChessGame
all: $(DESIGN)

ChessGame: $(OBJS)
	$(CC) -Wall $(OBJS) -o ChessGame
	
board.o: src/board.h src/board.c
	$(CC) $(CFLAGS) src/board.c -o board.o

Chat.o: src/Chat.h src/Chat.c
	$(CC) $(CFLAGS) src/Chat.c -o Chat.o
 
translate.o: src/translate.h src/translate.c
	$(CC) $(CFLAGS) src/translate.c -o translate.o
	
move.o: src/move.h src/move.c
	$(CC) $(CFLAGS) src/move.c -o move.o
	
main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -o main.o

database.o: src/database.c src/database.h
	$(CC) $(CFLAGS) src/database.c -o database.o

ChessGUI.o: src/ChessGUI.c src/ChessGUI.h
	gcc -c src/ChessGUI.c $(INC) $(OPTS) -o ChessGUI.o
	 
ChessGUI: ChessGUI.o move.o board.o translate.o
	gcc ChessGUI.o move.o board.o translate.o $(LIBS) $(OPTS) -o ChessGUI

LoginGUI.o: src/LoginGUI.c src/LoginGUI.h 
	gcc -c src/LoginGUI.c $(INC) $(OPTS) -o LoginGUI.o

LoginGUI: LoginGUI.o 
	gcc LoginGUI.o $(LIBS) $(OPTS) -o LoginGUI

RegisterGUI.o: src/RegisterGUI.c src/RegisterGUI.h
	gcc -c src/RegisterGUI.c $(INC) $(OPTS) -o RegisterGUI.o

RegisterGUI: RegisterGUI.o 
	gcc RegisterGUI.o $(LIBS) $(OPTS) -o RegisterGUI


#RegisterGUI: RegisterGUI.o 
#	gcc -c RegisterGUI.o $(LIBS) -o RegisterGUI
#hi

ChatGui.o: src/ChatGui.c src/ChatGui.h
	gcc -c src/ChatGui.c $(GTKINC) -o ChatGui.o

Chat: ChatGui.o database.o
	gcc ChatGui.o $(GTKLIBS) -g -DDEBUG database.o -o Chat
	
databaseTest: src/database.c src/database.h
	gcc -ansi -Wall -std=c99 -g -DDEBUG src/database.c -o databaseTest
	./databaseTest

server_sockerTest: src/server_socket.c src/server_socket.h database.o
	gcc -pthread -ansi -Wall -std=c99 -g -DDEBUG src/server_socket.c database.o -o server_socketTest
	./server_socketTest -p 1717

message_daemon.o: src/message_daemon.c src/message_daemon.h
	gcc -pthread -ansi -Wall -std=c99 -g src/message_daemon.c -o message_daemon.o

message_daemonTest: src/message_daemon.c src/message_daemon.h database.o
	gcc -pthread -ansi -Wall -std=c99 -g -DDEBUG src/message_daemon.c database.o -o message_daemonTest

client_sockerTest: src/client_socket.c src/client_socket.h
	gcc -ansi -Wall -std=c99 -g -DDEBUG src/client_socket.c -o client_socketTest
	./client_socketTest -p 1717

server_final: src/server_socket.c src/server_socket.h database.o
	gcc -pthread -ansi -Wall -std=c99 -g -DDEBUG src/server_socket.c database.o -o server

client_final: src/client_socket.c src/client_socket.h
	gcc -ansi -Wall -std=c99 -g -DDEBUG src/client_socket.c -o client

Socket_Communication_Demo: src/server_socket.c src/server_socket.h database.o src/client_socket.c src/client_socket.h Chat server_final
	echo "Starting Socket Communication Demo"
	echo "Notice that the Server is running in background!"
	./server -p 1717 &
	./Chat -p 1717

socketTester: src/socketTester.c
	gcc -ansi -Wall -std=c99 src/socketTester.c -o socketTester
	./socketTester -p 1717

drop_database:
	rm -f database/chat/*.cht
	rm -f database/chat/*.que
	rm -f database/user/*.usr
	rm -f database/user/*.fri
	rm -f database/user/*.sta

clean:
	rm -f *.o
	rm -f *.txt
	rm -f ChessGame
	rm -f ChessGUI
	rm -f client_socketTest
	rm -f databaseTest
	rm -f server_socketTest
	rm -f socketTester
	rm -f LoginGUI
	rm -f RegisterGUI

	
