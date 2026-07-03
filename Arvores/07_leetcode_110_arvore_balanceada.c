/*
 * ============================================================================
 * LeetCode 110 (Medium/Easy-Medium na pratica) - Balanced Binary Tree
 * ============================================================================
 * Ligação direta com a Aula 9 (Árvore AVL). A AVL nasce exatamente do
 * conceito cobrado aqui: o FATOR DE BALANCEAMENTO de um nó, definido nos
 * slides da Aula 9 como:
 *
 *      FB(no) = altura(subarvore_direita) - altura(subarvore_esquerda)
 *
 * Uma árvore é "AVL-balanceada" se, para TODO nó, |FB(no)| <= 1.
 * Esse exercicio do LeetCode pede exatamente essa verificação: dada uma
 * árvore binária qualquer, dizer se ela satisfaz essa propriedade em
 * TODOS os seus nós (não só na raiz).
 *
 * Isso é o PRIMEIRO passo antes de implementar rotações de AVL (LL, RR,
 * LR, RL - vistas na Aula 9): antes de rotacionar, é preciso saber
 * DETECTAR o desbalanceamento.
 *
 * TÉCNICA (pós-ordem, slide 11 da Aula 8): calculamos a altura dos
 * filhos ANTES de decidir se o nó atual está balanceado, e propagamos
 * um valor "sentinela" (-1) para cima assim que qualquer desbalanceamento
 * é detectado, cortando o resto do processamento.
 *
 * Complexidade: O(n) tempo (cada nó visitado uma vez), O(h) espaço.
 * (Uma implementação ingênua que recalcula a altura a cada nó separadamente
 * seria O(n^2) -- por isso combinamos "calcular altura" e "checar
 * balanceamento" na MESMA passada pós-ordem.)
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

#define DESBALANCEADO -1

/*
 * alturaOuDesbalanceado: retorna a altura do no (>= 0) se a subarvore
 * dele for balanceada; retorna DESBALANCEADO (-1) assim que encontrar
 * QUALQUER nó, em qualquer profundidade, cujo |FB| > 1.
 */
int alturaOuDesbalanceado(TreeNode *no) {
    if (no == NULL) return 0;   /* altura da arvore vazia = 0 */

    /* Pos-ordem (slide 11 Aula 8): resolve os filhos antes do pai */
    int alturaEsq = alturaOuDesbalanceado(no->left);
    if (alturaEsq == DESBALANCEADO) return DESBALANCEADO; /* corta cedo */

    int alturaDir = alturaOuDesbalanceado(no->right);
    if (alturaDir == DESBALANCEADO) return DESBALANCEADO; /* corta cedo */

    /* Fator de Balanceamento (Aula 9): diferenca entre as alturas */
    int fatorBalanceamento = alturaDir - alturaEsq;
    if (fatorBalanceamento < -1 || fatorBalanceamento > 1) {
        return DESBALANCEADO;
    }

    /* Se chegou aqui, o no atual esta OK; devolve a altura normalmente
       para que o PAI possa continuar o calculo. */
    int maior = (alturaEsq > alturaDir) ? alturaEsq : alturaDir;
    return 1 + maior;
}

bool isBalanced(TreeNode *root) {
    return alturaOuDesbalanceado(root) != DESBALANCEADO;
}

int main(void) {
    /* Arvore BALANCEADA:
     *        1
     *       / \
     *      2   2
     *     / \
     *    3   3
     */
    TreeNode *balanceada = newNode(1);
    balanceada->left = newNode(2);
    balanceada->right = newNode(2);
    balanceada->left->left = newNode(3);
    balanceada->left->right = newNode(3);
    printf("Arvore balanceada?      %s (esperado: sim)\n",
           isBalanced(balanceada) ? "sim" : "nao");

    /* Arvore DESBALANCEADA (classico caso que motiva rotacao LL na AVL):
     *          1
     *         /
     *        2
     *       /
     *      3
     */
    TreeNode *desbalanceada = newNode(1);
    desbalanceada->left = newNode(2);
    desbalanceada->left->left = newNode(3);
    printf("Arvore desbalanceada?   %s (esperado: nao)\n",
           isBalanced(desbalanceada) ? "sim" : "nao");

    return 0;
}
