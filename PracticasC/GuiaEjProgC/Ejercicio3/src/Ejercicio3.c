/*
 ============================================================================
 Name        : Ejercicio3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Ejercicio3.h"

typedef struct {
	char* txt_person_data;
	char** array_person_data;
}t_person;

t_person* new_person(char* _txt_person_data) {
	t_person* person = malloc(sizeof(t_person));
	person->txt_person_data = strdup(_txt_person_data);
	person->array_person_data = string_array_new();
	person->array_person_data = string_split(_txt_person_data, "; ");
	return person;
}

void add_person_to_list(char* txt_person, t_list** list) {
	list_add(*list, new_person(txt_person));
}

void add_line_of_file_into_list(FILE* file, t_list** list, void (*add_to_list)(char*, t_list**)) {
	//rewind(file);
	printf("Adentro\n");
	char character = getc(file);
	while(!(character == EOF)) {
		printf("1\n");
		ungetc(character, file);
		add_to_list(get_current_line(file), list);
		character = getc(file);
	}
}

int main() {
	/*
	char* hola = "Hola";
	char* chau = "Chau";

	printf("%d", strcmp(hola, chau));
	*/
	char* input_file_name = "ArchivoTestEj3.txt";
	FILE* input_file = fopen(input_file_name, "r");
	t_list* people_of_file = list_create();
	add_line_of_file_into_list(input_file, &people_of_file, add_person_to_list);

	return 0;
}
