/* printer.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WIN_PATH '\\'
#define LIN_PATH '/'
#define UNDERSCORE '_'
#define TEX_UNDERSCORE "\\_"




/**
 * this function is checing for underscore to escape it 
 *
 * @param FILE *file output file
 * @param const char* functionName string that is checking
 */
void printLaTeXFormatted(FILE *file, const char* functionName) {
    int i = 0;
    
    /* arguments check */
    if (!file || !functionName) {
    	printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
    
    /* iterating through functionname and if _ is found it will escape it  */
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
 * this function is printing module
 *
 * @param FILE *file output file
 * @param char *filename name of the module
 */
void print_module(FILE *file, char *module) {
	char *win;
	char *lin;
	
	/* arguments check */
    if (!file || !module) {
    	printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	
	/* finding the right slash */
	win = strrchr(module, WIN_PATH);
	lin = strrchr(module, LIN_PATH);
	
	
	/* initial print of subsection */
	fprintf(file,"\\subsection{Modul \\texttt{");
	
	/* for the right slash it gonna printf right name of module */
	if (win) { 
		printLaTeXFormatted(file, win + 1);
		
	}
	else if (lin) { 
		printLaTeXFormatted(file, lin + 1);
		
	}
	else {
		printLaTeXFormatted(file, module);
		
	}	
	
	/* end of print */
	fprintf(file,"}}\n");
}


/**
 * this function is printing packages
 *
 * @param FILE *file output file
 */
void print_packages(FILE *file) {
	
	/* arguments check */
	if (!file) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	/* printing packages */
	fprintf(file,"\\usepackage[utf8]{inputenc}\n");
	fprintf(file,"\\usepackage[IL2]{fontenc}\n");
	fprintf(file,"\\usepackage[czech]{babel}\n");
	
}


/**
 * this function is printing initial section
 *
 * @param FILE *file output file
 */
void print_section(FILE *file) {
	
	/* arguments check */
	if (!file) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	
	fprintf(file, "\\documentclass[12pt, a4paper]{article}\n");
	print_packages(file);
	fprintf(file,"\\begin{document}\n\\section{Programátorská dokumentace}\n");
	
}



/**
 * this function is printing subsections
 *
 * @param FILE *file output file
 * @param char *title name of subsection
 * @param char *content content of subsection
 */
void print_subsubsection(FILE *file, char *title, char *content) {
	
	/* arguments check */
	if (!file || !title || !content) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	
	
	
	fprintf(file,"\\subsubsection{");
	printLaTeXFormatted(file, title);
	fprintf(file,"\\texttt{");
	printLaTeXFormatted(file, content);
	fprintf(file,"}}\n");
	
}


/**
 * this function is printing textbf
 *
 * @param FILE *file output file
 * @param char *title title of textbf
 * @param char *content content of textbf
 */
void print_textbf(FILE *file, char *title, char *content) {
	/* arguments check */
	if (!file || !title || !content) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	
	
	fprintf(file, "\\textbf{%s}", title);
	fprintf(file, "%s", content);
	fprintf(file, "\\\\\n");
}


/**
 * this function is printing formated arguments
 *
 * @param FILE *file output file
 * @param char* paramLine parameter line
 */
void printf_verb(FILE *file, char* paramLine) {
	char datatype[50];
    char point[5];
    char dataname[256];
    char dest[512];
    int sscanfResult;
    char* star;
	
	
	/* arguments check */
	if (!file || !paramLine) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}

    /* checking if there is a star in the paramLine */
    
    star = strchr(paramLine, '*');
    
	/* finding the right format of param line and then printing it */
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


/**
 * this function is printing return line formated
 *
 * @param FILE *file output file
 * @param char *returnLine return line
 */
void printf_return(FILE *file, char *returnLine) {
	char datatype[50];
    char point[5];
    char dest[512];
    int sscanfResult;
    char* star;
	
	
	/* arguments check */
	if (!file || !returnLine) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}

    /* checking if there is a star in the returnLine */
    star = strchr(returnLine, '*');
    
    /* finding the right format of param line and then printing it */
    if (star && (star == returnLine || isspace(star[-1])) && isspace(star[1])) {
        sscanfResult = sscanf(returnLine, "%s %s %[^.\n]", datatype, point, dest);
        if (sscanfResult == 3) {
            fprintf(file, "\\verb\"%s %s\" -- %s. ", datatype, point,dest);
        }
    } else if (star && !isspace(star[1])) {
        sscanfResult = sscanf(returnLine, "%s %[^.\n]", datatype, dest);
        if (sscanfResult == 2) {
            fprintf(file, "\\verb\"%s\" -- %s. ", datatype, dest);
        }
        
    } else if (star && !isspace(star[-1])) {
        sscanfResult = sscanf(returnLine, "%s  %[^.\n]", datatype, dest);
        if (sscanfResult == 2) {
            fprintf(file, "\\verb\"%s\" -- %s. ", datatype, dest);
        }
    } else {
        sscanfResult = sscanf(returnLine, "%s %[^.\n]", datatype, dest);
        if (sscanfResult == 2) {
            fprintf(file, "\\verb\"%s\" -- %s. ", datatype,  dest);
        }
    }
    
    
    
}



/**
 * this function is printing endfile
 *
 * @param FILE *file output file
 */
void print_end(FILE *file) {
	/* arguments check */
	if (!file) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	fprintf(file, "\\end{document}\n");
}


/**
 * this fucntion is printig space
 *
 * @param FILE *file output file
 */
void print_space(FILE *file) {
	/* arguments check */
	if (!file) {
		printf("Wrong arguments");
    	exit(EXIT_FAILURE);
	}
	fprintf(file, "\\par\\noindent\n");
}
