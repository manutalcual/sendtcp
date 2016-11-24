//
// Clase: bencode Copyright (c) 2006 AMPER
// Autor: Manuel Cano Muñoz
// Fecha: Mon Aug 14 09:10:45 2006
// Time-stamp: <>
//
// Includes
//

#ifndef __bencode_h__
#define __bencode_h__

#include <string>

#include "log.hh"

namespace net {

	class bencode
	{
	public:
		bencode (int sock);
		~bencode ();
		operator bool ();
		bencode & operator >> (size_t & num);
	protected:
	private:
		int _sock;
		bool _ok;

		char read_char ();
		std::string read_till (char ch);
	};

} // end namespace net

#endif // __bencode_h__


