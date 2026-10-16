# TAD de Grafos em C

Implementação de uma TAD de grafos na linguagem C, desenvolvida para praticar a implementação de estruturas de dados e estudar a representação computacional de grafos.

## Implementação

O grafo é representado por listas de adjacência. Os vértices são armazenados em uma lista duplamente encadeada, e cada vértice mantém uma lista de suas arestas incidentes.

A implementação é dividida em módulos para grafo, vértice e aresta, cada um com seus próprios tipos, interfaces e operações. A organização busca seguir o princípio do ocultamento de informação, separando as interfaces públicas das representações internas das estruturas.

O grafo é não direcionado e não permite laços, mas admite arestas paralelas entre um mesmo par de vértices.

## Funcionalidades

- Inserção e remoção de vértices e arestas.
- Consulta da quantidade de vértices e arestas.
- Consulta do grau de um vértice.
- Busca de arestas entre dois vértices.
- Iteração sobre os vértices e as arestas do grafo.
- Iteração sobre as arestas incidentes a um vértice.

## Objetivo

Estudar a representação e a manipulação computacional de grafos, praticar a implementação de tipos abstratos de dados (TADs) e aprofundar os conhecimentos em estruturas de dados e programação em C.

## Compilação

Considerando um arquivo `main.c` que utiliza a TAD, a compilação pode ser realizada com:

```bash
gcc -Wall -Wextra -std=c11 main.c grafo.c vertice.c aresta.c -o grafos
```
