#include "dir_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_stack(DirStack *stack) {
    stack->top = NULL;
}

int pushd(DirStack *stack, const char *dir) {
    char *current_dir = getcwd(NULL, 0);
    if (!current_dir) {
        perror("getcwd failed");
        return -1;
    }

    if (chdir(dir) != 0) {
        perror("chdir failed");
        free(current_dir);
        return -1;
    }

    DirNode *node = (DirNode *)malloc(sizeof(DirNode));
    if (!node) {
        perror("malloc failed");
        free(current_dir);
        return -1;
    }
    node->dir = current_dir;
    node->next = stack->top;
    stack->top = node;

    printf("Directory pushed: %s\n", dir);
    return 0;
}

int popd(DirStack *stack) {
    if (stack->top == NULL) {
        fprintf(stderr, "popd: directory stack empty\n");
        return -1;
    }

    DirNode *node = stack->top;
    if (chdir(node->dir) != 0) {
        perror("chdir failed");
        return -1;
    }
    stack->top = node->next;
    printf("Directory popped: %s\n", node->dir);
    free(node->dir);
    free(node);

    return 0;
}

void cleanup_stack(DirStack *stack) {
    while (stack->top != NULL) {
        DirNode *node = stack->top;
        stack->top = node->next;
        free(node->dir);
        free(node);
    }
}
