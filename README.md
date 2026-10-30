# TAD de Grafos em C

Implementação de uma TAD (Tipo Abstrato de Dados) de grafos na linguagem C, desenvolvida para praticar a implementação de estruturas de dados e estudar a representação computacional de grafos.

## Implementação

O grafo é representado por listas de adjacência. Os vértices são armazenados em uma lista duplamente encadeada, e cada vértice mantém uma lista de suas arestas incidentes.

Cada aresta é representada por um único objeto, referenciado nas listas de adjacência de seus dois extremos. A estrutura utiliza ponteiros para predecessores e sucessores, permitindo inserir e remover elementos sem percorrer as listas quando suas posições já são conhecidas.

A implementação é dividida em módulos para grafo, vértice e aresta, cada um com seus próprios tipos, interfaces e operações. A organização segue o princípio do ocultamento de informação, separando as interfaces públicas das representações internas das estruturas.

O grafo é não direcionado, não permite laços e admite arestas paralelas entre um mesmo par de vértices.

## Funcionalidades

- Inserção e remoção de vértices e arestas.
- Consulta da quantidade de vértices e arestas.
- Consulta do grau de um vértice.
- Busca de uma aresta entre dois vértices.
- Iteração sobre os vértices e as arestas do grafo.
- Iteração sobre as arestas incidentes a um vértice.
- Consulta dos extremos de uma aresta e do extremo oposto a um vértice.

## Análise Assintótica

Considere um grafo não direcionado \(G=(V,E)\), em que:

- \(n=|V|\): número de vértices;
- \(m=|E|\): número de arestas;
- \(\deg(v)\): grau do vértice \(v\).

As complexidades abaixo consideram as operações sobre elementos já identificados por seus ponteiros, salvo indicação em contrário.

### Complexidade Temporal

| Operação | Complexidade | Observações |
|---|---:|---|
| Criação do grafo | \(O(1)\) | Inicialização da estrutura. |
| Consulta do número de vértices | \(O(1)\) | Utiliza contador armazenado. |
| Consulta do número de arestas | \(O(1)\) | Utiliza contador armazenado. |
| Consulta do grau de um vértice | \(O(1)\) | O grau é mantido no vértice. |
| Inserção de vértice | \(O(1)\) | Inserção no início da lista global. |
| Inserção de aresta | \(O(1)\) | Pressupõe que os extremos já são conhecidos. |
| Busca de aresta entre \(u\) e \(v\) | \(O(\min\{\deg(u),\deg(v)\})\) | Percorre a lista de adjacência do extremo de menor grau. |
| Remoção de aresta | \(O(1)\) | Pressupõe que o ponteiro da aresta é conhecido. |
| Remoção de vértice \(v\) | \(O(\deg(v)+1)\) | Remove as arestas incidentes e o próprio vértice. |
| Criação de iterador de vértices | \(O(1)\) | Inicialização do iterador. |
| Avanço do iterador de vértices | \(O(1)\) | Avança um ponteiro. |
| Criação de iterador de arestas incidentes | \(O(1)\) | Inicialização na lista de adjacência. |
| Avanço do iterador de arestas incidentes | \(O(1)\) | Avança um ponteiro de encadeamento. |
| Percurso de todos os vértices | \(O(n)\) | Cada vértice é percorrido uma vez. |
| Percurso de todas as arestas incidentes a \(v\) | \(O(\deg(v)+1)\) | Percorre a lista de adjacência de \(v\). |
| Criação de iterador global de arestas | \(O(1)\) | Inicialização do iterador. |
| Percurso global de arestas | \(O(n+m)\) | Percorre as listas de adjacência, evitando contar
