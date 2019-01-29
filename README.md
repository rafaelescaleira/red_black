Árvore Rubro - Negra (Red Black) (Genérica)
===========================================

![Build](https://img.shields.io/gitlab/pipeline/rafaelescaleira/red_black.svg)
![License](https://img.shields.io/github/license/rafaelescaleira/red_black.svg)

Esse repositório possui funções implementadas em linguagem C.
Segue a lista das funções :

* Inserção;
* Remoção;
* Busca;

Instruções para Compilação
--------------------------
Para compilar `` rb.c `` com `` teste_rb.c `` , ou seja, caso deseja testar o código de `` rb.c `` :

* `` ~$ gcc rb.c teste_rb.c -Wall -std=c99 -pedantic ``

Para compilar `` rb.c `` com `` main.c `` , ou seja, caso deseja executar o código e realizar seus próprios testes :

* `` ~$ gcc rb.c main.c -Wall -std=c99 -pedantic ``

Instruções para Execução
------------------------
Para executar o arquivo já compilado com `` teste_rb.c `` :

* `` ~$ ./a.out ``

Para executar o arquivo já compilado com `` main.c `` :

* `` ~$ ./a.out ``
* `` ~$ ./a.out < arquivo_entrada.txt ``

Complexidade de Tempo da Árvore Rubro - Negra (Red Black)
---------------------------------------------------------

| Algoritmo | Caso Médio | Pior Caso |
| --------- |:----------:|:---------:|
| Espaço | O (n) | O (n) |
| Busca | O (log n) | O (log n) |
| Inserção | O (log n) | O (log n) |
| Remoção | O (log n) | O (log n) |

Execução do Programa (Teste)
----------------------------
![grab-landing-page](https://j.gifs.com/L8kBP4.gif)

Execução do Programa (Principal)
--------------------------------
![grab-landing-page](https://j.gifs.com/nrqm3W.gif)
