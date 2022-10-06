#include <stdio.h>
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {

    struct ListNode *list = NULL;
    struct ListNode **sorted = &list;

    for (struct ListNode **indir; (list1 && list2); *indir = (*indir)->next) {
        indir = (list1->val <= list2->val) ? &list1 : &list2;
        *sorted = *indir;
        sorted = &(*sorted)->next;
    }

    *sorted = (list1 ? list1 : list2);
    return list;
}