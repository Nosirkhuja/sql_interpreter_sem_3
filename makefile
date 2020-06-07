all:
	make server
	make client

server: server.cpp table.cpp analyze.cpp exception.cpp Where_condition.cpp
	g++ -std=gnu++17 server.cpp table.cpp analyze.cpp exception.cpp Where_condition.cpp -o server

client: customer.cpp
	g++ -std=gnu++17  customer.cpp -o client
