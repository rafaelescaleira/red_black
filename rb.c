/* * * * * * * * * * * * * * * * * * * * * * * * *
 *                                               *
 * Nome : Rafael Escaleira Ferreira dos Santos.  *
 * Universidade Federal do Mato Grosso do Sul    *
 * Disciplina : Estrutura de Dados e Programação *
 *                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "rb.h"

/* * * * * * * * * * * Árvore Rubro - Negra * * * * * * * * * * * */

void free_inteiro (void * a) {

    (void)a;

}

int compara_inteiro (const void * a, const void * b) {

    if ((intptr_t)a < (intptr_t)b) {

        return - 1;

    }

    if ((intptr_t)a > (intptr_t)b) {

        return + 1;

    }

    return 0;

}

void imprime_inteiro (const void * a) {

    printf("%d\n", (int)(intptr_t)a);

}

void free_caracter (void *a) {
    
    free ((char *)a);
    
}

int compara_caracter (const void * a, const void * b) {
    
    return strcmp (a, b);
    
}

void imprime_caracter (const void * a) {
    
    printf ("%s", (char *)a);
    
}

tarv * rb_constroi (int (* cmp)(const void * , const void * ), void (* destroi_reg_func)(void *), void (* destroi_valor_func)(void *), void (* imprime_reg_func)(const void *), void (* imprime_valor_func)(const void *)) {
    
    tarv * parv;
    tnode * pnode;
    
    parv = (tarv *) malloc (sizeof (tarv));
    
    if (parv == NULL) {
        
        return NULL;
        
    }
    
    parv -> compara =  cmp;
    parv -> destroi_reg = destroi_reg_func;
    parv -> destroi_valor = destroi_valor_func;
    parv -> imprime_reg = imprime_reg_func;
    parv -> imprime_valor = imprime_valor_func;
    parv -> size = 0;
    
    pnode = parv -> nulo = (tnode *)malloc(sizeof (tnode));
    pnode -> pai = pnode -> esq = pnode -> dir = pnode;
    pnode -> VERMELHO = 0;
    pnode -> reg = 0;
    
    pnode = parv -> raiz = (tnode *)malloc(sizeof (tnode));
    pnode -> pai = pnode -> esq = pnode -> dir = parv -> nulo;
    pnode -> VERMELHO = 0;
    pnode -> reg = 0;
    
    return parv;
    
}

int rb_vazia (tarv * parv) {
    
    return (parv -> raiz -> esq == parv -> nulo);
    
}

unsigned int rb_tamanho (tarv * parv) {
    
    return parv -> size;
    
}

tnode * rb_inicio (tarv * parv) {
    
    tnode * x;
    
    x = parv -> raiz -> esq;
    
    while (x -> esq != parv -> nulo) {
        
        x = x -> esq;
        
    }
    
    return x;
    
}

tnode * rb_fim (tarv * parv) {
    
    return parv -> nulo;
    
}

static void rb_rotacao_esquerda (tarv * parv, tnode * x) {
    
    tnode * y, * nulo;
    
    nulo = parv -> nulo;
    y = x -> dir;
    x -> dir = y -> esq;
    
    if (y -> esq != nulo) { 
        
        y -> esq -> pai = x;
        
    }
    
    y -> pai = x -> pai;   
    
    if (x == x -> pai -> esq) {
        
        x -> pai -> esq = y;
        
    }
    
    else {
        
        x -> pai -> dir = y;
        
    }
    
    y -> esq = x;
    x -> pai = y;
    
    assert (!parv -> nulo -> VERMELHO);
    
}

static void rb_rotacao_direita (tarv * parv, tnode * y) {
    
    tnode * x, * nulo;
    
    nulo = parv -> nulo;
    x = y -> esq;
    y -> esq = x -> dir;
    
    if (nulo != x -> dir) {
        
        x -> dir -> pai = y;
        
    }
    
    x -> pai = y -> pai;
    
    if (y == y -> pai -> esq) {
        
        y -> pai -> esq = x;
        
    }
    
    else {
        
        y -> pai -> dir = x;
        
    }
    
    x -> dir = y;
    y -> pai = x;
    
    assert (!parv -> nulo -> VERMELHO);
    
}

static void rb_insere_fix_up (tarv * parv, tnode * z) {
    
    tnode * x, * y, * nulo;
    
    nulo = parv -> nulo;
    z -> esq = z -> dir = nulo;
    y = parv -> raiz;
    x = parv -> raiz -> esq;
    
    while (x != nulo) {
        
        y = x;
        
        if (parv -> compara (x -> reg, z -> reg) > 0) {
            
            x = x -> esq;
            
        }
        
        else { 
            
            x = x -> dir;
            
        }
        
    }
    
    z -> pai = y;
    
    if ((y == parv -> raiz) || (parv -> compara (y -> reg, z -> reg) > 0)) { 
        
        y -> esq = z;
        
    }
    
    else {
        
        y -> dir = z;
        
    }
    
    assert (!parv -> nulo -> VERMELHO);
    
}

tnode * rb_insere (tarv * parv, void * reg, void * valor) {
    
    tnode * x, * y, * novo;
    
    x = (tnode *) malloc (sizeof (tnode));
    x -> reg = reg;
    x -> valor = valor;
    
    rb_insere_fix_up (parv, x);
    
    novo = x;
    x -> VERMELHO = 1;
    
    while (x -> pai -> VERMELHO) {
        
        if (x -> pai == x -> pai -> pai -> esq) {
            
            y = x -> pai -> pai -> dir;
            
            if (y -> VERMELHO) {
                
                x -> pai -> VERMELHO = 0;
                y -> VERMELHO = 0;
                x -> pai -> pai -> VERMELHO = 1;
                x = x -> pai -> pai;
                
            }
            
            else {
                
                if (x == x -> pai -> dir) {
                    
                    x = x -> pai;
                    rb_rotacao_esquerda (parv, x);
                    
                }
                
                x -> pai -> VERMELHO = 0;
                x -> pai -> pai -> VERMELHO = 1;
                rb_rotacao_direita (parv, x -> pai -> pai);
                
            } 
            
        }
        
        else {
            
            y = x -> pai -> pai -> esq;
            
            if (y -> VERMELHO) {
                
                x -> pai -> VERMELHO = 0;
                y -> VERMELHO = 0;
                x -> pai -> pai -> VERMELHO = 1;
                x = x -> pai -> pai;
                
            }
            
            else {
                
                if (x == x -> pai -> esq) {
                    
                    x = x -> pai;
                    rb_rotacao_direita (parv, x);
                    
                }
                
                x -> pai -> VERMELHO = 0;
                x -> pai -> pai -> VERMELHO = 1;
                rb_rotacao_esquerda (parv, x -> pai -> pai);
                
            } 
            
        }
        
    }
    
    parv -> raiz -> esq -> VERMELHO = 0;
    ++ parv -> size;
    
#ifdef VERIFICA_RED_BLACK
    
    assert (rb_verifica (parv));
    
#endif
    
    return novo;
    
}

tnode * rb_sucessor (tarv * parv, tnode * x) { 
    
    tnode * y, * nulo, * raiz;
    
    nulo = parv -> nulo;
    raiz = parv -> raiz;
    
    if (nulo != (y = x -> dir)) {
        
        while (y -> esq != nulo) { 
            
            y = y -> esq;
            
        }
        
        return y;
        
    }
    
    else {
        
        y = x -> pai;
        
        while (x == y -> dir) { 
            
            x = y;
            y = y -> pai;
            
        }
        
        if (y == raiz) { 
            
            return nulo;
            
        }
        
        return y;
        
    }
    
}

tnode * rb_predecessor (tarv * parv, tnode * x) {
    
    tnode * y, * nulo, * raiz;
    
    nulo = parv -> nulo;
    raiz = parv -> raiz;
    
    if (nulo != (y = x -> esq)) {
        
        while (y -> dir != nulo) { 
            
            y = y -> dir;
            
        }
        
        return y;
        
    }
    
    else {
        
        y = x -> pai;
        
        while (x == y -> esq) {
            
            if (y == raiz) {
                
                return nulo; 
                
            }
            
            x = y;
            y = y -> pai;
            
        }
        
        return y;
        
    }
    
}

static void _rb_destroi (tarv * parv, tnode * x) {
    
    if (x != parv -> nulo) {
        
        _rb_destroi (parv, x -> esq);
        _rb_destroi (parv, x -> dir);
        
        parv -> destroi_reg (x -> reg);
        parv -> destroi_valor (x -> valor);
        
        free(x);
        
    }
    
}

void rb_destroi (tarv * parv) {
    
    _rb_destroi (parv, parv -> raiz -> esq);
    
    free (parv -> raiz);
    free (parv -> nulo);
    free (parv);
    
}

void imprime_arvore_rb (tarv * parv, tnode * raiz, int profundidade, void * elemento_inserido) {
    
    int anda, i;

    anda = 3;
    
    if (raiz != parv -> nulo) {
        
        imprime_arvore_rb (parv, raiz -> dir, profundidade + anda, elemento_inserido);
        
        for (i = 0; i < profundidade; i ++) {
            
            printf (" ");
            
        }
        
        if (raiz -> VERMELHO == 1) {
            
            cor_texto (vermelho);
            
        }
        
        else {
            
            estilo_texto (resetar);
            
        }

        if (parv -> compara (raiz -> valor, elemento_inserido) == 0) {

            //estilo_texto (piscar);
            estilo_texto (negrito);

        }
        
        parv -> imprime_valor (raiz -> valor);
        estilo_texto (resetar);
        imprime_arvore_rb (parv, raiz -> esq, profundidade + anda, elemento_inserido);
        
    }
    
}

tnode * rb_busca (tarv * parv, const void * reg) {
    
    tnode * x, * nulo;
    int compara_valor;
    
    x = parv -> raiz -> esq;
    nulo = parv -> nulo;
    
    if (x == nulo) {
        
        return NULL;
        
    }
    
    compara_valor = parv -> compara (x -> reg, reg);
    
    while (compara_valor != 0) {
        
        if (compara_valor > 0) {
            
            x = x -> esq;
            
        }
        
        else {
            
            x = x -> dir;
            
        }
        
        if (x == nulo) {
            
            return NULL;
            
        }
        
        compara_valor = parv -> compara (x -> reg, reg);
        
    }
    
    while (x -> esq != nulo && parv -> compara (reg, x -> esq -> reg) == 0) {
        
        x = x -> esq;
        
    }
    
    return x;
    
}

static void rb_remove_fix_up (tarv * parv, tnode * x) {
    
    tnode * raiz, * y;
    
    raiz = parv -> raiz -> esq;
    
    while ((!x -> VERMELHO) && (raiz != x)) {
        
        if (x == x -> pai -> esq) {
            
            y = x -> pai -> dir;
            
            if (y -> VERMELHO) {
                
                y -> VERMELHO = 0;
                x -> pai -> VERMELHO = 1;
                rb_rotacao_esquerda (parv, x -> pai);
                y = x -> pai -> dir;
                
            }
            
            if ((!y -> dir -> VERMELHO) && (!y -> esq -> VERMELHO)) { 
                
                y -> VERMELHO = 1;
                x = x -> pai;
                
            }
            
            else {
                
                if (!y -> dir -> VERMELHO) {
                    
                    y -> esq -> VERMELHO = 0;
                    y -> VERMELHO = 1;
                    rb_rotacao_direita (parv, y);
                    y = x -> pai -> dir;
                    
                }
                
                y -> VERMELHO = x -> pai -> VERMELHO;
                x -> pai -> VERMELHO = 0;
                y -> dir -> VERMELHO = 0;
                rb_rotacao_esquerda (parv, x -> pai);
                x = raiz; 
                
            }
            
        }
        
        else {
            
            y = x -> pai -> esq;
            
            if (y -> VERMELHO) {
                
                y -> VERMELHO = 0;
                x -> pai -> VERMELHO = 1;
                rb_rotacao_direita (parv, x -> pai);
                y = x -> pai -> esq;
                
            }
            
            if ((!y -> dir -> VERMELHO) && (!y -> esq -> VERMELHO)) {
                
                y -> VERMELHO = 1;
                x = x -> pai;
                
            }
            
            else {
                
                if (!y -> esq -> VERMELHO) {
                    
                    y -> dir -> VERMELHO = 0;
                    y -> VERMELHO = 1;
                    rb_rotacao_esquerda (parv, y);
                    y = x -> pai -> esq;
                    
                }
                
                y -> VERMELHO = x -> pai -> VERMELHO;
                x -> pai -> VERMELHO = 0;
                y -> esq -> VERMELHO = 0;
                rb_rotacao_direita (parv, x -> pai);
                x = raiz;
                
            }
            
        }
        
    }
    
    x -> VERMELHO = 0;
    
    assert(!parv -> nulo -> VERMELHO); 
    
}

void rb_remove (tarv * parv, tnode * z) {
    
    tnode * x, * y, * nulo, * raiz;
    
    nulo = parv -> nulo;
    raiz = parv -> raiz;
    
    y = ((z -> esq == nulo) || (z -> dir == nulo)) ? z : rb_sucessor (parv, z);
    x = (y -> esq == nulo) ? y -> dir : y -> esq;
    
    if (raiz == (x -> pai = y -> pai)) {
        
        raiz -> esq = x;
        
    }
    
    else {
        
        if (y == y -> pai -> esq) {
            
            y -> pai -> esq = x;
            
        }
        
        else {
            
            y -> pai -> dir = x;
            
        }
        
    }
    
    if (y != z) {
        
        assert ((y!=parv -> nulo)); 
        
        if (!(y -> VERMELHO)) {
            
            rb_remove_fix_up (parv, x);
            
        }
        
        parv -> destroi_reg (z -> reg);
        parv -> destroi_valor (z -> valor);
        
        y -> esq = z -> esq;
        y -> dir = z -> dir;
        y -> pai = z -> pai;
        y -> VERMELHO = z -> VERMELHO;
        z -> esq -> pai = z -> dir -> pai = y;
        
        if (z == z -> pai -> esq) {
            
            z -> pai -> esq = y; 
            
        }
        
        else {
            
            z -> pai -> dir = y;
            
        }
        
        free(z); 
        
    }
    
    else {
        
        parv -> destroi_reg (y -> reg);
        parv -> destroi_valor (y -> valor);
        
        if (!(y -> VERMELHO)) {
            
            rb_remove_fix_up (parv, x);
            
        }
        
        free(y);
        
    }
    
    -- parv -> size;
    
#ifdef VERIFICA_RED_BLACK
    
    assert (rb_verifica (parv));
    
#endif
    
}

static int _rb_verifica (tarv * parv, tnode * z, int blacks, int *blackmatch, unsigned int *count) {
    
    if (z -> VERMELHO) {
        
        if (z -> esq -> VERMELHO) {
            
            return 0;
            
        }
        
        if (z -> dir -> VERMELHO) {
            
            return 0;
            
        }
        
    }
    
    if (!z -> VERMELHO) {
        
        ++ blacks;
        
    }
    
    if (++ (* count) > parv -> size) {
        
        return 0;
        
    }
    
    if (z -> esq != parv -> nulo) {
        
        if (!_rb_verifica (parv, z -> esq, blacks, blackmatch, count)) {
            
            return 0;
            
        }
        
    }
    
    else {
        
        if (* blackmatch < 0) {
            
            * blackmatch = blacks;
            
        }
        
        else if (* blackmatch != blacks) {
            
            return 0;
            
        }
        
    }
    
    if (z -> dir != parv -> nulo) {
        
        if (!_rb_verifica (parv, z -> dir, blacks, blackmatch, count)) {
            
            return 0;
            
        }
        
    }
    
    else {
        
        if (* blackmatch < 0) {
            
            * blackmatch = blacks;
            
        }
        
        else if (* blackmatch != blacks) {
            
            return 0;
            
        }
        
    }
    
    return 1;
    
}

int rb_verifica (tarv * parv) {
    
    int blackmatch = - 1;
    unsigned int count = 0;
    
    if (parv -> nulo -> VERMELHO) {
        
        return 0;
        
    }
    
    if (parv -> raiz -> esq -> VERMELHO) {
        
        return 0;
        
    }
    
    if (parv -> raiz -> esq != parv -> nulo) {
        
        if (!_rb_verifica (parv, parv -> raiz -> esq, 0, &blackmatch, &count)) {
            
            return 0;
            
        }
        
    }
    
    if (count != parv -> size){
        
        return 0;
        
    }
    
    return 1;
    
}

/* * * * * * * * * * * * Funções (Teste) * * * * * * * * * * * */

void teste_caracter (void) {

    int i;
    char str [512];
    tnode * node;
    tarv * parv; 
    parv = rb_constroi (compara_caracter, free_caracter, free_caracter, imprime_caracter, imprime_caracter);
    
    assert (rb_vazia (parv) == 1);
    
    srand(4545);
    
    for (i = 0; i < 10000; i ++) {
        
        snprintf (str, sizeof (str), "Teste : %d", rand () % 1000000);
        rb_insere (parv, strdup (str), strdup ("Valor"));

    }
    
    srand(4545);

    for (i = 0; i < 10000; i ++) {

        snprintf (str, sizeof (str), "Teste : %d", rand () % 1000000);
        node = rb_busca (parv, str);
        assert (node);

    }    
    
    {
        node = rb_busca (parv, "Teste : 46554A");
        assert (node == NULL);
    }
    
    assert (rb_vazia (parv) == 0);
    assert (rb_tamanho (parv) == 10000);
    
    srand(4545);

    for (i = 0; i < 10000; i ++) {

        snprintf (str, sizeof (str), "Teste : %d", rand () % 1000000);
        node = rb_busca (parv, str);
        assert (node);
        rb_remove (parv, node);

    }
    
    assert (rb_vazia (parv) == 1);
    assert (rb_tamanho (parv) == 0);
    
    rb_destroi (parv);
}

void teste_inteiro (void) {

    int i;
    intptr_t val;
    tnode * node;
    tarv * parv;
    parv = rb_constroi (compara_inteiro, free_inteiro, free_inteiro, imprime_inteiro, imprime_inteiro);
    
    assert (rb_vazia (parv) == 1);
    
    srand (4545);

    for (i = 0; i < 10000; i ++) {

        val = rand () % 1000000;
        rb_insere (parv, (void *)val, (void *)val);

    }
    
    srand (4545);

    for (i = 0; i < 10000; i ++) {

        val = rand () % 1000000;
        node = rb_busca (parv, (void *)val);
        assert (node);

    }    
    
    {
        node = rb_busca (parv, (void *)234324);
        assert (node == NULL);
    }
    
    assert (rb_vazia (parv) == 0);
    assert (rb_tamanho (parv) == 10000);
    
    srand(4545);

    for (i = 0; i < 10000; i ++) {

        val = rand () % 1000000;
        node = rb_busca (parv, (void *)val);
        assert (node);
        rb_remove (parv, node);

    }
    
    assert (rb_vazia (parv) == 1);
    assert (rb_tamanho (parv) == 0);
    
    rb_destroi (parv);
}

void confere_funcionamento (void) {

    cor_texto (ciano);
    printf ("\n       * * * * * * * * ");
    estilo_texto (resetar);

    cor_texto (amarelo);
    printf ("CONFERE FUNCIONAMENTO");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf (" * * * * * * * *\n       *                                                   *\n");
    estilo_texto (resetar);

    teste_caracter ();
    teste_inteiro ();

    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);

    cor_texto (vermelho);
    printf("         * ");
    estilo_texto (resetar);

    printf ("Construção Rubro - Negra ");
    cor_texto (verde);
    printf("      OK");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *\n");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);

    cor_texto (vermelho);
    printf("         * ");
    estilo_texto (resetar);

    printf ("Inserção Rubro - Negra ");
    cor_texto (verde);
    printf("        OK");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *\n");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);

    cor_texto (vermelho);
    printf("         * ");
    estilo_texto (resetar);

    printf ("Busca Rubro - Negra ");
    cor_texto (verde);
    printf("           OK");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *\n");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);

    cor_texto (vermelho);
    printf("         * ");
    estilo_texto (resetar);

    printf ("Remoção Rubro - Negra ");
    cor_texto (verde);
    printf("         OK");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *\n");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf ("       *                                                   *\n       * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
    estilo_texto (resetar);

}

void teste_tempo_execucao (int n) {

    clock_t inicio, fim;
    double tempo [2], insersao [4], remocao [4];
    int i;
    intptr_t * v;
    tnode * node;
    tarv * parv;

    parv = rb_constroi (compara_inteiro, free_inteiro, free_inteiro, imprime_inteiro, imprime_inteiro);

    srand (time (NULL));

    v = (intptr_t *) malloc (n * sizeof (intptr_t));
    
    for (i = 0; i < n; i ++) {

        * (v + i) = rand () % (n * 4);

    }
    
    cor_texto (ciano);
    printf ("       * * * * * * * * ");
    estilo_texto (resetar);

    cor_texto (amarelo);
    printf("TEMPO DE EXECUÇÃO (TESTE)");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf (" * * * * * *\n");
    printf("       *                                                   *\n");
    printf ("       *           ");
    estilo_texto (resetar);

    cor_texto (vermelho);
    printf("Quantidade de Elementos : %d", n);
    estilo_texto (resetar);

    cor_texto (ciano);
    printf ("       *\n");
    printf("       *                                                   *\n");
    estilo_texto (resetar);

    /* Árvore Red Black */

    inicio = clock ();

    for (i = 0; i < n; i ++) {

        rb_insere (parv, (void *) (* (v + i)), (void *) (* (v + i)));

    }

    fim = clock ();
    tempo [0] = ( (double) (fim - inicio) ) / CLOCKS_PER_SEC;

    inicio = clock ();

    for (i = 0; i < n; i ++) {

        node = rb_busca (parv, (void *) (* (v + i)));
        assert (node);
        rb_remove (parv, node);

    } 

    fim = clock ();
    tempo [1] = ( (double) (fim - inicio) ) / CLOCKS_PER_SEC;

    insersao [1] = tempo [0];
    remocao [1] = tempo [1];

    rb_destroi (parv);

    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);

    cor_texto (verde);
    printf ("         * ");
    cor_texto (magenta);
    printf ("RB ");
    estilo_texto (resetar);
    printf("Inserção : %.6lf segundos     ", insersao [1]);

    cor_texto (ciano);
    printf("    *\n");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);

    cor_texto (verde);
    printf ("         * ");
    cor_texto (magenta);
    printf ("RB ");
    estilo_texto (resetar);
    printf ("Remoção  : %.6lf segundos     ", remocao [1]);

    cor_texto (ciano);
    printf("    *\n");
    estilo_texto (resetar);

    cor_texto (ciano);
    printf("       *                                                   *\n");
    printf("       * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
    estilo_texto (resetar);

    free (v);

}
