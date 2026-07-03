/*
 * ============================================================================
 * LeetCode 230 (Medium) - Kth Smallest Element in a BST
 * ============================================================================
 * Aplicação quase literal do slide 10 da Aula 8 (Caminhamento Central/
 * Em-ordem) combinada com o slide 17 (invariante da BST):
 *
 *   "Todos os registros com chaves menores estão na subárvore à esquerda,
 *    todos com chaves maiores estão na subárvore à direita" (slide 17)
 *
 * Consequência direta: se percorrermos a árvore em EM-ORDEM (esquerda,
 * raiz, direita - slide 10), os valores saem em ORDEM CRESCENTE.
 * Logo, o K-ésimo menor elemento é simplesmente o K-ésimo valor
 * visitado nessa travessia.
 *
 * Aqui implementamos de forma OTIMIZADA: paramos a recursão assim que
 * encontramos o k-ésimo elemento, em vez de percorrer a árvore inteira.
 * Complexidade: O(h + k) tempo no melhor caso (h = altura, slide 6),
 * O(h) espaço de pilha de recursão.
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

/*
 * emOrdemComParada: mesma lógica do slide 10, mas com dois "extras":
 *   - contador: quantos nós já visitamos na em-ordem até agora
 *   - resultado: onde guardamos o valor quando contador == k
 *   - encontrado: flag para CORTAR a recursão assim que achamos a resposta
 *     (evita percorrer o resto da árvore à toa)
 */
void emOrdemComParada(TreeNode *no, int k, int *contador,
                       int *resultado, bool *encontrado) {
    if (no == NULL || *encontrado) return;

    /* 1) Visita a subárvore ESQUERDA primeiro (slide 10) */
    emOrdemComParada(no->left, k, contador, resultado, encontrado);
    if (*encontrado) return;   /* ja achamos do lado esquerdo, nao precisa seguir */

    /* 2) "Lista(n)" do slide 10 -- aqui, em vez de imprimir, contamos */
    (*contador)++;
    if (*contador == k) {
        *resultado = no->val;
        *encontrado = true;
        return;
    }

    /* 3) Só then visita a subárvore DIREITA (slide 10) */
    emOrdemComParada(no->right, k, contador, resultado, encontrado);
}

int kthSmallest(TreeNode *root, int k) {
    int contador = 0;
    int resultado = -1;
    bool encontrado = false;
    emOrdemComParada(root, k, &contador, &resultado, &encontrado);
    return resultado;
}

int main(void) {
    /*        5
     *       / \
     *      3   6
     *     / \
     *    2   4
     *   /
     *  1
     */
    TreeNode *root = newNode(5);
    root->left = newNode(3);
    root->right = newNode(6);
    root->left->left = newNode(2);
    root->left->right = newNode(4);
    root->left->left->left = newNode(1);

    for (int k = 1; k <= 6; k++) {
        printf("%dº menor elemento = %d\n", k, kthSmallest(root, k));
    }
    /* Sequencia em-ordem esperada: 1 2 3 4 5 6 */

    return 0;
}
