#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
using namespace std;

int main(){

    int socket_FD = socket(AF_INET,SOCK_STREAM,0);
    if(socket_FD == -1){
        cout<<"Socket creation failed"<<endl;
        return -1;
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
    //server_addr.sin_addr.s_addr = INADDR_ANY;

    int bind_Status = bind(socket_FD,(sockaddr*)&server_addr , sizeof(server_addr));

    listen(socket_FD,5);
     std::cout << "Server waiting...\n";
     
     sockaddr_in client_socket;
     socklen_t client_len = sizeof(client_socket);
     
     while(true)
     {
         std::cout << "Server waiting... for new connection\n";
         int flags = fcntl(socket_FD,F_GETFL,0);
         fcntl(socket_FD,F_SETFL,flags|O_NONBLOCK);
         int client_FD = accept(socket_FD,(sockaddr*)&client_socket ,&client_len);
         if(client_FD < 0){
            cout<<" No client....\n";
            continue;
         }
            cout<<"Connection ESTB"<<endl;
         char ip[INET_ADDRSTRLEN];
         inet_ntop(AF_INET,&client_socket.sin_addr,ip,sizeof(ip));
          cout<<"CLI connected from IP :"<<ip<<"\nPort: "<<ntohs(client_socket.sin_port)<<endl;  
          while(true)
          {
              
              char buffer[1024] = {0};
              int nbytes =  recv(client_FD,buffer,sizeof(buffer),0);
              if(nbytes == 0)
              {
                  close(client_FD);
                  cout<<"CLI disconnected from IP :"<<ip<<"\nPort: "<<ntohs(client_socket.sin_port)<<endl; 
                  break; 
              }
              string rMsg (buffer,nbytes);
              cout<<"CLI: "<<rMsg<<endl;
            
            string msg;
            getline(cin,msg);
            //const char* msg = "Hello from server";
            cout<<"SERVER: "<<msg<<endl;
            send(client_FD, msg.c_str(), msg.size(), 0);
            
            
        }
     }

    close(socket_FD);
    return 0;
}