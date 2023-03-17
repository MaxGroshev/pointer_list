#include "list.h"

int main ()
{
    // struct list_t box = {};
    // list_construct (&box);

    lst_node_t* node1 = list_create (221);
    lst_node_t* node2 = list_create (408);
    lst_node_t* node3 = list_create (321);
    lst_node_t* node4 = list_create (111);
    lst_node_t* node5 = list_create (333);

    list_insert (node1, node2);            //node1->next->data = node2->data
    list_insert (node1, node3);
    list_insert (node3, node4);
   // list_insert (node4, node5);
    //list_insert (node3, node4);
    //list_push_front (node1, node5);

    list_push_back  (node2, list_create (555));
    //printf ("%p\n", node_x->next );
   // list_remove (node5, node3);
    list_push_front (node1, node5);
    list_graph  (node5);
    list_delete (node5);
    return 0;
}
