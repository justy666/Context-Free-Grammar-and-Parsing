#ifndef CSC173_pro2_rdp_h
#define CSC173_pro2_rdp_h

#endif

typedef struct node
{
    struct node *first_child;
    struct node *sibling;
    char *label;
} node;
typedef struct node *tree;
extern tree makeNode0(char *x);
extern tree makeNode1(char *x, tree t);
extern tree makeNode2(char *x, tree t1, tree t2);
extern tree makeNode3(char *x, tree t1, tree t2, tree t3);
extern tree parse(char *inp);
extern void printTree(tree tr, int dep);

char *lah; //lookahead
int depth;

extern tree E();
extern tree ET();
extern tree C();
extern tree CT();
extern tree S();
extern tree ST();
extern tree A();
extern tree X();
