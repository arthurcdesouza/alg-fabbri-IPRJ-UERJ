#include <gtest/gtest.h>
#include "sorted_merge_3way.h" // Inclui o algoritmo que está na pasta pai

TEST(SortedMergeTest, CasoBasico) {
    std::vector<int> v1 = {1, 5, 9};
    std::vector<int> v2 = {2, 6, 10};
    std::vector<int> v3 = {3, 7, 11};
    std::vector<int> esperado = {1, 2, 3, 5, 6, 7, 9, 10, 11};
    ASSERT_EQ(sorted_merge_3way(v1, v2, v3), esperado);
}

TEST(SortedMergeTest, ComVetorVazio) {
    std::vector<int> v1 = {1, 5};
    std::vector<int> v2 = {}; // Vetor vazio
    std::vector<int> v3 = {2, 6};
    std::vector<int> esperado = {1, 2, 5, 6};
    ASSERT_EQ(sorted_merge_3way(v1, v2, v3), esperado);
}

TEST(SortedMergeTest, TamanhosDiferentes) {
    std::vector<int> v1 = {10, 20};
    std::vector<int> v2 = {15, 25, 35, 45};
    std::vector<int> v3 = {5};
    std::vector<int> esperado = {5, 10, 15, 20, 25, 35, 45};
    ASSERT_EQ(sorted_merge_3way(v1, v2, v3), esperado);

