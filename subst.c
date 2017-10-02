#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ASCII_LENGTH 128 //Number of ascii characters

typedef struct node
{
    int char_code;
    int frequency;
}Node;


int is_letter(char letter) {
    if ((int)tolower(letter) >= 97 && tolower(letter) <= 122) { //ASCII lowercase letters
        return 1;
    }
    return 0;
}


void calculate_frequency(Node frequency_array[], char word[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        if (is_letter(word[i]) == 1) {
            frequency_array[(int)word[i]].frequency += 1;
            frequency_array[(int)word[i]].char_code = (int)tolower(word[i]);
        }
    }
}


void sort_frequency_array(Node frequency_vector[]) {
    int i, j;
    Node aux;

    for (i = 0; i < ASCII_LENGTH - 1; i++) { //ordenate by frequency
        for (j = i + 1; j < ASCII_LENGTH; j++) {
            if (frequency_vector[i].frequency < frequency_vector[j].frequency) {
                aux = frequency_vector[j];
                frequency_vector[j] = frequency_vector[i];
                frequency_vector[i] = aux;
            }
        }
    }

    for (i = 0; i < ASCII_LENGTH - 1; i++) { //subordenate same frequency nodes by char_code
        for (j = i + 1; j < ASCII_LENGTH; j++) {
            if (frequency_vector[i].frequency == frequency_vector[j].frequency) {
                if (frequency_vector[i].char_code > frequency_vector[j].char_code) {
                aux = frequency_vector[j];
                frequency_vector[j] = frequency_vector[i];
                frequency_vector[i] = aux;
                }
            }
        }
    }

}


int main() {
    int m, n, i, j, counter;
    Node frequency_clean[ASCII_LENGTH] = { 0 };
    Node frequency_obscure[ASCII_LENGTH] = { 0 };
    char *clean, *obscure;

    //read the number of characters of the first string input (clean text)
    scanf("%i", &n);
    getchar();

    //allocate space for the first string and reads it
    clean = malloc(n * sizeof(char));
    fgets(clean, n + 1, stdin);
    getchar();

    //read the number of characters of the second string input (encoded text)
    scanf("%i", &m);
    getchar();

    //allocate space for the second string and reads it
    obscure = malloc(m * sizeof(char));
    fgets(obscure, m + 1, stdin);

    calculate_frequency(frequency_clean, clean, n);
    calculate_frequency(frequency_obscure, obscure, m);

    sort_frequency_array(frequency_clean);
    sort_frequency_array(frequency_obscure);

    for (int i = 0; i < m; i++) {
        counter = 0;
        for (j = 0; j < m; j++) {
            if (is_letter(obscure[i]) == 1) {
                if ((int)tolower(obscure[i]) == frequency_obscure[counter].char_code) {
                    obscure[i] = frequency_clean[counter].char_code;
                }
                counter++;
            }
        }
    }

    printf("%s\n", obscure);

    //free pointers
    free(obscure);
    free(clean);
}
