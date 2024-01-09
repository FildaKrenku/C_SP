/* modifier.h */
 
#ifndef __MODIFIER__
#define __MODIFIER__

/**
 * this function is removing spaces of text
 *
 * @param char *text text 
 */
void remove_spaces(char *text);
 
/**
 * this function is rmoving quotes of str
 *
 * @param char *str string with quotes
 */
char* removeQuotes(char *str);
 
/**
 * this function is extracting path of filename
 *
 * @param char *filename name of file 
 */
char* extract_path(char *filename);
 
 
/**
 * this function is connecting path to filename
 *
 * @param char *path path to file
 * @param char *filename name of file
 */
char* connect_path(char *path, char *filename);
 
/**   
 * this function is extraction extension of filename
 *
 * @param char *filename name of file
 */  
char* extractExtension(char *filename);


/**
 * this fucntion is trimmig whitespace of input
 *
 * @param char *input string with whitespaces
 */
char* trim_white_spaces(char *input);
 

 
 
 
 #endif