/*
 * ============================================================================
 * LeetCode 102 (Medium) - Binary Tree Level Order Traversal
 * ============================================================================
 * A Aula 8 (slide 8) apresenta três caminhamentos, TODOS baseados em
 * recursão/DFS (busca em profundidade): pré-ordem, em-ordem, pós-ordem.
 *
 * Este exercício pede um QUARTO tipo de caminhamento, muito cobrado no
 * LeetCode, que NÃO está nos slides mas é o complemento natural do
 * conceito de "nível" que aparece no slide 6 e 7 da aula:
 *
 *   "O nível de 'A' é 1 e o de 'G' é 4" (slide 7)
 *
 * -> Caminhamento em LARGURA (BFS): visita a árvore nível por nível,
 *    da esquerda para a direita, usando uma FILA (não uma pilha/recursão).
 *
 * Estrutura: para cada nível, colocamos todos os nós desse nível numa
 * fila, processamos todos ANTES de avançar para o próximo nível.
 * Complexidade: O(n) tempo, O(n) espaço (no pior caso, a última
 * "camada" de uma árvore quase completa - ver slide 14 - guarda ~n/2 nós).
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

/* Fila simples de ponteiros para TreeNode, implementada com vetor circular.
 * Usamos uma fila (FIFO) porque BFS SEMPRE processa "quem chegou primeiro
 * primeiro" -- diferente da recursão dos caminhamentos da aula, que é
 * uma pilha (LIFO) implícita da chamada de função. */
typedef struct {
    TreeNode **dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila *criarFila(int capacidade) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->dados = (TreeNode **)malloc(sizeof(TreeNode *) * capacidade);
    f->capacidade = capacidade;
    f->inicio = f->fim = f->tamanho = 0;
    return f;
}

void enfileirar(Fila *f, TreeNode *no) {
    f->dados[f->fim] = no;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

TreeNode *desenfileirar(Fila *f) {
    TreeNode *no = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return no;
}

/*
 * levelOrder: retorna uma matriz onde cada linha é um nível da árvore.
 * returnSize      -> quantidade de níveis (linhas)
 * returnColumnSizes -> quantidade de nós em cada nível
 * (Essa assinatura imita exatamente o formato pedido pelo LeetCode em C)
 */
int **levelOrder(TreeNode *root, int *returnSize, int **returnColumnSizes) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    /* Superestimamos a capacidade da fila para simplificar (n nós cabem
       tranquilamente numa fila de tamanho n, já que cada nó entra e sai
       exatamente uma vez). Para descobrir n rapidamente, fazemos uma
       contagem prévia com pré-ordem (slide 9). */
    int n = 0;
    void contar(TreeNode *no) {
        if (no == NULL) return;
        n++;
        contar(no->left);
        contar(no->right);
    }
    contar(root);

    Fila *fila = criarFila(n + 1);
    enfileirar(fila, root);

    int **resultado = (int **)malloc(sizeof(int *) * n); /* no maximo n niveis */
    int *tamanhos = (int *)malloc(sizeof(int) * n);
    int niveis = 0;

    while (fila->tamanho > 0) {
        int qtdNoNivel = fila->tamanho;   /* "foto" de quantos nós tem NESTE nível */
        int *nivelAtual = (int *)malloc(sizeof(int) * qtdNoNivel);

        for (int i = 0; i < qtdNoNivel; i++) {
            TreeNode *no = desenfileirar(fila);
            nivelAtual[i] = no->val;

            /* Enfileira os filhos: eles serao processados no PROXIMO nivel */
            if (no->left)  enfileirar(fila, no->left);
            if (no->right) enfileirar(fila, no->right);
        }

        resultado[niveis] = nivelAtual;
        tamanhos[niveis] = qtdNoNivel;
        niveis++;
    }

    *returnSize = niveis;
    *returnColumnSizes = tamanhos;
    free(fila->dados);
    free(fila);
    return resultado;
}

int main(void) {
    /*        3
     *       / \
     *      9   20
     *         /  \
     *        15   7
     */
    TreeNode *root = newNode(3);
    root->left = newNode(9);
    root->right = newNode(20);
    root->right->left = newNode(15);
    root->right->right = newNode(7);

    int returnSize;
    int *returnColumnSizes;
    int **niveis = levelOrder(root, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        printf("Nivel %d: ", i);
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", niveis[i][j]);
        }
        printf("\n");
        free(niveis[i]);
    }
    free(niveis);
    free(returnColumnSizes);

    return 0;
}
