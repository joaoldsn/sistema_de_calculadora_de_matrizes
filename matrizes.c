#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "matrizes.h"

/*funcoes de validacao*/

int validarDimensao(int valor) {
    return valor >= 1 && valor <= MAX;
}

int validarQuantidade(int quantidade) {
    return quantidade >= 2 && quantidade <= MAX;
}

int validarOpcao(int opcao) {
    return opcao >= 0 && opcao <= 4;
}

/*leitura de inteiros*/

int lerInteiro(const char *mensagem, int *valor) {
    char entrada[256];
    char *fim;
    long numero;
    int caractere;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            return 0;

        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            while ((caractere = getchar()) != '\n' &&
                   caractere != EOF);

            printf("Entrada muito longa. Tente novamente.\n");
            continue;
        }

        errno = 0;
        numero = strtol(entrada, &fim, 10);

        while (*fim == ' ' || *fim == '\t' ||
               *fim == '\n' || *fim == '\r') {
            fim++;
        }

        if (fim == entrada || *fim != '\0' ||
            errno == ERANGE ||
            numero < -2147483647L - 1 ||
            numero > 2147483647L) {

            printf("Valor invalido! Digite um numero inteiro.\n");
            continue;
        }

        *valor = (int)numero;
        return 1;
    }
}

/*leitura de numeros reais*/

int lerReal(const char *mensagem, double *valor) {
    char entrada[256];
    char *fim;
    double numero;
    int caractere;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            return 0;

        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            while ((caractere = getchar()) != '\n' &&
                   caractere != EOF);

            printf("Entrada muito longa. Tente novamente.\n");
            continue;
        }

        errno = 0;
        numero = strtod(entrada, &fim);

        while (*fim == ' ' || *fim == '\t' ||
               *fim == '\n' || *fim == '\r') {
            fim++;
        }

        if (fim == entrada || *fim != '\0' ||
            errno == ERANGE || !isfinite(numero)) {

            printf("Valor invalido! Digite um numero real valido.\n");
            continue;
        }

        *valor = numero;
        return 1;
    }
}

/*leitura das matrizes*/

int lerMatriz(Matriz *m, int numero) {
    int i, j;
    char mensagem[100];

    printf("\n========== MATRIZ %d ==========\n", numero);

    while (1) {
        if (!lerInteiro(
            "Quantidade de linhas (1 a 10): ",
            &m->linhas))
            return 0;

        if (validarDimensao(m->linhas))
            break;

        printf("Quantidade de linhas invalida!\n");
    }

    while (1) {
        if (!lerInteiro(
            "Quantidade de colunas (1 a 10): ",
            &m->colunas))
            return 0;

        if (validarDimensao(m->colunas))
            break;

        printf("Quantidade de colunas invalida!\n");
    }

    for (i = 0; i < m->linhas; i++) {
        for (j = 0; j < m->colunas; j++) {

            snprintf(mensagem, sizeof(mensagem),
                     "Elemento [%d][%d]: ", i + 1, j + 1);

            if (!lerReal(mensagem, &m->valor[i][j]))
                return 0;
        }
    }

    return 1;
}

/*exibicao das matrizes*/

void mostrarMatriz(Matriz m) {
    int i, j;

    for (i = 0; i < m.linhas; i++) {
        for (j = 0; j < m.colunas; j++) {
            printf("%12.4lf ", m.valor[i][j]);
        }

        printf("\n");
    }
}

/*adicao*/

int somar(Matriz a, Matriz b, Matriz *r) {
    int i, j;

    if (a.linhas != b.linhas ||
        a.colunas != b.colunas)
        return 0;

    r->linhas = a.linhas;
    r->colunas = a.colunas;

    for (i = 0; i < a.linhas; i++) {
        for (j = 0; j < a.colunas; j++) {
            r->valor[i][j] =
                a.valor[i][j] + b.valor[i][j];
        }
    }

    return 1;
}

/*subtracao*/

int subtrair(Matriz a, Matriz b, Matriz *r) {
    int i, j;

    if (a.linhas != b.linhas ||
        a.colunas != b.colunas)
        return 0;

    r->linhas = a.linhas;
    r->colunas = a.colunas;

    for (i = 0; i < a.linhas; i++) {
        for (j = 0; j < a.colunas; j++) {
            r->valor[i][j] =
                a.valor[i][j] - b.valor[i][j];
        }
    }

    return 1;
}

/*multiplicacao*/

int multiplicar(Matriz a, Matriz b, Matriz *r) {
    int i, j, k;

    if (a.colunas != b.linhas)
        return 0;

    r->linhas = a.linhas;
    r->colunas = b.colunas;

    for (i = 0; i < r->linhas; i++) {
        for (j = 0; j < r->colunas; j++) {

            r->valor[i][j] = 0.0;

            for (k = 0; k < a.colunas; k++) {
                r->valor[i][j] +=
                    a.valor[i][k] * b.valor[k][j];
            }
        }
    }

    return 1;
}

/*inversa - gauss-jordan*/

int inversa(Matriz a, Matriz *r) {
    double auxiliar[MAX][MAX * 2];
    double escalaLinha[MAX];
    double maior, razao, temp, pivo;

    int i, j, k, linhaPivo;
    int n;

    if (a.linhas != a.colunas)
        return 0;

    n = a.linhas;

    /* Monta a matriz aumentada [A | I] */
    for (i = 0; i < n; i++) {

        escalaLinha[i] = 0.0;

        for (j = 0; j < n; j++) {

            if (!isfinite(a.valor[i][j]))
                return 0;

            auxiliar[i][j] = a.valor[i][j];

            if (fabs(a.valor[i][j]) > escalaLinha[i])
                escalaLinha[i] = fabs(a.valor[i][j]);
        }

        if (escalaLinha[i] == 0.0)
            return 0;

        for (j = 0; j < n; j++) {
            auxiliar[i][j + n] =
                (i == j) ? 1.0 : 0.0;
        }
    }

    /* Eliminacao de Gauss-Jordan */
    for (i = 0; i < n; i++) {

        maior = -1.0;
        linhaPivo = i;

        /* Procura o melhor pivo */
        for (k = i; k < n; k++) {

            razao = fabs(auxiliar[k][i]) /
                    escalaLinha[k];

            if (razao > maior) {
                maior = razao;
                linhaPivo = k;
            }
        }

        /* Verifica se o pivo e muito pequeno */
        if (maior <= TOLERANCIA)
            return 0;

        /* Troca as linhas */
        if (linhaPivo != i) {

            for (j = 0; j < 2 * n; j++) {
                temp = auxiliar[i][j];
                auxiliar[i][j] = auxiliar[linhaPivo][j];
                auxiliar[linhaPivo][j] = temp;
            }

            temp = escalaLinha[i];
            escalaLinha[i] = escalaLinha[linhaPivo];
            escalaLinha[linhaPivo] = temp;
        }

        pivo = auxiliar[i][i];

        /* Normaliza a linha do pivo */
        for (j = 0; j < 2 * n; j++) {
            auxiliar[i][j] /= pivo;
        }

        /* Zera os demais elementos da coluna */
        for (k = 0; k < n; k++) {

            if (k != i) {

                temp = auxiliar[k][i];

                for (j = 0; j < 2 * n; j++) {
                    auxiliar[k][j] -=
                        temp * auxiliar[i][j];
                }
            }
        }
    }

    /* Copia a inversa para o resultado */
    r->linhas = n;
    r->colunas = n;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {

            if (!isfinite(auxiliar[i][j + n]))
                return 0;

            r->valor[i][j] = auxiliar[i][j + n];
        }
    }

    return 1;
}

/*divisao matricial*/

int dividir(Matriz a, Matriz b, Matriz *r) {
    Matriz inv;

    if (b.linhas != b.colunas)
        return -1;

    if (!inversa(b, &inv))
        return -2;

    if (a.colunas != inv.linhas)
        return -3;

    if (!multiplicar(a, inv, r))
        return -3;

    return 1;
}

/*menu principal*/
void menu() {
    printf("\n========== CALCULADORA DE MATRIZES ==========\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao matricial\n");
    printf("0 - Encerrar programa\n");
    printf("=============================================\n");
}
