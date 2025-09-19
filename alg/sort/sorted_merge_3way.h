/* R. Fabbri, 2024 */
#ifndef SORTED_MERGE_3WAY_H
#define SORTED_MERGE_3WAY_H

/*
 * Merges three sorted integer lists (lista_a, lista_b, lista_c) into a
 * single sorted list (lista_abc).
 *
 * @param lista_a   Pointer to the first list.
 * @param na        Number of elements in the first list.
 * @param lista_b   Pointer to the second list.
 * @param nb        Number of elements in the second list.
 * @param lista_c   Pointer to the third list.
 * @param nc        Number of elements in the third list.
 * @param lista_abc Pointer to the output list, which must have enough space
 *                  to hold all elements from the input lists (na+nb+nc).
 * @return          `true` if the merge was successful and all input lists
 *                  were sorted, `false` otherwise.
 */
bool
sorted_merge_3way(
    const int *list_a, int na,
    const int *list_b, int nb,
    const int *list_c, int nc,
    int *list_abc);

#endif /* SORTED_MERGE_3WAY_H */
