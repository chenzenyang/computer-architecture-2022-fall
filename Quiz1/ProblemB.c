/*
Fill in B01, B02, B03 and B04 to complete the reverse function which takes in a head to the head of a linked list and 
    returns a new copy of the linked list in reverse order.
You must allocate space for the new linked list that you return. An (incomplete) example program using reverse is also shown below.
*/

/*
You shall provide the functioned implementations. B01 is a declaration for function parameter. B02, B03, and B04 are C expressions.
You must obey the following rules when filling them:
- Write shorter code as possible as you can.
- Do necessary casting to eliminate compilation warnings.
- Follow the consistent coding style. That is, we prefer struct list_node *h to struct list_node* h. Be aware of the spaces! Details determine success or failure.
*/
#include <assert.h>
#include <stdlib.h>

struct list_node {
    int val;
    struct list_node *next;
};

struct list_node *reverse(struct list_node **p /* Fill Your Code */)
{
    struct list_node *next = NULL, *ret;
    while (*p) {
        ret = malloc(sizeof(struct list_node));
        ret->val = (*p)->val /* Fill Your Code */;
        ret->next = next /* Fill Your Code */;
        next = ret /* Fill Your Code */;
        *p = (*p)->next;
    }
    return ret;
}

/* Assume that NEW_LL_1234() properly malloc’s a linked list
 * 1 -> 2 -> 3 -> 4, and returns a pointer that points to the first
 * list_node in the linked list. Assume that before test_reverse
 * returns, head and ret will be properly freed.
 */
void test_reverse()
{
    struct list_node *head = NEW_LL_1234();
    assert(head->val == 1);        /* returns True */
    assert(head->next->val == 2);  /* returns True */
    struct list_node *ret = reverse(&head);
    assert(head != ret);    /* ret is a new copy of the original list */
    assert(ret->val == 4);  /* should return True */
}