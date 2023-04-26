#include "list.h"

int list_constructor (list_t* list)
{
    if (list == NULL)
    {
        MY_ASSERT (0);
        return -1;
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return 0;
}

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

lst_node_t* list_insert (list_t* list, lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT (node != NULL)

    if (node->next != NULL || node->prev != NULL)
    {
        fprintf (stderr, "ERROR: impossible to add node that already has a child(ren))\n");
        return NULL;
    }
    else if (list->size == 0)
    {
        list->head = head;
        list->tail = node;
    }
    else if (list->tail == head) list->tail = node;

    lst_node_t* current = head;
    node->prev          = current;
    node->next          = current->next;
    if (current->next  != NULL) current->next->prev = node;
    current->next       = node;

    if (head->next == NULL && head->prev == NULL) list->size += 2;
    else list->size++;

    return head;
}

lst_node_t* list_push_front (list_t* list, lst_node_t* node)
{
    MY_ASSERT (node != NULL)

    if (node->next != NULL)
    {
        fprintf (stderr, "ERROR: impossible to add node that already has a child(ren))\n");
        return NULL;
    }
    else if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;

    return node;
}

lst_node_t* list_push_back (list_t* list, lst_node_t* node)
{
    MY_ASSERT (node != NULL)

    if (list->tail == NULL)
    {
        list->tail = node;
    }
    else
    {
        node->next = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
        list->size++;
    }

    return node;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_remove (list_t* list, lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT (head != NULL);

    if (node == head)
    {
        lst_node_t* ret = head->next;
        free (head);
        list->size--;
        return ret;
    }

    if (list->head == head && head->next != NULL)
    {
        list->head = head->next;
        list->head->prev = NULL;
        free (head);
        return list->head;
    }
    if (list->tail == head && head->prev != NULL)
    {
        list->tail = head->prev;
        list->head->next = NULL;
        free (head);
        return list->tail;
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
    list->size--;

    return head;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_delete (list_t* list)
{
    while (list->head == NULL)
    {
        fprintf (stderr,"List was already freed\n");
        return NULL;
    }

    lst_node_t* current = list->head;
    while (current != NULL)
    {
        current = list_remove (list, current, current);
    }

    return NULL;
}

