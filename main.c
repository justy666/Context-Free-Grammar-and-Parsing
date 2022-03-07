#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdp.h"
#include "eva.h"

int rdp(char *inp)
{
    int validness = 0;
    printf("Recursive descent parser\n");
    lah = inp;
    tree parseTree = parse(inp);
    if (parseTree == NULL)
    {
        printf("Invalid\n");
        validness = 1;
    }
    else
    {

        printTree(parseTree, 0);
    }
    return validness;
}

void tdp(char *inp)
{

    struct table *tab = gentable();
    nodes *output = parsethrough(inp, tab);
    printf("Table driven parser\n");
    printtdptree(output);
    for (int i = 0; i < 8; i++)
    {
        free(tab->blocks[i]);
    }
    free(tab->blocks);
    free(tab);
}

void eva(char *inp)
{
    printf("Evaluate parse expression\n");
    lah = inp;
    tree parseTree = parse(inp);
    tree exp_t = exptree(parseTree);
    prtexp(exp_t);
    printf("\n");
}

int main()
{
    printf("Enter input, enter QUIT to quit\n");
    char input[128];
    scanf("%s", input);
    while (strcmp(input, "QUIT") != 0)
    {
        if (rdp(input) == 1)
        {
            printf("Rejected, please enter another input\n");
            scanf("%s", input);
        }
        else
        {
            tdp(input);
            eva(input);
            printf("Accepted, please enter another input\n");
            scanf("%s", input);
        }
    }
    printf("Program ends.");
}