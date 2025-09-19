/* R. Fabbri, 2024 */
#include <gtest/gtest.h>
#include <string.h> // For memcmp
#include <stdio.h>

#include <sorted_merge_3way.h>

// This will print to stdout, which GTest captures.
void
show_result(const int *a, int na, bool resultado)
{
  if (resultado) {
    for (int i=0; i < na; ++i)
      printf("%d ", a[i]);
    printf("\n");
  } else
    printf("Alguma das listas nao esta ordenada\n");
}

// Test case 1: Valid merge
TEST(JuntaListasTest, ValidMerge)
{
  int a[3] = { 3, 6, 11 };
  int b[4] = { 4, 16, 21, 25 };
  int c[2] = { 1, 10 };
  int abc[3+4+2];
  static const int abc_ground_truth[] = { 1, 3, 4, 6, 10, 11, 16, 21, 25 };

  bool res = sorted_merge_3way( a, 3, b, 4, c, 2, abc);

  // Call show_result as requested
  show_result(abc, 3+4+2, res);

  ASSERT_TRUE(res) << "sorted_merge_3way returned false unexpectedly (input was sorted).";
  ASSERT_EQ(0, memcmp(abc, abc_ground_truth, (3+4+2) * sizeof(int)))
      << "Merged array content mismatch.";
}

// Test case 2: Unsorted input (c is {11, 10})
TEST(JuntaListasTest, UnsortedInput)
{
  int a[3] = { 3, 6, 11 };
  int b[4] = { 4, 16, 21, 25 };
  int c[2] = { 11, 10 }; // This list is unsorted
  int abc[3+4+2];

  bool res = sorted_merge_3way( a, 3, b, 4, c, 2, abc);

  // Call show_result as requested
  show_result(abc, 3+4+2, res);

  ASSERT_FALSE(res) << "sorted_merge_3way returned true unexpectedly (input was unsorted).";
}
