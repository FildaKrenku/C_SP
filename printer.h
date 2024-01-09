/* printer.h */


#ifndef __PRINTER__
#define __PRINTER__

/**
 * this function is checing for underscore to escape it 
 *
 * @param FILE *file output file
 * @param const char* functionName string that is checking
 */
void printLaTeXFormatted(FILE *file, const char* functionName);

/**
 * this function is printing module
 *
 * @param FILE *file output file
 * @param char *filename name of the module
 */
void print_module(FILE *file, char *filename);

/**
 * this function is printing packages
 *
 * @param FILE *file output file
 */
void print_packages(FILE *file);

/**
 * this function is printing initial section
 *
 * @param FILE *file output file
 */
void print_section(FILE *file);

/**
 * this function is printing subsections
 *
 * @param FILE *file output file
 * @param char *title name of subsection
 * @param char *content content of subsection
 */
void print_subsubsection(FILE *file, char *title, char *content);

/**
 * this function is printing textbf
 *
 * @param FILE *file output file
 * @param char *title title of textbf
 * @param char *content content of textbf
 */
void print_textbf(FILE *file, char *title, char *content);

/**
 * this function is printing formated arguments
 *
 * @param FILE *file output file
 * @param char* paramLine parameter line
 */
void printf_verb(FILE *file, char* paramLine);

/**
 * this function is printing return line formated
 *
 * @param FILE *file output file
 * @param char *returnLine return line
 */
void printf_return(FILE *file, char *returnLine);

/**
 * this function is printing endfile
 *
 * @param FILE *file output file
 */
void print_end(FILE *file);

/**
 * this fucntion is printig space
 *
 * @param FILE *file output file
 */
void print_space(FILE *file);




#endif