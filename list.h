#pragma once
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphviz.h"
#include "my_ASSERT.h"
#include "list_check.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CUR_POS_IN_PROG    __FILE__, __PRETTY_FUNCTION__, __LINE__

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

typedef int list_type; // type of elem in list

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum code_of_errors
{
    LST_IS_OKAY         =  0,
    LST_NODE_HAS_CHILD  = -1,
    LST_CELL_NOT_EXIST  = -2,
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
    size_t       size;
    lst_node_t*  head;
    lst_node_t*  tail;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

int         list_constructor(list_t* list);
lst_node_t* list_create     (list_type elem);
int list_insert     (list_t* list, lst_node_t* head, lst_node_t* node = NULL);
int list_emplace (list_t* list, int position, lst_node_t* node = NULL);
int list_push_front (list_t* list, lst_node_t* node);
int list_push_back  (list_t* list, lst_node_t* node);

int list_pop_front(list_t* list);
int list_pop_back (list_t* list);
lst_node_t* list_erase     (list_t* list, lst_node_t* head, lst_node_t* node = NULL);
lst_node_t* list_delete     (list_t* list);

int         find_logic_pos (list_t* list, lst_node_t* node);

void        list_print      ();
void        list_graph      (list_t* list, lst_node_t* head);
void        list_check      (const char* DUR_FILE, const char* FUNCTION, int LINE);

void list_error (int code_of_error, const char* DUR_FILE, const char* FUNCTION, int LINE);

