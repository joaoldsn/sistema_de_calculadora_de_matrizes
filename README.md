# Calculadora de Matrizes em C

## Objetivo

Desenvolver um sistema em linguagem C para realizar operações matemáticas com duas ou mais matrizes.

## Funcionalidades

- Cadastro de duas ou mais matrizes.
- Leitura de linhas, colunas e elementos.
- Adição de matrizes.
- Subtração de matrizes.
- Multiplicação de matrizes.
- Divisão matricial utilizando matriz inversa.
- Identificação de matrizes singulares.
- Validação dos dados informados.
- Menu interativo.

## Arquivos do projeto

- `main.c`: controla o funcionamento do programa.
- `matrizes.c`: contém as funções de leitura, validação, exibição e operações matemáticas.
- `matrizes.h`: contém a estrutura das matrizes e as declarações das funções.

## Compilação

Com o GCC instalado, execute no terminal:

```bash
gcc -Wall -Wextra -std=c11 main.c matrizes.c -o calculadora -lm
Execução
No Linux:


bash
./calculadora
No Windows:


bash
calculadora.exe
Funções implementadas
validarDimensao(): valida as dimensões das matrizes.

validarQuantidade(): valida a quantidade de matrizes.

validarOpcao(): valida as opções do menu.

lerInteiro() e lerReal(): realizam a leitura dos dados.

lerMatriz(): cadastra uma matriz.

mostrarMatriz(): exibe uma matriz.

somar(): realiza a adição.

subtrair(): realiza a subtração.

multiplicar(): realiza a multiplicação.

inversa(): calcula a matriz inversa pelo método de Gauss-Jordan.

dividir(): realiza a divisão matricial.

menu(): apresenta as opções do sistema.

Exemplo de utilização
Matriz A:


text
1  2
3  4
Matriz B:


text
5  6
7  8
Selecionando a opção 1 - Adição, o resultado será:


text
6   8
10  12
O usuário poderá realizar novas operações ou encerrar o programa selecionando a opção 0.

Tecnologias utilizadas
Linguagem C.

Compilador GCC.

Biblioteca padrão do C.

Biblioteca matemática math.h.

Projeto desenvolvido para a atividade de Desenvolvimento de Algoritmos e Pensamento Computacional.
