#include "list.h"

#include <stdio.h>

int main(void)
{
    List *list = create_list();

    insert_to_list(list, 0, 0);
    insert_to_list(list, 100, 0);
    count_elements(list);

    append_to_list(list, 1);
    append_to_list(list, 10);
    append_to_list(list, 100);
    append_to_list(list, -100);
    append_to_list(list, -10);
    append_to_list(list, -100);

    int size = count_elements(list);
    printf("SIZE -> %d\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("VALUE OF INDEX_%d -> %d\n", i, get_nth_element(list, i));
    }

    remove_nth_element(list, 0);
    remove_nth_element(list, 2);
    remove_nth_element(list, -1);
    insert_to_list(list, 15, 0);
    size = count_elements(list);
    printf("SIZE -> %d\n", size);
    insert_to_list(list, 15, 5);

    for (int i = 0; i < 10; i++)
    {
        insert_to_list(list, i * i % 16, i);
    }

    size = count_elements(list);
    printf("SIZE -> %d\n", size);

    for (int i = 0; i < size; i++)
    {
        printf("VALUE OF INDEX_%d -> %d\n", i, get_nth_element(list, i));
    }
    sort_list(list);
    printf("SORTED\n");
    for (int i = 0; i < size; i++)
    {
        printf("VALUE OF INDEX_%d -> %d\n", i, get_nth_element(list, i));
    }


    reverse_list(list);
    printf("REVERSED!\n");
    for (int i = 0; i < size; i++)
    {
        printf("VALUE OF INDEX_%d -> %d\n", i, get_nth_element(list, i));
    }

    reverse_list(list);
    for (int i = 0; i < size; i++)
    {
        printf("VALUE OF INDEX_%d -> %d\n", i, get_nth_element(list, i));
    }

    destroy_list(&list);
}


