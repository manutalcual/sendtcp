//
// Clase:  strbencode Copyright (c) 2006 Manuel Cano Muñoz
// Author: Manuel Cano Muñoz
// Date:   Mon Aug 14 18:51:45 2006
// Time-stamp: <>
//
//
// Includes
//
#include "strbencode.hh"

namespace sis {

	std::string intostr (size_t num)
	{
		char buf[124];

		::sprintf (buf, "%d", num);

		return buf;
	}

	size_t strtoint (std::string num)
	{
		return ::strtol(num.c_str(), NULL, 10);
	}

	strbencode::strbencode ()
		: _ok (false),
		  _str ("")
	{
	}

	strbencode::strbencode (std::string str)
		: _ok (true),
		  _str (str)
	{
	}

	strbencode::~strbencode ()
	{
	}

	bool strbencode::is_ok () const
	{
		return _ok;
	}

	std::string strbencode::str () const
	{
		return _str;
	}

	strbencode & strbencode::operator >> (time_t & num)
	{
		size_t n = num;
		operator>>(n);
		num = n;

		return *this;
	}

	strbencode & strbencode::operator >> (size_t & num)
	{
		if (_str[0] == 'i')
		{
			int p = _str.find('e');
			
			if (p != std::string::npos)
			{
				std::string str;
				// Begin at pos 1 because we skip the 'i' char
				str = _str.substr(1, p - 1);
				_str = _str.substr(p + 1);
				num = strtoint(str);
			}
		}

		if (_str.size() <= 0)
			_ok = false;

		return *this;
	}

	strbencode & strbencode::operator >> (std::string & str)
	{
		if (_str.size() <= 0)
		{
			str = "";
			return *this;
		}

		if (_str[0] == 'i')
		{
			int p = _str.find('e');
			
			if (p != std::string::npos)
			{
				// Begin at pos 1 because we skip the 'i' char
				str = _str.substr(1, p - 1);
				_str = _str.substr(p + 1);
			}
		}
		else if (_str[0] == 'l')
		{
			throw "This is a list.";
		}
		else if (_str[0] == 'd')
		{
			throw "This is a dictionary.";
		}
		else
		{
			std::string size ("0"); // Prevent havoc
			int p = _str.find(':');
			
			if (p != std::string::npos)
			{
				size = _str.substr(0, p);
				_str = _str.substr(p);
			}
			int s = strtoint(size);
			// Begin at pos 1 because we skip the ':' char
			str = _str.substr(1,  s);
			_str = _str.substr(s + 1);
		}

		if (_str.size() <= 0)
			_ok = false;

		return *this;
	}

	strbencode & strbencode::operator << (size_t i)
	{
		_ok = true;
		_str += "i";
		_str += intostr(i);
		_str += "e";

		return *this;
	}

	strbencode & strbencode::operator << (std::string str)
	{
		if (str.size())
		{
			_ok = true;
			_str += intostr(str.size());
			_str += ":";
			_str += str;
		}
		
		return *this;
	}

	strbencode & strbencode::operator << (vecsizet_t & nums)
	{
		_ok = true;
		vecsizet_t::iterator it = nums.begin();
		vecsizet_t::iterator ite = nums.end();

		_str += "l";
		for (; it != ite; ++it)
		{
			_str += "i";
			_str += intostr(*it);
			_str += "e";
		}
		_str += "e";

		return *this;
	}

	strbencode & strbencode::operator << (vecstring_t & strings)
	{
		_ok = true;
		vecstring_t::iterator it = strings.begin();
		vecstring_t::iterator ite = strings.end();

		_str += "l";
		for (; it != ite; ++it)
		{
			_str += intostr(it->size());
			_str += ":";
			_str += *it;
		}
		_str += "e";

		return *this;
	}

} // end namespace sis


