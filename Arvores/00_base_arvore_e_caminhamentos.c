/*
 * ============================================================================
 * 00 - BASE: Estrutura de Árvore Binária + Caminhamentos (Aula 8)
 * ============================================================================
 * Este arquivo é a BASE usada por todos os outros arquivos desta série.
 * Ele implementa exatamente o que a Aula 8 (Árvores) apresenta:
 *
 *   - Estrutura de nó (slide 20: "No" com pEsq/pDir -> aqui chamados left/right)
 *   - Pré-ordem  (slide 9)  -> raiz, esquerda, direita
 *   - Central/In-ordem (slide 10) -> esquerda, raiz, direita
 *   - Pós-ordem (slide 11) -> esquerda, direita, raiz
 *
 * Nos exercícios do LeetCode, a struct costuma se chamar "TreeNode" e os
 * campos "left"/"right"/"val". Usamos esses nomes para já deixar o código
 * no "idioma" que aparece nos enunciados do LeetCode, mas o CONCEITO é
 * idêntico ao "No" com pEsq/pDir da aula.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* Estrutura de nó de árvore binária (equivalente ao "No" do slide 20) */
typedef struct TreeNode {
    int val;                  /* Registro/Chave do slide 20 */
    struct TreeNode *left;    /* pEsq do slide 20 */
    struct TreeNode *right;   /* pDir do slide 20 */
} TreeNode;

/* Cria um novo nó folha (sem filhos) */
TreeNode *newNode(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*
 * PRÉ-ORDEM (slide 9): Lista(n) primeiro, depois os filhos da esquerda
 * para a direita, cada um em pré-ordem.
 * Uso típico: copiar/serializar a árvore, pois a raiz aparece antes dos
 * filhos (útil para reconstruir a árvore depois).
 */
void preOrdem(TreeNode *n) {
    if (n == NULL) return;      /* "Se T é uma árvore nula, a lista é nula" */
    printf("%d ", n->val);      /* Lista(n) */
    preOrdem(n->left);          /* PREORDEM(filho esquerdo) */
    preOrdem(n->right);         /* PREORDEM(filho direito) */
}

/*
 * CENTRAL / IN-ORDEM (slide 10): esquerda, raiz, direita.
 * Uso típico: em uma Árvore Binária de Pesquisa (BST), a in-ordem
 * sempre retorna os elementos EM ORDEM CRESCENTE. Isso é a base de
 * vários exercícios de LeetCode sobre BST (ex: Validar BST, K-ésimo menor).
 */
void emOrdem(TreeNode *n) {
    if (n == NULL) return;
    emOrdem(n->left);           /* CENTRAL(filho mais à esquerda) */
    printf("%d ", n->val);      /* Lista(n) */
    emOrdem(n->right);          /* CENTRAL(demais filhos) */
}

/*
 * PÓS-ORDEM (slide 11): filhos (esquerda -> direita), depois a raiz.
 * Uso típico: quando é preciso processar os filhos antes do pai,
 * por exemplo para liberar memória (destruir a árvore) ou para
 * calcular propriedades "de baixo para cima" (altura, soma de subárvore).
 */
void posOrdem(TreeNode *n) {
    if (n == NULL) return;
    posOrdem(n->left);
    posOrdem(n->right);
    printf("%d ", n->val);      /* Lista(n) por último */
}

/* Libera toda a memória da árvore (aplicação clássica de pós-ordem) */
void liberarArvore(TreeNode *n) {
    if (n == NULL) return;
    liberarArvore(n->left);
    liberarArvore(n->right);
    free(n);
}

/* Altura da árvore (slide 6: "altura de um nó é o caminho de maior
 * comprimento até uma folha"). Retorna -1 para árvore vazia (convenção
 * comum no LeetCode) ou 0 se preferir contar nós; aqui usamos "número
 * de nós no caminho mais longo" para casar com problemas de LeetCode. */
int altura(TreeNode *n) {
    if (n == NULL) return 0;
    int he = altura(n->left);
    int hd = altura(n->right);
    return 1 + (he > hd ? he : hd);
}

/* ---------------------------------------------------------------------
 * TESTE: monta a árvore do slide 4/7 da Aula 8
 *              A
 *           /  |  \
 *          B   C    D
 *              |
 *              E
 *            /  \
 *           F    G
 * (simplificada para binária: aqui usamos apenas 2 filhos por nó,
 *  já que os exercícios do LeetCode trabalham com árvore BINÁRIA)
 * --------------------------------------------------------------------- */
int main(void) {
    TreeNode *A = newNode('A');
    TreeNode *B = newNode('B');
    TreeNode *C = newNode('C');
    TreeNode *E = newNode('E');
    TreeNode *F = newNode('F');
    TreeNode *G = newNode('G');

    A->left = B;
    A->right = C;
    C->left = E;
    E->left = F;
    E->right = G;

    printf("Pre-ordem : "); preOrdem(A); printf("\n");
    printf("Em-ordem  : "); emOrdem(A);  printf("\n");
    printf("Pos-ordem : "); posOrdem(A); printf("\n");
    printf("Altura    : %d\n", altura(A));

    liberarArvore(A);
    return 0;
}
