/* printer.h */


#ifndef __PRINTER__
#define __PRINTER__


void printLaTeXFormatted(FILE *file, const char* functionName);

void print_module(FILE *file, char *filename);

void print_packages(FILE *file);

void print_section(FILE *file);

void print_subsubsection(FILE *file, char *title, char *content);

void print_textbf(FILE *file, char *title, char *content);

void printf_verb(FILE *file, char* paramLine);

void print_end(FILE *file);

void print_space(FILE *file);




#endif