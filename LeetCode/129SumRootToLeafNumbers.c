# 100 %

void dfs(struct TreeNode *root, int num, int *sum)
{
    if (root == NULL)
    {
        return;
    }
    num = num * 10 + root->val;
    if (root->left == NULL && root->right == NULL)
    {
        *sum += num;
        return;
    }
    dfs(root->left, num, sum);
    dfs(root->right, num, sum);
}

int sumNumbers(struct TreeNode *root)
{
    int sum = 0;
    dfs(root, 0, &sum);
    return sum;
}
