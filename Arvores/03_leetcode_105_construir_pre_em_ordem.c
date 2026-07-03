/*
 * ============================================================================
 * LeetCode 105 (Medium) - Construct Binary Tree from Preorder and Inorder
 * Traversal
 * ============================================================================
 * Este exercício é quase um "exercício de prova" direto da Aula 8,
 * slides 9 e 10 (Pré-ordem e Em-ordem/Central). A ideia central:
 *
 *   1) Na PRÉ-ORDEM (slide 9), o PRIMEIRO elemento listado é SEMPRE a raiz
 *      da árvore (ou subárvore) atual: "lista o nó raiz, seguido de suas
 *      subárvores".
 *
 *   2) Na EM-ORDEM (slide 10), a raiz aparece NO MEIO: tudo o que está à
 *      esquerda dela na lista é a subárvore ESQUERDA, e tudo à direita é
 *      a subárvore DIREITA ("lista subárvore esquerda, lista raiz,
 *      lista subárvore direita").
 *
 * Juntando os dois fatos: usamos o próximo elemento da pré-ordem para
 * descobrir a raiz, localizamos essa raiz na em-ordem para saber o
 * TAMANHO da subárvore esquerda, e repetimos recursivamente.
 *
 * Exemplo:
 *   preorder = [3, 9, 20, 15, 7]
 *   inorder  = [9, 3, 15, 20, 7]
 *
 *   - Primeiro da pré-ordem = 3  -> raiz da árvore inteira
 *   - Posição de 3 na em-ordem = índice 1
 *       -> subárvore esquerda em-ordem = [9]         (1 elemento)
 *       -> subárvore direita  em-ordem = [15, 20, 7]  (3 elementos)
 *   - Repete o processo recursivamente para cada lado.
 *
 * Complexidade: O(n) usando um mapa de valor->índice na em-ordem para
 * não precisar buscar linearmente a cada chamada (aqui simplificamos com
 * busca linear O(n) por chamada = O(n^2) no pior caso, e comentamos como
 * otimizar para O(n) com um vetor de índices).
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

/* Encontra o índice de "valor" dentro de inorder[esq..dir] (busca linear).
 * OTIMIZAÇÃO (não implementada aqui para manter o código didático):
 * pré-processar um vetor `indiceNaEmOrdem[valor] = posicao` em O(n) uma
 * única vez, transformando cada busca em O(1) e o algoritmo inteiro em O(n). */
int encontrarNaEmOrdem(int *inorder, int esq, int dir, int valor) {
    for (int i = esq; i <= dir; i++) {
        if (inorder[i] == valor) return i;
    }
    return -1; /* nao deveria acontecer se as entradas forem validas */
}

/*
 * preIdx: índice "global" (passado por ponteiro) que indica qual é o
 * PRÓXIMO elemento não usado da pré-ordem. Como a pré-ordem sempre lista
 * a raiz ANTES dos filhos (slide 9), cada chamada recursiva simplesmente
 * consome (e avança) esse índice.
 */
TreeNode *construir(int *preorder, int *preIdx,
                     int *inorder, int inEsq, int inDir) {
    if (inEsq > inDir) return NULL;   /* subárvore vazia */

    /* Passo 1 (slide 9): o próximo valor da pré-ordem é a raiz atual */
    int valorRaiz = preorder[*preIdx];
    (*preIdx)++;
    TreeNode *raiz = newNode(valorRaiz);

    /* Passo 2 (slide 10): localizamos a raiz na em-ordem para separar
       o que é subárvore esquerda do que é subárvore direita */
    int posRaiz = encontrarNaEmOrdem(inorder, inEsq, inDir, valorRaiz);

    /* Passo 3: a subárvore ESQUERDA usa os elementos de inorder[inEsq..posRaiz-1]
       e, como a pré-ordem lista a esquerda inteira antes da direita, o
       próximo bloco de preIdx corresponde exatamente a essa subárvore. */
    raiz->left  = construir(preorder, preIdx, inorder, inEsq, posRaiz - 1);

    /* Passo 4: a subárvore DIREITA usa o restante: inorder[posRaiz+1..inDir] */
    raiz->right = construir(preorder, preIdx, inorder, posRaiz + 1, inDir);

    return raiz;
}

TreeNode *buildTree(int *preorder, int preSize, int *inorder, int inSize) {
    (void)preSize; /* preSize == inSize sempre, mantido so pela assinatura padrao do LeetCode */
    int preIdx = 0;
    return construir(preorder, &preIdx, inorder, 0, inSize - 1);
}

/* Reaproveita a em-ordem (slide 10) so para IMPRIMIR e conferir o resultado */
void emOrdem(TreeNode *n) {
    if (n == NULL) return;
    emOrdem(n->left);
    printf("%d ", n->val);
    emOrdem(n->right);
}

void preOrdem(TreeNode *n) {
    if (n == NULL) return;
    printf("%d ", n->val);
    preOrdem(n->left);
    preOrdem(n->right);
}

int main(void) {
    int preorder[] = {3, 9, 20, 15, 7};
    int inorder[]  = {9, 3, 15, 20, 7};
    int n = 5;

    TreeNode *root = buildTree(preorder, n, inorder, n);

    printf("Pre-ordem reconstruida (deve bater com a entrada): ");
    preOrdem(root); printf("\n");

    printf("Em-ordem reconstruida (deve bater com a entrada) : ");
    emOrdem(root); printf("\n");

    return 0;
}
