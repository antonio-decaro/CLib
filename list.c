#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct c_node {
    void* data;
    struct c_node* next;
    struct c_node* prev;
};

struct c_list {
    struct c_node* first;
    struct c_node* last;
    int size;
};

// prototipi

void insertNode(List list, void* el, int pos);
Node getNode(List list, int pos);
void removeNode(List list, int pos);
void clearNode(Node node);


List newList()
{
    List list = (List) malloc(sizeof(struct c_list));
    list->size = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

List newFromArray(void** array, int size) 
{
    List list = newList();
    for (int i = 0; i < size; i++)
        appendListItem(list, array[i]);

    return list;
}

void insertListItem(List list, void* el, int pos)
{
    if (list == NULL || pos < 0 || pos > list->size)
        return;
    
    insertNode(list, el, pos);
}

void appendListItem(List list, void* el)
{
    insertNode(list, el, list->size);    
}

void pushListItem(List list, void* el)
{
    insertNode(list, el, 0);
}

void removeListItem(List list, int pos)
{
    if (list == NULL || pos < 0 || pos >= list->size)
        return;

    removeNode(list, pos);
}

void* getListItem(List list, int pos)
{
    if (list == NULL || pos < 0 || pos >= list->size)
        return NULL;
    
    Node node = getNode(list, pos);
    return node->data;
}

void* popListItem(List list)
{
    if (list == NULL || list->size == 0)
        return NULL;
    
    Node node = list->first;
    list->first->next->prev = NULL;
    list->first = list->first->next;

    void* ret = node->data;
    free(node);
    return ret;
}

int listSize(List list)
{
    if (list == NULL)
        return -1;
    return list->size;
}

void clearList(List list)
{
    for (int i = 0; i < list->size; i++)
        clearNode(getNode(list, i));
}

void** listIntoArray(List list)
{
    if (list == NULL)
        return NULL;

    void** array = malloc(sizeof(void*) * list->size);

    int counter = 0;
    Node pointer = list->first;
    while (pointer != NULL && counter < list->size)
    {
        array[counter++] = pointer->data;
        pointer = pointer->next;
    }

    return array;
}

Node getListIterator(List list)
{
    if (list == NULL)
        return NULL;
    
    return list->first;
}

Node getLastListIterator(List list)
{
    if (list == NULL)
        return NULL;
    
    return list->last;
}

Node getNextIterator(List list, Node iterator)
{
    if (list == NULL || iterator == NULL)
        return NULL;
    
    if (list->last == iterator)
        return NULL;
    
    return iterator->next;
}

Node getPrevIterator(List list, Node iterator)
{
    if (list == NULL || iterator == NULL)
        return NULL;
    
    if (list->first == iterator)
        return NULL;
    
    return iterator->prev;
}

void* getItemIterator(Node iterator)
{
    if (iterator == NULL)
        return NULL;

    return iterator->data;
}

void insertItemIterator(Node iterator, List list, void* el)
{
    if (list == NULL)
        return;
    
    if (list->size == 0 && iterator == NULL)
        pushListItem(list, el);
    
    
    else if (list->size > 0 && iterator == NULL)
        appendListItem(list, el);

    else if (list->size > 0 && iterator != NULL)
    {
        if (iterator->prev == NULL)
        {
            pushListItem(list, el);
        }
        else
        {
            Node new_node = malloc(sizeof(struct c_node));
            new_node->data = el;
            // inserting before the iterator
            new_node->next = iterator;
            new_node->prev = iterator->prev;

            iterator->prev->next = new_node;
            iterator->prev = new_node;
        }

        list->size++;
    }
}

void removeItemIterator(Node iterator, List list)
{
    if (list == NULL || list->size == 0 || iterator == NULL)
        return;
    
    if (iterator == list->first || iterator == list->last)
    {
        int pos = iterator == list->first ? 0 : list->size - 1;
        removeNode(list, pos);
    }
    
    else
    {
        Node prev = iterator->prev;
        Node next = iterator->next;

        prev->next = next;
        next->prev = prev;

        clearNode(iterator);
        list->size--;
    }
}

// helping functions

void insertNode(List list, void* el, int pos)
{
    Node new_node = malloc(sizeof(struct c_node));
    new_node->data = el;
    new_node->next = new_node->prev = NULL;
    
    if (list->size == 0)
    {
        list->first = list->last = new_node;
    }
    
    else if (pos == 0)
    {
        new_node->next = list->first;
        list->first->prev = new_node;
        list->first = new_node;
    }

    else if (pos == list->size)
    {
        new_node->prev = list->last;
        list->last->next = new_node;
        list->last = new_node;
    }

    else
    {
        Node curr_node = getNode(list, pos);
        new_node->prev = curr_node->prev;
        new_node->next = curr_node;
        
        curr_node->prev->next = new_node;
        curr_node->prev = new_node;
    }

    list->size++;
}

Node getNode(List list, int pos)
{
    if (pos == 0)
        return list->first;
    
    else if (pos == list->size - 1)
        return list->last;

    else if (pos <= list->size / 2) // if the position is in the first half
    {
        int c = 0;
        Node curr_node = list->first;
        while (c < pos)
        {
            c++;
            curr_node = curr_node->next;
        }
        return curr_node;     
    }

    else // if the position is in the second half
    {
        int c = list->size - 1;
        Node curr_node = list->last;
        while (c > pos)
        {
            c--;
            curr_node = curr_node->prev;
        }

        return curr_node;
    }   
}

void removeNode(List list, int pos)
{
    if (list->size == 0)
        return;

    Node to_remove = NULL;

    if (list->size == 1 && pos == 0)
    {
        to_remove = list->first;

        list->first = list->last = NULL;
    }

    else if (pos == 0)
    {
        to_remove = list->first;

        list->first->next->prev = NULL;
        list->first = list->first->next;
    }

    else if (pos == list->size - 1)
    {
        to_remove = list->last;

        list->last->prev->next = NULL;
        list->last = list->last->prev;
    }

    else
    {
        to_remove = getNode(list, pos);
        
        to_remove->next->prev = to_remove->prev;
        to_remove->prev->next = to_remove->next;
    }

    clearNode(to_remove);
    list->size--;
}

void clearNode(Node node)
{
    node->next = node->prev = NULL;
    free(node->data);
    free(node);
}