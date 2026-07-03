#Resposta 100 %

bool isValid(char *s)
{
    char stack[strlen(s)];
    int top = -1;

    if (s[0] == '}' || s[0] == ']' || s[0] == ')')
    {
        return false;
    }

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            top++;
            stack[top] = s[i];
        }
        else
        {
            if (top < 0 && i < strlen(s))
            {
                return false;
            }
            else if (s[i] == ')' && stack[top] == '(')
            {
                top--;
            }
            else if (s[i] == ']' && stack[top] == '[')
            {
                top--;
            }
            else if (s[i] == '}' && stack[top] == '{')
            {
                top--;
            }
            else
            {
                return false;
            }
        }
    }
    if (top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}