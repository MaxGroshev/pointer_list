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

int list_insert (list_t* list, lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT  (node != NULL)
    LIST_CHECK (node->next == NULL && node->prev == NULL, LST_NODE_HAS_CHILD)

    if (list->size == 0)
    {
        list->head = head;
        list->tail = node;
    }
    else if (list->tail == head) list->tail = node;

    if (head->next == NULL && head->prev == NULL) list->size += 2;
    else list->size++;

    lst_node_t* current = head;
    node->prev          = current;
    node->next          = current->next;
    if (current->next  != NULL) current->next->prev = node;
    current->next       = node;

    return 0;
}

int list_emplace (list_t* list, int position, lst_node_t* node)
{
    MY_ASSERT  (node != NULL)
    LIST_CHECK (node->next == NULL && node->prev == NULL, LST_NODE_HAS_CHILD)
    LIST_CHECK (position > 0 && position <= list->size + 1, LST_CELL_NOT_EXIST)

    if (list->size == 0)
    {
        list->head = node;
        list->tail = node;
    }
    else if (position == 1)
    {
        list_push_front (list, node);
        return 0;
    }
    else if (position == list->size + 1)
    {
        list_push_back (list, node);
        return 0;
    }

    lst_node_t* current = list->head;
    for (int i = 1; i < position - 1; i++)
    {
        current = current->next;
    }
    node->prev          = current;
    node->next          = current->next;
    if (current->next  != NULL) current->next->prev = node;
    current->next       = node;
    list->size++;

    return 0;
}

int list_push_front (list_t* list, lst_node_t* node)
{
    MY_ASSERT  (node != NULL)
    LIST_CHECK (node->next == NULL, LST_NODE_HAS_CHILD)

    if (list->head == NULL)
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

    return 0;
}

int list_push_back (list_t* list, lst_node_t* node)
{
    MY_ASSERT  (node != NULL)
    LIST_CHECK (node->next == NULL, LST_NODE_HAS_CHILD)

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

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int find_logic_pos (list_t* list, lst_node_t* node)
{
    LIST_CHECK (node != NULL, LST_CELL_NOT_EXIST)

    lst_node_t* current = list->head;
    int pos_of_elem = 0;
    while (current != node)
    {
        current = current->next;
        pos_of_elem++;
    }

    return pos_of_elem;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_erase (list_t* list, lst_node_t* head, lst_node_t* node)
{
    MY_ASSERT (head != NULL);

    if (node != NULL && head == node)
    {
        lst_node_t* ret = head->next;
        free (head);
        list->size--;

        return ret;
    }
    if (list->head == head && head->next != NULL)
    {
        list_pop_front (list);
        return list->head;
    }
    else if (list->tail == head && head->prev != NULL)
    {
        list_pop_back (list);
        return list->tail;
    }
    else if (node == NULL)
    {
        head->next->prev = head->prev;
        head->prev->next = head->next;
        free (head);
        list->size--;

        return NULL;
    }

    lst_node_t* current = head;
    while (current->next != node)
    {
        if (current->next == NULL)
        {
            return head;
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

int list_pop_front (list_t* list)
{
    LIST_CHECK (list->head != NULL, LST_CELL_NOT_EXIST)

    list->head = list->head->next;
    free (list->head->prev);
    list->head->prev = NULL;
    list->size--;

    return 0;
}

int list_pop_back (list_t* list)
{
    LIST_CHECK (list->tail != NULL, LST_CELL_NOT_EXIST)

    list->tail = list->tail->prev;
    free (list->tail->next);
    list->tail->next = NULL;
    list->size--;

    return 0;
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
        current = list_erase (list, current, current);
    }

    return NULL;
}

