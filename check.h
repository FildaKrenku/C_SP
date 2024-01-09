/* check.h */


#ifndef __CHECK__
#define __CHECK__



/**
 * this function is checking if after the prefix is only whitespaces
 *
 * @param const char *str line 
 * @param const char *prefix prefix
 */
int linecheck(const char *str, const char *prefix);

/**
 * this function is checking if file existing
 *
 * @param char *filename name of file
 */
int is_file_exist(char *filename);

                







#endif