#include <stdio.h>
#include "matrizes.h"

int main() {

    Matriz matrizes[MAX], resultado, auxiliar;

    int quantidade;
    int opcao;
    int i;
    int sucesso;
    int continuar = 1;

    printf("====================================\n");
    printf("     CALCULADORA DE MATRIZES\n");
    printf("====================================\n");

    /* Cadastro da quantidade de matrizes */
    while (1) {

        if (!lerInteiro(
            "\nQuantas matrizes deseja cadastrar? ",
            &quantidade)) {

            printf("\nEntrada encerrada.\n");
            return 0;
        }

        if (validarQuantidade(quantidade))
            break;

        printf("Informe uma quantidade entre 2 e %d.\n", MAX);
    }

    /* Cadastro das matrizes */
    for (i = 0; i < quantidade; i++) {

        if (!lerMatriz(&matrizes[i], i + 1)) {

            printf("\nEntrada encerrada durante o cadastro.\n");
            return 0;
        }
    }

    /* Menu e execucao das operacoes */
    while (continuar) {

        menu();

        if (!lerInteiro("Escolha uma opcao: ", &opcao)) {

            printf("\nEntrada encerrada.\n");
            break;
        }

        if (!validarOpcao(opcao)) {

            printf("\nOpcao invalida! Escolha de 0 a 4.\n");
            continue;
        }

        if (opcao == 0) {

            printf("\nPrograma encerrado!\n");
            continuar = 0;
            continue;
        }

        /* Comeca pela primeira matriz */
        resultado = matrizes[0];
        sucesso = 1;

        /* Executa as operacoes em sequencia */
        for (i = 1; i < quantidade; i++) {

            switch (opcao) {

                case 1:
                    sucesso = somar(
                        resultado,
                        matrizes[i],
                        &auxiliar
                    );
                    break;

                case 2:
                    sucesso = subtrair(
                        resultado,
                        matrizes[i],
                        &auxiliar
                    );
                    break;

                case 3:
                    sucesso = multiplicar(
                        resultado,
                        matrizes[i],
                        &auxiliar
                    );
                    break;

                case 4:
                    sucesso = dividir(
                        resultado,
                        matrizes[i],
                        &auxiliar
                    );
                    break;
            }

            /* Interrompe se ocorrer algum erro */
            if (sucesso != 1)
                break;

            resultado = auxiliar;
        }

        /* Apresenta o resultado */
        if (sucesso == 1) {

            printf("\n========== RESULTADO ==========\n");

            mostrarMatriz(resultado);

            printf("===============================\n");

        } else {

            printf("\nNAO FOI POSSIVEL REALIZAR A OPERACAO.\n");

            if (opcao == 4) {

                if (sucesso == -1) {
                    printf("Erro: a matriz divisora nao e quadrada.\n");
                }
                else if (sucesso == -2) {
                    printf("Erro: a matriz divisora e singular ou nao possui inversa numericamente calculavel.\n");
                }
                else if (sucesso == -3) {
                    printf("Erro: dimensoes incompativeis para a divisao matricial.\n");
                }

            } else {

                printf("Erro: dimensoes incompativeis entre as matrizes.\n");
            }
        }
    }

    return 0;
}
