#include "Ejercicio2.h"
#include <string.h>

FILE* open_file(char* file_name, char* open_mode) {
	return fopen(file_name, open_mode);
}

void close_file(FILE* file) {
	fclose(file);
}

char* read_line(FILE* file, int line_number){
	rewind(file); // set file position at beginning of file
	char *return_string;
	for(int i = 0; i < line_number; i++) { //get line until the one asked
		return_string = get_current_line(file);
	}
	return return_string;
}

char* get_current_line(FILE* file) {
	int counter = 0;
	do {
		counter++;
	} while((getc(file)) != '\n' && !feof(file)); // count characters until '\n' is found
	fseek(file, -counter, SEEK_CUR); // set file to the beginning of the line
	char* return_string = malloc(sizeof(char) * counter); // assign memmory for the line
	return_string = fgets(return_string, counter, file); //assign line
	fseek(file, 1, SEEK_CUR); // set file to after '\n' for next line
	return return_string;
}


void execute_function_per_line(FILE* file, void (*function_for_string)(char* line_content)) {
	rewind(file);
	printf("Adentro\n");
	char character = getc(file);
	while(!(character == EOF)) {
		ungetc(character, file);
		function_for_string(get_current_line(file));
		character = getc(file);
	}
}


void iterate_list_and_add_to_file(FILE* file, char* (*function)(void* list), void** list) {
	fseek(file, 0, SEEK_END);
	while(*list != NULL) {
		char* return_to_write = function(*list);
		int success = fputs(return_to_write, file);
		printf("%d", success);
		list++;
	}
}














