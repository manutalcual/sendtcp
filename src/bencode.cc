//
// Clase: bencode Copyright (c) 2006 SISDETEC
// Autor: Manuel Cano Muñoz
// Fecha: Mon Aug 14 09:10:45 2006
// Time-stamp: <15-Aug-2006 21:24:31 manuel>
//
//
// Includes
//
#include "bencode.hh"

namespace net {

	bencode::bencode (int sock)
		: _sock (sock),
		  _ok (true)
	{
	}

	bencode::~bencode ()
	{
	}

	bencode::operator bool ()
	{
		return _ok;
	}

	bencode & bencode::operator >> (size_t & num)
	{
		int r = 0;

		char ch = read_char();

		if (ch == 'i')
		{
			std::string str = read_till('e'); // Bencode nums end in 'e'
			num = ::strtol(str.c_str(), NULL, 10);
		}
		else
			_ok = false;

		return *this;
	}

	char bencode::read_char ()
	{
		char ch = 0;
		int i = 0;

		if ( (i = read(_sock, reinterpret_cast<char **>(&ch), 1)) <= 0)
			_ok = false;

		return ch;
	}

	std::string bencode::read_till (char ch)
	{
		std::string str;
		char c;

		do
		{
			c = read_char();
			if (c != ch)
				str += c;
		}
		while (_ok && c != ch);

		return str;
	}

} // end namespace net


