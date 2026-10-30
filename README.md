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

As complexidades abaixo pressupõem que os elementos necessários já foram identificados por seus ponteiros, salvo indicação em contrário.

### Complexidade Temporal

| Operação | Complexidade | Observações |
|---|---|---|
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
| Percurso global de arestas | \(O(n+m)\) | Percorre as listas de adjacência e evita contar cada aresta duas vezes. |
| Destruição do grafo | \(O(n+m)\) | Remove todos os vértices e arestas. |

**Observação sobre os iteradores:** o percurso global de arestas possui complexidade \(O(n+m)\) para uma travessia completa. Não se deve atribuir automaticamente complexidade \(O(1)\) de pior caso a cada chamada de avanço, pois o iterador pode precisar ignorar arestas já visitadas.

### Complexidade Espacial

| Estrutura | Complexidade espacial |
|---|---|
| Grafo completo | \(O(n+m)\) |
| Lista global de vértices | \(O(n)\) |
| Objetos de vértice | \(O(n)\) |
| Objetos de aresta | \(O(m)\) |
| Referências às arestas nas listas de adjacência | \(O(m)\) |
| Iterador individual | \(O(1)\) |

A representação utiliza espaço \(O(n+m)\). Cada vértice e cada aresta são armazenados em um único objeto, embora cada aresta seja referenciada nas listas de adjacência de seus dois extremos.

Para grafos esparsos, nos quais \(m=O(n)\), o espaço ocupado é \(O(n)\). Para grafos densos, nos quais \(m=\Theta(n^2)\), o espaço ocupado é \(O(n^2)\).

## Considerações sobre a Complexidade

A análise assintótica depende das condições em que cada operação é executada.

- **Inserção de aresta:** a complexidade \(O(1)\) pressupõe que os ponteiros dos vértices extremos já são conhecidos. A busca prévia desses vértices não está incluída.
- **Remoção de aresta:** a complexidade \(O(1)\) pressupõe que o ponteiro da aresta já está disponível.
- **Busca de aresta:** a complexidade considera os ponteiros dos vértices de entrada e o percurso da lista de adjacência de menor grau.
- **Remoção de vértice:** o custo depende do grau do vértice, pois todas as suas arestas incidentes precisam ser removidas.
- **Iterador global de arestas:** a implementação utiliza marcas de visita nas arestas para evitar retorná-las mais de uma vez. Esse mecanismo depende do estado do campo de visita e deve ser considerado ao realizar percursos sucessivos ou simultâneos.

As complexidades apresentadas são limites assintóticos para as operações descritas, e não garantias de tempo real de execução.

## Objetivo

Estudar a representação e a manipulação computacional de grafos, praticar a implementação de tipos abstratos de dados e aprofundar os conhecimentos em estruturas de dados e programação em C.

A implementação também serve de base para estudar algoritmos sobre grafos, incluindo busca em profundidade (DFS), busca em largura (BFS), caminhos mínimos e árvores geradoras mínimas (MST).

## Compilação

Considerando um arquivo `main.c` que utiliza a TAD, a compilação pode ser realizada com:

```bash
gcc -Wall -Wextra -Wpedantic -std=c11 -g \
    main.c grafo.c vertice.c aresta.c -o grafos
```

Para executar o programa:

```bash
./grafos
```

## Estrutura dos Módulos

- `grafo.h` / `grafo.c`: interface pública e implementação das operações do grafo.
- `vertice.h` / `vertice.c`: interface e implementação das operações sobre vértices.
- `aresta.h` / `aresta.c`: interface e implementação das operações sobre arestas.

## Tecnologias

- Linguagem C
- Padrão C11
- Listas duplamente encadeadas
- Listas de adjacência
- Ocultamento de informação e modularização
