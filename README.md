# Comandos para Geração do Arquivo

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
gcc -o analisador main.c parser.tab.c lex.yy.c util.c
```

Deve ser passado o nome do arquivo de entrada por linha de comando, por exemplo:
```sh
./analisador test.txt
```

Observação: Pode ser usado também o g++ para compilação caso utilize códigos em C++.
