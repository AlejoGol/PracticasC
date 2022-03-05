#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_concat(const char*, const char*);
void string_concat_dinamyc(const char*, const char*, char**);
void mail_split(const char* mail, char** user, char** dominio);

int main(void) {
    
    /*
    char* nombre = "Ritchie";
    char* saludo = string_concat("Hola ", nombre);
    printf("%s", saludo);
    */
    /*
    char* nombre = "Ritchie";
    char* saludo;
    string_concat_dinamyc("Hola ", nombre, &saludo);
    printf("%s", saludo);
    */
    char* mail = "ritchie@ansic.com.ar";
    char* user;
    char* dominio;
    mail_split(mail, &user, &dominio);
    printf("user: %s, dominio: %s \n", user, dominio);
    return 0;
}


char* string_concat(const char* first_string, const char* second_string) {
    int concat_size = strlen(first_string) + strlen(second_string);
    char* concat_string = malloc(concat_size);
    strcat(concat_string, first_string);
    strcat(concat_string, second_string);
    return concat_string;
} 

void string_concat_dinamyc(const char* first_string, const char* second_string, char** concat_string) {
    char* aux_string = string_concat(first_string, second_string);
    //strcpy(*concat_string, aux_string);
    *concat_string = aux_string;
}

void mail_split(const char* mail, char** user, char** dominio) {
    int counter = 0;
    while(mail[counter] != '@')
        counter++;
    char* aux_user = malloc(sizeof(char) * counter + 1);
    char* aux_dominio = malloc(sizeof(char) * (strlen(mail) - strlen(aux_user)) + 1);
    strncpy(aux_user, mail, counter);
    printf("%s\n", aux_user);
    strcpy(aux_dominio, mail + counter + 1);
    printf("%s\n", aux_dominio);

    *user = aux_user;
    *dominio = aux_dominio;
}