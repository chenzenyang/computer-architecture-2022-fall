/*
link : https://hackmd.io/@sysprog/arch2022-quiz1.

Popular programming journal Obscure C Techniques for Experts has published a novel way to save space for a doubly-linked list program. Instead of storing
two pointers (one next and one previous), this new technique stores a single value: the XOR of previous and next pointers. Check Wikipedia XOR linked list for details.

The below code (filename xorlist.c) implements XOR linked list:
*/

/*
The corresponding program output:
99
0
1
2
3
4
5
4
3
2
1
0
99

Ensure your code meets the expected operations and initialization of such a list as well as the insertion, and deletion, of elements from such a list.
Here, we assume each malloc call will succeed and omit the memory de-allocation.

Obviously, the above C code listing was incomplete, you shall provide the functioned implementations.
A01, A02, A03, and A04 are C expressions. You must obey the following rules when filling them:
- Write shorter code as possible as you can.
- Do necessary casting to eliminate compilation warnings.
- The intptr_t and uintptr_t types are extremely useful for casting pointers when you want to do address arithmetic.
    You shall consider to explicitly use the types provided by <inttypes.h>.
- Follow the consistent coding style.
    That is, we prefer (xorlist_t *) (*head)->link to (xorlist_t*)(*head)->link or (xorlist_t *)(*head)->link.
    Be aware of the spaces! Details determine success or failure.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_START 0
#define LIST_END 5

typedef struct {
    int data;
    intptr_t link;
} xorlist_t;

void dump_list(xorlist_t *pt)
{
    intptr_t prev = (intptr_t) NULL;

    while (pt) {
        printf("%d\n", pt->data);
        xorlist_t *current = pt;
        /* Decode xored pointers with last node's address to find next */
        pt = (xorlist_t *) (pt->link ^ prev);
        prev = (intptr_t) current;
    }
}

/* insert head */
void insert_head(xorlist_t **head, int data)
{
    xorlist_t *new_node = malloc(sizeof(xorlist_t));
    new_node->data = data;

    if (!*head) {
        new_node->link = (intptr_t) NULL;
    } else {
        /* Update original link of head node */
        (*head)->link = (*head)->link ^ (intptr_t) new_node;
        new_node->link = (intptr_t) *head;
    }

    *head = new_node;
}

/* remove a node from head */
void remove_head(xorlist_t **head)
{
    if (!(*head)) return;

    xorlist_t *tmp = (xorlist_t *) (*head)->link;
    /* Update the link of new head */
    if (tmp)
        tmp->link ^= (intptr_t) *head /* Fill Your Code */;
    free(*head);
    *head = tmp;
}

void release_list(xorlist_t *pt)
{
    intptr_t prev = (intptr_t) NULL;
    while (pt) {
        xorlist_t *current = pt;
        pt = (xorlist_t *) (pt->link ^ prev);
        prev = (intptr_t) current /* Fill Your Code */;
        free(current);
    }
}

int main()
{
    xorlist_t *head = malloc(sizeof(xorlist_t)), *tail;
    xorlist_t *pt = head;
    intptr_t last_node = (intptr_t) NULL;
    for (int c = LIST_START; c < LIST_END; ++c) {
        xorlist_t *new_node = malloc(sizeof(xorlist_t));
        *pt = (xorlist_t) {
            .data = c, .link = (intptr_t) new_node ^ last_node
        };
        last_node = (intptr_t) pt;
        pt = new_node;
    }
    *pt = (xorlist_t) {
        .data = LIST_END, .link = last_node ^ (intptr_t) NULL
    };
    tail = pt;

    insert_head(&head, 99);
    dump_list(head);

    remove_head(&tail);
    dump_list(tail);

    release_list(head);

    return 0;
}