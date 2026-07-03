# 100 %

bool validation(struct TreeNode *root, long max, long min)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->val <= min || root->val >= max)
    {
        return false;
    }

    return validation(root->left, root->val, min) && validation(root->right, max, root->val);
}

bool isValidBST(struct TreeNode *root)
{
    return validation(root, LLONG_MAX, LLONG_MIN);
}