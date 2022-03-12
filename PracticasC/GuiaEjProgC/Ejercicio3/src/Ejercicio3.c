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
	char* txt_person_data_formatted;
	char** array_person_data;
	char** array_person_data_formatted;
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
	rewind(file);
	printf("Adentro\n");
	char character = getc(file);
	while(!(character == EOF)) {
		printf("1\n");
		ungetc(character, file);
		add_to_list(get_current_line(file), list);
		character = getc(file);
	}
}

void show_original_person_txt(void* person) {
	t_person* one_person = person;
	char* txt_person = one_person->txt_person_data;
	printf("%s\n", txt_person);
}

void show_formatted_person_txt(void* person) {
	t_person* one_person = person;
	char* txt_person = one_person->txt_person_data_formatted;
	printf("%s\n", txt_person);
}

bool is_of_age(void* person) {
	t_person* one_person = person;
	printf("%s\n", one_person->array_person_data[2]);
	printf("%d\n", strcmp(one_person->array_person_data[2], "17"));
	return (atoi(one_person->array_person_data[2]) >= 18); // hago == xq si es menor de edad retorna -1 y como es diferente de 0 en un if seria true
}
/*
void add_formatted_data(t_person **one_person, int format_position, int original_position) {
	(*one_person)->array_person_data_formatted[format_position] = (*one_person)->array_person_data[original_position];
}
*/

void add_formatted_data(t_person **person, int original_position) {
	if(original_position == 1) {
		string_array_push(&((*person)->array_person_data_formatted), string_substring_until((*person)->array_person_data[original_position], 30));
	} else {
		string_array_push(&((*person)->array_person_data_formatted), (*person)->array_person_data[original_position]);
	}
}

t_person* format_person_array(t_person* person) {
	person->array_person_data_formatted = string_array_new();
	/*
	add_formatted_data(&person, 0, 0);
	add_formatted_data(&person, 1, 2);
	add_formatted_data(&person, 2, 4);
	//add_formatted_data(&one_person, 3, 1);
	printf("%s\n", string_substring_until(person->array_person_data[1], 30));
	strcpy(person->array_person_data_formatted[3], string_substring_until(person->array_person_data[1], 30));
	add_formatted_data(&person, 4, 3);
	*/
	/*
	string_array_push(&(person->array_person_data_formatted), person->array_person_data[0]);
	string_array_push(&(person->array_person_data_formatted), person->array_person_data[2]);
	string_array_push(&(person->array_person_data_formatted), person->array_person_data[4]);
	string_array_push(&(person->array_person_data_formatted), string_substring_until(person->array_person_data[1], 30));
	string_array_push(&(person->array_person_data_formatted), person->array_person_data[3]);
	*/
	add_formatted_data(&person, 0);
	add_formatted_data(&person, 2);
	add_formatted_data(&person, 4);
	add_formatted_data(&person, 1);
	add_formatted_data(&person, 3);
	return person;
}

t_person* format_person_txt(t_person* person) {
	person->txt_person_data_formatted = string_new();
	string_append(&(person->txt_person_data_formatted), person->array_person_data_formatted[0]);
	for(int i = 1; i < 5; i++) {
		string_append_with_format(&(person->txt_person_data_formatted), " | %s", person->array_person_data_formatted[i]);
	}
	return person;
}

void* format_person(void* person) {
	t_person* one_person = person;
	one_person = format_person_array(one_person);
	one_person = format_person_txt(one_person);
	person = one_person;
	return person;
}

char* person_region(t_person* person) {
	return person->array_person_data_formatted[0];
}

char* person_age(t_person* person) {
	return person->array_person_data_formatted[1];
}

bool person_goes_first_in_list(void* one_person, void* another_person) {
	t_person *one_person_t = one_person;
	t_person *another_person_t = another_person;
	return string_equals_ignore_case(person_region(one_person_t), person_region(another_person_t)) ? (strcmp(person_age(one_person_t), person_age(another_person_t)) < 1) : (strcmp(person_region(one_person_t), person_region(another_person_t)) < 1);
}

void add_person_to_output_file(void* one_person) {
	t_person *person = one_person;
	fprintf(output_file, "%s\n", person->txt_person_data_formatted);
}

void log_person_with_low_payment(void* one_person) {
	t_person *person = one_person;
	if(atoi(person->array_person_data[5]) < 100)
		log_trace(logger, "%s\n", person->txt_person_data_formatted);
}

int main() {
	/*
	char* hola = "Hola";
	char* chau = "Chau";

	printf("%d", strcmp(hola, chau));
	*/
	char* input_file_name = "ArchivoTestEj3.txt";
	char* output_file_name = "ArchivoTestEj3Salida.txt";
	FILE* input_file = fopen(input_file_name, "r");
	output_file = fopen(output_file_name, "w");
	t_list* people_of_file = list_create();
	logger = log_create("LogEj3.txt", "Ejercicio3", true, LOG_LEVEL_TRACE);

	add_line_of_file_into_list(input_file, &people_of_file, add_person_to_list);
	list_iterate(people_of_file, show_original_person_txt);
	people_of_file = list_filter(people_of_file, is_of_age);
	list_iterate(people_of_file, show_original_person_txt);
	people_of_file = list_map(people_of_file, format_person);
	list_iterate(people_of_file, show_formatted_person_txt);
	list_sort(people_of_file, person_goes_first_in_list);
	list_iterate(people_of_file, show_formatted_person_txt);
	list_iterate(people_of_file, add_person_to_output_file);
	list_iterate(people_of_file, log_person_with_low_payment);


	log_destroy(logger);
	fclose(input_file);
	fclose(output_file);
	return 0;
}
