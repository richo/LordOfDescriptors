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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_LordOfDescriptors.h"



static int le_LordOfDescriptors;

const zend_function_entry LordOfDescriptors_functions[] = {
    PHP_FE(recv_socket, NULL)
	PHP_FE_END	/* Must be the last line in LordOfDescriptors_functions[] */
};


zend_module_entry LordOfDescriptors_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"LordOfDescriptors",
	LordOfDescriptors_functions,
	PHP_MINIT(LordOfDescriptors),
	PHP_MSHUTDOWN(LordOfDescriptors),
	PHP_RINIT(LordOfDescriptors),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(LordOfDescriptors),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(LordOfDescriptors),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_LORDOFDESCRIPTORS
ZEND_GET_MODULE(LordOfDescriptors)
#endif


PHP_FUNCTION(recv_socket)
{
    char *sock = NULL;
    int argc = ZEND_NUM_ARGS();

    if (zend_parse_parameters(argc TSRMLS_CC, "r", &sock) == FAILURE) {
        php_error_doc_ref(NULL TSRMLS_CC, E_ERROR, "Invalid Parameters");
        return;
    }

    RETURN_STRING("butts", 1);
}



PHP_MINIT_FUNCTION(LordOfDescriptors)
{
	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(LordOfDescriptors)
{
	return SUCCESS;
}



PHP_RINIT_FUNCTION(LordOfDescriptors)
{
	return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(LordOfDescriptors)
{
	return SUCCESS;
}


PHP_MINFO_FUNCTION(LordOfDescriptors)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "LordOfDescriptors support", "enabled");
	php_info_print_table_end();

}





