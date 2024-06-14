#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int **dist = NULL; // Matriz de distâncias (int)
bool *visitada = NULL; // Array de cidades visitada

// Função para encontrar a cidade mais próxima não visitada
int encontraCidade(int cidadeAtual, int n);

// Algoritmo do Vizinho Mais Próximo
void cidadeProxima(int cidadeInicial, int n, int *path, int *distTotal, int nivel);


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

    file = fopen("../casos/br-maranhao.xlsx_-_Distancia_quilometros (1).csv", "r");

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
    int distTotal = 0;
    visitada = (bool*)malloc(sizeof(bool) * n);

    for (int i = 0; i < n; i++) {
        visitada[i] = false; // Inicializa todas as cidades como não visitada
    }

    cidadeProxima(0, n, path, &distTotal,0); // Começa pela cidade 0
    printf("Distancia total: %d\n", distTotal);
    printf("Caminho: ");
    for (int i = 0; i <= n; i++) {
        printf("%s ", cidades[cidades[path[i]].id].nome);
    }
    printf("\n");

    return 0;

}

int encontraCidade(int cidadeAtual, int n) {
    int cidadeMaisProxima = -1;
    int minDist = __INT_MAX__;

    for (int i = 0; i < n; i++) {
        if (!visitada[i] && dist[cidadeAtual][i] < minDist) {
            cidadeMaisProxima = i;
            minDist = dist[cidadeAtual][i];
        }
    }

    return cidadeMaisProxima;
}

void cidadeProxima(int cidadeAtual, int n, int *path, int *distTotal, int nivel) {
    path[nivel] = cidadeAtual;
    visitada[cidadeAtual] = true;

    int proxCidade = encontraCidade(cidadeAtual, n);
    if (proxCidade == -1) {
        *distTotal += dist[cidadeAtual][path[0]]; // Retorna à cidade inicial
        path[nivel + 1] = path[0]; // Completa o ciclo
        return;
    }

    *distTotal += dist[cidadeAtual][proxCidade];
    cidadeProxima(proxCidade, n, path, distTotal, nivel + 1);
}