//
// Clase:  net Copyright (c) 2006 Manuel Cano Muñoz
// Author: Manuel Cano Muñoz
// Date:   Sun Aug 13 19:57:17 2006
// Time-stamp: <15-Aug-2006 23:53:23 manuel>
//
//
// Includes
//
#include "net.hh"


namespace net {

	net::net (int port)
		: _sock (-1),
		  _port (port),
		  _readsock (-1),
		  _ok (false)
	{
		bfunc();
	}

	net::~net ()
	{
	}

	bool net::connect (const char * srv)
	{
		bfunc();
		struct sockaddr_in dest_addr;

		_readsock = ::socket(PF_INET, SOCK_STREAM, 0);
		if (! _readsock)
		{
			log("No se puede crear el socket para conectar.");
			return false;
		}

		struct hostent * host = gethostbyname("localhost");

		
		::memset (&dest_addr, '\0', sizeof(dest_addr));
		dest_addr.sin_family = AF_INET;          // host byte order
		dest_addr.sin_port = htons(_port);   // short, network byte order
		log("Adress: " << host->h_addr);
		dest_addr.sin_addr.s_addr = ::inet_addr(srv);

		_ok = (::connect (_readsock, (struct sockaddr *)&dest_addr, 
						  sizeof(struct sockaddr)) == 0);						  
		return _ok;
	}

	bool net::shutdown (enum eshutdown how)
	{
		bfunc();
		return (::shutdown(_readsock, how) == 0);
	}

	void net::close ()
	{
		bfunc();
		::close (_readsock);
	}

	size_t net::write (std::string buf)
	{
		bfunc();
		return write(_readsock, buf);
	}

	size_t net::write (int sock, std::string buf)
	{
		bfunc();
		int sent = 0;		// Sent bytes count
		sis::strbencode b;
		
		b << buf.size();
		buf = b.str() + buf;

		const char * bbuf = buf.c_str();
		int tosend = buf.size();
	
		log("Escribiendo '" << buf << "', len " 
			<< buf.size()
			<< " (socket " << sock << ")");
		int realsize = buf.size();
		while (sent != realsize) 
		{
			int s = 0;
			errno = 0;
			s = send(sock, &bbuf[sent], tosend, MSG_NOSIGNAL);
			if (s == -1) {
				log("Error: " << strerror(errno));
				switch (errno) 
				{
				case EPIPE:
					log("Error EPIPE.");
					return sent;
					break;
				case EINTR:
					log("Error EINTR.");
					return sent;
					break;
				default:
					log("Error desconocido en el socket.");
				}
				throw "##### ERROR: El socket no puede enviar (1) #####";
			}
			sent += s;
			tosend -= sent;
		}
		log("Datos escritos");

		//
		// We add a header to the data, if the client
		// verifies the data sent, it *must* be the
		// data received (if we send all data, obviously)
		//
		if (sent > buf.size())
			return buf.size();

		return sent;
	}

	int net::sock ()
	{
		return _sock;
	}

} // end namespace net

