#include "list.h"
//
// //void list_check (list_t* box, const char* DUR_FILE, const char* FUNCTION, int LINE)
// {
//     if (box->free == 0)
//     {
//         fprintf (stderr, "Free cell was't found in %s: %s: %d:\n", DUR_FILE, FUNCTION, LINE);
//         list_print (box);
//     }
//
//     else
//     {
//         fprintf (stderr, "Impossible to use numbers of elements that does't belong to list in %s: %s: %d:\n", DUR_FILE, FUNCTION, LINE);
//         list_print (box);
//     }
// }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------

//void list_print (list_t* box)
// {
//     FILE* print_list = fopen ("./dump_info/list_dump.txt", "w");
//     MY_ASSERT (print_list != NULL);
//
//     fprintf (print_list, "=========================HEAD_&_TAIL====================================\n"
//                           "%3ld [%ld] - head point to this cell\n"
//                           "%3ld [%d] - tail point to this cell\n"
//                           "%3ld - capacity of list\n"
//                           "%3ld - size of list\n"
//                           "============================LIST=======================================\n\n"
//                           ,box->head, *box->head, box->tail, box->data[box->tail], box->capacity, box->size);
//
//     fprintf (print_list, " [cell] | [prev] | [next] | [data]\n");
//     for (int i = 0; i < box->capacity; i++)
//     {
//         if (i == box->tail)
//         {
//             if (box->tail == box->head)
//             {
//                 fprintf (print_list, "%4d %8ld %8ld %9d - head & tail point to this cell\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
//             }
//
//             else
//             {
//                 fprintf (print_list, "%4d %8ld %8ld %9d - tail point to this cell\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
//             }
//         }
//
//         else if (i == box->head)
//         {
//             fprintf (print_list, "%4d %8ld %8ld %9d - head point to this cell\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
//         }
//
//         else
//         {
//             fprintf (print_list, "%4d %8ld %8ld %9d\n", i, box->index[i].prev, box->index[i].next, box->data[i]);
//         }
//     }
//     fclose (print_list);
// }

//-----------------------------------------------------------------------------------------------------------------------------------------

void list_graph (lst_node_t* head)
{
    FILE* graphviz               = fopen ("./dump_info/list_dump.dot", "w");
    MY_ASSERT (graphviz != NULL)
    dump_graph_t graph_dump_set  = {};
    init_graph (graphviz, &graph_dump_set);

    lst_node_t* current = head;
    for (int i = 0; current != NULL; i++)
    {
        if (current->next == NULL)
        {
            //printf ("Hello");
            graph_dump_set.nodes[i].fillcolor = "#006400";
            graph_dump_set.edges[i].label = "TAIL";
            make_node (graphviz, &graph_dump_set, &current->data, graph_dump_set.nodes[i], NULL, 4, current->data);
            current = current->next;
        }
        else
        {
            graph_dump_set.edges[i].fillcolor = "blue";
            make_node (graphviz, &graph_dump_set, &current->data, graph_dump_set.nodes[i], &current->next->data, 4, current->data);
            make_edge (graphviz, &graph_dump_set, &current->data, &current->next->data, graph_dump_set.edges[i]);
            current = current->next;
        }
    }

    // current = head;
    // printf ("%p %p - head\n", current, head);
    // for (int i = 0; current->next != NULL; i++)
    // {
    //     printf ("%p %p - head\n", current, head);
    //     graph_dump_set.edges[i].fillcolor = "blue";
    //     //graph_dump_set.edges[i].constraint = "false";
    //     make_edge (graphviz, &graph_dump_set, &current->data, &current->next->data, graph_dump_set.edges[i]);
    //     current = current->next;
    // }

    run_graphviz (graphviz, &graph_dump_set);
    fclose (graphviz);
}

