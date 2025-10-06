# Makefile

all:
	g++ -std=c++17 server.cpp -o server -luWS -lssl -lcrypto -lz -lpthread
