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

#include <stdio.h>
#include <stdlib.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE

int brute_force(int n, integer_t *p, integer_t desired_sum, int current_index, integer_t partial_sum, integer_t *b)
{
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

int brute_force_2(int n, integer_t *p, integer_t desiredSum, int current_index, integer_t partialSum,  integer_t mask, integer_t *b)
{
    //soma já excede -> stop the COUNT
    if (partialSum > desiredSum)
        return 0;

    //obter a soma
    if (partialSum == desiredSum)
    {
        *b = mask;
        return 1;
    }

    //chegar ao ultimo index (neste caso o 1º (0))
    if (current_index < 0)
        return 0;

    if (brute_force_2(n, p, current_index - 1, partialSum + p[current_index], desiredSum, (mask | (1 << (current_index))), b))
        return 1;

    else
        return brute_force_2(n, p, current_index - 1, partialSum, desiredSum, mask, b);
}
void showbits2(integer_t x, int total_bits)
{
    for (int i = 0; i <= total_bits - 1; i++)
    {
        putchar(x & (1u << i) ? '1' : '0');
    }
}
//
// main program
//

int main(void)
{
  freopen("brute_force.txt","w",stdout);

  for (int i = 0; i < n_problems; i++)
  {
    double somaTempos = 0;
    double tempoMaximo = 0;
    int n = all_subset_sum_problems[i].n;
    integer_t *p = malloc(n*sizeof(integer_t)); // the weights
    // integer_t *b = calloc(n,sizeof(integer_t));  // bit's array
    integer_t b = 0;
    for (int k = 0; k < n; k++)
    {
      p[k] = all_subset_sum_problems[i].p[k];
    }

    printf("\n-------------------- Array to work: %d -------------------\n", n);
    for (int j = 0; j < n_sums; j++)
    {
      double time = cpu_time();
      integer_t desired_sum = all_subset_sum_problems[i].sums[j]; // the desired sum
      // printf("\n desired_sum %llu", desired_sum);
      // brute_force(n, p, desired_sum, 0, 0, b);
      if(brute_force_2(n, p, desired_sum, 0, n-1, 0, &b)){  
        showbits2(b, n);
        printf("\n");
      }
      else
      {
        printf("\nSoluçao NÃO encontrada!\n");
      }

      // printf(" bits: ");
      // for (int i = 0; i < n; i++)
      // {
      //   printf("%lld", b[i]);
      // }
      // printf("\n");
      time = cpu_time() - time;
      somaTempos += time;
      if (time > tempoMaximo)
          tempoMaximo = time;
      
    }
    double tempoMedio = somaTempos / n_sums;
    printf("%d %f %f\n", i + 10, tempoMedio, tempoMaximo);
    // free(b); 
    free(p);
  }
  return 0;
}
