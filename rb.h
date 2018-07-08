/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 * Nome : Rafael Escaleira Ferreira dos Santos.  *
 * Universidade Federal do Mato Grosso do Sul    *
 * Disciplina : Estrutura de Dados e Programação *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _RB_H_
#define _RB_H_

/* * * * * * * * * * * Cores * * * * * * * * * * */

#define cor_texto(cor) cor
#define estilo_texto(estilo_texto_) estilo_texto_

/* * * * * * * * * Cor do Texto * * * * * * * * * */

#define preto printf("\033[30m") 
#define vermelho printf("\033[31m") 
#define verde printf("\033[32m") 
#define amarelo printf("\033[33m") 
#define azul printf("\033[34m") 
#define magenta printf("\033[35m") 
#define ciano printf("\033[36m") 
#define branco printf("\033[37m") 
#define normal printf("\033[39m") 

/* * * * * * * * Estilo do Texto * * * * * * * * */

#define negrito printf("\033[1m")
#define fosco printf("\033[2m")
#define estilo_normal printf("\033[22m")
#define resetar printf("\033[0m")
#define sublinhado printf("\033[4m")
#define piscar printf("\033[5m")
#define italico printf("\033[3m")
#define negativo printf("\033[7m")

/* * * * * * * * * * Registros * * * * * * * * * */

typedef struct _node {

    void * reg;
    void * valor;
    struct _node * esq;
    struct _node * dir;
    struct _node * pai;
    int VERMELHO;

} tnode;

typedef struct _arv {

    int (* compara)(const void * a, const void * b);

    void (* destroi_reg)(void * a);
    void (* destroi_valor)(void * a);
    void (* imprime_reg)(const void * a);
    void (* imprime_valor)(const void * a);

    tnode * raiz;
    tnode * nulo;

    unsigned int size;

} tarv;

/* * * * * * * * * * * * Declaração de Funções * * * * * * * * * * * */

void free_inteiro (void * a);

int compara_inteiro (const void * a, const void * b);

void imprime_inteiro (const void * a);

tarv * rb_constroi (int (* cmp)(const void * , const void * ), void (* destroi_reg_func)(void *), void (* destroi_valor_func)(void *), void (* imprime_reg_func)(const void *), void (* imprime_valor_func)(const void *));

int rb_vazia (tarv * parv);

unsigned int rb_tamanho (tarv * parv);

tnode * rb_inicio (tarv * parv);

tnode * rb_fim (tarv * parv);

tnode * rb_insere (tarv * parv, void * reg, void * valor);

tnode * rb_sucessor (tarv * parv, tnode * x);

tnode * rb_predecessor (tarv * parv, tnode * x);

void rb_destroi (tarv * parv);

void imprime_arvore_rb (tarv * parv, tnode * raiz, int profundidade, void * elemento_inserido);

tnode * rb_busca (tarv * parv, const void * reg);

void rb_remove (tarv * parv, tnode * z);

int rb_verifica (tarv * parv);

/* * * * * * * * * * * * Funções (Teste) * * * * * * * * * * * */

void confere_funcionamento (void);

void teste_tempo_execucao (int n);

#endif
