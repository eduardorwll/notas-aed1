# 100 %

struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (key < root->val)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->val)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            return root->right;
        }
        if (root->right == NULL)
        {
            return root->left;
        }
        struct TreeNode *temp = root->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }
    return root;
}
