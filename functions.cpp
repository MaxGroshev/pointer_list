#include "graphviz.h"

void init_graph (FILE* graphviz, dump_graph_t* graph_dump_set)
{
    MY_ASSERT (graphviz != NULL && graph_dump_set != NULL)
    graph_dump_set->edge_capacity = 1;
    graph_dump_set->node_capacity = 1;
    graph_dump_set->node_size     = 0;
    graph_dump_set->edge_size     = 0;
    graph_dump_set->nodes = (struct node_t*) calloc (graph_dump_set->node_capacity, sizeof (struct node_t)); //add different types
    graph_dump_set->edges = (struct edge_t*) calloc (graph_dump_set->edge_capacity, sizeof (struct edge_t));
    MY_ASSERT (graph_dump_set->nodes != NULL && graph_dump_set->edges != NULL);

    struct node_t init_struct_node;
    struct edge_t init_struct_edge;
    for (int i = 0; i < graph_dump_set->node_capacity; i++)
    {
        graph_dump_set->nodes[i] = init_struct_node;
    }
    for (int i = 0; i < graph_dump_set->edge_capacity; i++)
    {
        graph_dump_set->edges[i] = init_struct_edge;
    }

    print_def_info (graphviz, graph_dump_set);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void make_node (FILE* graphviz, dump_graph_t* graph_dump_set, int* node_address, struct node_t nodes, int* next, int* prev, int value)
{
    //printf ("%ld\n", graph_dump_set->node_size);
    if (graph_dump_set->node_capacity <= graph_dump_set->node_size + 1) resize_struct (graph_dump_set);


    fprintf (graphviz, "node%p [shape = \"%s\", fillcolor = \"%s\", style = \"%s\", fontcolor = \"%s\", fontname = \"%s\", color = \"%s\", label = \"{cell = %p\\n %s| {value = %d |next = %p |prev = %p}}\"]\n",
                node_address, nodes.shape,  nodes.fillcolor,    nodes.style,    nodes.fontcolor,    nodes.fontname,    nodes.color,  node_address, nodes.label ,         value,      next,       prev);
    graph_dump_set->node_size++;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void make_edge (FILE* graphviz, dump_graph_t* graph_dump_set, int* node_from, int* node_to, struct edge_t edges)
{
   // printf ("%ld\n", graph_dump_set->edge_size);
    if (graph_dump_set->edge_capacity <= graph_dump_set->edge_size + 1) resize_struct (graph_dump_set);

    fprintf (graphviz, "node%p -> node%p [color = \"%s\", style = \"%s\", constraint = %s, fillcolor = \"%s\",   fontcolor = \"%s\", fontname = \"%s\", label = \"%s\"];\n",
                        node_from, node_to, edges.color,   edges.style,    edges.constraint, edges.fillcolor, edges.fontcolor,    edges.fontname,     edges.label);
    graph_dump_set->edge_size++;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void print_def_info (FILE* graphviz, dump_graph_t* graph_dump_set)
{
    fprintf (graphviz, "digraph   \n{\n");
    fprintf (graphviz, "rankdir = \"%s\"\n",   graph_dump_set->orientation);
    fprintf (graphviz, "splines = \"%s\"\n\n", graph_dump_set->splines);

    fprintf (graphviz, "node_stat [margin = \"0.3*0.3\", style = \"filled\", shape = \"record\", fillcolor = \"#8DB6CD\" label = \"capacity = %ld | size = %ld | head point = %ld | tail point = %ld\"]\n",
                        graph_dump_set->info.capacity, graph_dump_set->info.size, graph_dump_set->info.head, graph_dump_set->info.tail);
    fprintf (graphviz, "{rank = source; node_stat}\n\n");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void resize_struct (dump_graph_t* graph_dump_set)
{

    if (graph_dump_set->edge_capacity <= graph_dump_set->edge_size + 1)
    {
        size_t prev_capacity = graph_dump_set->edge_capacity ;
        graph_dump_set->edge_capacity *= 2;
        edge_t* edges_resize = (edge_t*) realloc (graph_dump_set->edges,  graph_dump_set->edge_capacity * sizeof (struct edge_t));

        MY_ASSERT (edges_resize != NULL);
        graph_dump_set->edges = edges_resize;
        struct edge_t init_struct_edge;
        for (int i = prev_capacity; i < graph_dump_set->edge_capacity; i++)
        {
            graph_dump_set->edges[i] = init_struct_edge;
        }
    }

    if (graph_dump_set->node_capacity <= graph_dump_set->node_size + 1)
    {
        size_t prev_capacity = graph_dump_set->node_capacity;
        graph_dump_set->node_capacity *= 2;
        node_t* node_resize = (node_t*) realloc (graph_dump_set->nodes,  graph_dump_set->node_capacity * sizeof (struct node_t));

        MY_ASSERT (node_resize != NULL);
        graph_dump_set->nodes = node_resize;
        struct node_t init_struct_node;
        for (int i = prev_capacity; i < graph_dump_set->node_capacity; i++)
        {
            graph_dump_set->nodes[i] = init_struct_node;
        }
        printf ("here");
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

void run_graphviz  (FILE* graphviz, dump_graph_t* graph_dump_set)
{
    fprintf (graphviz, "}\n");
    free    (graph_dump_set->nodes);
    free    (graph_dump_set->edges);
    //system  ("xdg-open ./dump_info/list_dump.pdf");
}
