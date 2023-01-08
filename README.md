# Comandos para Geração do Arquivo

Primeiro, gere o código C do analisador sintático por meio do seguinte comando:
```sh
bison -d sintatico.y
```

A diretiva -d fará que o gerador do analisador sintático gere o .c e o .h da BNF. Uma vez gerado o .h é necessário incluí-lo no código .l das definições dos tokens.

Em seguida, gere o código C do analisador léxico com o seguinte comando:
```sh
flex lexico.l
```

Uma vez gerados os dois códigos, basta compilá-los usando o comando a seguir:
```sh
gcc -o analisador sintatico.tab.c lex.yy.c
```

Observação: Pode ser usado também o g++ para compilação caso utilize códigos em C++.