# Projeto: Implementação de Tabela Hash em C (Estrutura de Dados 2)

## Breve Descrição do Projeto

Este projeto consiste na implementação de uma Tabela Hash em linguagem C, como atividade prática da disciplina **Estrutura de Dados 2**. A tabela funciona como um dicionário que realiza o mapeamento de **strings (chaves)** para **inteiros (valores)**, utilizando:

- **Função Hash pelo Método da Multiplicação**, adaptada para strings.
- **Tratamento de colisões via Encadeamento Separado (Separate Chaining)**, usando listas encadeadas.

O programa permite realizar as seguintes operações sobre a Tabela Hash:

- Inserir novos elementos.
- Buscar elementos por chave.
- Remover elementos.
- Imprimir o conteúdo da tabela.
- Inserção em lote via leitura de arquivo texto.

Toda a gestão de memória foi feita manualmente (uso de `malloc` e `free`), sem o uso de bibliotecas prontas de hashing.

## Instruções de Compilação e Execução

### Pré-requisitos

- Compilador C compatível com padrão **C99 ou C11** (exemplo: GCC ou Clang).
- Sistema operacional Linux, Windows ou Mac (qualquer ambiente que suporte GCC).

### Estrutura de Arquivos do Projeto

```
.
├── implementacao
    ├── hash.c
    ├── hash.h
    ├── lista_encad.c
    ├── lista_encad.h
    ├── main.c
    └── gerador_viagens.c
└── README.md
```

### Como Compilar o Projeto (usando GCC)

Abra o terminal na pasta onde estão os arquivos do projeto e execute o seguinte comando:

```bash
gcc main.c hash.c lista_encad.c -o hash -lm
```


No windows, execute:
```bash
gcc main.c hash.c lista_encad.c -o hash
```

### Como Executar o Programa

Após a compilação bem-sucedida, execute o programa com:

```bash
./hash
```

No Windows, execute:

```bash
./hash.exe
```
### Teste com Arquivo de Entrada (Opção 3 do Programa)

Antes de utilizar a opção 3 do programa para popular a tabela hash automaticamente, o usuário deve primeiro executar o código `gerador_viagens.c`, que é responsável por gerar o arquivo `viagens.txt` contendo as chaves e valores de exemplo.

Para compilar o gerador, execute:

```bash
gcc gerador_viagens.c -o gerador
```

E para rodá-lo:

```bash
./gerador
```

No Windows, execute:

```bash
./gerador.exe
```

Isso criará o arquivo `viagens.txt` na pasta do projeto.

Depois disso, ao rodar o programa principal e escolher a opção 3 do menu, siga as instruções:

```yaml
Nome do arquivo: viagens.txt
Número de linhas: 42 
```
O programa irá ler os 42 pares de chave-valor do arquivo ou a quantidade que você deseja e inseri-los na tabela hash.

💡 Observação:
O usuário pode editar o conteúdo do arquivo `viagens.txt` manualmente ou criar um arquivo com suas próprias viagens, desde que siga o formato esperado (uma chave e um valor por linha).

## Explicação da Função Hash (Método da Multiplicação)

A função hash utilizada neste projeto foi implementada com base no **Método da Multiplicação**, adaptado para trabalhar com strings.

### Etapas de Transformação da Chave (String) em Índice da Tabela

1. **Conversão da string para um valor numérico (k)**:

   - Cada caractere da string é convertido para seu valor na tabela ASCII.
   - Subtrai-se 65 de cada caractere, assumindo que as chaves são compostas apenas por letras maiúsculas (exemplo: 'A' vira 0, 'B' vira 1, etc.).
   - Cada caractere é ponderado com potências de 26 (base alfabética), com maior peso nas primeiras posições da string.
   - Exemplo:  
     Para a chave `"BELMAN"`, o cálculo de `k` é:

     ```
     k = (B-65)×26^5 + (E-65)×26^4 + (L-65)×26^3 + (M-65)×26^2 + (A-65)×26^1 + (N-65)×26^0
     ```

2. **Aplicação do Método da Multiplicação**:

   - A fórmula aplicada é:

     ```
     h(k) = floor(M * (k * A mod 1))
     ```

   - Onde:
     - `M` é o tamanho da tabela hash (neste caso: **127**).
     - `A` é uma constante fracionária: **(√5 - 1) / 2 ≈ 0.6180339887**.

3. **Resultado**:
   - O valor final é um índice inteiro dentro do intervalo `[0, M-1]`, que determina a posição na tabela hash onde o elemento será armazenado.

## Observações Importantes sobre a Implementação

- **Encadeamento Separado**:  
  Cada posição da tabela hash aponta para o início de uma **lista encadeada**, permitindo o armazenamento de múltiplos elementos no caso de colisões.

- **Tamanho Fixo da Tabela Hash**:  
  O tamanho da tabela foi definido como **127** (número primo), conforme a recomendação do trabalho para melhorar a dispersão dos índices.

- **Arquivos Separados (.h e .c)**:  
  O projeto está organizado com a devida separação de interface (arquivos `.h`) e implementação (arquivos `.c`), seguindo boas práticas de modularização.

- **Leitura de Arquivo**:  
  Incluímos uma opção no menu (opção 3) para ler e inserir múltiplos elementos a partir de um arquivo texto (`viagens.txt`), facilitando testes com grandes volumes de dados.

- **Liberação de Memória**:  
  Todos os espaços de memória alocados com `malloc()` são devidamente liberados com `free()` ao final do programa, evitando vazamentos de memória.

## Desafios Encontrados Durante o Desenvolvimento

Durante o processo de implementação, enfrentamos alguns desafios interessantes:

- **Colisões intencionais para testes**:  
  Construímos um conjunto de dados de example (no `viagens.txt`) que contém várias chaves com padrões semelhantes, forçando algumas colisões na tabela, para validar o funcionamento correto do encadeamento separado.

- **Gerenciamento correto de memória**:  
  Tivemos atenção especial para evitar memory leaks, especialmente na manipulação das listas encadeadas durante inserções, buscas e remoções.

- **Tratamento de entrada inválida**:  
  Foram feitas verificações básicas de erro (ex.: ponteiros nulos, falha de alocação de memória, arquivo não encontrado), garantindo maior robustez ao código.

## Créditos

Projeto desenvolvido por Álefe Alves (2023010253) , Leonardo Vinícius (2022009946), Andersson (2023010440) e Matheus Rebouças (2023010413), como parte da disciplina **Estrutura de Dados 2**, sob orientação do professor **Jean Bertrand**.
