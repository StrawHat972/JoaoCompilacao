# Comandos para Geração do Arquivo

Esse repositório diz respeito a um compilador da linguagem teórica TINY para Assembly RISC-V.

Para compilar o código do projeto, digite no seu terminal o seguinte comando:
```sh
make all
```

Uma vez gerado o executável, para realizar a compilação é preciso passar o nome do arquivo de entrada por linha de comando, por exemplo:
```sh
./compiler test.txt
```

Utilize o seguinte comando para excluir arquivos gerados pela compilação:
```sh
make clean
```

Caso não possa utilizar a diretiva make, o seguinte passo a passo é necessário para realizar a compilação:

Primeiro, gere o código C do analisador sintático por meio do seguinte comando:
```sh
bison -d parser.y
```

A diretiva -d fará que o gerador do analisador sintático gere o .c e o .h da BNF. Uma vez gerado o .h é necessário incluí-lo no código .l das definições dos tokens.

Em seguida, gere o código C do analisador léxico com o seguinte comando:
```sh
flex scanner.l
```

Uma vez gerados os dois códigos, basta compilá-los usando o comando a seguir:
```sh
g++ -o compiler main.cpp parser.tab.c lex.yy.c util.c analyser.cpp
```

Deve ser passado o nome do arquivo de entrada por linha de comando, por exemplo:
```sh
./compiler test.txt
```
