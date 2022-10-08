#include <stdio.h>

#define ABS(N) ((N<0)?(-N):(N))

/* p p', q q', r r', s s' */
/* 1 -1, 2 -2, 3 -3, 4 -4 */

void resolve(int*, int*);

int main()
{
    /* char *formula[] = {"pq", "p'qrs'", "r's'"}; */
    int formula[][5] = { {1,2,0}, {-1,2,3,-4,0}, {-3,-4,0} };

    resolve(formula[0], formula[1]);

    return 0;
}

void resolve(int* c1, int* c2)
{
    int clashes = 0;
    int l1, l2;
    int new_clause[10] = {0};
    int new_clause_size = 0;

    while (*c1 != 0 && *c2 != 0) {
        l1 = *c1; l2 = *c2;
        if (l1 == -l2 || l2 == -l1) { /* Same magnitude, different sign */
            clashes++; 
            c1++; c2++;
            continue; 
        }
        if (l1 == l2) { 
            new_clause[new_clause_size++] = l1;
            c1++; 
            c2++; 
        }
        if (ABS(l1) > ABS(l2)) { 
            new_clause[new_clause_size++] = l2; 
            c2++; 
        }
        if (ABS(l1) < ABS(l2)) { 
            new_clause[new_clause_size++] = l1; 
            c1++; 
        }
    }

    if (*c1 != *c2) {
        if (*c1 == 0) {
            while (*c2 != 0) {
                new_clause[new_clause_size++] = *(c2++);
            }
        }
        else if (*c2 == 0) {
            while (*c1 != 0) {
                new_clause[new_clause_size++] = *(c1++);
            }
        }
    }

    printf("clashes %d\n", clashes);

    if (clashes == 1) {
        for (int i = 0; i < 10; i++) {
            printf("%d\n", new_clause[i]);
        }
    }
}
