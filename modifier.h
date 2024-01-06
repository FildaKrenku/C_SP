/* modifier.h */
 
#ifndef __MODIFIER__
#define __MODIFIER__
 
void remove_spaces(char *text);
 
char* removeQuotes(char *str);
 
char* extract_path(char *filename);
 
char* connect_path(char *path, char *filename);
 
/**   
 * kokotipica
 */  
char* extractExtension(char *filename);

char* trim_white_spaces(char *input);
 

 
 
 
 #endif