// Copyleft Daniel Hartmann 2021

#include "TCPServer.h"

TCPServer::TCPServer()
    :TCPServer(8080)
{
    // Empty constructor for default port 8080
}

TCPServer::TCPServer(int Port)
    :Port(Port)
{
    std::cout << "Initializing TCP Server... \t";

    this->InitializeSocket();

    this->Address.sin_family = AF_INET;
    this->Address.sin_addr.s_addr = INADDR_ANY;
    this->Address.sin_port = htons(Port);
    this->Bind();
    
    std::cout << "\tDone" << std::endl;

    this->Listen();
}

void TCPServer::InitializeSocket()
{
    int SocketOpt;
    int Opt = 1;
    
    // Create socket using IPv4 (AF_INET) using TCP (SOCK_STREAM)
    this->Socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (this->Socket == -1)
    {
        Log("Failed initializing socket");
        exit(EXIT_FAILURE);
    }

    SocketOpt = setsockopt(this->Socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &Opt, sizeof(Opt));
    
    if (SocketOpt == -1)
    {
        Log("Failed setting socket opt");
        exit(EXIT_FAILURE);
    }
}

void TCPServer::Bind()
{
    int BindReturn;
    
    BindReturn = bind(this->Socket, (struct sockaddr *)&this->Address,
        sizeof(this->Address));
    
    if (BindReturn < 0)
    {
        Log("Failed binding socket to localhost");
        exit(EXIT_FAILURE);
    }
}

const int TCPServer::GetPort()
{
    return Port;
}

void TCPServer::Listen()
{
    int ListenResult;
    int Connection;
    char Buffer[1024] = {0};

    
    ListenResult = listen(this->Socket, 5);
    if (ListenResult == -1)
    {
        Log("Failed listening");
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening on port " << Port << std::endl;

    int ClientAddressSize = sizeof(this->ClientAddress);
    Connection = accept(this->Socket, (struct sockaddr *)&this->ClientAddress,
        (socklen_t*)&ClientAddressSize);

    if (Connection == -1)
    {
        Log("Failed creating connection");
        exit(EXIT_FAILURE);
    }
    
    read(Connection, Buffer, 1024);
    std::cout << Buffer << std::endl;

    
    std::cout << "Finished listening." << std::endl;
}

void TCPServer::Log(string Message)
{
    std::cout << "[ERROR] " << Message << std::endl;
}
