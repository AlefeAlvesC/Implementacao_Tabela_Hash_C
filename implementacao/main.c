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

    fp = fopen("viagens.txt", "r");//Reabro novamente o arquivo, para voltar ao começo

    for(int i = 0; i < 42; i++){//Novamente vou percorrer o arquivo
        fscanf(fp, "%s", chave);//Realizo a leitura da chave
        fscanf(fp, "%d", &cod);//Aqui realizo a leitura do codigo, apenas para passar para proxima linha, pois não utilizo este aqui
        printf("O codigo da chave %s eh %d e seu indice na tabela hash é: %d\n", chave, *buscar(tabela, chave), hash(chave));    
    }

    liberar_tabela(tabela);
    fclose(fp);
    return 0;
}