#ifndef _ERROR_H
#define _ERROR_H





typedef enum err_code_e {
	OK,
	ERROR,
	MAX_ERROR
}err_code_t;





/*
 * Description: Print an error message according to supplied error code
 * 
 * err_codes_t err_code - error code [in]
 * const char *err_msg - error message to print [in]
 * 
 */
void print_error(err_code_t err_code, const char *err_msg);


#endif
