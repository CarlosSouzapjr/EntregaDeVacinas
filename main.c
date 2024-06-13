#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct cidades{
    int id;
    char nome[25];
} Cidades;

int main(){
    
    char S[512]; // String que receberá a linha lida pelo fgets()
    char *ptr; // Ponteiro que assumirá sunção de token para o strtok()
    int **dist = NULL; // Matriz de distâncias (int)
    int linha = 0; // A linha da cidade atual
    int n = 5; // Quantidade de cidades = tamanho da matriz
    

    Cidades* cidades;


    FILE *file;

    file = fopen("../casos/modelo_simples.csv", "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    cidades = (Cidades*)malloc(sizeof(Cidades)*n);


    while (fgets(S, sizeof(S), file)) { // Pega cada linha do arquivo
        static int flag_linha = 0; // Flag que indica a leitura da linha do nome das cidades

        if (flag_linha == 0){ // Leitura do nome das cidade (string)

            S[strcspn(S, "\n")] = '\0'; // Remove o \n de fim de linha
            
            ptr = strtok(S, ",");
            ptr = strtok(NULL, ","); // Pula a primeira coluna

            for (int k = 0; ptr != NULL; k++) { // Itera sobre cada palavra da LINHA (string)
                strcpy(cidades[k].nome, ptr);
                cidades[k].id = k;
                
                printf("%s ", cidades[k].nome);
                ptr = strtok(NULL, ",");
                // n++;
            }
            printf("\n");
            flag_linha = 1; // Linha das cidades lida

            dist = (int**)malloc(sizeof(int*)*n); // Define o tamanho da matriz de distancias (int)
            
            for(int i = 0; i < n; i++){ // Define o tamanho dos vetores da matriz (int)
                dist[i] = (int*)malloc(sizeof(int)*n);
            }
        }
        else{ // Leitura das distâncias (int)

            S[strcspn(S, "\n")] = '\0'; 
            
            ptr = strtok(S, ",");
            ptr = strtok(NULL, ",");

            for (int j = 0; ptr != NULL; j++) { 
                dist[linha][j] = atoi(ptr);
                printf("%d ", dist[linha][j]);
                ptr = strtok(NULL, ",");
            }
            printf("\n");
            linha++;

        }
    }
    printf("Tamanho: %d\n\n", n);
    // for (int i = 0; i < n; i++){
    //     printf("%s ", cidades[i].nome);
    //     printf("%d \n", cidades[i].id);
    // }
    fclose(file);


    return 0;
}
