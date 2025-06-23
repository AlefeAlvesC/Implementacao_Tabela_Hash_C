#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_LINHAS 1000

int main() {
    const char* capitais[] = {"BEL", "MAN", "PAL", "BOA", "RIO", "MAC", "POR"};
    const int n = sizeof(capitais) / sizeof(capitais[0]);
    FILE* arquivo = fopen("viagens.txt", "w");

    if (!arquivo) {
        perror("Erro ao criar o arquivo viagens.txt");
        return 1;
    }

    srand(time(NULL)); //inicializa o gerador de números aleatórios

    int codigo = 100001;
    for (int i = 0; i < TOTAL_LINHAS; i++) {
        int origem = rand() % n;
        int destino;

        //permite que origem seja diferente do destino
        do {
            destino = rand() % n;
        } while (destino == origem);

        fprintf(arquivo, "%s%s\t%d\n", capitais[origem], capitais[destino], codigo++);
    }

    fclose(arquivo);
    printf("Arquivo viagens.txt com %d registros gerado com sucesso.\n", TOTAL_LINHAS);
    return 0;
}
