// Copyleft Daniel Hartmann 2021

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

using namespace std;

class TCPServer
{
public:
    TCPServer();
    TCPServer(int Port);

    const int GetPort();

protected:
    const int Port;

private:
    int Socket;
    struct sockaddr_in Address;
    struct sockaddr_in ClientAddress;
    void InitializeSocket();
    void Bind();
    void Listen();

    void Log(string Message);
};