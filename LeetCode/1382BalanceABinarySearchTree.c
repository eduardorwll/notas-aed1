#bate 65.52 %

void inorder(struct TreeNode *root, int *arr, int *idx)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left, arr, idx);
    arr[(*idx)++] = root->val;
    inorder(root->right, arr, idx);
}

struct TreeNode *build(int *arr, int left, int right)
{
    if (left > right)
    {
        return NULL;
    }
    int mid = (left + right) / 2;
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = arr[mid];
    node->left = build(arr, left, mid - 1);
    node->right = build(arr, mid + 1, right);
    return node;
}

struct TreeNode *balanceBST(struct TreeNode *root)
{
    int arr[10000];
    int idx = 0;
    inorder(root, arr, &idx);
    return build(arr, 0, idx - 1);
}
