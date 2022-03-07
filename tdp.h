typedef struct stack stack;
typedef struct nodes nodes;
typedef struct table table;
typedef struct pointerstack pointerstack;

nodes *parsethrough(char *parseinput, table *parsetable);
void printtdptree(nodes *root);
void recur_printtdptree(nodes *root, int lvl);
void addstack(stack *stack, char input);
char popstack(stack *stack);
void callFunc(int a, stack *stack, char curinput, nodes *nodesin, pointerstack *pointstack);
int isEmpty(stack *stack);
void printstack(stack *stack);
int findindex(table *parsetable, char character, char curparser);

void FNC_X(stack *stack, char curinput, nodes *nodesin, pointerstack *pointstack);
void FNC_A(stack *stack, char curinput, nodes *nodesin, pointerstack *pointstack);
void FNC_ST(stack *stack, char curinput, nodes *nodesin, pointerstack *pointstack);
void FNC_S(stack *stack, nodes *nodesin, pointerstack *pointstack);
void FNC_CT(stack *stack, char curinput, nodes *nodesin, pointerstack *pointstack);
void FNC_C(stack *stack, nodes *nodesin, pointerstack *pointstack);
void FNC_ET(stack *stack, char curinput, nodes *nodesin, pointerstack *pointstack);
void FNC_E(stack *stack, nodes *nodesin, pointerstack *pointstack);

nodes *createnode(char *input);
char *toproperstring(char in);
nodes *poppointer(pointerstack *points);
void addpointer(pointerstack *points, nodes *input);
void printpointer(pointerstack *stack);
int isEmptyp(pointerstack *points);
table *gentable();

struct stack
{
    int Top;
    int high;
    char *Stacks;
};

struct nodes
{

    nodes *lleaves;
    nodes *cleaves;
    nodes *rleaves;
    char *nodename;
};

struct pointerstack
{
    nodes **nodestacks;
    int Top;
};
struct table
{
    int **blocks;
    char topcol[33];
    char *leftrow[10];
};
