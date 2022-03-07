#ifndef EJERCICIO2_H_
#define EJERCICIO2_H_

#include <stdio.h>
#include <stdlib.h>

FILE* open_file(char* file_name, char* open_mode);
void close_file(FILE* file);
char* read_line(FILE* file, int line_number);
void execute_function_per_line(FILE* file, void (*function_for_string)(char* line_content));
void iterate_list_and_add_to_file(FILE* file, char* (*function)(void* list), void** list);
char* get_current_line(FILE* file);


#endif /* EJERCICIO2_H_ */
