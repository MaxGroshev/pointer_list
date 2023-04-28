#include "list.h"

int main ()
{
    list_t list = {};
    list_constructor (&list);

    lst_node_t* node1 = list_create (221);
    lst_node_t* node2 = list_create (408);
    lst_node_t* node3 = list_create (123);
    lst_node_t* node4 = list_create (111);
    lst_node_t* node5 = list_create (333);

    list_insert    (&list, node1, node2);            //node1->next->data = node2->data
    list_push_front(&list, node5);

    list_push_back (&list, list_create (555));
    list_emplace   (&list, 5, node4);
    list_emplace   (&list, 2, node3);

    int res = find_logic_pos (&list, node2);
    printf ("%d\n", res);

    list_erase  (&list, node3);
    list_graph  (&list, list.head);
    list_delete (&list);
    return 0;
}
