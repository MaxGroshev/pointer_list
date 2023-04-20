#pragma once
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphviz.h"
#include "my_ASSERT.h"
#include "list_check.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef int list_type; // type of elem in list

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum code_of_errors
{
    LIST_IS_OKAY    =  0,
    CELL_NOT_FOUND  = -1,
    NO_FREE_CELL    = -2,
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct lst_node_t
{
    lst_node_t*  next;
    lst_node_t*  prev;
    list_type    data;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

lst_node_t* list_create     (list_type elem);
lst_node_t* list_insert     (lst_node_t* head, lst_node_t* node);
lst_node_t* list_push_front (lst_node_t* node, lst_node_t* head = NULL);
lst_node_t* list_push_back  (lst_node_t* node, lst_node_t* tail = NULL);

lst_node_t* list_pop        (lst_node_t* head, size_t position);
lst_node_t* list_pop_front  (lst_node_t* head, lst_node_t* node);
lst_node_t* list_pop_back   (lst_node_t* head, lst_node_t* node);
lst_node_t* list_remove     (lst_node_t* head, lst_node_t* node);
lst_node_t* list_delete     (lst_node_t* head);

void        list_print      ();
void        list_graph      (lst_node_t* head);
void        list_check      (const char* DUR_FILE, const char* FUNCTION, int LINE);
