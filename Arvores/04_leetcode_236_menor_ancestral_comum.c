/*
 * ============================================================================
 * LeetCode 236 (Medium) - Lowest Common Ancestor of a Binary Tree
 * ============================================================================
 * Ligação direta com a Aula 8, slide 5 e 7:
 *
 *   slide 5: "Se ni é antecedente a nk, nk é descendente de ni"
 *   slide 7: "'A' é um ancestral de 'G'", "'G' é um descendente de 'A'"
 *
 * O problema pede o "Lowest Common Ancestor" (LCA) = o ANCESTRAL COMUM
 * mais PROFUNDO (mais próximo das folhas) entre dois nós p e q.
 * Ou seja: o nó mais "baixo" na árvore que ainda é ancestral de p E de q.
 *
 * IDEIA (baseada em pós-ordem, slide 11 - resolve os filhos antes do pai):
 *   - Se o nó atual é NULL, ou é igual a p, ou é igual a q -> retorna o
 *     próprio nó atual (ele é candidato a resposta ou ponto de parada).
 *   - Busca recursivamente à esquerda e à direita.
 *   - Se AMBOS os lados encontraram algo (não-NULL), significa que p está
 *     de um lado e q está do outro -> o nó ATUAL é o LCA.
 *   - Se só um lado encontrou algo, o LCA está inteiramente daquele lado
 *     -> repassamos esse resultado para cima.
 *
 * Complexidade: O(n) tempo (visita cada nó no máximo uma vez),
 * O(h) espaço (pilha de recursão, h = altura da árvore - slide 6).
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

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

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    /* Caso base: chegamos ao fim de um ramo, ou encontramos p, ou
       encontramos q. Em qualquer um desses casos, devolvemos o nó atual
       para quem chamou decidir o que fazer com ele. */
    if (root == NULL || root == p || root == q) {
        return root;
    }

    /* Busca nos dois lados -- exatamente como uma pós-ordem (slide 11):
       resolvemos os filhos ANTES de decidir algo sobre o nó atual. */
    TreeNode *esquerda = lowestCommonAncestor(root->left, p, q);
    TreeNode *direita  = lowestCommonAncestor(root->right, p, q);

    /* Achou em ambos os lados -> p e q estao em ramos diferentes ->
       o nó ATUAL é o ancestral comum mais baixo (a "bifurcacao"). */
    if (esquerda != NULL && direita != NULL) {
        return root;
    }

    /* So achou de um lado -> o LCA esta inteiramente naquele lado,
       entao repassamos esse resultado para cima na recursao. */
    return (esquerda != NULL) ? esquerda : direita;
}

int main(void) {
    /*            3
     *          /   \
     *         5     1
     *        / \   / \
     *       6   2 0   8
     *          / \
     *         7   4
     */
    TreeNode *n3 = newNode(3);
    TreeNode *n5 = newNode(5);
    TreeNode *n1 = newNode(1);
    TreeNode *n6 = newNode(6);
    TreeNode *n2 = newNode(2);
    TreeNode *n0 = newNode(0);
    TreeNode *n8 = newNode(8);
    TreeNode *n7 = newNode(7);
    TreeNode *n4 = newNode(4);

    n3->left = n5; n3->right = n1;
    n5->left = n6; n5->right = n2;
    n1->left = n0; n1->right = n8;
    n2->left = n7; n2->right = n4;

    /* Caso 1: LCA(5, 1) deve ser a raiz 3 (estao em ramos diferentes) */
    TreeNode *lca1 = lowestCommonAncestor(n3, n5, n1);
    printf("LCA(5, 1) = %d (esperado: 3)\n", lca1->val);

    /* Caso 2: LCA(5, 4) deve ser 5 (4 e descendente de 5) */
    TreeNode *lca2 = lowestCommonAncestor(n3, n5, n4);
    printf("LCA(5, 4) = %d (esperado: 5)\n", lca2->val);

    return 0;
}
