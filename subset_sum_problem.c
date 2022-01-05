//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// 101099 Victor Melo  100480 Airton
//

#if __STDC_VERSION__ < 199901L
#error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
#define STUDENT_H_FILE "000000.h"
#endif

//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE

int brute_force(int n, integer_t *p, integer_t desired_sum, int current_index, integer_t partial_sum, integer_t *b)
{

  // int remaining_sum = (desired_sum - partial_sum);
  // if( (partial_sum > desired_sum) || (partial_sum + remaining_sum < desired_sum) ){
  //    for(int i = current_index; i < n; i++){
  //     b[i]=0;
  //   } //zerando todos os outros bits do seguinte ao ultimos
  //   return 1;
  // }
  if (desired_sum == partial_sum)
  {
    for (int i = current_index; i < n; i++)
    {
      b[i] = 0;
    }
    return 1;
  }

  if (current_index == n)
  {
    return 0;
  }
  // Nao usar o proximo elemento.(rejeitar o elemento na posicao current_index)
  b[current_index] = 0;
  int sol_found = brute_force(n, p, desired_sum, current_index + 1, partial_sum, b);
  if (sol_found == 1)
  {
    return 1;
  }
  // Usar o prox elemento
  b[current_index] = 1;
  return brute_force(n, p, desired_sum, current_index + 1, partial_sum + p[current_index], b);
}

// int improved(integer_t*arr, integer_t val){
//   //do the same thing that was done in python
// }

//  Meet in the middle  //

// basicamente temos:
// i = 0;
// j = array_length;
// array[7]={1,3,4,5,6,7}
// table de exemplo :
// i   |   j  | soma (a[i] + b[j])
// -------------------------------
// 0   |   3  | 16
// 0   |   3  | 9
// 1   |   2  | 10
// 2   |   2  | 12
// 3   |   2  | 13
// 4   |   1  | 14
// 5   |   0  | 15

// tarefas
// 1 - subdividir o array  dado, criando 2 arrays
// 2 - para 1 array, fazer todas as possiveis somas de seus elementos (fazer 2 vezes)
// 3 - ordenar(sort) (fazer 2 vezes)
// 4 - procurar a solucao, o que fazer se nao encontrar a soma?
// 5 - resposta em array binario

//
// main program
//

int main(void)
{
  fprintf(stderr, "Program configuration:\n");
  fprintf(stderr, "  min_n ....... %d\n", min_n);
  fprintf(stderr, "  max_n ....... %d\n", max_n);
  fprintf(stderr, "  n_sums ...... %d\n", n_sums);
  fprintf(stderr, "  n_problems .. %d\n", n_problems);
  fprintf(stderr, "  integer_t ... %d bits\n", 8 * (int)sizeof(integer_t));

  printf("\n\t --- BRUTE FORCE IMPLEMENTATION --- \t\n");

  for (int i = 0; i < n_problems; i++)
  {
    int n = all_subset_sum_problems[i].n;
    integer_t p[n]; // the weights
    integer_t b[n]; // bit's array
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
      brute_force(n, p, desired_sum, 0, 0, b);

      printf(" bits: ");
      for (int i = 0; i < n; i++)
      {
        printf("%lld", b[i]);
      }
      printf("\n");
    }
  }
  return 0;
}

//  Para Compilar:
//
//  gcc subset_sum_problem.c -Wall -o subset_sum_problem
//  ./subset_sum_problem
//