//
// Programa: sendtcp Copyright (c) 2007 Manuel Cano Muñoz
// Autor: Manuel Cano Muñoz
// Fecha: Fri Mar 23 10:22:08 2007
// Time-stamp: <>
//
// Includes
//
#include "main.hh"


int main (int argc, char ** argv)
{
	bfunc();
	
	if (argc < 2)
	{
		std::cout << "sendtcp (c) 2007 Sisdedec, S.L." << std::endl;
		std::cout << "Author: Manuel Cano\n" << std::endl;
		std::cout << "Parameters:" << std::endl;
		std::cout << "-i|--ip <remote ip>" << std::endl;
		std::cout << "-p|--port <port number>" << std::endl;
		std::cout << "\nAll text thrown through cin will be sent to "
			"that IP and PORT" << std::endl;
		std::cout << "BEWARE! This application uses a bencode len "
			"prefix to tell the size data to the server.\n"
			"That means xxx will be sent as i3exxx" << std::endl;
		::exit (1);
	}

	int port = 0;
	const char * dir = 0;

	for (int i = 1; i < argc; ++i)
	{
		if (::strcmp(argv[i], "-p") == 0 
			|| ::strcmp(argv[i], "--port") == 0)
		{
			port = ::strtol(argv[++i], NULL, 10);
		}
		if (::strcmp(argv[i], "-i") == 0 
			|| ::strcmp(argv[i], "--ip") == 0)
		{
			dir = argv[++i];
		}
	}

	log("Beginning application.");
	log("Creating net object.");
	net::net n (port);
	std::string data;

	log("Connecting to host.");
	if (n.connect(dir))
	{
		log("Readind input.");
		while (std::cin)
		{
			std::string tmp;
			std::cin >> tmp;
			data += tmp;
		}
		log("Writing data.");
		n.write (data);
		log("Shut	ting down.");
		n.shutdown (net::net::for_both);
		n.close ();
	}
	else
	{
		log("Can't connect to the server.");
	}


	return 0;
}



