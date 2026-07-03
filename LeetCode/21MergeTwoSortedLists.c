#include <stdlib.h>
#include <stdio.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

// Referências para uso das funções no main antes de descritas
void printList();
ListNode *mergeTwoLists();

int main()
{
    ListNode *list1 = (ListNode *)malloc(sizeof(ListNode));
    ListNode *list2 = (ListNode *)malloc(sizeof(ListNode));

    ListNode *b1 = (ListNode *)malloc(sizeof(ListNode));
    ListNode *b2 = (ListNode *)malloc(sizeof(ListNode));
    ListNode *c1 = (ListNode *)malloc(sizeof(ListNode));
    ListNode *c2 = (ListNode *)malloc(sizeof(ListNode));

    list1->val = 1;
    list1->next = b1;
    b1->val = 2;
    b1->next = c1;
    c1->val = 4;
    c1->next = NULL;

    list2->val = 1;
    list2->next = b2;
    b2->val = 3;
    b2->next = c2;
    c2->val = 4;
    c2->next = NULL;

    ListNode *result = mergeTwoLists(list1, list2);

    printList(result);

    free(c2);
    free(c1);
    free(b2);
    free(b1);
    free(list2);
    free(list1);
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode newList;
    newList.next = NULL;
    ListNode *p = &newList;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->val > list2->val)
        {
            p->next = list2;
            list2 = list2->next;
        }
        else
        {
            p->next = list1;
            list1 = list1->next;
        }
        p = p->next;
    }

    if (list1 != NULL)
    {
        p->next = list1;
    }
    else
    {
        p->next = list2;
    }

    return newList.next;
}

void printList(ListNode *head)
{
    ListNode *temp = head;

    while (temp)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
}