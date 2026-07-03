#bate 16.13 %

int postorder(struct TreeNode *root, int *sums, int *idx)
{
    if (root == NULL)
    {
        return 0;
    }
    int left = postorder(root->left, sums, idx);
    int right = postorder(root->right, sums, idx);
    int sum = left + right + root->val;
    sums[(*idx)++] = sum;
    return sum;
}

int *findFrequentTreeSum(struct TreeNode *root, int *returnSize)
{
    int sums[10000];
    int idx = 0;
    postorder(root, sums, &idx);

    int count[10000];
    for (int i = 0; i < idx; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < idx; i++)
    {
        for (int j = 0; j < idx; j++)
        {
            if (sums[j] == sums[i])
            {
                count[i]++;
            }
        }
    }

    int max = 0;
    for (int i = 0; i < idx; i++)
    {
        if (count[i] > max)
        {
            max = count[i];
        }
    }

    int *result = malloc(sizeof(int) * idx);
    int r = 0;
    for (int i = 0; i < idx; i++)
    {
        if (count[i] == max)
        {
            int dup = 0;
            for (int k = 0; k < r; k++)
            {
                if (result[k] == sums[i])
                {
                    dup = 1;
                }
            }
            if (!dup)
            {
                result[r++] = sums[i];
            }
        }
    }

    *returnSize = r;
    return result;
}
