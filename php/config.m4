dnl $Id$
dnl config.m4 for extension LordOfDescriptors

PHP_ARG_ENABLE(LordOfDescriptors, whether to enable LordOfDescriptors support,
dnl Make sure that the comment is aligned:
[  --enable-LordOfDescriptors           Enable LordOfDescriptors support])

if test "$PHP_LORDOFDESCRIPTORS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-LordOfDescriptors -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/LordOfDescriptors.h"  # you most likely want to change this
  dnl if test -r $PHP_LORDOFDESCRIPTORS/$SEARCH_FOR; then # path given as parameter
  dnl   LORDOFDESCRIPTORS_DIR=$PHP_LORDOFDESCRIPTORS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for LordOfDescriptors files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LORDOFDESCRIPTORS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LORDOFDESCRIPTORS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the LordOfDescriptors distribution])
  dnl fi

  dnl # --with-LordOfDescriptors -> add include path
  dnl PHP_ADD_INCLUDE($LORDOFDESCRIPTORS_DIR/include)

  dnl # --with-LordOfDescriptors -> check for lib and symbol presence
  dnl LIBNAME=LordOfDescriptors # you may want to change this
  dnl LIBSYMBOL=LordOfDescriptors # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LORDOFDESCRIPTORS_DIR/lib, LORDOFDESCRIPTORS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_LORDOFDESCRIPTORSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong LordOfDescriptors lib version or lib not found])
  dnl ],[
  dnl   -L$LORDOFDESCRIPTORS_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(LORDOFDESCRIPTORS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(LordOfDescriptors, LordOfDescriptors.c, $ext_shared)
fi
