#include <stdio.h>
#include <stdlib.h>
#include "lista_encad.h"
#include "hash.h"

void menu(){
    printf ("\n----Testando implementação da nossa TABELA HASH----\n");
    printf("1. Criar uma nova tabela hash.\n");
    printf("2. Inserir um novo elemento na tabela.\n");
    printf("3. Inserir novos elementos através de um arquivo.\n");
    printf("4. Remover um elemento da tabela hash.\n");
    printf("5. Apagar todos elementos da tabela hash.\n");
    printf("6. Imprimir um elemento da tabela hash.\n");
    printf("7. Imprimir todos elementos da tabela hash.\n");
    printf("8. Busca um elemento da tabela hash.\n");
    printf("0. Sair.\n");
    printf("Escolha uma das opções.\n");
}

void limpar_buffer() {
    printf("\nPressione enter tecla para continuar...\n");
    getchar();
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(){

    TabelaHash *tabela = NULL;
    FILE *fp;
    char nome_arquivo[30];//Variavel para o nome do arquivo
    int linhas;
    char chave[7];//Variavel de leitura para as chaves
    int cod;//Variavel de leitura para o codigo das chaves
    char enter[30];
    while(1){
        menu();
        int opcao;
        scanf("%d", &opcao);

        switch (opcao){
        case 0:
            liberar_tabela(tabela);
            printf("Finalizando programa.");
            return 0;
        case 1:
            if(tabela)
                liberar_tabela(tabela);
            tabela = criar_tabela_hash();
            printf("A tabela hash foi criada com sucesso.\n");
            
            limpar_buffer();
            break;

        case 2:
            printf("Digite uma chave de até 6 caracteres para a viagem:\n");
            scanf("%s", chave);
            printf("Digite o código da viagem:\n");
            scanf("%d", &cod);    

            if(inserir(tabela, chave, cod))
                printf("Inserção feita com sucesso.\n");
            else
                printf("Erro ao inserir, tente novamente.\n");

            limpar_buffer();

            break;
        case 3:
            printf("Digite o nome do arquivo que contem os elementos:\n");
            scanf("%s", nome_arquivo);
            printf("Digite a quantidades de linhas desse arquivo.\n");
            scanf("%d", &linhas);
            fp = fopen(nome_arquivo, "r");
            if(!fp){
                printf("Erro ao fazer leitura do arquivo, tente novamente.\n");
                limpar_buffer();
                break;
            }
            
            for(int i = 0; i < linhas; i++){//Forma de percorrer o arquivo, nesse caso, percorro as 42 linhas dele
                fscanf(fp, "%s", chave);//Realizo a leitura da chave
                fscanf(fp, "%d", &cod);//Realizo a leitura do codigo
                inserir(tabela, chave, cod);//Insiro na tabela hash
            }
            fclose(fp);//Fecho o arquivo
            
            printf("A inserção pelo arquivo feita com sucesso.\n");
            limpar_buffer();
            break;
        case 4:
            printf("Digite uma chave do elemento que deseja remover:\n");
            scanf("%s", chave);
        
            if(remover(tabela, chave))
                printf("Remoção feita com sucesso.\n");
            else
                printf("Erro ao remover, tente novamente.\n");
            limpar_buffer();
            break;
        
        case 5:
            liberar_tabela(tabela);
            tabela = criar_tabela_hash();

            printf("A tabela hash foi esvaziada com sucesso.\n");
            limpar_buffer();
            break;

        case 6:
            printf("Digite uma chave de até 6 caracteres para a viagem que deseja imprimir:\n");
            scanf("%s", chave);
            
            int *valor = buscar(tabela, chave);
            if(valor)
                printf("A chave %s tem codigo %d.\n", chave, *valor);
            else
                printf("Não foi possivel imprimir o elemento com a chave informada, tente novamente.\n");
            
            limpar_buffer();    
            break;
        case 7:
            imprimir_tabela(tabela);
            limpar_buffer();
            break;
        case 8:
            printf("Digite uma chave de até 6 caracteres para a viagem que deseja buscar:\n");
            scanf("%s", chave);
            
            int *busca_val = buscar(tabela, chave);
            if(busca_val)
                printf("A chave %s tem codigo %d.\n", chave, *busca_val);
            else
                printf("Não foi possivel buscar o elemento com a chave informada, tente novamente.\n");
            
            limpar_buffer();
            break;
        default:
            printf("Opção inválida, por favor escolha novamente.\n");
            limpar_buffer();
            break;
        }
        
    }
    
    return 0;
}