dnl $Id$
dnl config.m4 for extension fstd

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(fstd, for fstd support,
dnl Make sure that the comment is aligned:
[  --with-fstd             Include fstd support.])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(fstd, whether to enable fstd support,
dnl Make sure that the comment is aligned:
dnl [  --enable-fstd           Enable fstd support])

if test "$PHP_FSTD" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-fstd -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/fstd.h"  # you most likely want to change this
  dnl if test -r $PHP_FSTD/$SEARCH_FOR; then # path given as parameter
  dnl   FSTD_DIR=$PHP_FSTD
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for fstd files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FSTD_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FSTD_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the fstd distribution])
  dnl fi

  dnl # --with-fstd -> add include path
  dnl PHP_ADD_INCLUDE($FSTD_DIR/include)

  dnl # --with-fstd -> check for lib and symbol presence
  dnl LIBNAME=fstd # you may want to change this
  dnl LIBSYMBOL=fstd # you most likely want to change this 

  PG_LIB_NAME=pgc
  PG_LIB_SYMBOL=eq128
  PG_LIB_DIR=/opt/pgi/linux86-64/2012/libso

  dnl # Make sure env var LIBS="-lpgf90 -lpghpf2 -lpgf90rtl -lpgftnrtl -lpghpf_rpm -lpgc -lrt -lm"
  dnl # and LDFLAGS="-L/opt/pgi/linux86-64/2012/libso",
  dnl # Reason is the order that they must be in..
  PHP_CHECK_LIBRARY($PG_LIB_NAME,$PG_LIB_SYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($PG_LIB_NAME, $PG_LIB_DIR, FSTD_SHARED_LIBADD)
    AC_DEFINE(HAVE_FSTDLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong fstd lib version or lib not found])
  ],[
    -L$PG_LIB_DIR
  ])
  

  FSTD_LIB_NAME=rmn_local # you may want to change this
  FSTD_LIB_SYMBOL=fstlis_ # you most likely want to change this 
  FSTD_LIB_DIR=/Users/matt/aurams/trunk/rmn/

  PHP_CHECK_LIBRARY($FSTD_LIB_NAME,$FSTD_LIB_SYMBOL,
  [
    PHP_ADD_LIBRARY_WITH_PATH($FSTD_LIB_NAME, $FSTD_LIB_DIR, FSTD_SHARED_LIBADD)
    AC_DEFINE(HAVE_FSTDLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong fstd lib version or lib not found])
  ],[
    -L$PG_LIB_DIR -lpgc -L$FSTD_LIB_DIR
  ])
  


  dnl PHP_SUBST(FSTD_SHARED_LIBADD)

  PHP_NEW_EXTENSION(fstd, fstd.c, $ext_shared)
fi
