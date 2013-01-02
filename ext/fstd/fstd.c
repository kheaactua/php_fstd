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
#include "php_fstd.h"

/* If you declare any globals in php_fstd.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(fstd)
*/

///* True global resources - no need for thread safety here */
//static int le_fstd;

/* {{{ fstd_functions[]
 *
 * Every user visible function must have an entry in fstd_functions[].
 */

const zend_function_entry fstd_functions[] = {
	PHP_FE(confirm_fstd_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(fstd_print,    NULL)
	PHP_FE(fstd_test, NULL)
	PHP_FE(fstd_diff, NULL)
	PHP_FE_END	/* Must be the last line in fstd_functions[] */
};
/* }}} */

/* {{{ fstd_module_entry
 */
zend_module_entry fstd_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"fstd",
	fstd_functions,
	PHP_MINIT(fstd),
	PHP_MSHUTDOWN(fstd),
	PHP_RINIT(fstd),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(fstd),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(fstd),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FSTD
ZEND_GET_MODULE(fstd)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("fstd.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_fstd_globals, fstd_globals)
    STD_PHP_INI_ENTRY("fstd.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_fstd_globals, fstd_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_fstd_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_fstd_init_globals(zend_fstd_globals *fstd_globals)
{
	fstd_globals->global_value = 0;
	fstd_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(fstd)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(fstd)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(fstd)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(fstd)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(fstd)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "fstd support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_fstd_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_fstd_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "fstd", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ proto void hello_print(void)
*   Print a message to show how much PHP extensions rock */
PHP_FUNCTION(fstd_print)
{
    php_printf("Hello, world!\n");
}
/* }}} */
/* {{{ proto void fstd_test(void)
*  Read nomvar and output it's dimensions */
PHP_FUNCTION(fstd_test)
{
	int iun = 1;
	int ier = 0;

	int ni,nj,nk,key;

	int m1=-1;

	char *nomvar = NULL;
	int nomvar_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &nomvar, &nomvar_len) == FAILURE) {
		RETURN_LONG(-100);
	}

	ier = c_fnom(iun, "test.fst", "STD+RND", 1);
	if (ier<0) {
		php_printf("Could not associate test.fst!\n");
	} else {
		php_printf("test.fst associate!\n");
	}

	ier = c_fstouv( iun, " ");
	if (ier<0) {
		php_printf("Could not open test.fst!\n");
	} else {
		php_printf("test.fst open (with fstouv)!\n");
	}

	//                                 datev, etickt, ip1,ip2,ip3, typvar
	//key = c_fstinf(iun, &ni, &nj, &nk, m1, "           ",m1,m1,m1," ", nomvar);
	key = c_fstinf(iun, &ni, &nj, &nk, m1, "POSX",m1,m1,m1,"X", nomvar);

	/* Return ni,nj  Should be done be reference right now.. */
	if (key<0) {
		php_printf("Error, could not find key\n");
	}
	php_printf("nomvar=%s, ni=%d, nj=%d\n", nomvar, ni, nj);

	/* Pass by reference? http://stackoverflow.com/questions/678026/passing-a-variable-by-reference-into-a-php-extension */
	/* Forming php types: http://devzone.zend.com/317/extension-writing-part-ii-parameters-arrays-and-zvals/ */

	// Form an array to return
	//ALLOC_INIT_ZVAL(return_value);
	//Z_TYPE_P(return_value) = IS_ARRAY;
	array_init(return_value);
	add_assoc_long(return_value, "key", key);
	add_assoc_long(return_value, "ni", ni);
	add_assoc_long(return_value, "nj", nj);

	/* Close the file */
	ier=c_fstfrm(iun);
	ier=c_fclos(iun);

	php_printf("Closing test.fst\n");

	//return return_value;
}
/* }}} */

/* {{{ proto void fstd_diff(filA, nomvarA, ..., mult)
*  Read nomvar and output it's dimensions */
// void difffst_(*char,*char, *char,*char, *char,*char, double)
PHP_FUNCTION(fstd_diff)
{
	char *filA = NULL;
	char *filB = NULL;
	char *filO = NULL;
	int filA_len, filB_len, filO_len;

	char *nomvarA = NULL;
	char *nomvarB = NULL;
	char *newnomvar = NULL;
	int nomvarA_len, nomvarB_len, newnomvar_len;

	double mult;

	int ier;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssssssd", 
	   &filA, &filA_len,
	   &nomvarA, &nomvarA_len,
	   &filB, &filB_len,
	   &nomvarB, &nomvarB_len,
	   &filO, &filO_len,
	   &newnomvar, &newnomvar_len,
	   &mult
	   ) == FAILURE) {
		RETURN_LONG(-100);
	}

	php_printf("Read arguments:\nfilA: %s, nomvara: %s\nfilB: %s, nomvarB: %s\nfilO: %s, nomvarO: %s\nMult: %0.3f\n", filA,nomvarA, filB,nomvarB, filO,newnomvar, mult);

// Maybe the issue is the returns?
	//difffst_(filA,nomvarA, filB,nomvarB, filO,newnomvar, mult, 0);
	ier = difffst_(filA,nomvarA, filB,nomvarB, filO,newnomvar, mult);
	//difffst_(filA,nomvarA, filB,nomvarB, filO,newnomvar, mult);

	RETURN_LONG(1);
	//return;

}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
