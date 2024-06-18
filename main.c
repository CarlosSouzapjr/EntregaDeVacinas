#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


int **dist = NULL; // Matriz de distâncias (int)
bool *visitada = NULL; // Array de cidades visitada

typedef struct cidades{ // Estrutura cidade que armazena seu respectivo nome e endereço na matriz principal
    int id;
    char nome[25];
} Cidades;

// Função para ler o arquivo
int lerArquivo(FILE *file, Cidades* cidades, int n);

// Função para encontrar a cidade mais próxima não visitada
int encontraCidade(int cidadeAtual, int n);

// Algoritmo do Vizinho Mais Próximo
void cidadeProxima(int cidadeAtual, int n, int *path, int *distTotal, int nivel);

// Função para gerar todas as permutações do problema TSP (Algoritmo força bruta)
void permutar(int path[], int inicio, int n, int *distTotal, int custoAtual);

// Cria o arquivo "resultado.txt" que armazena o caminho ótimo
int criarArquivo(Cidades* cidades, int tamanho, int *bestPath, int distancia);



int main(){

    /*  Declaração inicial de variáveis  */
    int caso;
    int n;
    char arquivoName[50];
    FILE *file;
    Cidades* cidades;

    /*  Mecanismo de escolha de caso  */

    printf("Casos:\n - Modelo simples: 1\n - Modelo do Maranhao: 2\n - Modelo do Para: 3\n - Inserir um diretorio diferente: 4\nDigite o caso desejado: ");
    scanf("%d",&caso);
    printf("\n");

    switch (caso) {
        case 1:
            file = fopen("../casos/modelo_simples.csv", "r");
            n = 5;         // A linha da cidade atual
            break;
        case 2:
            file = fopen("../casos/br-maranhao Distancia (quilometros).csv", "r");
            n = 15;         // A linha da cidade atual
            break;
        case 3:
            file = fopen("../casos/br-para.xls - Distancia (quilometros).csv", "r");
            n = 15;         // A linha da cidade atual
            break;
        case 4:
            printf("Digite o endereço do arquivo que deseja:\n");
            scanf("%s", arquivoName);
            file = fopen(arquivoName,"r");
            printf("Digite o tamanho da matriz:\n");
            scanf("%d",&n);
            break;
    }

    cidades = (Cidades*)malloc(sizeof(Cidades)*n); // Alocação dinâmica para o vetor cidades do tipo Cidades

    visitada = (bool*)malloc(sizeof(bool) * n);

    if (visitada == NULL || cidades == NULL || n<1){
        perror("Erro ao alocar memoria.");
        return EXIT_FAILURE;
    }

    if(lerArquivo(file, cidades, n) == EXIT_FAILURE){ // Chama a função para ler os arquivos
        perror("Erro ao encontrar o arquivo.");
        return EXIT_FAILURE;
    }


    int path[n+1]; // Caminho a ser percorrido, +1 para incluir retorno à cidade inicial

    int distParcial = 0;

    for (int i = 0; i < n; i++) {
        visitada[i] = false; // Inicializa todas as cidades como não visitada
    }

    
    cidadeProxima(0, n, path, &distParcial,0); // Começa pela cidade 0

    int distTotal = distParcial; // A variável de distância total recebe o resultado do Nearest Neighbor para servir de parâmetro comparativo para o resultado preciso

    printf("Distancia aproximada: %d\n", distParcial); // Imprime o resultado do algoritmo Nearest Neighbor

    printf("Calculando distância ideal...\n");


    permutar(path, 1, n, &distTotal, 0);  // Inicia a permutação com o parâmetro de comparativo sendo o valor aproximado obtido pelo Nearest Neighbor

    /*  Impressão no terminal dos resultados */


    printf("Distancia ótima: %d\n", distTotal);
    printf("Caminho ótimo: ");
    for (int i = 0; i <= n; i++) {
        printf("%s ", cidades[path[i]].nome);
    }
    printf("\n");

    printf("Caminho ótimo (id): ");
    for (int i = 0; i <= n; i++) {
        printf("%d ", cidades[path[i]].id);
    }

    printf("\n\n");

    /*  Mecanismo de escolha do salvamento do resultado em um arquivo txt  */
    printf("Voce deseja salvar este resultado? (y/n): ");
    char resposta[5];

    scanf("%s",resposta);

    if (!strcmp(resposta,"Y") || !strcmp(resposta,"y")){
        criarArquivo(cidades, n, path, distTotal);
    }

    for(int i=0;i<n;i++) free(dist[i]);
    free(dist);
    free(visitada);
    free(cidades);


    return 0;
}

int lerArquivo(FILE *file, Cidades* cidades, int n){

    char S[512];          // String que receberá a linha lida pelo fgets()
    char *ptr;           // Ponteiro que assumirá sunção de token para o strtok()
    int linha = 0;      // Indice de linha da matriz dist (matriz de inteiros)

    if (file == NULL) {
        return EXIT_FAILURE;
    }



    while (fgets(S, sizeof(S), file)) {         // Pega cada linha do arquivo
        static int flag_linha = 0;             // Flag que indica a leitura da linha do nome das cidades

        if (flag_linha == 0){                // Leitura do nome das cidade (string)

            S[strcspn(S, "\n")] = '\0';     // Remove o \n de fim de linha

            ptr = strtok(S, ",");
            ptr = strtok(NULL, ",");        // Pula a primeira coluna

            for (int k = 0; ptr != NULL; k++) {         // Itera sobre cada palavra da LINHA (string)
                strcpy(cidades[k].nome, ptr);
                cidades[k].id = k;

                printf("%s ", cidades[k].nome);
                ptr = strtok(NULL, ",");

            }
            printf("\n");
            flag_linha = 1;                             // Linha das cidades lida

            dist = (int**)malloc(sizeof(int*)*n);       // Define o tamanho da matriz de distancias (int)

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

void permutar(int path[], int inicio, int n, int *distTotal, int custoAtual){
    if (inicio == n) {
        int custoFinal = custoAtual + dist[path[n - 1]][path[0]]; // Custo final incluindo retorno à cidade inicial
        if (custoFinal < *distTotal) {
            *distTotal = custoFinal;
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
            permutar(path, inicio + 1, n, distTotal, novoCusto);
        }

        // Desfazer a troca para testar as próximas permutações
        temp = path[inicio];
        path[inicio] = path[i];
        path[i] = temp;
    }
}

int criarArquivo(Cidades* cidades, int tamanho, int *bestPath, int distancia){
    const char *filename = "./resultado.txt";
    FILE *resultado = fopen(filename, "w");

    char string[25];

    fprintf(resultado, "Caminho ótimo: "); // Caminho ótimo com o nome das cidades
    for(int i = 0; i < tamanho; i++){
        strcpy(string, cidades[bestPath[i]].nome);
        fprintf(resultado, string);
        fprintf(resultado, " => ");
    }
    fprintf(resultado, cidades[bestPath[0]].nome);

    fprintf(resultado,"\n");

    int id;

    fprintf(resultado, "Caminho ótimo (id): ");
    for(int i = 0; i < tamanho; i++){
        id = cidades[bestPath[i]].id;
        fprintf(resultado,"%d", id);
        fprintf(resultado, " => ");
    }
    id = cidades[bestPath[0]].id;
    fprintf(resultado, "%d", id);

    fprintf(resultado,"\n");

    fprintf(resultado, "Distância ótima: %d", distancia);

    return 0;
}
