#ifndef _ERROR_H
#define _ERROR_H




typedef enum err_codes_e {
	OK,
	ERROR,
	MAX_ERROR
}err_codes_t;





/*
 * Description: Check for errors and print error message.
 * 
 * err_codes_t err_code - error code [in]
 * char *err_msg - error message to print [in]
 * 
 */
void check_error(err_codes_t err_code, const char *err_msg);


#endif
