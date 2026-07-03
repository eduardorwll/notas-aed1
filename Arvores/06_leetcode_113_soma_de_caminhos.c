/*
 * ============================================================================
 * LeetCode 113 (Medium) - Path Sum II
 * ============================================================================
 * Usa diretamente a definição de CAMINHO da Aula 8, slide 5:
 *
 *   "Um caminho de ni a nk, onde ni é antecedente a nk, é a sequência de
 *    nós para se chegar de ni a nk."
 *
 * O exercício pede: encontrar TODOS os caminhos da RAIZ até uma FOLHA
 * (slide 6: "nós que não têm descendentes são chamados de nós folhas")
 * cuja SOMA dos valores seja igual a um alvo dado.
 *
 * TÉCNICA: backtracking (tentativa e retrocesso) sobre uma pré-ordem
 * (slide 9 - visitamos a raiz ANTES dos filhos, pois precisamos "descer"
 * acumulando o caminho atual antes de decidir se ele é valido):
 *   1. Adiciona o nó atual no caminho e soma seu valor.
 *   2. Se é folha E a soma bate com o alvo -> salva uma cópia do caminho.
 *   3. Senão, tenta recursivamente esquerda e direita.
 *   4. Ao VOLTAR (backtrack), REMOVE o nó atual do caminho -- fundamental,
 *      pois o mesmo vetor de caminho é reaproveitado para todos os ramos.
 *
 * Complexidade: O(n^2) no pior caso (cada um dos até n caminhos pode ter
 * até n nós, para copiar quando é valido); O(h) de espaço para o caminho
 * em construção (h = altura, slide 6).
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *newNode(int val) {
    TreeNode *n = (TreeNode *)malloc(sizeof(TreeNode));
    n->val = val; n->left = NULL; n->right = NULL;
    return n;
}

#define MAX_ALTURA 1000   /* limite pratico para o vetor do caminho atual */

/* Variaveis globais so para simplificar o exemplo didatico (numa solucao
   "de producao" isso viraria uma struct de contexto passada por parametro) */
int caminhoAtual[MAX_ALTURA];
int topoCaminho = 0;

int **resultados;
int *tamanhosResultados;
int totalResultados = 0;

void salvarCaminhoAtual(void) {
    int *copia = (int *)malloc(sizeof(int) * topoCaminho);
    for (int i = 0; i < topoCaminho; i++) copia[i] = caminhoAtual[i];
    resultados[totalResultados] = copia;
    tamanhosResultados[totalResultados] = topoCaminho;
    totalResultados++;
}

void buscarCaminhos(TreeNode *no, int somaRestante) {
    if (no == NULL) return;

    /* 1) Adiciona o no atual ao caminho (equivalente ao "Lista(n)" da
          pre-ordem no slide 9, so que guardando em vez de imprimir) */
    caminhoAtual[topoCaminho++] = no->val;
    somaRestante -= no->val;

    /* 2) E folha (slide 6: sem filhos) E a soma do caminho bateu? */
    bool ehFolha = (no->left == NULL && no->right == NULL);
    if (ehFolha && somaRestante == 0) {
        salvarCaminhoAtual();
    } else {
        /* 3) Continua descendo (pre-ordem: esquerda depois direita) */
        buscarCaminhos(no->left, somaRestante);
        buscarCaminhos(no->right, somaRestante);
    }

    /* 4) BACKTRACK: remove o no atual antes de voltar para o pai,
          para que o vetor caminhoAtual fique correto para os OUTROS
          ramos da arvore que ainda serao visitados. */
    topoCaminho--;
}

int **pathSum(TreeNode *root, int targetSum, int *returnSize, int **returnColumnSizes) {
    resultados = (int **)malloc(sizeof(int *) * 10000);      /* capacidade generosa */
    tamanhosResultados = (int *)malloc(sizeof(int) * 10000);
    totalResultados = 0;
    topoCaminho = 0;

    buscarCaminhos(root, targetSum);

    *returnSize = totalResultados;
    *returnColumnSizes = tamanhosResultados;
    return resultados;
}

int main(void) {
    /*              5
     *            /   \
     *           4     8
     *          /     /  \
     *         11    13   4
     *        /  \        / \
     *       7    2      5   1
     *
     * targetSum = 22
     * Caminhos esperados: [5,4,11,2] e [5,8,4,5]
     */
    TreeNode *r = newNode(5);
    r->left = newNode(4);
    r->right = newNode(8);
    r->left->left = newNode(11);
    r->left->left->left = newNode(7);
    r->left->left->right = newNode(2);
    r->right->left = newNode(13);
    r->right->right = newNode(4);
    r->right->right->left = newNode(5);
    r->right->right->right = newNode(1);

    int returnSize;
    int *returnColumnSizes;
    int **caminhos = pathSum(r, 22, &returnSize, &returnColumnSizes);

    printf("Caminhos encontrados com soma 22:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("  [");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d%s", caminhos[i][j], (j < returnColumnSizes[i] - 1) ? ", " : "");
        }
        printf("]\n");
        free(caminhos[i]);
    }
    free(caminhos);
    free(returnColumnSizes);

    return 0;
}
