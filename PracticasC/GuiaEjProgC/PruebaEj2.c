#include "Ejercicio2.h"
#include <string.h>

int main() {
	char *file_name = "ArchivoTestEj2.txt";
	FILE *file = open_file(file_name, "a");

	/*
	char *line;
	line = read_line(file, 2);
	printf("%s\n", line);
	line = read_line(file, 1);
	printf("%s\n", line);
	close_file(file);
	*/
	/*
	void print_string(char* string) {
		printf("%s\n", string);
	}
	print_string("Hello world");
	execute_function_per_line(file, print_string);
	*/
	printf("Hello World\n");
	void** example_list = malloc(sizeof(char) * 8 * 3);
	printf("%d\n", sizeof(char) * 8 * 3);
	example_list[0] = "Hola";
	example_list[1] = "Chau";
	example_list[2] = "iasshdia";
	char* test = example_list[0];
	printf("%s\n", test);
	char* concat_with_letter_a(void* string) {
		char* first_string = string;
		char* second_string = "aaaaaaaa";
		int concat_size = strlen(first_string) + strlen(second_string);
		char* concat_string = malloc(sizeof(char) * concat_size);
	    strcat(concat_string, first_string);
	    strcat(concat_string, second_string);
		return concat_string;
	}
	printf("%s", concat_with_letter_a(example_list[0]));
	iterate_list_and_add_to_file(file, concat_with_letter_a, example_list);
	return 0;
}
