/* printer.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WIN_PATH '\\'
#define LIN_PATH '/'
#define UNDERSCORE '_'
#define TEX_UNDERSCORE "\\_"





void printLaTeXFormatted(FILE *file, const char* functionName) {
    int i = 0;
    while (functionName[i] != '\0') {
        if (functionName[i] == UNDERSCORE) {
            fprintf(file, TEX_UNDERSCORE);
        } else {
            fprintf(file, "%c", functionName[i]);
        }
        i++;
    }
   
}


/**
 * Funkce pro vypsani modulu
 *
 * @param char * module nazev modulu co ma byt vypsan.
 */
void print_module(FILE *file, char *module) {
	char *win = strrchr(module, WIN_PATH);
	char *lin = strrchr(module, LIN_PATH);
	
	fprintf(file,"\\subsection{Modul \\texttt{");
	
	
	if (win) { 
		printLaTeXFormatted(file, win + 1);
		
	}
	else if (lin) { 
		printLaTeXFormatted(file, lin + 1);
		
	}
	else {
		printLaTeXFormatted(file, module);
		
	}	
	fprintf(file,"}}\n");
}

void print_packages(FILE *file) {
	
	fprintf(file,"\\usepackage[utf8]{inputenc}\n");
	fprintf(file,"\\usepackage[IL2]{fontenc}\n");
	fprintf(file,"\\usepackage[czech]{babel}\n");
	
}


void print_section(FILE *file) {
	fprintf(file, "\\documentclass[12pt, a4paper]{article}\n");
	print_packages(file);
	fprintf(file,"\\begin{document}\n\\section{Programátorskáčřšěůřž dokumentace}\n");
	
}

void print_subsubsection(FILE *file, char *title, char *content) {
	fprintf(file,"\\subsubsection{");
	printLaTeXFormatted(file, title);
	fprintf(file,"\\texttt{");
	printLaTeXFormatted(file, content);
	fprintf(file,"}}\n");
	
}

void print_textbf(FILE *file, char *title, char *content) {
	fprintf(file, "\\textbf{%s}", title);
	fprintf(file, "%s", content);
	fprintf(file, "\\\\\n");
}

void printf_verb(FILE *file, char* paramLine) {
    char datatype[50];
    char point[5];
    char dataname[256];
    char dest[512];
    int sscanfResult;
    char* star = strchr(paramLine, '*');
    

    if (star && (star == paramLine || isspace(star[-1])) && isspace(star[1])) {
        sscanfResult = sscanf(paramLine, "%s %s %s %[^.\n]", datatype, point, dataname, dest);
        if (sscanfResult == 4) {
            fprintf(file, "\\verb\"%s %s %s\" -- %s. ", datatype, point, dataname, dest);
        }
    } else if (star && !isspace(star[1])) {
        sscanfResult = sscanf(paramLine, "%s %s %[^.\n]", datatype, dataname, dest);
        if (sscanfResult == 3) {
            fprintf(file, "\\verb\"%s %s\" -- %s. ", datatype, dataname, dest);
        }
    } else if (star && !isspace(star[-1])) {
        sscanfResult = sscanf(paramLine, "%s %s %[^.\n]", datatype, dataname, dest);
        if (sscanfResult == 3) {
            fprintf(file, "\\verb\"%s %s\" -- %s. ", datatype, dataname, dest);
        }
    } else {
        sscanfResult = sscanf(paramLine, "%s %s %[^.\n]", datatype, dataname, dest);
        if (sscanfResult == 3) {
            fprintf(file, "\\verb\"%s %s\" -- %s. ", datatype, dataname, dest);
        }
    }
    
    
}


void print_end(FILE *file) {
	fprintf(file, "\\end{document}\n");
}

void print_space(FILE *file) {
	fprintf(file, "\\par\\noindent\n");
}
