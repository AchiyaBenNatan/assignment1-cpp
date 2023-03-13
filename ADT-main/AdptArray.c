#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    PElement* data;
    int size;
    COPY_FUNC copy;
    DEL_FUNC del;
    PRINT_FUNC print;
} AdptArray;

static Result ResizeArr(PAdptArray arr, int newSize, PElement element) {
    PElement* newData = realloc(arr->data, newSize * sizeof(element));
    if (newData == NULL) {
        return FAIL;
    }
    arr->data = newData;
    arr->size = newSize;
    return SUCCESS;
}
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print) {
    PAdptArray arr = malloc(sizeof(AdptArray));
    if (arr == NULL) {
        return NULL;
    }
    arr->data = NULL;
    arr->size = 0;
    arr->copy = copy;
    arr->del = del;
    arr->print = print;
    return arr;
}
void DeleteAdptArray(PAdptArray arr) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i]!=NULL)
        {
            arr->del(arr->data[i]);
        }
    }
    free(arr->data);
    free(arr);
}
Result SetAdptArrayAt(PAdptArray arr, int index, PElement elem) {
    if (index < 0) {
        return FAIL;
    }
    if (index >= arr->size)
    {
        if(ResizeArr(arr,index+1,elem) == FAIL)
        {
            return FAIL;
        }
    }
    arr->data[index] = arr->copy(elem);
    if (arr->size<index+1)
    {
        arr->size = index + 1;
    }
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray arr, int index) {
    if (index < 0 || index >= arr->size) {
        return NULL;
    }
    if (arr->data[index]==NULL)
    {
        return NULL;
    }
    PElement elem = arr->copy(arr->data[index]);
    return elem;
}
int GetAdptArraySize(PAdptArray arr) {
    return arr->size;
}
void PrintDB(PAdptArray arr) {
    printf("Array Contents: \n");
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i]!=NULL)
        {
            arr->print(arr->data[i]);
        }
    }
}