CC = gcc
BIN1 = server
BIN2 = client
FLAGS = -g

shm_simple_exchange: *.c
				$(CC) server.c -o $(BIN1) $(FLAGS)
				$(CC) client.c -o $(BIN2) $(FLAGS)
