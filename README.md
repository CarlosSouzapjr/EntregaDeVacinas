
# Otimização de Entrega de Vacinas
Esse é um trabalho de _otimização_ realizado pelos estudantes [José Carlos Souza](https://github.com/CarlosSouzapjr), [Igor Khalil](https://github.com/IgorKhalil) e [Enrico Uchoa](https://github.com/lunn-inred) da _Universidade Federal do Maranhão_ na cadeira de _Linguagem de Programação_.

## 💻 Entendendo o Problema
O enunciado: Uma empresa de distribuição de vacinas precisa enviar um lote de vacinas para as 15 maiores cidades do Maranhão. O objetivo é minimizar a distância total percorrida, garantindo que todas as cidades recebam as vacinas o mais rápido possível. Há apenas um veículo disponível para realizar a entrega, e ele deve retornar à capital, São Luís, após a conclusão das entregas.


Nosso trabalho consiste em resolver um problema de otimização de _Entrega de Vacinas_ semelhante ao _Problema do Caixeiro Viajante_ (_traveling salesman problem_).

Nosso algoritmo tem o objetivo de _calcular o menor percurso possível de uma rota partindo de uma cidade inicial_, nesse caso São Luís, _retornando à ela sem passar pela mesma cidade mais de uma vez_.



Nós resolvemos esse problema de três maneiras diferentes (os códigos estão disponíveis em suas respectivas branchs):
- 1º [Algoritmo de força bruta (Brute force) com Branch N Bound](https://github.com/CarlosSouzapjr/EntregaDeVacinas/tree/BruteForce-BranchNBound)
- 2º [Algoritmo Guloso Nearest Neighbor](https://github.com/CarlosSouzapjr/EntregaDeVacinas/tree/Version-1)
- 3º [Algoritmo Brute Force com Branch N Bound e com Nearest Neighbor](https://github.com/CarlosSouzapjr/EntregaDeVacinas/tree/BranchNBound-Guloso)

Por fim, nosso código final consiste no Algoritmo Brute Force com Branch N Bound e com Nearest Neighbor, onde usamos a solução do algoritmo guloso como parâmetro de comparação para o algoritmo do Branch N Bound, otimizando o tempo do resultado da melhor solução adquirida.



## 📃Instruções

Crie o diretório output

    mkdir output 

Entre no diretório criado

    cd output

Compile o programa

    gcc -o main ../main.c

Inicie o arquivo main para rodar o código

    ./main

### Entradas
Casos:

    - 1 -> Modelo Simples
    - 2 -> Modelo Maranhão
    - 3 -> Modelo Pará
    - 4 -> Inserir um novo diretório

Os casos 1, 2 e 3 rodam o código para alguns casos predefinidos. Caso você escolha o caso 4, insira o arquivo na pasta "casos" em formato .csv e digite o caminho do diretório como no exemplo:
    
    ../casos/{nomeDoArquivo}.csv

Logo em seguida digite o tamanho da matriz (o mesmo número de cidades):

    Digite o tamanho da matriz: {inteiro}

### Saídas
Como saída, no terminal aparecerá a matriz importada junto com seu tamanho, por exemplo:

    Cidades,São Luís,Cidade A,Cidade B,Cidade C,Cidade D
    São Luís,0,100,150,200,250
    Cidade A,100,0,120,180,130
    Cidade B,150,120,0,160,210
    Cidade C,200,180,160,0,170
    Cidade D,250,130,210,170,0
    Tamanho: 5

Logo depois temos o resultado do algoritmo do Nearest Neighbor, como um resultado aproximado, e o algoritmo de Brute Force com Branch N Bound, como resultado definitivo, junto com a sequência das cidades do caminho percorrido e seus ids.

    Distancia aproximada: 800
    Distancia ótima: 710
    Caminho ótimo: São Luís Cidade A Cidade B Cidade C Cidade D São Luís
    Caminho ótimo (id): 0 1 2 3 4 0
## ℹInformações
- Arquitetura utilizada: _windows x86_64_

- Compilador: GCC

- Diretório ./main: Arquivo principal

- Diretório ./output: Diretório de saída do resultado do código
