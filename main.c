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
#include <time.h>
#include "rb.h"

int main (void) {
    
    confere_funcionamento ();
    
    int n, i;
    clock_t inicio, fim;
    double tempo [2];
    intptr_t * v;
    tnode * node;
    tarv * parv;

    parv = rb_constroi (compara_inteiro, free_inteiro, free_inteiro, imprime_inteiro, imprime_inteiro);

    printf ("Quantidade de Elementos : ");
    scanf ("%d", &n);

    v = (intptr_t *) malloc (n * sizeof (intptr_t));

    printf ("\nVetor : ");
    
    for (i = 0; i < n; i ++) {

        scanf ("%ld", v + i);

    }
    
    printf("\n");
    
    /* Inserção em RB */
    
    inicio = clock ();
    
    for (i = 0; i < n; i ++) {
        
        cor_texto (ciano);
        printf ("\n* * * * * * * * ");
        estilo_texto (resetar);
        printf ("Inserção RB");
        cor_texto (ciano);
        printf (" * * * * * * * *\n\n");
        estilo_texto (resetar);
        
        printf ("Insere : ");
        cor_texto (verde);
        printf ("%ld\n\n", * (v + i));
        estilo_texto (resetar);
        
        rb_insere (parv, (void *) (* (v + i)), (void *) (* (v + i)));

        imprime_arvore_rb (parv, parv -> raiz -> esq, 0, (void *) (* (v + i)));
        
        estilo_texto (resetar);
        
    }
    
    fim = clock ();
    
    tempo [0] = ( (double) (fim - inicio) ) / CLOCKS_PER_SEC;
    
    /* Remoção em RB */
    
    inicio = clock ();

    for (i = 0; i < n; i ++) {
        
        cor_texto (ciano);
        printf ("\n\n* * * * * * * * ");
        estilo_texto (resetar);
        printf ("Remoção RB");
        cor_texto (ciano);
        printf (" * * * * * * * *\n\n");
        estilo_texto (resetar);
        
        printf ("Remove : ");
        cor_texto (verde);
        printf ("%ld\n\n", (intptr_t)(parv -> raiz -> esq -> valor));
        estilo_texto (resetar);
        
        node = rb_busca (parv, parv -> raiz -> esq -> valor);
        assert (node);
        rb_remove (parv, node);

        imprime_arvore_rb (parv, parv -> raiz -> esq, 0, parv -> raiz -> esq -> valor);
        
        if (parv -> raiz -> esq == parv -> nulo) {
            
            cor_texto (verde);
            printf("       * * * * * *\n       *");
            estilo_texto (resetar);
            
            cor_texto (vermelho);
            printf ("   NULL  ");
            estilo_texto (resetar);
            
            cor_texto (verde);
            printf("*\n       * * * * * *\n");
            estilo_texto (resetar);
            
        }
        
    }
    
    printf ("\n");
    
    fim = clock ();
    
    tempo [1] = ( (double) (fim - inicio) ) / CLOCKS_PER_SEC;
    
    cor_texto (ciano);
    printf ("       * * * * * * * * * ");
    estilo_texto (resetar);
    
    cor_texto (amarelo);
    printf("TEMPO DE EXECUÇÃO");
    estilo_texto (resetar);
    
    cor_texto (ciano);
    printf (" * * * * * * * * *\n");
    printf("       *                                                   *\n");
    estilo_texto (resetar);
    
    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);
    
    cor_texto (verde);
    printf ("         * ");
    cor_texto (magenta);
    printf ("AVL ");
    estilo_texto (resetar);
    printf ("Inserção : %.6lf segundos    ", tempo [0]);
    
    cor_texto (ciano);
    printf("    *\n");
    estilo_texto (resetar);
    
    cor_texto (ciano);
    printf("       *");
    estilo_texto (resetar);
    
    cor_texto (verde);
    printf ("         * ");
    cor_texto (magenta);
    printf ("AVL ");
    estilo_texto (resetar);
    printf ("Remoção  : %.6lf segundos    ", tempo [1]);
    
    cor_texto (ciano);
    printf("    *\n");
    estilo_texto (resetar);
    
    cor_texto (ciano);
    printf("       *                                                   *\n");
    printf("       * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
    estilo_texto (resetar);
    
    rb_destroi (parv);
    free (v);
    
    cor_texto (vermelho);
    estilo_texto (piscar);
    printf ("                          FIM DE EXECUÇÃO\n\n");
    estilo_texto (resetar);
    
    return 0;
    
}
