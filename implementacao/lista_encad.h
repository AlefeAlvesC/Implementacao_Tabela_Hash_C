//TAD de lista encadeada
#ifndef _LISTA_ENCAD_H_
#define _LISTA_ENCAD_H_
#define TAMANHO_MAX_CHAVE 6

//Tipos exportados:

//Struct para o ParChaveValor que deve ser guardado na tabela hash
typedef struct ParChaveValor{
    char chave[TAMANHO_MAX_CHAVE];
    int codigo;
}Viagem;

//Struct no_lista onde guardamos o ponteiro para o próximo nó e a informação do nó atual
typedef struct no_lista{
    struct no_lista *prox;
    Viagem info;
}No;

//Struct lista_encadeada, onde temos o total de itens da lista e ponteiro para o primeiro elemento na lista.
typedef struct lista_encadeada{
    No *header;
    int tam;
}Lista;

//Função para criar uma nova lista
//Essa função aloca memória para um ponteiro do tipo lista e o retorna
Lista *lista_cria();

//Função para inserir um novo elemento em uma lista
//Essa função recebe como parametro o ponteiro da lista e o valor que se deseja inserir nessa lista
void lista_insere(Lista *l, Viagem valor);

//Função para remover um elemento na lista
//Essa função recebe como parametro o ponteiro para um lista e o elemento que deve ser removido da lista
void lista_remove(Lista* l, const char* chave);

//Função para buscar um elemento na lista
//Essa função recebe o ponteiro da lista e chave que deve ser buscada, retornando assim o valor correspondente da chave
int *lista_busca(Lista* l, const char* chave);

//Função para imprimir todos os elementos presentes em uma lista
//Essa função recebe um ponteiro para uma lista e imprime todos os elementos dessa lista
void lista_imprime(Lista* l);

//Função para verificar se a lista esta vazia
//Essa função retorna 1 para lista vazia e 0 para lista não vazia
int lista_vazia(Lista* l);

//Função para liberar a memória alocada a uma lista
void lista_libera(Lista* l);

#endif