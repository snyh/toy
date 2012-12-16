all : db server client

client: client.cpp
	g++ $^ -std=c++0x -lpthread -lboost_system  -o client
server: server.cpp
	g++ $^ -std=c++0x -lpthread -lboost_system  -o server
db: db.cpp
	g++ -std=c++0x $^ -ldb_cxx -o db
