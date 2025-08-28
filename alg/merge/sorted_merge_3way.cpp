#include "sorted_merge_3way.h"
#include <limits.h>

bool sorted_merge_3way(const int *list_a, int na,
                       const int *list_b, int nb,
                       const int *list_c, int nc,
                       int *list_abc) {
    for (int i = 0; i < na - 1; ++i) {
        if (list_a[i] > list_a[i + 1]) {
            return false;
        }
    }

    for (int i = 0; i < nb - 1; ++i) {
        if (list_b[i] > list_b[i + 1]) {
            return false;
        }
    }

    for (int i = 0; i < nc - 1; ++i) {
        if (list_c[i] > list_c[i + 1]) {
            return false;
        }
    }

    int i = 0, j = 0, k = 0, l = 0;

    while (i < na || j < nb || k < nc) {
        int val_a = (i < na) ? list_a[i] : INT_MAX;
        int val_b = (j < nb) ? list_b[j] : INT_MAX;
        int val_c = (k < nc) ? list_c[k] : INT_MAX;

        if (val_a <= val_b && val_a <= val_c) {
            list_abc[l++] = val_a;
            i++;
        } else if (val_b <= val_a && val_b <= val_c) {
            list_abc[l++] = val_b;
            j++;
        } else {
            list_abc[l++] = val_c;
            k++;
        }
    }
 
    return true; 
}