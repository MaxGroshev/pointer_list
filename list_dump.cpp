#include "list.h"

void list_graph (lst_node_t* head)
{
    FILE* graphviz               = fopen ("./dump_info/list_dump.dot", "w");
    MY_ASSERT (graphviz != NULL)
    dump_graph_t graph_dump_set  = {};
    init_graph (graphviz, &graph_dump_set);

    lst_node_t* current = head;
    int node_count = 0;
    for (int edge_count = 0; current != NULL; node_count++, edge_count++)
    {
         printf ("%d\n", node_count);
        if (current->next == NULL)
        {
            graph_dump_set.nodes[node_count].fillcolor = "#006400";
            graph_dump_set.nodes[node_count].label     = "TAIL";

            make_node (graphviz, &graph_dump_set, &current->data, graph_dump_set.nodes[node_count], NULL, &current->prev->data, current->data);

            graph_dump_set.edges[edge_count].style       = "invis";
            graph_dump_set.edges[edge_count].constraint  = "false";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->prev->data, graph_dump_set.edges[edge_count]);

            graph_dump_set.edges[++edge_count].fillcolor = "orange";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->prev->data, graph_dump_set.edges[edge_count]);
            current = current->next;
        }
        else if (current->prev == NULL)
        {
            graph_dump_set.nodes[node_count].fillcolor = "#008080";
            graph_dump_set.nodes[node_count].label     = "HEAD";
            make_node (graphviz, &graph_dump_set, &current->data, graph_dump_set.nodes[node_count], &current->next->data, NULL, current->data);

            graph_dump_set.edges[edge_count].style       = "invis";
            graph_dump_set.edges[edge_count].constraint  = "false";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->next->data, graph_dump_set.edges[edge_count]);

            graph_dump_set.edges[++edge_count].fillcolor = "blue";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->next->data, graph_dump_set.edges[edge_count]);
            current = current->next;
        }
        else
        {
            make_node (graphviz, &graph_dump_set, &current->data, graph_dump_set.nodes[node_count], &current->next->data, &current->prev->data, current->data);

            graph_dump_set.edges[edge_count].style = "invis";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->next->data, graph_dump_set.edges[edge_count]);

            graph_dump_set.edges[++edge_count].fillcolor = "blue";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->next->data, graph_dump_set.edges[edge_count]);

            graph_dump_set.edges[++edge_count].fillcolor = "orange";
            make_edge (graphviz, &graph_dump_set, &current->data, &current->prev->data, graph_dump_set.edges[edge_count]);
            current = current->next;
        }
    }

    run_graphviz (graphviz, &graph_dump_set);
    fclose (graphviz);
}

