# Comandos para Geração do Arquivo

Esse repositório diz respeito a um compilador da linguagem teórica TINY para Assembly RISC-V.

Para compilar o código do projeto, digite no seu terminal o seguinte comando:
```sh
make all
```

Uma vez gerado o executável, para realizar a compilação é preciso passar o nome do arquivo de entrada por linha de comando, por exemplo:
```sh
./compiler tests/fatorial.tiny
```

Pode-se também utilizar diretivas de compilação como por exemplo:
```sh
./compiler -a tests/fatorial.tiny
```

As diretivas válidas são -t para mostrar a Árvore Sintática gerada, -s para a Tabela de Símbolos, -p para o Código Intermediário (P-Code) ou -a para mostrar todos os três.

Com o código compilado para Assembly RISC-V, utilize o seguinte comando para então executá-lo (caso alguma janela seja aberta, apenas a ignore):
```sh
./fpgrars tests/fatorial.s
```

Utilize o comando a seguir para excluir arquivos gerados pela compilação:
```sh
make clean
```

Caso não possa utilizar a diretiva make, o seguinte passo a passo é necessário para realizar a compilação:

Primeiro, gere o código C do analisador sintático por meio do seguinte comando:
```sh
bison -d analysis/parser.y
```

A diretiva -d fará que o gerador do analisador sintático gere o .c e o .h da BNF. Uma vez gerado o .h é necessário incluí-lo no código .l das definições dos tokens.

Em seguida, gere o código C do analisador léxico com o seguinte comando:
```sh
flex analysis/scanner.l
```

Uma vez gerados os dois códigos, basta compilá-los usando o comando a seguir:
```sh
g++ -o compiler main.cpp parser.tab.c lex.yy.c analysis/*.cpp synthesis/*.cpp
```

Depois disso é só seguir o mesmo passo-a-passo apresentado anteriormente para o make.

Observação: O executável fpgrars.exe só funciona em Windows.