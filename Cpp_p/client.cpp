#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
using namespace std;

int main(){

    int socket_FD = socket(AF_INET,SOCK_STREAM,0);
    if(socket_FD == -1){
        cout<<"Socket creation failed"<<endl;
        return -1;
    }

    sockaddr_in Client_addr;
    Client_addr.sin_family = AF_INET;
    Client_addr.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&Client_addr.sin_addr);
    //server_addr.sin_addr.s_addr = INADDR_ANY;

    int con_st = connect(socket_FD, (sockaddr*)&Client_addr,sizeof(Client_addr));

    while(true)
    {
        string msg;
        getline(cin,msg);
        
        if(msg == "Exit")
        {
            close(socket_FD);
            break;
        }
        //const char* msg = "HEllo server";
        cout<<"CLI: "<<msg<<endl;
        send(socket_FD,msg.c_str(),msg.size(),0);
        
        char buffer[1024] = {0};
        int nbytes = recv(socket_FD,buffer,sizeof(buffer),0);
        if(nbytes == 0){
            close(socket_FD);
            cout<<"disconnected from server\n";
            break;

        }
        string rMsg (buffer,nbytes);
        cout<<"SERVER: "<<rMsg<<endl;
    }

return 0;
}