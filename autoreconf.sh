# !/bin/bash

LTMAINDIR=/usr/share/libtool
LTMAIN=ltmain.sh

if [ ! -f $LTMAIN ]; then
	if [ -d $LTMAINDIR ] && [ -f $LTMAINDIR/$LTMAIN ]; then
		cp $LTMAINDIR/$LTMAIN .
		chmod 755 $LTMAIN
	fi
fi

aclocal
autoheader
autoconf
autoheader
automake --add-missing --copy



