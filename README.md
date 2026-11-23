# Calculadora de Matrizes em C

Projeto referente à **questão 01 do módulo 01**: desenvolver uma calculadora de matrizes utilizando a linguagem C.

## Funcionalidades

- Permite escolher de **2 a 10 matrizes**.
- Solicita a quantidade de linhas, colunas e os valores de cada matriz (até **10 × 10**).
- Calcula **soma**, **subtração** e **multiplicação** de várias matrizes.
- Verifica se as dimensões são compatíveis com a operação escolhida.
- Exibe a **matriz solução** em formato de tabela.
- Impede informar matrizes antes de escolher a quantidade e impede realizar operações antes de cadastrar as matrizes.
- Valida a entrada de números e as escolhas do menu.

> **Observação sobre o enunciado:** a opção de subtração aparece duas vezes (operações 2 e 4). O programa mantém ambas as opções exatamente como descritas, executando a mesma operação de subtração. Não foi adicionada divisão de matrizes porque ela não foi solicitada explicitamente.

## Arquivos

- `main.c` — código-fonte completo da calculadora.
- `README.md` — descrição do projeto e instruções de execução.
- `.gitignore` — evita publicar arquivos executáveis e temporários por engano.

## Como compilar e executar

É necessário ter um compilador C, por exemplo o **GCC**.

### Linux / macOS

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o calculadora
./calculadora
```

### Windows (GCC/MinGW)

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o calculadora.exe
calculadora.exe
```

Também é possível abrir `main.c` no Code::Blocks, Dev-C++ ou Visual Studio Code, configurar um compilador de C e executar o programa.

## Como usar

No menu principal:

1. **Escolher quantidade de matrizes** — escolha entre 2 e 10.
2. **Informar as matrizes** — digite as dimensões e os valores de cada elemento.
3. **Escolher operação matemática** — selecione `1` para soma, `2` para subtração, `3` para multiplicação ou `4` para a subtração repetida no enunciado.
4. **Apresentar a matriz solução** — exibe o resultado calculado.
0. **Sair** — encerra o programa.

Digite números decimais com **ponto**, por exemplo `3.5`.

### Exemplo: soma de duas matrizes

**Matriz A**

```text
[ 1  2 ]
[ 3  4 ]
```

**Matriz B**

```text
[ 5  6 ]
[ 7  8 ]
```

**Resultado A + B**

```text
[  6.00   8.00 ]
[ 10.00  12.00 ]
```

### Regras matemáticas utilizadas

- **Soma e subtração:** todas as matrizes devem ter o mesmo número de linhas e colunas. As operações são realizadas elemento a elemento.
- **Multiplicação:** o número de colunas da matriz da esquerda deve ser igual ao número de linhas da matriz da direita. O resultado é calculado seguindo a ordem de cadastro: `(A × B) × C`, e assim por diante.
- **Mais de duas matrizes:** a soma e a subtração seguem a ordem `A + B + C` e `A - B - C`.

## Como publicar no GitHub

1. Entre no [GitHub](https://github.com/) com sua conta.
2. Selecione **New repository** (Novo repositório).
3. Dê o nome `calculadora-matrizes-c` e selecione **Public**.
4. Crie o repositório. Não é necessário gerar outro README pelo GitHub, porque este projeto já o inclui.
5. Clique em **Add file > Upload files** e envie `main.c`, `README.md` e `.gitignore` (se o envio do arquivo oculto não funcionar, os dois primeiros já são suficientes).
6. Confirme usando **Commit changes**.
7. Copie o link público, normalmente no formato `https://github.com/SEU_USUARIO/calculadora-matrizes-c`, e envie-o no Blackboard no momento solicitado.

**Importante:** publicar o repositório e enviar o link no Blackboard são ações que você precisa realizar com sua conta.
