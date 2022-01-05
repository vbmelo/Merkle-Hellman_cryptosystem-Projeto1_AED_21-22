//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// Place your student numbers and names here
//

#if __STDC_VERSION__ < 199901L
// error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
#define STUDENT_H_FILE "000000.h"
#define ARRAYSIZE(a) (sizeof(a)) / (sizeof(a[0])) // find the length of an array
#endif
#include <stdio.h>
#include <stdlib.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE

struct Subset
{
  integer_t *p, *t, *b;
};

struct Subset printSubset(integer_t *p, integer_t *t, int t_size, integer_t *b, int n)
{
  struct Subset subset = {p, t, b};
  printf(" bits: ");
  for (int i = 0; i < n; i++)
  {
    printf("%lld", b[i]);
  }
  printf("\n");
  return subset;
}

// inputs
// p            - set vector
// t            - tuplet vector
// n            - set size
// t_size       - tuplet size so far  / 0
// current_index- current index       / 0
// partial_sum  - partial_sum so far  / 0
// desired_sum  - sum to be found
// b            - bit vector
void subset_sum(integer_t *p, integer_t *t, int n, int t_size, int partial_sum, int current_index, int const desired_sum, integer_t *b)
{
  for (int i = 0; i < n; i++)
  {
    b[i] = 0; // filling the bit array with zeroes
  }

  if (desired_sum == partial_sum)
  {
    // filling the bit array with 1's for the numbers that are present in the subset for the desired sum
    for (int a = 0; a < n; a++)
    { // iterates through all the numbers in the given weight array
      for (int x = 0; x < t_size; x++)
      {                   // iterates through all the different subset's and it's content
        if (t[x] == p[a]) // matching each subset item with it correspondent index in the weight array
        {
          b[a] = 1; // element in the same index that matched the subset is set to 1, wich indicates it's being used in the subset.
        }
      }
    }
    // We found partial_sum
    printSubset(p, t, t_size, b, n);
    // constraint check
    if (current_index + 1 < n && partial_sum - p[current_index] + p[current_index + 1] <= desired_sum)
    {
      // Exclude previous added current_indexm and consider next candidate
      subset_sum(p, t, n, t_size - 1, partial_sum - p[current_index], current_index + 1, desired_sum, b);
    }
    return;
  }
  else
  {
    // constraint check
    if (current_index < n && partial_sum + p[current_index] <= desired_sum)
    {
      // generate nodes along the breadth
      for (int i = current_index; i < n; i++)
      {
        t[t_size] = p[i];
        if (partial_sum + p[i] <= desired_sum)
        {
          // consider next level node (along depth)
          subset_sum(p, t, n, t_size + 1, partial_sum + p[i], i + 1, desired_sum, b);
        }
      }
    }
  }
}

// Wrapper that prints subsets that sum to desired_sum
void generateSubsets(integer_t *p, int size, int desired_sum, integer_t *b)
{
  integer_t *tuplet_vector = (integer_t *)malloc(size * sizeof(integer_t));

  int total = 0;

  for (int i = 0; i < size; i++)
  {
    total += p[i];
  }

  if (p[0] <= desired_sum && total >= desired_sum)
  {
    subset_sum(p, tuplet_vector, size, 0, 0, 0, desired_sum, b);
  }
  free(tuplet_vector);
}

int main(void)
{
  fprintf(stderr, "Program configuration:\n");
  fprintf(stderr, "  min_n ....... %d\n", min_n);
  fprintf(stderr, "  max_n ....... %d\n", max_n);
  fprintf(stderr, "  n_sums ...... %d\n", n_sums);
  fprintf(stderr, "  n_problems .. %d\n", n_problems);
  fprintf(stderr, "  integer_t ... %d bits\n", 8 * (int)sizeof(integer_t));
  //

  for (int i = 0; i < n_problems; i++)
  {
    int n = all_subset_sum_problems[i].n;
    integer_t p[n]; // the weights
    integer_t b[n];
    int k = 0;
    for (int k = 0; k < n; k++)
    {
      p[k] = all_subset_sum_problems[i].p[k];
    }

    if (n > 20)
    {
      continue;
    }

    printf("\n-------------------- Array to work: %d -------------------\n", n);
    for (int j = 0; j < n_sums; j++)
    {
      integer_t desired_sum = all_subset_sum_problems[i].sums[j]; // the desired sum
      printf("\n desired_sum %llu", desired_sum);
      generateSubsets(p, n, desired_sum, b); // encontrar uma forma de depois mudar o weigths para o ponterio p que aponta para os mesmos valores ou fazer uma função aparte que cria um array com esses valores
    }
  }
  return 0;
}