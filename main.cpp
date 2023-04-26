#include "list.h"

int main ()
{
    list_t list = {};
    list_constructor (&list);

    lst_node_t* node1 = list_create (221);
    lst_node_t* node2 = list_create (408);
    //lst_node_t* node4 = list_create (&list, 111);
    lst_node_t* node5 = list_create (333);

    list_insert (&list, node1, node2);            //node1->next->data = node2->data
    //list_insert (&list, node1, node4);
    // list_insert (&list, node2, node4);
    //list_insert (&list, node2, node5);
    //list_insert (node3, node4);
    list_push_front (&list, node5);
    // list_push_front (&list, node1);


    list_push_back  (&list, list_create (555));
    //printf ("%p\n", node_x->next );
    //list_remove (node5, node3);
    list_graph  (&list, list.head);
    list_delete (&list, list.head);
    return 0;
}
