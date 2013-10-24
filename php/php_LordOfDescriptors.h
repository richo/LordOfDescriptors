/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_LORDOFDESCRIPTORS_H
#define PHP_LORDOFDESCRIPTORS_H

extern zend_module_entry LordOfDescriptors_module_entry;
#define phpext_LordOfDescriptors_ptr &LordOfDescriptors_module_entry

#ifdef PHP_WIN32
#	define PHP_LORDOFDESCRIPTORS_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_LORDOFDESCRIPTORS_API __attribute__ ((visibility("default")))
#else
#	define PHP_LORDOFDESCRIPTORS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_FUNCTION(recv_socket);

PHP_MINIT_FUNCTION(LordOfDescriptors);
PHP_MSHUTDOWN_FUNCTION(LordOfDescriptors);
PHP_RINIT_FUNCTION(LordOfDescriptors);
PHP_RSHUTDOWN_FUNCTION(LordOfDescriptors);
PHP_MINFO_FUNCTION(LordOfDescriptors);




#ifdef ZTS
#define LORDOFDESCRIPTORS_G(v) TSRMG(LordOfDescriptors_globals_id, zend_LordOfDescriptors_globals *, v)
#else
#define LORDOFDESCRIPTORS_G(v) (LordOfDescriptors_globals.v)
#endif

#endif	/* PHP_LORDOFDESCRIPTORS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
