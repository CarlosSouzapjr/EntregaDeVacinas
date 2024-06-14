#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define MAX_N 15 // Define o número máximo de cidades
int **dist = NULL; // Matriz de distâncias (int)
bool *visited = NULL; // Array de cidades visitadas

// Função para encontrar a cidade mais próxima não visitada
int findNearest(int currentCity, int n);

// Algoritmo do Vizinho Mais Próximo
void nearestNeighbor(int startCity, int n, int *path, int *totalCost);


typedef struct cidades{
    int id;
    char nome[25];
} Cidades;

int main(){

    char S[512]; // String que receberá a linha lida pelo fgets()
    char *ptr; // Ponteiro que assumirá sunção de token para o strtok()
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
    fclose(file);

    int path[n + 1]; // Caminho a ser percorrido, +1 para incluir retorno à cidade inicial
    int totalCost = 0;
    visited = (bool*)malloc(sizeof(bool)*n);

    for (int i = 0; i < n; i++) {
        visited[i] = false; // Inicializa todas as cidades como não visitadas
    }

    nearestNeighbor(0, n, path, &totalCost); // Começa pela cidade 0

    printf("Custo total: %d\n", totalCost);
    printf("Caminho: ");
    for (int i = 0; i <= n; i++) {
        printf("%s ", cidades[path[i]].nome);
    }
    printf("\n");

    return 0;

}

int findNearest(int currentCity, int n) {
    int nearestCity = -1;
    int minDist = __INT_MAX__;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[currentCity][i] < minDist) {
            nearestCity = i;
            minDist = dist[currentCity][i];
        }
    }

    return nearestCity;
}

void nearestNeighbor(int startCity, int n, int *path, int *totalCost) {
    int currentCity = startCity;
    *totalCost = 0;

    for (int i = 0; i < n; i++) {
        path[i] = currentCity;
        visited[currentCity] = true;

        int nextCity = findNearest(currentCity, n);
        if (nextCity == -1) {
            *totalCost += dist[currentCity][startCity]; // Retorna à cidade inicial
            path[n] = startCity; // Completa o ciclo
            break;
        }

        *totalCost += dist[currentCity][nextCity];
        currentCity = nextCity;
    }
}