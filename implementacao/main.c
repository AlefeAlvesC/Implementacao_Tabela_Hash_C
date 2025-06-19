#include <stdio.h>
#include "hash.h"

int main(){
    
    TabelaHash *tabela = criar_tabela_hash();
    inserir(tabela, "BELMAN", 161714);
    inserir(tabela, "BELPAL", 141312);
    inserir(tabela, "MANBEL", 345382);
    inserir(tabela, "MANBOA", 246790);
    inserir(tabela, "MANMAC", 162984);

    
    char *test[5];
    test[0] = "BELMAN";
    test[1] = "BELPAL";
    test[2] = "MANBEL";
    test[3] = "MANBOA";
    test[4] = "MANMAC";

    for(int i = 0; i < 5; i++){
        printf("O codigo da chave %s eh %d e seu indice na tabela hash é: %d\n", test[i], *buscar(tabela, test[i]), hash(test[i]));    
    }
    return 0;
}