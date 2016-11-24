//
// Class:  net Copyright (c) 2006 Manuel Cano Muñoz
// Author: Manuel Cano Muñoz
// Date:   Sun Aug 13 19:57:17 2006
// Time-stamp: <15-Aug-2006 23:05:00 manuel>
//
// Includes
//


#ifndef __net_h__
#define __net_h__

#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <map>

#include "log.hh"
#include "bencode.hh"
#include "strbencode.hh"

namespace net {
	   
	class net
	{
	public:
		enum eshutdown { for_read = SHUT_RD, 
						 for_write = SHUT_WR, 
						 for_both = SHUT_RDWR };
		net (int port);
		~net ();
		bool connect (const char * srv);
		bool shutdown (enum eshutdown how);
		void close ();
		size_t write (std::string buf);
		size_t write (int sock, std::string buf);
		int sock ();
	protected:
	private:
		int _sock;
		int _port;
		int _readsock;
		bool _ok;
		bool _readerror;
	};
  
} // end namespace net


#endif // __net_h__


