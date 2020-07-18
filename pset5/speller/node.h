#include "dictionary.h"



typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;