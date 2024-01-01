 /* modifier.h */
 
 #ifndef __MODIFIER__
 #define __MODIFIER__
 
 void remove_spaces(char *text);
 
 char* removeQuotes(char *str);
 
 char* extract_path(char *filename);
 
 char* connect_path(char *path, char *filename);
 
 char* extractExtension(char *filename);
 
 
 
 
 
 
 #endif