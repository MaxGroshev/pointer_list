#include "list.h"

void list_construct (list_t* box) //TODO return code of error
{
    box->capacity = 1;
    //box->head = (struct lst_node_t*) calloc (box->capacity, sizeof (struct lst_node_t));
    //box->tail = (struct lst_node_t*) calloc (box->capacity, sizeof (struct lst_node_t));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_create (list_type value)
{
    lst_node_t* node = (struct lst_node_t*) calloc (1, sizeof (struct lst_node_t));
    MY_ASSERT  (node != NULL)
    node->data = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_insert (lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT (node != NULL)

    lst_node_t* current = head;
    // printf ("1) %p %p - head\n", node, head);
    // for (int i = 0; current->next != NULL; i++)
    // {
    //     current   = current->next;
    // }
    node->prev    = current;
    node->next    = current->next;
    current->next = node;
    return head;
}

lst_node_t* list_push_front (lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT (head != NULL && node != NULL)
    node->prev = NULL;
    node->next = head;
    head->prev = node;
    return node;
}

lst_node_t* list_push_back (lst_node_t* tail, lst_node_t* node)
{
    MY_ASSERT (tail != NULL && node != NULL)
    node->next = NULL;
    node->prev = tail;
    tail->next = node;
    return node;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_remove (lst_node_t* head, lst_node_t* node)
{
    if (node == head)
    {
        lst_node_t* ret = head->next;
        free (head);
        return ret;
    }

    lst_node_t* current = head;
    while (current->next != node)
    {
        if (current->next == NULL)
        {
            return head; //printf (inpossible to dedlete node that doesnot exist)
        }
        current = current->next;
    }
    lst_node_t* tmp_node      = current->next;
    current->next->next->prev = current;
    current->next             = current->next->next;
    free (tmp_node);
    return head;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_delete (lst_node_t* head)
{
    lst_node_t* current = head;
    while (head != NULL)
    {
        head = list_remove (head, head);
    }
    return NULL;
}

