#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    struct list_head *node = l->next;
    while (node != l) {
        element_t *tmp = list_entry(node, element_t, list);
        node = node->next;
        free(tmp->value);
        free(tmp);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }
    element_t *node = malloc(sizeof(element_t));
    if (!node) {
        return false;
    }
    node->value = strdup(s);
    if (!node->value) {
        free(node);
        return false;
    }
    list_add(&node->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }
    element_t *node = malloc(sizeof(element_t));
    if (!node) {
        return false;
    }

    node->value = strdup(s);
    if (!node->value) {
        free(node);
        return false;
    }
    list_add(&node->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *node = list_entry(head->next, element_t, list);
    if (sp != NULL) {
        strncpy(sp, node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
        list_del(&node->list);
    }

    return node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    element_t *node = list_last_entry(head, element_t, list);
    if (sp != NULL) {
        strncpy(sp, node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
        list_del(&node->list);
    }
    return node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return false;
    }
    struct list_head *left = head->prev, *right = head->next;
    while (left != right && left->next != right) {
        left = left->prev;
        right = right->next;
    }
    element_t *node = list_entry(right, element_t, list);
    list_del(&node->list);
    q_release_element(node);
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return false;
    }

    struct list_head *fast, *now = NULL;
    bool isNeedDel = false;
    list_for_each_safe (now, fast, head) {
        element_t *node = list_entry(now, element_t, list);
        element_t *dulNode = list_entry(fast, element_t, list);
        if (node->list.next != head &&
            strcmp(node->value, dulNode->value) == 0) {
            isNeedDel = true;
            list_del(fast);
            q_release_element(dulNode);
        } else if (isNeedDel) {
            list_del(now);
            q_release_element(node);
            isNeedDel = false;
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
