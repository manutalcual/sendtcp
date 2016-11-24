//
// Class:  strbencode Copyright (c) 2006 Manuel Cano Muñoz
// Author: Manuel Cano Muñoz
// Date:   Mon Aug 14 18:51:45 2006
// Time-stamp: <>
//
// Includes
//


#ifndef __strbencode_h__
#define __strbencode_h__

#include <string.h>
#include <string>
#include <vector>
#include <map>

#include "log.hh"

namespace sis {

	typedef std::vector<size_t> vecsizet_t;
	typedef std::vector<std::string> vecstring_t;

	std::string intostr (size_t num);
	size_t strtoint (std::string num);

	class strbencode
	{
	public:
		strbencode ();
		strbencode (std::string str);
		~strbencode ();
		bool is_ok () const;
		std::string str () const;
		strbencode & operator >> (size_t & i);
		strbencode & operator >> (time_t & i);
		strbencode & operator >> (std::string & str);
		strbencode & operator << (size_t i);
		strbencode & operator << (std::string str);
		strbencode & operator << (vecsizet_t & nums);
		strbencode & operator << (vecstring_t & strings);
	protected:
	private:
		bool _ok;
		std::string _str;
	};

} // end namespace sis


#endif // __strbencode_h__


