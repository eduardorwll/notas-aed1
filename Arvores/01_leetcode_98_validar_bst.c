/*
 * ============================================================================
 * LeetCode 98 (Medium) - Validate Binary Search Tree
 * ============================================================================
 * Liga direto com a Aula 8, slide 17 ("Árvores Binárias de Pesquisa sem
 * Balanceamento"):
 *
 *   "Para qualquer nó que contenha um registro, temos a relação invariante:
 *    - Todos os registros com chaves MENORES estão na subárvore à ESQUERDA.
 *    - Todos os registros com chaves MAIORES estão na subárvore à DIREITA."
 *
 * O ERRO MAIS COMUM (e a pegadinha do exercício) é validar só comparando
 * o nó com seus filhos diretos. Isso está ERRADO porque a regra da BST
 * vale para TODA a subárvore, não só para o filho imediato.
 * Exemplo de árvore INVÁLIDA que passaria numa checagem ingênua:
 *
 *            5
 *           / \
 *          1   4
 *             / \
 *            3   6      <- 3 é menor que 5, mas está na subárvore direita!
 *
 * SOLUÇÃO 1: usar limites (min, max) que vão sendo restringidos na recursão
 * (essa é a forma mais usada em entrevistas).
 * SOLUÇÃO 2: usar EM-ORDEM (slide 10) -- numa BST válida, a em-ordem sempre
 * gera uma sequência estritamente crescente. Também implementada abaixo.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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

/* -----------------------------------------------------------------------
 * SOLUÇÃO 1: Recursão com limites (min, max)
 * Cada chamada recebe o intervalo de valores permitido para o nó atual.
 * Ao descer para a esquerda, o limite MÁXIMO passa a ser o valor do pai.
 * Ao descer para a direita, o limite MÍNIMO passa a ser o valor do pai.
 * Complexidade: O(n) tempo, O(h) espaço (h = altura, pilha de recursão).
 * ----------------------------------------------------------------------- */
bool validarComLimites(TreeNode *no, long min, long max) {
    if (no == NULL) return true;         /* árvore vazia é válida (slide 8) */

    /* Viola a invariante do slide 17? */
    if (no->val <= min || no->val >= max) return false;

    /* Esquerda: todos devem ser < no->val  -> novo teto (max) é no->val   */
    /* Direita : todos devem ser > no->val  -> novo piso (min) é no->val   */
    return validarComLimites(no->left, min, no->val) &&
           validarComLimites(no->right, no->val, max);
}

bool isValidBST_limites(TreeNode *root) {
    /* Usamos long + LONG_MIN/LONG_MAX para não ter problema se o valor
       do nó for exatamente INT_MIN ou INT_MAX. */
    return validarComLimites(root, LONG_MIN, LONG_MAX);
}

/* -----------------------------------------------------------------------
 * SOLUÇÃO 2: Em-ordem (slide 10) deve ser estritamente crescente
 * Mantemos o "último valor visitado" e comparamos a cada passo.
 * ----------------------------------------------------------------------- */
bool emOrdemCrescente(TreeNode *no, long *ultimo) {
    if (no == NULL) return true;

    if (!emOrdemCrescente(no->left, ultimo)) return false;

    /* Aqui é exatamente o "Lista(n)" da Aula 8, só que em vez de
       imprimir, comparamos com o valor anterior da sequência. */
    if (no->val <= *ultimo) return false;
    *ultimo = no->val;

    return emOrdemCrescente(no->right, ultimo);
}

bool isValidBST_emOrdem(TreeNode *root) {
    long ultimo = LONG_MIN;
    return emOrdemCrescente(root, &ultimo);
}

/* ---------------------------------------------------------------------- */
int main(void) {
    /* Árvore INVÁLIDA de propósito (exemplo clássico do enunciado):
     *         5
     *        / \
     *       1   4
     *          / \
     *         3   6
     */
    TreeNode *root = newNode(5);
    root->left = newNode(1);
    root->right = newNode(4);
    root->right->left = newNode(3);
    root->right->right = newNode(6);

    printf("Metodo limites : %s\n", isValidBST_limites(root) ? "valida" : "INVALIDA");
    printf("Metodo em-ordem: %s\n", isValidBST_emOrdem(root) ? "valida" : "INVALIDA");

    /* Árvore VÁLIDA */
    TreeNode *root2 = newNode(5);
    root2->left = newNode(3);
    root2->right = newNode(8);
    printf("Arvore 2 (valida) -> metodo limites : %s\n",
           isValidBST_limites(root2) ? "valida" : "INVALIDA");

    return 0;
}
