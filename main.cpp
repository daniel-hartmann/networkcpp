// Copyleft Daniel Hartmann 2021

#include <iostream>
#include <stdio.h>
#include "TCPServer.h"

int main(int argc, char **argv)
{
	TCPServer* TrustedServer = new TCPServer();
    TrustedServer->GetPort();
    
	return 0;
}
