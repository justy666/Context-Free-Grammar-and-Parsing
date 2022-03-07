#include <stdio.h>
#include <stdlib.h>
#include "rdp.h"

#define FAILED NULL

tree makeNode0(char *x)
{
    tree root;
    root = (tree)malloc(sizeof(node));
    root->label = x;
    root->first_child = NULL;
    root->sibling = NULL;
    return root;
}

tree makeNode1(char *x, tree t)
{
    tree root;
    root = makeNode0(x);
    root->first_child = t;
    return root;
}

tree makeNode2(char *x, tree t1, tree t2)
{
    tree root;
    root = makeNode1(x, t1);
    t1->sibling = t2;
    return root;
}
tree makeNode3(char *x, tree t1, tree t2, tree t3)
{
    tree root;
    root = makeNode0(x);
    root->first_child = t1;
    t1->sibling = t2;
    t2->sibling = t3;
    return root;
}

/*char* lookahead;
void assign_lookhead(char* input){
    lookahead=input;
}*/

void printTree(tree tree1, int depth1)
{
    if (tree1 == NULL)
    {
        return;
    }
    else
    {
        for (int i = 0; i < depth1; i++)
        {
            printf("  ");
        }
        printf("%s\n", tree1->label);
        printTree(tree1->first_child, depth1 + 1);
        printTree(tree1->sibling, depth1);
    }
    free(tree1);
}

tree parse(char *inp)
{
    tree inp_tree = E();
    if (*lah == '\0')
    {
        return inp_tree;
    }
    else
    {
        return FAILED;
    }
}

tree X()
{
    switch (*lah)
    {
    case ('a'):
        lah++;
        return (makeNode1("X", makeNode0("a")));
    case ('b'):
        lah++;
        return (makeNode1("X", makeNode0("b")));
    case ('c'):
        lah++;
        return (makeNode1("X", makeNode0("c")));
    case ('d'):
        lah++;
        return (makeNode1("X", makeNode0("d")));
    case ('e'):
        lah++;
        return (makeNode1("X", makeNode0("e")));
    case ('f'):
        lah++;
        return (makeNode1("X", makeNode0("f")));
    case ('g'):
        lah++;
        return (makeNode1("X", makeNode0("g")));
    case ('h'):
        lah++;
        return (makeNode1("X", makeNode0("h")));
    case ('i'):
        lah++;
        return (makeNode1("X", makeNode0("i")));
    case ('j'):
        lah++;
        return (makeNode1("X", makeNode0("j")));
    case ('k'):
        lah++;
        return (makeNode1("X", makeNode0("k")));
    case ('l'):
        lah++;
        return (makeNode1("X", makeNode0("l")));
    case ('m'):
        lah++;
        return (makeNode1("X", makeNode0("m")));
    case ('n'):
        lah++;
        return (makeNode1("X", makeNode0("n")));
    case ('o'):
        lah++;
        return (makeNode1("X", makeNode0("o")));
    case ('p'):
        lah++;
        return (makeNode1("X", makeNode0("p")));
    case ('q'):
        lah++;
        return (makeNode1("X", makeNode0("q")));
    case ('r'):
        lah++;
        return (makeNode1("X", makeNode0("r")));
    case ('s'):
        lah++;
        return (makeNode1("X", makeNode0("s")));
    case ('t'):
        lah++;
        return (makeNode1("X", makeNode0("t")));
    case ('u'):
        lah++;
        return (makeNode1("X", makeNode0("u")));
    case ('v'):
        lah++;
        return (makeNode1("X", makeNode0("v")));
    case ('w'):
        lah++;
        return (makeNode1("X", makeNode0("w")));
    case ('x'):
        lah++;
        return (makeNode1("X", makeNode0("x")));
    case ('y'):
        lah++;
        return (makeNode1("X", makeNode0("y")));
    case ('z'):
        lah++;
        return (makeNode1("X", makeNode0("z")));
    default:
        return FAILED;
    }
}

tree A()
{
    tree firstA;
    if (*lah == '(')
    {
        lah++;
        firstA = E(lah);
        if (firstA != FAILED && *lah == ')')
        {
            lah++;
            return makeNode3("A", makeNode0("("), firstA, makeNode0(")"));
        }
        else
        {
            return FAILED;
        }
    }
    else
    {
        firstA = X();
        if (firstA != FAILED)
        {
            return makeNode1("A", firstA);
        }
        else
        {
            return FAILED;
        }
    }
}

tree ST()
{
    tree firstST;
    if (*lah == '*')
    {
        lah++;
        firstST = ST();
        if (firstST != FAILED)
        {
            return makeNode2("ST", makeNode0("*"), firstST);
        }
        else
        {
            return FAILED;
        }
    }
    else
    {
        return makeNode1("ST", makeNode0("eps"));
    }
}

tree S()
{
    tree firstS, secondS;
    firstS = A();
    secondS = ST();
    if (firstS != FAILED && secondS != FAILED)
    {
        return makeNode2("S", firstS, secondS);
    }
    else
    {
        return FAILED;
    }
}

tree CT()
{
    tree firstCT;
    if (*lah == '.')
    {
        lah++;
        firstCT = C(lah);
        if (firstCT != FAILED)
        {
            return makeNode2("CT", makeNode0("."), firstCT);
        }
        else
        {
            return FAILED;
        }
    }
    else
    {
        return makeNode1("CT", makeNode0("eps"));
    }
}

tree C()
{
    tree firstC, secondC;
    firstC = S();
    secondC = CT();
    if (firstC != FAILED && secondC != FAILED)
    {
        return makeNode2("C", firstC, secondC);
    }
    else
    {
        return FAILED;
    }
}

tree ET()
{
    tree firstET;
    if (*lah == '|')
    {
        lah++;
        firstET = E();
        if (firstET != FAILED)
        {
            return makeNode2("ET", makeNode0("|"), firstET);
        }
        else
        {
            return FAILED;
        }
    }
    else
    {
        return makeNode1("ET", makeNode0("eps"));
    }
}

tree E()
{
    tree firstE, secondE;
    firstE = C();
    secondE = ET();
    if (firstE != FAILED && secondE != FAILED)
    {
        return makeNode2("E", firstE, secondE);
    }
    else
    {
        return FAILED;
    }
}