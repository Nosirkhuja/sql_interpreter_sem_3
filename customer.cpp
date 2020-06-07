#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std; 

int main(){

    // создаем сокет
    int sock=socket(AF_INET, SOCK_STREAM, 0);
    if (sock==-1)
    {
        return 1;
    }
    // создаем структуру для соединения с сервером 

    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        cout << "111111";
        return 1;
    }

    char buf[4096];
    string userInput;

    do {
        //      Ввод строк 
        cout << "> ";
        getline(cin, userInput);

        //      отправляем в сервер
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //      Ждем ответа от сервера
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (strcmp(buf,"END")==0){
            close(sock);
            return 1;
        }
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            //      Display response
            cout << "Сервер> " << string(buf, bytesReceived) << "\r\n";
        }
    } while(true);

    //  Закрываем сокет 
    close(sock);

    return 0;
}


