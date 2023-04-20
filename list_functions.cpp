#include "list.h"

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

    if (node->next != NULL || node->prev != NULL)
    {
        fprintf (stderr, "ERROR: impossible to add node that already has a child(ren))\n");
        return NULL;
    }
    lst_node_t* current = head;
    node->prev          = current;
    node->next          = current->next;
    if (current->next != NULL) current->next->prev = node;
    current->next       = node;
    return head;
}

lst_node_t* list_push_front (lst_node_t* node, lst_node_t* head)
{
    MY_ASSERT (head != NULL && node != NULL)

    if (node->next != NULL || node->prev != NULL)
    {
        fprintf (stderr, "ERROR: impossible to add node that already has a child(ren))\n");
        return NULL;
    }

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



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_remove (lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT (node != NULL);
    if (node == head)
    {
        lst_node_t* ret = head->next;
        free (head);

        return ret;
    }

    // if (node == )
    // {
    //     lst_node_t* ret = head->next;
    //     free (head);
    //     return ret;
    // }

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

