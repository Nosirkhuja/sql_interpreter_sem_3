#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
//#include "analyze.h"    // Analyze: start()

using namespace std; 

int main(){
	//создаем сокет
    cout<< "Waiting for client";

	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
    //создаем ip адрес и порт для сокета
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));
    
    listen(listening, SOMAXCONN);
 	// ждем соединения 

 	sockaddr_in client;
 	socklen_t clientSize = sizeof(client);

 	int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

 	char host[NI_MAXHOST];      
    char service[NI_MAXSERV];   

    memset(host, 0, NI_MAXHOST); 
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }

     // Закрываем сокет 
    close(listening);

    
    //Принимаем и отправляем сообщение клиенту 

    char buf[4096];
 
    while (true)
    {
        memset(buf, 0, 4096);
 
        
        // Ждем отправки данных клиента
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
        // Analyze analyze = Analyze(listening, buf); // анализируем и выполняем команды
        // analyze.start();

 
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }
 
        //cout << string(buf, 0, bytesReceived) << endl;
 
        // Отправляем сообщение обратно клиенту
        send(clientSocket, buf, bytesReceived + 1, 0);
    }
 
    // Закрываем сокет
    close(clientSocket);
 
    return 0;
}


