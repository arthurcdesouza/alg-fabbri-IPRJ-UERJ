#include "sorted_merge_3way.h"
#include <climits>

bool sorted_merge_3way(
    const int *list_a, int na,
    const int *list_b, int nb,
    const int *list_c, int nc,
    int *list_abc)
{
    for (int i = 1; i < na; i++)
        if (list_a[i] < list_a[i-1]) return false;

    for (int i = 1; i < nb; i++)
        if (list_b[i] < list_b[i-1]) return false;

    for (int i = 1; i < nc; i++)
        if (list_c[i] < list_c[i-1]) return false;

    int ia = 0, ib = 0, ic = 0;
    int k = 0;

    while (ia < na || ib < nb || ic < nc) {
        int va = (ia < na) ? list_a[ia] : INT_MAX;
        int vb = (ib < nb) ? list_b[ib] : INT_MAX;
        int vc = (ic < nc) ? list_c[ic] : INT_MAX;

        if (va <= vb && va <= vc) {
            list_abc[k++] = va;
            ia++;
        } else if (vb <= va && vb <= vc) {
            list_abc[k++] = vb;
            ib++;
        } else {
            list_abc[k++] = vc;
            ic++;
        }
    }

    return true;
}
