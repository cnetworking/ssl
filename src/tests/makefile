sockets:
	make server
	make client
server: server.c
	gcc -Wall -o server server.c -L/usr/local/lib -lssl -lcrypto
client: client.c
	gcc -Wall -o client client.c -L/usr/local/lib -lssl -lcrypto