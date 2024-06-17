#ifndef DIR_STACK_H
#define DIR_STACK_H

typedef struct DirNode {
    char *dir;
    struct DirNode *next;
} DirNode;

typedef struct DirStack {
    DirNode *top;
} DirStack;

void init_stack(DirStack *stack);
int pushd(DirStack *stack, const char *dir);
int popd(DirStack *stack);
void cleanup_stack(DirStack *stack);

#endif // DIR_STACK_H
