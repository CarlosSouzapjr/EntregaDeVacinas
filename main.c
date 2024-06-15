#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int **dist = NULL; // Matriz de distâncias (int)
bool *visitada = NULL; // Array de cidades visitada

typedef struct cidades{
    int id;
    char nome[25];
} Cidades;

// Função para ler o arquivo
int lerArquivo(FILE *file, Cidades* cidades, int n);

// Função para encontrar a cidade mais próxima não visitada
int encontraCidade(int cidadeAtual, int n);

// Algoritmo do Vizinho Mais Próximo
void cidadeProxima(int cidadeAtual, int n, int *path, int *distTotal, int nivel);


void permutar(int path[], int inicio, int n, int *distTotal, int bestPath[], int custoAtual);


int criarArquivo(Cidades* cidades, int tamanho, int *bestPath, int distancia);



int main(){

    int caso;
    int n;
    char arquivoName[50];
    FILE *file;
    Cidades* cidades;

    printf("Digit o numero do caso desejado:\n Modelo simples: 1\n Modelo do Maranhao: 2\n Modelo do Para: 3\n Inserir um diretorio diferente: 4\n");
    scanf("%d",&caso);

    switch (caso) {
        case 1:
            file = fopen("../casos/modelo_simples.csv", "r");
            n = 5;         // A linha da cidade atual
            break;
        case 2:
            file = fopen("../casos/br-maranhao.xlsx_-_Distancia_quilometros.csv", "r");
            n = 15;         // A linha da cidade atual
            break;
        case 3:
            file = fopen("../casos/br-para-Distancia_quilometros.csv", "r");
            n = 15;         // A linha da cidade atual
            break;
        case 4:
            printf("Digite o endereço do arquivo que deseja\n");
            scanf("%s", arquivoName);
            file = fopen(arquivoName,"r");
            printf("Digite o tamanho da matriz\n");
            scanf("%d",&n);
            break;
    }

    lerArquivo(file, cidades, n);
//    if((lerArquivo(file, cidades, n))==EXIT_FAILURE){
//        perror("Error opening file");
//        return EXIT_FAILURE;
//    }

    int path[n+1]; // Caminho a ser percorrido, +1 para incluir retorno à cidade inicial

    int distParcial = 0;
    visitada = (bool*)malloc(sizeof(bool) * n);

    for (int i = 0; i < n; i++) {
        visitada[i] = false; // Inicializa todas as cidades como não visitada
    }
    int bestPath[n];

    cidadeProxima(0, n, path, &distParcial,0); // Começa pela cidade 0

    printf("%d \n", distParcial);
    int distTotal = distParcial;
    for (int i = 0; i < n; i++) {
        path[i] = i;
    }
    permutar(path, 1, n, &distTotal, bestPath, 0);

    printf("Distancia total: %d\n", distTotal);
    printf("Caminho ótimo: ");
    for (int i = 0; i <= n; i++) {
        printf("%s ", cidades[bestPath[i]].nome);
    }
    printf("\n");

    printf("Caminho ótimo (id): ");
    for (int i = 0; i <= n; i++) {
        printf("%d ", cidades[bestPath[i]].id);
    }
    printf("\n");

    criarArquivo(cidades, n, bestPath, distTotal);

    return 0;

}

int lerArquivo(FILE *file, Cidades* cidades, int n){

    char S[512];          // String que receberá a linha lida pelo fgets()
    char *ptr;           // Ponteiro que assumirá sunção de token para o strtok()
    int linha = 0;    // Quantidade de cidades = tamanho da matriz

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    cidades = (Cidades*)malloc(sizeof(Cidades)*n);

    while (fgets(S, sizeof(S), file)) {     // Pega cada linha do arquivo
        static int flag_linha = 0;                       // Flag que indica a leitura da linha do nome das cidades

        if (flag_linha == 0){                           // Leitura do nome das cidade (string)

            S[strcspn(S, "\n")] = '\0';     // Remove o \n de fim de linha

            ptr = strtok(S, ",");
            ptr = strtok(NULL, ",");        // Pula a primeira coluna

            for (int k = 0; ptr != NULL; k++) {         // Itera sobre cada palavra da LINHA (string)
                strcpy(cidades[k].nome, ptr);
                cidades[k].id = k;

                printf("%s ", cidades[k].nome);
                ptr = strtok(NULL, ",");
                // n++;
            }
            printf("\n");
            flag_linha = 1;                               // Linha das cidades lida

            dist = (int**)malloc(sizeof(int*)*n);   // Define o tamanho da matriz de distancias (int)

            for(int i = 0; i < n; i++){                 // Define o tamanho dos vetores da matriz (int)
                dist[i] = (int*)malloc(sizeof(int)*n);
            }
        }
        else{               // Leitura das distâncias (int)

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
    fclose(file);
    printf("Tamanho: %d\n\n", n);
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

void permutar(int path[], int inicio, int n, int *distTotal, int bestPath[], int custoAtual){
    if (inicio == n) {
        int custoFinal = custoAtual + dist[path[n - 1]][path[0]]; // Custo final incluindo retorno à cidade inicial
        if (custoFinal < *distTotal) {
            *distTotal = custoFinal;
            for (int i = 0; i < n; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    for (int i = inicio; i < n; i++) {
        // Trocar
        int temp = path[inicio];
        path[inicio] = path[i];
        path[i] = temp;

        // Calcular o novo custo parcial
        int novoCusto = custoAtual + dist[path[inicio - 1]][path[inicio]];

        // Se o custo parcial for menor que o custo mínimo atual, continuar a permutação
        if (novoCusto < *distTotal) {
            permutar(path, inicio + 1, n, distTotal, bestPath, novoCusto);
        }

        // Desfazer a troca
        temp = path[inicio];
        path[inicio] = path[i];
        path[i] = temp;
    }
}

int criarArquivo(Cidades* cidades, int tamanho, int *bestPath, int distancia){
    const char *filename = "resultado.txt";
    FILE *resultado = fopen(filename, "w");

    if (resultado == NULL) {
        perror("Erro ao criar o arquivo de resultado%s\n");
        return EXIT_FAILURE;
    }

    char string[25];

    fprintf(resultado, "Caminho ótimo: "); // Caminho ótimo com o nome das cidades
    for(int i = 0; i < tamanho; i++){
        strcpy(string, cidades[bestPath[i]].nome);
        fprintf(resultado, string);
        fprintf(resultado, " => ");
    }
    fprintf(resultado, cidades[bestPath[0]].nome);

    fprintf(resultado,"\n");

    char id[5];

    fprintf(resultado, "Caminho ótimo (id): ");
    for(int i = 0; i < tamanho; i++){
        itoa(cidades[bestPath[i]].id, id, 10);
        fprintf(resultado, id);
        fprintf(resultado, " => ");
    }
    itoa(cidades[bestPath[0]].id, id, 10);
    fprintf(resultado, id);

    fprintf(resultado,"\n");

    fprintf(resultado, "Distância ótima: %d", distancia);
}