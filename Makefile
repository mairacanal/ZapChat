CC=g++

all: server client

server:
	$(CC) src/server.cpp \
		src/socket/socket.cpp \
		src/server/server.cpp \
		-pthread -o server -std=c++17

client:
	$(CC) src/client.cpp \
		src/gtk/window/window.cpp \
		-o client `pkg-config --cflags --libs gtkmm-3.0` -std=c++17

clear:
	rm server client
