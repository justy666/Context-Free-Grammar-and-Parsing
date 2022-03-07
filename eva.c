#include <stdio.h>
#include <stdlib.h>
#include "eva.h"

tree exptree(tree parse_t)
{
    switch (*(parse_t->label))
    {
    case ('A'):
        if (*(parse_t->first_child->label) == 'X')
        {
            return makeNode0(parse_t->first_child->first_child->label);
        }
        else
        {
            return makeNode3(" ", makeNode0("("), exptree(parse_t->first_child->sibling), makeNode0(")"));
        }

    case ('C'):
        if (*(parse_t->first_child->sibling->first_child->label) == '.')
        {
            return makeNode2(".", exptree(parse_t->first_child), exptree(parse_t->first_child->sibling->first_child->sibling));
        }
        else
        {
            return exptree(parse_t->first_child);
        }
    case ('E'):
        if (*(parse_t->first_child->sibling->first_child->label) == '|')
        {
            return makeNode2("|", exptree(parse_t->first_child), exptree(parse_t->first_child->sibling->first_child->sibling));
        }
        else
        {
            return exptree(parse_t->first_child);
        }

    case ('S'):
        if (*(parse_t->first_child->sibling->first_child->label) == '*')
        {
            tree s = parse_t->first_child->sibling;
            int counter = 0;
            while (s != NULL && (*(s->first_child->label) == '*'))
            {
                counter = counter + 1;
                s = s->first_child->sibling;
            }
            s = makeNode1("*", exptree(parse_t->first_child));
            for (int x = counter - 1; x > 0; x--)
            {
                s = makeNode1("*", s);
            }
            return s;
        }
        else
        {
            return exptree((parse_t->first_child));
        }

    default:
        return NULL;
    }
}

void prtexp(tree input)
{
    if (input == NULL)
    {
        return;
    }
    printf("(");
    if (*(input->label) == '|')
    {
        printf("UNION ");
        prtexp(input->first_child);
        prtexp(input->sibling);
        printf(")");
    }
    else if (*(input->label) == '.')
    {
        printf("CONCAT ");
        prtexp(input->first_child);
        prtexp(input->sibling);
        printf(")");
    }
    else if (*(input->label) == '*')
    {
        printf("CLOSURE ");
        prtexp(input->first_child);
        prtexp(input->sibling);
        printf(")");
    }
    else
    {
        printf("ATOMIC %s", input->label);
        printf(")");
        prtexp(input->first_child);
        prtexp(input->sibling);
    }
}
