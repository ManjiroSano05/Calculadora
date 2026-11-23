#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MATRIZES 10
#define MAX_DIMENSAO 10
#define TAM_ENTRADA 128
#define EPSILON 1e-12

typedef struct {
    int linhas;
    int colunas;
    double valores[MAX_DIMENSAO][MAX_DIMENSAO];
} Matriz;

/* Le numeros inteiros com validacao, evitando problemas com scanf. */
int ler_inteiro(const char *mensagem, int minimo, int maximo) {
    char entrada[TAM_ENTRADA];
    char *fim;
    long numero;

    while (1) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            puts("\nEntrada encerrada.");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        numero = strtol(entrada, &fim, 10);
        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != entrada && *fim == '\0' && errno != ERANGE &&
            numero >= minimo && numero <= maximo) {
            return (int)numero;
        }

        puts("Entrada invalida. Tente novamente.");
    }
}

/* Os numeros decimais devem ser digitados com ponto: 2.5 */
double ler_real(const char *mensagem) {
    char entrada[TAM_ENTRADA];
    char *fim;
    double numero;

    while (1) {
        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            puts("\nEntrada encerrada.");
            exit(EXIT_SUCCESS);
        }

        errno = 0;
        numero = strtod(entrada, &fim);
        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != entrada && *fim == '\0' && errno != ERANGE &&
            isfinite(numero)) {
            return numero;
        }

        puts("Numero invalido. Use ponto para decimais, por exemplo 2.5.");
    }
}

void mostrar_matriz(const Matriz *matriz) {
    int i, j;
    for (i = 0; i < matriz->linhas; i++) {
        printf("[ ");
        for (j = 0; j < matriz->colunas; j++) {
            printf("%8.2f ", matriz->valores[i][j]);
        }
        puts("]");
    }
}

void informar_matrizes(Matriz matrizes[], int quantidade) {
    int k, i, j;
    char pergunta[100];

    for (k = 0; k < quantidade; k++) {
        printf("\n--- Matriz %d ---\n", k + 1);
        matrizes[k].linhas = ler_inteiro("Quantidade de linhas (1 a 10): ", 1, MAX_DIMENSAO);
        matrizes[k].colunas = ler_inteiro("Quantidade de colunas (1 a 10): ", 1, MAX_DIMENSAO);

        for (i = 0; i < matrizes[k].linhas; i++) {
            for (j = 0; j < matrizes[k].colunas; j++) {
                snprintf(pergunta, sizeof(pergunta), "Elemento [%d][%d]: ", i + 1, j + 1);
                matrizes[k].valores[i][j] = ler_real(pergunta);
            }
        }

        printf("Matriz %d cadastrada:\n", k + 1);
        mostrar_matriz(&matrizes[k]);
    }
}

/* Soma (operacao 1) ou subtracao (operacao 2). */
int somar_ou_subtrair(const Matriz matrizes[], int quantidade,
                     int subtrair, Matriz *resultado) {
    int k, i, j;

    for (k = 1; k < quantidade; k++) {
        if (matrizes[k].linhas != matrizes[0].linhas ||
            matrizes[k].colunas != matrizes[0].colunas) {
            puts("Erro: para somar ou subtrair, todas as matrizes precisam ter o mesmo tamanho.");
            return 0;
        }
    }

    *resultado = matrizes[0];
    for (k = 1; k < quantidade; k++) {
        for (i = 0; i < resultado->linhas; i++) {
            for (j = 0; j < resultado->colunas; j++) {
                if (subtrair) {
                    resultado->valores[i][j] -= matrizes[k].valores[i][j];
                } else {
                    resultado->valores[i][j] += matrizes[k].valores[i][j];
                }
            }
        }
    }
    return 1;
}

/* Multiplica da esquerda para a direita: ((A * B) * C) ... */
int multiplicar(const Matriz matrizes[], int quantidade, Matriz *resultado) {
    int k, i, j, x;
    Matriz produto;

    *resultado = matrizes[0];
    for (k = 1; k < quantidade; k++) {
        if (resultado->colunas != matrizes[k].linhas) {
            printf("Erro: nao e possivel multiplicar pelo fator %d.\n", k + 1);
            printf("O resultado anterior tem %d colunas, mas a proxima matriz tem %d linhas.\n",
                   resultado->colunas, matrizes[k].linhas);
            return 0;
        }

        produto = (Matriz){0};
        produto.linhas = resultado->linhas;
        produto.colunas = matrizes[k].colunas;

        for (i = 0; i < produto.linhas; i++) {
            for (j = 0; j < produto.colunas; j++) {
                for (x = 0; x < resultado->colunas; x++) {
                    produto.valores[i][j] +=
                        resultado->valores[i][x] * matrizes[k].valores[x][j];
                }
            }
        }
        *resultado = produto;
    }
    return 1;
}

/* Encontra a inversa usando Gauss-Jordan com pivoteamento parcial.
   Retorna 0 quando a matriz nao e quadrada ou nao e inversivel. */
int inverter_matriz(const Matriz *matriz, Matriz *inversa) {
    double aumentada[MAX_DIMENSAO][2 * MAX_DIMENSAO] = {{0}};
    double escala = 0.0;
    int n, i, j, k, linha_pivo;

    if (matriz->linhas != matriz->colunas) {
        return 0;
    }
    n = matriz->linhas;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            aumentada[i][j] = matriz->valores[i][j];
            if (fabs(aumentada[i][j]) > escala) {
                escala = fabs(aumentada[i][j]);
            }
        }
        aumentada[i][n + i] = 1.0;
    }
    if (escala == 0.0) {
        return 0;
    }

    for (k = 0; k < n; k++) {
        double maior = fabs(aumentada[k][k]);
        double pivo;
        linha_pivo = k;

        for (i = k + 1; i < n; i++) {
            double valor = fabs(aumentada[i][k]);
            if (valor > maior) {
                maior = valor;
                linha_pivo = i;
            }
        }
        /* Pivos muito proximos de zero sinalizam matriz singular. */
        if (maior <= EPSILON * escala) {
            return 0;
        }
        if (linha_pivo != k) {
            for (j = 0; j < 2 * n; j++) {
                double troca = aumentada[k][j];
                aumentada[k][j] = aumentada[linha_pivo][j];
                aumentada[linha_pivo][j] = troca;
            }
        }

        pivo = aumentada[k][k];
        for (j = 0; j < 2 * n; j++) {
            aumentada[k][j] /= pivo;
        }
        for (i = 0; i < n; i++) {
            if (i != k) {
                double fator = aumentada[i][k];
                for (j = 0; j < 2 * n; j++) {
                    aumentada[i][j] -= fator * aumentada[k][j];
                }
            }
        }
    }

    *inversa = (Matriz){0};
    inversa->linhas = n;
    inversa->colunas = n;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inversa->valores[i][j] = aumentada[i][n + j];
            if (!isfinite(inversa->valores[i][j])) {
                return 0;
            }
        }
    }
    return 1;
}

/* Divisao sequencial: ((A x B^-1) x C^-1) ... */
int dividir_matrizes(const Matriz matrizes[], int quantidade, Matriz *resultado) {
    Matriz inversa, produto;
    int etapa, i, j, k;

    *resultado = matrizes[0];
    for (etapa = 1; etapa < quantidade; etapa++) {
        if (matrizes[etapa].linhas != matrizes[etapa].colunas) {
            printf("Erro: a matriz divisora %d nao e quadrada.\n", etapa + 1);
            return 0;
        }
        if (resultado->colunas != matrizes[etapa].linhas) {
            printf("Erro: dimensoes incompativeis na divisao pela matriz %d.\n",
                   etapa + 1);
            return 0;
        }
        if (!inverter_matriz(&matrizes[etapa], &inversa)) {
            printf("Erro: a matriz divisora %d e singular (sem inversa).\n",
                   etapa + 1);
            return 0;
        }

        produto = (Matriz){0};
        produto.linhas = resultado->linhas;
        produto.colunas = inversa.colunas;
        for (i = 0; i < produto.linhas; i++) {
            for (j = 0; j < produto.colunas; j++) {
                for (k = 0; k < resultado->colunas; k++) {
                    produto.valores[i][j] +=
                        resultado->valores[i][k] * inversa.valores[k][j];
                }
            }
        }
        *resultado = produto;
    }
    return 1;
}

void mostrar_menu(void) {
    puts("\n========== CALCULADORA DE MATRIZES ==========");
    puts("1 - Escolher quantidade de matrizes");
    puts("2 - Informar as matrizes");
    puts("3 - Escolher operacao matematica");
    puts("4 - Apresentar a matriz solucao");
    puts("0 - Sair");
    puts("=============================================");
}

void mostrar_operacoes(void) {
    puts("\n--- OPERACOES ---");
    puts("1 - Soma de matrizes");
    puts("2 - Subtracao de matrizes");
    puts("3 - Multiplicacao de matrizes");
    puts("4 - Divisao matricial");
    puts("0 - Voltar ao menu principal");
}

int main(void) {
    Matriz matrizes[MAX_MATRIZES] = {0};
    Matriz resultado = {0};
    int quantidade = 0;
    int matrizes_informadas = 0;
    int tem_resultado = 0;
    int opcao, operacao, sucesso;

    puts("Bem-vindo(a) a calculadora de matrizes em C!");

    while (1) {
        mostrar_menu();
        opcao = ler_inteiro("Escolha uma opcao: ", 0, 4);

        switch (opcao) {
            case 0:
                puts("Programa encerrado.");
                return 0;

            case 1:
                quantidade = ler_inteiro("Quantidade de matrizes (2 a 10): ", 2, MAX_MATRIZES);
                matrizes_informadas = 0;
                tem_resultado = 0;
                printf("Quantidade definida: %d. Agora use a opcao 2.\n", quantidade);
                break;

            case 2:
                if (quantidade == 0) {
                    puts("Primeiro escolha a quantidade de matrizes (opcao 1).");
                    break;
                }
                matrizes_informadas = 0;
                tem_resultado = 0;
                informar_matrizes(matrizes, quantidade);
                matrizes_informadas = 1;
                puts("Todas as matrizes foram informadas com sucesso.");
                break;

            case 3:
                if (!matrizes_informadas) {
                    puts("Primeiro defina a quantidade (1) e informe as matrizes (2).");
                    break;
                }
                mostrar_operacoes();
                operacao = ler_inteiro("Digite a operacao desejada: ", 0, 4);
                if (operacao == 0) {
                    break;
                }

                tem_resultado = 0;
                if (operacao == 1) {
                    sucesso = somar_ou_subtrair(matrizes, quantidade, 0, &resultado);
                } else if (operacao == 2) {
                    sucesso = somar_ou_subtrair(matrizes, quantidade, 1, &resultado);
                } else if (operacao == 3) {
                    sucesso = multiplicar(matrizes, quantidade, &resultado);
                } else {
                    sucesso = dividir_matrizes(matrizes, quantidade, &resultado);
                }

                if (sucesso) {
                    tem_resultado = 1;
                    puts("Operacao realizada! Selecione 4 para ver a matriz solucao.");
                }
                break;

            case 4:
                if (tem_resultado) {
                    printf("\nMatriz solucao (%d x %d):\n", resultado.linhas, resultado.colunas);
                    mostrar_matriz(&resultado);
                } else {
                    puts("Nenhum resultado disponivel. Realize uma operacao na opcao 3.");
                }
                break;
        }
    }
}
