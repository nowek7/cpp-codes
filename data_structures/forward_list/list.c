#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node Node;

struct Node
{
  Node *next;
  int elem;
};

struct List
{
  Node* head;
};

List* create_list(void)
{
  List *list = malloc(sizeof(List));
  list->head = NULL;

  return list;
}

void destroy_list(List** list)
{
  clear_list(*list);
  free(*list);
  *list = NULL;
}

void clear_list(List* list)
{
  while (list->head)
  {
    remove_nth_element(list, 0);
  }
}

void append_to_list(List* list, int elem)
{
  Node *new_node = malloc(sizeof(Node));
  new_node->elem = elem;
  new_node->next = NULL;

  if (list->head)
  {
    Node *node = list->head;
    while (node->next)
    {
      node = node->next;
    }

    node->next = new_node;
  }
  else
  {
    list->head = new_node;
  }
}

int count_elements(List* list)
{
  int count = 0;
  if (list)
  {
    Node *node = list->head;
    while (node)
    {
      count++;
      node = node->next;
    }
  }

  return count;
}

int get_nth_element(List* list, int index)
{
  Node *node = list->head;
  for (int i = 0; i < index && node; i++)
  {
    node = node->next;
  }

  return node->elem;
}

void remove_nth_element(List* list, int index)
{
  if (list && index >= 0 && list->head)
  {
    Node *node = list->head;

    // Remove head.
    if (index == 0)
    {
      list->head = node->next;
      free(node);
    }
    else
    {
      // Find the previous node before the node to be deleted.
      for (int i = 1; i < index && node; i++)
      {
        node = node->next;
      }

      // Check if the index is less than the count of nodes.
      if (node && node->next)
      {
        Node *to_remove_node = node->next;

        // Shift node.
        node->next = to_remove_node->next;

        // Release memory.
        free(to_remove_node);
      }
    }
  }
}

void insert_to_list(List* list, int elem, int index)
{
  // Check if the range of index. It must be in the interval [0, count_elements].
  if (list && index >= 0 && index <= count_elements(list))
  {
    Node *new_node = malloc(sizeof(Node));
    new_node->elem = elem;
    new_node->next = NULL;

    Node *node = list->head;
    if (index != 0)
    {
      // Move to the node before the inserting index.
      for (int idx = 1; idx < index && node; idx++)
      {
        node = node->next;
      }

      // Insert new node and shift old node.
      Node *old_node = node->next;
      node->next = new_node;
      new_node->next = old_node;
    }
    else
    {
      Node *old_node = node;
      list->head = new_node;
      list->head->next = old_node;
    }
  }
}

void sort_list(List* list)
{
  if (!list && !list->head)
  {
    return;
  }

  Node *node = list->head;
  Node *next_node = NULL;
  bool sorted = false;
  while (!sorted)
  {
    sorted = true;
    while (node->next != next_node)
    {
      // Swap elements.
      if (node->elem > node->next->elem)
      {
        node->next->elem = node->elem + node->next->elem;
        node->elem = node->next->elem - node->elem;
        node->next->elem = node->next->elem - node->elem;
        sorted = false;
      }

      node = node->next;
    }

    next_node = node;
    node = list->head;
  }
}

void reverse_list(List* list)
{
  if (!list)
  {
    return;
  }

  Node *previous_node = NULL;
  Node *node = list->head;
  Node *next_node = NULL;
  while (node)
  {
    // Store next node.
    next_node = node->next;

    // Change connection in reverse order.
    node->next = previous_node;
    previous_node = node;

    // Move forward.
    node = next_node;
  }

  // Set last node as head of list.
  list->head = previous_node;
}