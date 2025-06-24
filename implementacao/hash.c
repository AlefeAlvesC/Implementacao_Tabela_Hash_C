#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "hash.h"
#include "lista_encad.h"
#define A 0.6180339887

int hash(const char chave[]){
    //Primeiro transforma a chave em número
    int k = 0; 
    for(int i = 0; chave[i] != '\0'; i++){
        //Levando em conta que a chave só contem letras maiusculas, diminui menos 65, pois é a posição de A na tabela ASCII e 26 elevado 5 menos i para a posição da letra na chave
        k += (chave[i]-65) * pow(26, 5 - i); //IMPORTANTE: essa funcao assume que a chave apenas tem letras maiusculas (A-Z)
    }
    
    //Pegando o mod de 1 de k*A. Como % não funciona direito com tipos double, fiz dessa forma para pegar o modulo
    double fracao = (k * A) - (int)(k * A);
    
    int index = (int)(TAMANHO_HASH * fracao);
    return index;
}

TabelaHash* criar_tabela_hash(){
    TabelaHash *tabela = (TabelaHash*) malloc(sizeof(TabelaHash));//Aloca memória para uma nova tabela hash
    
    for(int i = 0; i < TAMANHO_HASH; i++){//Inicializa cada ponteiro com NULL, para evitar acesso a lixo de memória 
        tabela->tabela_hash[i] = NULL;
    }
    
    return tabela;//Retorna o ponteiro com a memória alocada
}

bool inserir(TabelaHash* tabela, const char* chave, int valor){
    if(!tabela)//Verifica se o ponteiro para a tabla é valido
        return false;

    int index = hash(chave);//Salva o index da tabela em que o novo item será inserido
    Lista* l;
    
    if(tabela->tabela_hash[index] == NULL){//Verifica se é o primeiro item a ser inserido, se for cria uma lista
        l = lista_cria();
        tabela->tabela_hash[index] = l;
    }else{//Se não apenas reutiliza o lista já criada
        l = tabela->tabela_hash[index];
    }
    
    Viagem novo;//Cria um novo elemento viagem que deve ser inserido na lista
    strcpy(novo.chave, chave);
    novo.codigo = valor;
    
    if(lista_insere(l, novo)){//Caso a inserção ocorra corretamente retorna true, caso não retorna false
        return true;
    }else{ 
        
        return false;
    }
}

int* buscar(TabelaHash* tabela, const char* chave){
    int index = hash(chave);//Salvamos o index da posição da hash que buscuremos o informação
    int *valor = lista_busca(tabela->tabela_hash[index], chave);//Realizamos a busca na lista 

    //Verificamos se o valor retornado da busca é valido
    if(valor == NULL)
        return NULL;
    else
        return valor;
}

int buscar_todas(TabelaHash* tabela, const char* chave) {
    if (!tabela) return 0;

    int index = hash(chave); //Calculamos o indice da chave na tabela hash
    return lista_busca_todas(tabela->tabela_hash[index], chave); // Chamamos a lista_busca_todas para buscar e imprimir todas as ocorrencias da chave
    // o valor retorno é as ocorrencias encontradas
}

bool remover(TabelaHash* tabela, const char* chave){
    if(!tabela)//Verifica se o ponteiro para a tabela é valida, caso não retorna
        return false;

    int index = hash(chave);//Salva a posição da tabela onde o item procurado esta
    if(lista_remove(tabela->tabela_hash[index], chave))//Retorna true caso a remoção tenha ocorrido com sucesso e false caso não
        return true;
    else
        return false;
}

bool remover_por_chave_valor(TabelaHash* tabela, const char* chave, int codigo) { //retira um item especifico da tabela hash com base na chave e no codigo
    if (!tabela)
        return false;

    int index = hash(chave); //pega o indice da chave na tabela
    if (tabela->tabela_hash[index] == NULL)
        return false;

    //chama a funcao para remover especificamente da lista
    return lista_remove_por_chave_valor(tabela->tabela_hash[index], chave, codigo);
}

void imprimir_tabela(TabelaHash* tabela){
    if(!tabela)//Verifica se o ponteiro para a tabela é valido, no caso diferente de NULL
        return;
    printf("--- Imprimindo TABELA HASH ---\n");
    for(int i = 0; i < TAMANHO_HASH; i++){//Percorre a hash
        Lista* l = tabela->tabela_hash[i];//Acessa lista da vez a ser imprimida
        if(l != NULL && !lista_vazia(l)){ //Faz a verificacao se a lista existe e não está vazia
            printf("\nImprimindo itens na posicao %d da tabela:\n", i);
            lista_imprime(l);//Chama a função da lista para imprimir seus elementos
        }
    }
}

void liberar_tabela(TabelaHash* tabela){
    if(tabela == NULL)//Verifica se o ponteiro para tabela é null e retorna caso seja
        return;

    for(int i = 0; i < TAMANHO_HASH; i++){//Percorre a hash e chama a função libera_lista para liberar cada lista individualmente
        lista_libera(tabela->tabela_hash[i]);
    }

    free(tabela);//Por fim libera a estrutura tabela
}

bool chave_valida(const char *chave) { //Verifica se a chave apenas tem letras (A-Z)
    for (int i = 0; chave[i] != '\0'; i++) {
        if (!isalpha(chave[i])) {
            return false;
        }
    }
    return true;
}

void normalizar_chave(char *chave) { //converte a chave para letras maiusculas
    for (int i = 0; chave[i] != '\0'; i++) {
        chave[i] = toupper((unsigned char)chave[i]);
    }
}