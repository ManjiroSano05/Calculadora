# Calculadora de Matrizes em C

## Objetivo

Aplicação em linguagem C para cadastrar matrizes e realizar operações matemáticas por meio de um menu interativo.

## Funcionalidades

- Cadastro de 2 a 10 matrizes, com até 10 linhas e 10 colunas cada.
- Adição, subtração, multiplicação e divisão matricial.
- Divisão definida como `A / B = A × B⁻¹`, calculada da esquerda para a direita quando há três ou mais matrizes.
- Verificação das dimensões necessárias para cada operação.
- Identificação de matrizes divisoras não quadradas ou singulares (sem inversa).
- Exibição da matriz resultante e possibilidade de realizar novas operações.
- Validação de números e opções do menu.

## Como compilar e executar

Com o **GCC** instalado, abra o terminal na pasta que contém `main.c` e digite:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o calculadora -lm
./calculadora
```

No Windows, o programa compilado pode ser iniciado com `calculadora.exe`. Para valores decimais, utilize ponto, como `2.5`.

## Funções implementadas

| Função | Responsabilidade |
| --- | --- |
| `ler_inteiro` | Ler e validar números inteiros e opções do menu. |
| `ler_real` | Ler e validar os elementos numéricos das matrizes. |
| `informar_matrizes` | Cadastrar dimensões e valores de cada matriz. |
| `mostrar_matriz` | Exibir uma matriz organizada em linhas e colunas. |
| `somar_ou_subtrair` | Executar soma ou subtração entre matrizes compatíveis. |
| `multiplicar` | Multiplicar as matrizes na ordem de cadastro. |
| `inverter_matriz` | Calcular a inversa por Gauss-Jordan e detectar matrizes singulares. |
| `dividir_matrizes` | Realizar divisões sequenciais usando a inversa da matriz divisora. |
| `mostrar_menu` e `mostrar_operacoes` | Apresentar os menus disponíveis. |
| `main` | Controlar o fluxo de cadastro, operações e encerramento. |

## Exemplo de utilização

No menu principal, escolha **1** para definir **2 matrizes** e depois **2** para cadastrar os elementos.

Matriz A (2 × 2):

```text
[ 2  0 ]
[ 0  4 ]
```

Matriz B (2 × 2):

```text
[ 1  0 ]
[ 0  2 ]
```

Escolha a opção **3** (operações) e depois **4** (divisão). Em seguida, escolha a opção **4** no menu principal para visualizar o resultado de `A × B⁻¹`:

```text
[ 2.00  0.00 ]
[ 0.00  2.00 ]
```

Se a matriz divisora fosse `[[1, 2], [2, 4]]`, o sistema informaria que ela é singular e não possui inversa.
