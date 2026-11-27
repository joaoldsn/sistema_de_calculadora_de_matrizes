#ifndef MATRIZES_H
#define MATRIZES_H

#define MAX 10
#define TOLERANCIA 1e-10

typedef struct {
    int linhas;
    int colunas;
    double valor[MAX][MAX];
} Matriz;

/* Funcoes de validacao */
int validarDimensao(int valor);
int validarQuantidade(int quantidade);
int validarOpcao(int opcao);

/* Funcoes de leitura */
int lerInteiro(const char *mensagem, int *valor);
int lerReal(const char *mensagem, double *valor);
int lerMatriz(Matriz *m, int numero);

/* Funcao de exibicao */
void mostrarMatriz(Matriz m);

/* Operacoes matematicas */
int somar(Matriz a, Matriz b, Matriz *r);
int subtrair(Matriz a, Matriz b, Matriz *r);
int multiplicar(Matriz a, Matriz b, Matriz *r);
int inversa(Matriz a, Matriz *r);
int dividir(Matriz a, Matriz b, Matriz *r);

/* Menu */
void menu();

#endif
