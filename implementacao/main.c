#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    printf("8. Buscar ocorrencias de um elemento da tabela hash.\n");
    printf("9. Remover elementos através de um arquivo.\n");
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
        case 0://Finalizar programa
            liberar_tabela(tabela);
            printf("Finalizando programa.");
            return 0;
        case 1://Criar nova tabela
            if(tabela)//Libera a tabela, caso já exista
                liberar_tabela(tabela);
            tabela = criar_tabela_hash();//Aloca memoria a uma nova
            printf("A tabela hash foi criada com sucesso.\n");
            
            limpar_buffer();
            break;

        case 2://Inserir um novo elemento na tabela
            if (tabela == NULL) {//Verifica se já foi criada uma tabela
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            printf("Digite uma chave de até 6 caracteres para a viagem:\n");
            
            if (scanf("%s", chave) != 1) {//Tratamento caso ocorra erro na leitura
                printf("Erro na leitura da chave.\n");
                limpar_buffer();
                break;
            }

            normalizar_chave(chave);

            // Validar tamanho da chave
            if (strlen(chave) > 6) {
                printf("Chave muito grande! Máximo permitido: 6 caracteres.\n");
                limpar_buffer();
                break;
            }

            if (!chave_valida(chave)) {
                printf("Chave invalida! Use apenas letras (sem números ou símbolos).\n");
                limpar_buffer();
                break;
            }

            printf("Digite o código da viagem:\n");
            if (scanf("%d", &cod) != 1) {//Tratamento caso ocorra erro no leitura do codigo
                printf("Entrada inválida para o código.\n");
                limpar_buffer();
                break;
            }   

            if(inserir(tabela, chave, cod))//Verifica se a inserção ocorreu com sucesso
                printf("Inserção feita com sucesso.\n");
            else
                printf("Erro ao inserir, tente novamente.\n");

            limpar_buffer();

            break;
        case 3://Inserir elementos por um arquivo
            if (tabela == NULL) {//Verifica se já existe tabela criada
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            printf("Digite o nome do arquivo que contem os elementos:\n");
            if (scanf("%s", nome_arquivo) != 1) {//Tratamento caso ocorra erro na leitura do nome do arquivo
                printf("Erro ao ler o nome do arquivo.\n");
                limpar_buffer();
                break;
            }

            printf("Digite a quantidades de linhas desse arquivo.\n");
            if (scanf("%d", &linhas) != 1 || linhas <= 0) {//Tratamento caso ocorra erro na leitura do numero de linhas
                printf("Número de linhas inválido.\n");
                limpar_buffer();
                break;
            }

            fp = fopen(nome_arquivo, "r");
            if(!fp){//Tratamento caso ocorra erro quanto a existencia do arquivo
                printf("Erro ao abrir o arquivo '%s'. Verifique se o nome está correto e se o arquivo existe.\n", nome_arquivo);
                limpar_buffer();
                break;
            }
            
            int sucesso_inserir = 1;
            for(int i = 0; i < linhas; i++){//Forma de percorrer o arquivo, nesse caso, percorre a qtde de linhas informadas
                if (fscanf(fp, "%s %d", chave, &cod) != 2) { //Realizo a leitura da chave e do codigo e faz o tratamento caso exista um formato de entrada invalido  no arquivo
                    printf("Erro na leitura da linha %d do arquivo. Verificar se o formato esta certo. \n", i + 1);
                    sucesso_inserir = 0;
                    break;
                }
                
                normalizar_chave(chave);

                if (!chave_valida(chave)) {
                    printf("Chave invalida! Use apenas letras (sem números ou símbolos).\n");
                    sucesso_inserir = 0;
                    limpar_buffer();
                    break;
                }

                if(!inserir(tabela, chave, cod)){ //Insiro na tabela hash
                    printf("Erro ao inserir chave '%s' com codigo %d.\n", chave, cod);
                    sucesso_inserir = 0;
                    break;
                }
            }
            fclose(fp);//Fecho o arquivo
            
            if (sucesso_inserir) {
                printf("A inserção pelo arquivo feita com sucesso.\n");
            } else {
                printf("A inserção pelo arquivo interrompida em decorrencia de erro.\n");
            }

            limpar_buffer();
            break;
        case 4://Remove um elemento da tabela  hash
            if (tabela == NULL) {//Verifica se já existe uma tabela hash
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            printf("Digite uma chave do elemento que deseja remover:\n");
            if (scanf("%s", chave) != 1) {
                printf("Erro na leitura da chave.\n");
                limpar_buffer();
                break;
            }

            normalizar_chave(chave);

            if (!chave_valida(chave)) { //validar a chave inserida
                printf("Chave invalida! Use apenas letras (sem números ou símbolos).\n");
                limpar_buffer();
                break;
            }

            // Validar tamanho da chave
            if (strlen(chave) > 6) {
                printf("Chave muito grande! Máximo permitido: 6 caracteres.\n");
                limpar_buffer();
                break;
            }
        
            if(remover(tabela, chave))
                printf("Remoção feita com sucesso.\n");
            else
                printf("Erro ao remover, tente novamente.\n");
            limpar_buffer();
            break;
        
        case 5://Apaga todos os elementos da tabela hash
            if (tabela == NULL) {//Verifica se já existe uma tabela hash
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            liberar_tabela(tabela);
            tabela = criar_tabela_hash();

            printf("A tabela hash foi esvaziada com sucesso.\n");
            limpar_buffer();
            break;

        case 6://Imprime todas as ocorrencias de uma chave
            if (tabela == NULL) {
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            printf("Digite uma chave de até 6 caracteres para a viagem que deseja imprimir:\n");
            if (scanf("%s", chave) != 1) {
                printf("Erro na leitura da chave.\n");
                limpar_buffer();
                break;
            }

            normalizar_chave(chave);

            if (!chave_valida(chave)) { //validar a chave inserida
                printf("Chave invalida! Use apenas letras (sem números ou símbolos).\n");
                limpar_buffer();
                break;
            }

            // Validar tamanho da chave
            if (strlen(chave) > 6) {
                printf("Chave muito grande! Máximo permitido: 6 caracteres.\n");
                limpar_buffer();
                break;
            }
            
            int impressos = buscar_todas(tabela, chave);
            if (impressos = 0) {
                printf("Não foi possivel imprimir o elemento com a chave %s, nenhuma ocorrencia encontrada.\n", chave);
            }
            
            limpar_buffer();    
            break;
        case 7://Imprime todos os elementos presentes na tabela hash
            if (tabela == NULL) {
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            imprimir_tabela(tabela);
            limpar_buffer();
            break;
        case 8://Busca e mostra o total de ocorrencias de uma chave
            if (tabela == NULL) {
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            printf("Digite uma chave de até 6 caracteres para a viagem que deseja buscar:\n");
            if (scanf("%s", chave) != 1) {
                printf("Erro na leitura da chave.\n");
                limpar_buffer();
                break;
            }

            normalizar_chave(chave);

            if (!chave_valida(chave)) { //validar a chave inserida
                printf("Chave invalida! Use apenas letras (sem números ou símbolos).\n");
                limpar_buffer();
                break;
            }

            // Validar tamanho da chave
            if (strlen(chave) > 6) {
                printf("Chave muito grande! Máximo permitido: 6 caracteres.\n");
                limpar_buffer();
                break;
            }
            
            int total = buscar_todas(tabela, chave);
            if (total == 0) {
                printf("Nenhuma ocorrência encontrada para a chave '%s'.\n", chave);
            }else{
                printf("Total de ocorrências encontradas: %d\n", total);
            }
            
            limpar_buffer();
            break;
        case 9: // Remover elementos usando um arquivo
            if (tabela == NULL) {//Verifica se já existe tabela criada
                printf("Tabela não criada. Por favor, crie a tabela primeiro (opção 1).\n");
                limpar_buffer();
                break;
            }
            printf("Digite o nome do arquivo que contem os elementos a serem removidos:\n");
            if (scanf("%s", nome_arquivo) != 1) {//Tratamento caso ocorra erro na leitura do nome do arquivo
                printf("Erro ao ler o nome do arquivo.\n");
                limpar_buffer();
                break;
            }

            printf("Digite a quantidades de linhas desse arquivo.\n");
            if (scanf("%d", &linhas) != 1 || linhas <= 0) {//Tratamento caso ocorra erro na leitura do numero de linhas
                printf("Número de linhas inválido.\n");
                limpar_buffer();
                break;
            }

            fp = fopen(nome_arquivo, "r");
            if(!fp){//Tratamento caso ocorra erro quanto a existencia do arquivo
                printf("Erro ao abrir o arquivo '%s'. Verifique se o nome está correto e se o arquivo existe.\n", nome_arquivo);
                limpar_buffer();
                break;
            }
            
            int sucesso_remover = 1;
            for(int i = 0; i < linhas; i++){//Forma de percorrer o arquivo, nesse caso, percorre a qtde de linhas informadas
                if (fscanf(fp, "%s %d", chave, &cod) != 2) { //Realizo a leitura da chave e do codigo e faz o tratamento caso exista um formato de entrada invalido  no arquivo
                    printf("Erro na leitura da linha %d do arquivo. Verificar se o formato esta certo. \n", i + 1);
                    sucesso_remover = 0;
                    break;
                }

                normalizar_chave(chave);

                if (!chave_valida(chave)) { //validar a chave inserida
                    printf("Chave invalida! Use apenas letras (sem números ou símbolos).\n");
                    sucesso_remover = 0;
                    limpar_buffer();
                    break;
                }

                if(!remover_por_chave_valor(tabela, chave, cod)){ 
                    printf("Erro ao inserir chave '%s' com codigo %d.\n", chave, cod);
                    sucesso_remover = 0;
                    break;
                }
            }
            fclose(fp);//Fecho o arquivo
            
            if (sucesso_remover) {
                printf("A remocao por arquivo foi feita com sucesso.\n");
            } else {
                printf("A remocao por arquivo foi interrompida em decorrencia de erro.\n");
            }

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