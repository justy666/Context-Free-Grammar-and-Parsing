#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdp.h"

char popstack(stack *stacks)
{
    if (stacks->Top != 0)
    {
        char output = stacks->Stacks[stacks->Top];
        stacks->Stacks[stacks->Top] = '0';
        stacks->Top = stacks->Top - 1;
        return output;
    }
    else
    {
        return -1;
    }
}
void addstack(stack *stack, char input)
{
    if (stack->Top < 0)
    {
        stack->Stacks[0] = input;
        stack->Top = 0;
    }
    else if (stack->Top > 9)
    {
        return;
    }
    else
    {
        stack->Top = stack->Top + 1;
        stack->Stacks[stack->Top] = input;
    }
}

void printstack(stack *stack)
{
    for (int x = 0; x < stack->Top; x++)
    {
        printf("%c ", stack->Stacks[x]);
    }
    printf("\n");
}

void callFunc(int a, stack *stack, char curinput, nodes *in, pointerstack *ptstack)
{
    if (a == 0)
    {
        FNC_E(stack, in, ptstack);
    }
    else if (a == 1)
    {
        FNC_ET(stack, curinput, in, ptstack);
    }
    else if (a == 2)
    {
        FNC_C(stack, in, ptstack);
    }
    else if (a == 3)
    {
        FNC_CT(stack, curinput, in, ptstack);
    }
    else if (a == 4)
    {
        FNC_S(stack, in, ptstack);
    }
    else if (a == 5)
    {
        FNC_ST(stack, curinput, in, ptstack);
    }
    else if (a == 6)
    {
        FNC_A(stack, curinput, in, ptstack);
    }
    else if (a == 7)
    {
        FNC_X(stack, curinput, in, ptstack);
    }
}

void FNC_X(stack *stack, char curinput, nodes *in, pointerstack *ptstack)
{
    char a[] = "abcdefghijklmnopqrstuvwxyz"; // include all charaters
    for (int x = 0; x < strlen(a); x++)
    {
        if (curinput == a[x])
        {

            char str[2] = "\0";
            addstack(stack, a[x]);
            str[0] = a[x];
            nodes *nodeleft = createnode(str);
            in->lleaves = nodeleft;
            addpointer(ptstack, nodeleft);
            break;
        }
    }
}
void FNC_A(stack *stack, char curinput, nodes *in, pointerstack *ptstack)
{
    if (curinput != '(')
    {
        nodes *nodeleft = createnode("X");
        addstack(stack, 'H');
        in->lleaves = nodeleft;
        addpointer(ptstack, nodeleft);
    }
    else
    {
        nodes *nodel = createnode("(");
        nodes *nodec = createnode("E");
        nodes *noder = createnode(")");
        addstack(stack, ')');
        addstack(stack, 'A');
        addstack(stack, '(');
        in->lleaves = nodel;
        in->cleaves = nodec;
        in->rleaves = noder;
        addpointer(ptstack, noder);
        addpointer(ptstack, nodec);
        addpointer(ptstack, nodel);
    }
}

void FNC_ST(stack *stack, char curinput, nodes *in, pointerstack *ptstack)
{
    if (curinput != '*')
    {

        nodes *nodeleft = createnode("esp");
        addstack(stack, 'Z');
        in->lleaves = nodeleft;
        addpointer(ptstack, nodeleft);
    }
    else
    {
        nodes *nodeleft = createnode("*");
        nodes *nodecenter = createnode("ST");
        addstack(stack, 'F');
        addstack(stack, '*');
        in->lleaves = nodeleft;
        in->cleaves = nodecenter;
        addpointer(ptstack, nodecenter);
        addpointer(ptstack, nodeleft);
    }
}

void FNC_S(stack *stack, nodes *in, pointerstack *ptstack)
{
    nodes *nodeleft = createnode("A");
    nodes *nodecenter = createnode("ST");
    addstack(stack, 'F');
    addstack(stack, 'G');
    in->lleaves = nodeleft;
    in->cleaves = nodecenter;
    addpointer(ptstack, nodecenter);
    addpointer(ptstack, nodeleft);
}

void FNC_CT(stack *stack, char curinput, nodes *in, pointerstack *ptstack)
{
    if (curinput != '.')
    {
        nodes *nodeleft = createnode("esp");
        addstack(stack, 'Z');
        in->lleaves = nodeleft;
        addpointer(ptstack, nodeleft);
    }
    else
    {
        nodes *nodeleft = createnode(".");
        nodes *nodecenter = createnode("C");
        addstack(stack, 'C');
        addstack(stack, '.');
        in->lleaves = nodeleft;
        in->cleaves = nodecenter;
        addpointer(ptstack, nodecenter);
        addpointer(ptstack, nodeleft);
    }
}

void FNC_C(stack *stack, nodes *in, pointerstack *ptstack)
{
    nodes *nodeleft = createnode("S");
    nodes *nodecenter = createnode("CT");
    addstack(stack, 'D');
    addstack(stack, 'E');
    in->lleaves = nodeleft;
    in->cleaves = nodecenter;
    addpointer(ptstack, nodecenter);
    addpointer(ptstack, nodeleft);
}

void FNC_ET(stack *stack, char curinput, nodes *in, pointerstack *ptstack)
{
    if (curinput != '|')
    {
        nodes *nodeleft = createnode("esp");
        addstack(stack, 'Z');
        in->lleaves = nodeleft;
        addpointer(ptstack, nodeleft);
    }
    else
    {
        nodes *nodeleft = createnode("|");
        nodes *nodecenter = createnode("E");
        addstack(stack, 'A');
        addstack(stack, '|');
        in->lleaves = nodeleft;
        in->cleaves = nodecenter;
        addpointer(ptstack, nodecenter);
        addpointer(ptstack, nodeleft);
    }
}

void FNC_E(stack *stack, nodes *in, pointerstack *ptstack)
{
    nodes *nodeleft = createnode("C");
    nodes *nodecenter = createnode("ET");
    addstack(stack, 'B');
    addstack(stack, 'C');
    in->lleaves = nodeleft;
    in->cleaves = nodecenter;
    addpointer(ptstack, nodecenter);
    addpointer(ptstack, nodeleft);
}

int findindex(table *parsetable, char character, char curparser)
{
    int row = 0;
    int col = 0;

    for (int x = 0; x < strlen(parsetable->topcol); x++)
    {
        char a = parsetable->topcol[x];
        if (character == a)
        {
            col = x;
            break;
        }
    }
    if (curparser == 'A')
    {
        row = 0;
    }
    else if (curparser == 'B')
    {
        row = 1;
    }
    else if (curparser == 'C')
    {
        row = 2;
    }
    else if (curparser == 'D')
    {
        row = 3;
    }
    else if (curparser == 'E')
    {
        row = 4;
    }
    else if (curparser == 'F')
    {
        row = 5;
    }
    else if (curparser == 'G')
    {
        row = 6;
    }
    else if (curparser == 'H')
    {
        row = 7;
    }
    return parsetable->blocks[row][col];
}

nodes *createnode(char *input)
{
    nodes *output = (nodes *)malloc(sizeof(nodes));
    if (output != NULL)
    {
        output->nodename = malloc(strlen(input) + 1);
        strcpy(output->nodename, input);
        output->lleaves = NULL;
        output->rleaves = NULL;
        output->cleaves = NULL;
    }
    return output;
}

int isEmpty(stack *stack)
{
    if (stack->Top < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isEmptyp(pointerstack *points)
{
    if (points->Top < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

nodes *poppointer(pointerstack *points)
{
    if (points->Top == 0)
    {
        nodes *output = createnode("empty");
        return output;
    }
    else
    {
        nodes *output = points->nodestacks[points->Top];
        points->nodestacks[points->Top] = NULL;
        points->Top = points->Top - 1;
        return output;
    }
}
void addpointer(pointerstack *point, nodes *input)
{
    if (point->Top < 0)
    {
        point->nodestacks[0] = input;
        point->Top = 0;
    }
    else if (point->Top > 9)
    {
        return;
    }
    else
    {
        point->Top = point->Top + 1;
        point->nodestacks[point->Top] = input;
    }
}

void printpointer(pointerstack *stack)
{
    for (int x = 0; x < stack->Top; x++)
    {
        printf("%s	", stack->nodestacks[x]->nodename);
    }
    printf("\n");
}

char *toproperstring(char in)
{
    if (in == 'A')
    {
        return "E";
    }
    else if (in == 'B')
    {
        return "ET";
    }
    else if (in == 'C')
    {
        return "C";
    }
    else if (in == 'D')
    {
        return "CT";
    }
    else if (in == 'E')
    {
        return "S";
    }
    else if (in == 'F')
    {
        return "ST";
    }
    else if (in == 'G')
    {
        return "A";
    }
    else if (in == 'H')
    {
        return "X";
    }
    return "\0";
}

nodes *parsethrough(char *input, table *table)
{
    int curindex = 0; //currentindex
    int ER = 0;       //record of error

    struct pointerstack *ptstack = (pointerstack *)malloc(sizeof(stack));
    ptstack->Top = 0;
    ptstack->nodestacks = (nodes **)malloc(sizeof(nodes *) * 10);

    struct stack *parsestack = (stack *)malloc(sizeof(stack));

    parsestack->Stacks = (char *)malloc(sizeof(char) * 10);
    parsestack->Top = 0;

    nodes *topnode = createnode("E");
    addstack(parsestack, 'A');
    addpointer(ptstack, topnode);

    while (ER == 0 && curindex < strlen(input) + 1)
    {

        if (isEmpty(parsestack))
        {
            printf("The error has been recorde\n");
            ER = 1;
            break;
        }
        char curparse = popstack(parsestack);
        nodes *curNode = poppointer(ptstack);
        if (curparse == 'A' || curparse == 'B' || curparse == 'C' || curparse == 'D' || curparse == 'E' || curparse == 'F' || curparse == 'G' || curparse == 'H')
        {
            int nexFunction = findindex(table, input[curindex], curparse);
            if (nexFunction != -1)
            {
                callFunc(nexFunction, parsestack, input[curindex], curNode, ptstack);
                if (curNode->lleaves != NULL)
                {
                }
                if (curNode->rleaves != NULL)
                {
                }
                if (curNode->cleaves != NULL)
                {
                }
            }
            else
            {
                ER = 1;
                break;
            }
        }
        else if (curparse == 'Z')
        {
        }
        else
        {
            if (isEmptyp(ptstack))
            {
                break;
            }
            else
            {
                curindex++;
            }
        }
    }

    if (ER == 1 || curindex < strlen(input))
    {
        topnode->lleaves = NULL;
        topnode->cleaves = NULL;
        topnode->lleaves = NULL;
    }
    free(ptstack->nodestacks);
    free(parsestack->Stacks);
    free(parsestack);
    free(ptstack);

    return topnode;
}

void printtab(int numtabs)
{
    for (int x = 0; x < numtabs; x++)
    {
        printf(" ");
    }
}

void recur_printtdptree(nodes *root, int lvl)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printtab(lvl);
        printf("%s\n", root->nodename);
        if (root->lleaves != NULL)
        {
            printtab(lvl);
            recur_printtdptree(root->lleaves, lvl + 1);
        }
        if (root->cleaves != NULL)
        {
            printtab(lvl);
            recur_printtdptree(root->cleaves, lvl + 1);
        }
        if (root->rleaves != NULL)
        {
            printtab(lvl);
            recur_printtdptree(root->rleaves, lvl + 1);
        }
        free(root->nodename);
        free(root);
    }
}

void printtdptree(nodes *root)
{
    recur_printtdptree(root, 0);
}

//generate a table for parsing
table *gentable()
{
    struct table *parsetable = (table *)malloc(sizeof(table));
    parsetable->blocks = (int **)malloc(8 * sizeof(int *));
    strcpy(parsetable->topcol, "|*.(abcdefghijklmnopqrstuvwxyz\0");
    parsetable->leftrow[0] = "E";
    parsetable->leftrow[1] = "ET";
    parsetable->leftrow[2] = "C";
    parsetable->leftrow[3] = "CT";
    parsetable->leftrow[4] = "S";
    parsetable->leftrow[5] = "ST";
    parsetable->leftrow[6] = "A";
    parsetable->leftrow[7] = "X";

    for (int x = 0; x < 8; x++)
    {
        parsetable->blocks[x] = (int *)malloc(30 * sizeof(int));
    }

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 30; y++)
        {
            parsetable->blocks[x][y] = -1;
        }
    }
    for (int x = 3; x < 30; x++)
    {
        parsetable->blocks[0][x] = 0;
        parsetable->blocks[2][x] = 2;
        parsetable->blocks[4][x] = 4;
        parsetable->blocks[6][x] = 6;
    }
    for (int x = 4; x < 30; x++)
    {
        parsetable->blocks[7][x] = 7;
    }
    for (int x = 0; x < 30; x++)
    {
        parsetable->blocks[1][x] = 1;
        parsetable->blocks[3][x] = 3;
        parsetable->blocks[5][x] = 5;
    }
    return parsetable;
}
