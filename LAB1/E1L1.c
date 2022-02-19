#include "stdio.h"
#include "string.h"
#include "ctype.h"
#define MAX_CHAR_FOR_COMMAND 10
#define MAX 100
char *cercaRegexp(char *src, char *regexp);
int evaluate_reg_1(char *c);
int evaluate_reg_2(char c, char *list_of_char, int len_list);
int evaluate_reg_4(char *c);
int evaluate_reg_5(char *c);
int regexQuadra(char *src, char *regexp, int *i, int *j);
int main() {
    char *c, string[MAX], regex[MAX];
    printf("inserisci stringa :");
    scanf("%s", string);
    printf("inserisci regex:");
    scanf("%s", regex);
    c = cercaRegexp(string, regex);
    printf(" punto a %s",c);
}
char *cercaRegexp(char *src, char *regexp) {
    int i = 0, j = 0, continua = 1, tmp_c = 0;
    char *l=NULL,tmp_buffer[MAX_CHAR_FOR_COMMAND] = "";
    for (i = 0; i < strlen(src);) { //scorro dentro il vettore per cercare l'inizio giusto
        j = 0;
        continua = 1;
        while (j < strlen(regexp) && continua) { //scorro dentro regex
            if (j==0){
                l = &src[i];
            }

            if (isalpha(regexp[j])) {
                //se ho un carattere, verifico che sia uguale in src
                if (regexp[j] != src[i]) {
                    continua = 0; //rompi la lettura del regex e continua con la scansione del vettore
                } else {
                    j++;i++;
                } // vai avanti
            } else {
                switch (regexp[j]) {
                    case '.':
                        if (evaluate_reg_1(&src[i])) {
                            j++;i++;
                        } //se valido,vai avanti,
                        else {
                            i++;continua = 0;
                        } //altrimenti skippa
                        break;
                    case '[':
                        tmp_c = 0; //parto da carattere dopo '['
                        if (regexp[j + 1] == '^') {
                            while (regexp[j + tmp_c + 2] != ']' && j + tmp_c < strlen(regexp)) {
                                tmp_buffer[tmp_c] = regexp[j + tmp_c + 2];
                                tmp_c++;
                            }
                            if (evaluate_reg_2(src[i], tmp_buffer, tmp_c)) {
                                i++;continua = 0;
                            } else {
                                i++;j += tmp_c + 3;
                            }
                        } else {
                            while (regexp[j + tmp_c + 1] != ']' && j + tmp_c < strlen(regexp)) {
                                tmp_buffer[tmp_c] = regexp[j + tmp_c + 1];
                                tmp_c++;
                            }
                            if (evaluate_reg_2(src[i], tmp_buffer, tmp_c)) {
                                i++;j += tmp_c + 2;
                            } else {
                                i++;continua = 0;
                            }
                        }
                        break;
                    case '\\':
                        if (regexp[j + 1] == 'a') {
                            if (evaluate_reg_4(&src[i])) {
                                i++;j += 2;
                            } else {
                                i++;continua = 0;
                            }
                        } else if (regexp[j + 1] == 'A') {
                            if (evaluate_reg_5(&src[i])) {
                                i++;j += 2;
                            } else {
                                i++;continua = 0;
                            }
                        }
                        break;
                }
            }
        }
        if (j == strlen(regexp)) {
            return l;
        }
    }
    return NULL;
}
int evaluate_reg_1(char *c) {
    if (isalpha(*c)) return 1;
    else return 0;
}
int evaluate_reg_2(char c, char *list_of_char, int len_list) {
    for (int i = 0; i < len_list; i++) {
        if (c == list_of_char[i]) return 1; //list_of_char è un puntatore, però lo tratto come vettore grazie 
                                            // al dualismo che li caratterizzano.
    }
    return 0;
}
int evaluate_reg_4(char *c) {
    if (islower(*c)) return 1;
    return 0;
}
int evaluate_reg_5(char *c) {
    if (isupper(*c)) return 1;
    return 0;
}