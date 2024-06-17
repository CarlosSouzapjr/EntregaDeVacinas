# Otimização de Entrega de Vacinas
Esse é um trabalho de _otimização_ realizado pelos estudantes [José Carlos Souza](https://github.com/CarlosSouzapjr), [Igor Khalil](https://github.com/IgorKhalil) e [Enrico Uchoa](https://github.com/lunn-inred) da _Universidade Federal do Maranhão_ na cadeira de _Linguagem de Programação_.

## 💻 Entendendo o Problema
O enunciado: Uma empresa de distribuição de vacinas precisa enviar um lote de vacinas para as 15 maiores cidades do Maranhão. O objetivo é minimizar a distância total percorrida, garantindo que todas as cidades recebam as vacinas o mais rápido possível. Há apenas um veículo disponível para realizar a entrega, e ele deve retornar à capital, São Luís, após a conclusão das entregas.<br/>
<br/>
Nosso trabalho consiste em resolver um problema de otimização de _Entrega de Vacinas_ semelhante ao _Problema do Caixeiro Viajante_ (_traveling salesman problem_). <br/>
<br/>
Nosso algoritmo tem o objetivo de _calcular o menor percurso possível de uma rota partindo de uma cidade inicial_, nesse caso São Luís, _retornando à ela sem passar pela mesma cidade mais de uma vez_. <br/>
<br/>
Nós resolvemos esse problema de três maneiras diferentes (os códigos estão disponíveis em suas respectivas branchs):
1. [Algoritmo de força bruta (Brute force) com Branch N Bound](https://github.com/CarlosSouzapjr/EntregaDeVacinas/tree/BruteForce-BranchNBound)
2. [Algoritmo Guloso Nearest Neighbor](https://github.com/CarlosSouzapjr/EntregaDeVacinas/tree/Version-1)
3. [Algoritmo Brute Force com Branch N Bound e com Nearest Neighbor](https://github.com/CarlosSouzapjr/EntregaDeVacinas/tree/BranchNBound-Guloso)




