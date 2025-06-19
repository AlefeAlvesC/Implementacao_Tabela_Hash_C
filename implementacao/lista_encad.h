//TAD de lista encadeada

//Tipos exportados:

//Struct no_lista onde guardamos o ponteiro para o próximo nó e a informação do nó atual
typedef struct no_lista{
    struct no_lista *prox;
    int info;
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
void lista_insere(Lista *l, int valor);

//Função para remover um elemento na lista
//Essa função recebe como parametro o ponteiro para um lista e o elemento que deve ser removido da lista
void lista_remove(Lista* l, int valor);

//Função para verificar se a lista esta vazia
//Essa função retorna 1 para lista vazia e 0 para lista não vazia
int lista_vazia(Lista* l);

//Função para liberar a memória alocada a uma lista
void lista_libera(Lista* l);