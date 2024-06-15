#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int **dist = NULL; // Matriz de distâncias (int)

void permute(int path[], int start, int n, int *min_cost, int best_path[], int current_cost) {
    if (start == n) {
        int final_cost = current_cost + dist[path[n - 1]][path[0]]; // Custo final incluindo retorno à cidade inicial
        if (final_cost < *min_cost) {
            *min_cost = final_cost;
            for (int i = 0; i < n; i++) {
                best_path[i] = path[i];
            }
        }
        return;
    }

    for (int i = start; i < n; i++) {
        // Trocar
        int temp = path[start];
        path[start] = path[i];
        path[i] = temp;

        // Calcular o novo custo parcial
        int new_cost = current_cost + dist[path[start - 1]][path[start]];

        // Se o custo parcial for menor que o custo mínimo atual, continuar a permutação
        if (new_cost < *min_cost) {
            permute(path, start + 1, n, min_cost, best_path, new_cost);
        }

        // Desfazer a troca
        temp = path[start];
        path[start] = path[i];
        path[i] = temp;
    }
}


typedef struct cidades{
    int id;
    char nome[25];
} Cidades;

int main(){

    char S[512]; // String que receberá a linha lida pelo fgets()
    char *ptr; // Ponteiro que assumirá sunção de token para o strtok()
    int linha = 0; // A linha da cidade atual
    int n; // Quantidade de cidades = tamanho da matriz

    printf("Entre com o número de cidades: ");
    scanf("%d", &n);

    Cidades* cidades;


    FILE *file;

    file = fopen("../casos/br-para.xls - Distancia (quilometros).csv", "r");

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

    int path[n+1]; // Caminho a ser percorrido, +1 para incluir retorno à cidade inicial
    for (int i = 0; i < n; i++) { // Preenche o vetor com números diferentes entre si
        path[i] = i;
    }

    int distTotal = INT_MAX;

    int best_path[n];

    permute(path, 1, n, &distTotal, best_path, 0);

    printf("Distancia total: %d\n", distTotal);
    printf("Caminho: ");
    for (int i = 0; i <= n; i++) {
        printf("%s ", cidades[cidades[path[i]].id].nome);
    }
    printf("\n");

    return 0;

}
