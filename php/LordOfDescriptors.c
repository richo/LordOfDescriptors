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
#include "../ext/sockets/php_sockets.h"
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
    char *arg1 = NULL;
    int argc = ZEND_NUM_ARGS();

    if (zend_parse_parameters(argc TSRMLS_CC, "r", &arg1) == FAILURE) {
        RETURN_FALSE;
    }

    int le_socket = 0;
    char *le_socket_name = "Socket";

    php_socket  *out_sock = (php_socket*)emalloc(sizeof(php_socket));
    php_socket  *in_sock;

    ZEND_GET_RESOURCE_TYPE_ID(le_socket, le_socket_name);

    ZEND_FETCH_RESOURCE(in_sock, php_socket*, &arg1, -1, le_socket_name, le_socket);

    int    len;
    int    pass_sd;
    struct iovec   iov;
    struct msghdr  msg;
    int accepted;
    memset(&msg,   0, sizeof(msg));
    memset(&iov,    0, sizeof(iov));

    char fd_buf[CMSG_SPACE(sizeof(int))];
    msg.msg_iov     = &iov;
    msg.msg_iovlen  = 1;
    msg.msg_control    = fd_buf;
    msg.msg_controllen = sizeof(fd_buf);

    printf("Waiting on recvmsg\n");
    if (recvmsg(in_sock->bsd_socket, &msg, 0) < 0)
    {
        perror("recvmsg() failed");
    }

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    memcpy(&pass_sd, CMSG_DATA(cmsg), sizeof(int));
    printf("Received descriptor = %d\n", pass_sd);

    out_sock->bsd_socket = pass_sd;
    out_sock->type = AF_UNIX;
    out_sock->error = 0;
    out_sock->blocking = 1;

    ZEND_REGISTER_RESOURCE(return_value, in_sock, le_socket);

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





