#include <stdio.h>
#include <stdlib.h>
#include "lista_encad.h"
#include "hash.h"

int main(){
    
    TabelaHash *tabela = criar_tabela_hash();
    FILE *fp;//Ponteiro para o arquivo
    fp = fopen("viagens.txt", "r");
    char chave[7];//Variavel de leitura para as chaves
    int cod;//Variavel de leitura para o codigo das chaves

    for(int i = 0; i < 42; i++){//Forma de percorrer o arquivo, nesse caso, percorro as 42 linhas dele
        fscanf(fp, "%s", chave);//Realizo a leitura da chave
        fscanf(fp, "%d", &cod);//Realizo a leitura do codigo
        inserir(tabela, chave, cod);//Insiro na tabela hash
    }
    fclose(fp);//Fecho o arquivo

    
    imprimir_tabela(tabela);


    liberar_tabela(tabela);
    return 0;
}