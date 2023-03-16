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

enum list_side
{
    TAIL = 1,
    HEAD = 2,
};

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

struct list_t
{
    struct lst_node_t*  head;
    struct lst_node_t*  tail;
    struct lst_node_t*  free;
    size_t          capacity;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void        list_construct  (list_t* box);

lst_node_t* list_create     (list_type elem);
lst_node_t* list_insert     (lst_node_t* head, lst_node_t* node);
lst_node_t* list_push_front (lst_node_t* head, lst_node_t* node);

lst_node_t* list_pop        (list_t* box, size_t position);
lst_node_t* list_remove     (lst_node_t* head, lst_node_t* node);
lst_node_t* list_delete     (lst_node_t* head);

void        list_print      (list_t* box);
void        list_graph      (lst_node_t* head);
void        list_check      (list_t* box, const char* DUR_FILE, const char* FUNCTION, int LINE);
