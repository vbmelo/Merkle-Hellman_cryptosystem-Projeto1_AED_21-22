//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// Place your student numbers and names here
//

#if __STDC_VERSION__ < 199901L
# error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
# define STUDENT_H_FILE "101099.h"
#endif


//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE


//
// custom data types
//
// the STUDENT_H_FILE defines the following constants and data types
//
//   #define min_n       24                   --- the smallest n value we will handle
//   #define max_n       57                   --- the largest n value we will handle
//   #define n_sums      20                   --- the number of sums for each n value
//   #define n_problems  (max_n - min_n + 1)  --- the number of n values
//
//   typedef unsigned long long integer_t;    ---  64-bit unsigned integer
//   typedef struct
//   {
//     int n;                                 --- number of elements of the set (for a valid problem, min_n <= n <= max_n)
//     integer_t p[max_n];                    --- the elements of the set, already sorted in increasing order (only the first n elements are used)
//     integer_t sums[n_sums];                --- several sums (problem: for each sum find the corresponding subset)
//   }
//   subset_sum_problem_data_t;               --- weights p[] and sums for a given value of n
//
//   subset_sum_problem_data_t all_subset_sum_problems[n_problems]; --- // the problems
//


//
// place your code here
//
// possible function prototype for a recursive brute-force function:
//   int brute_force(int n,integer_t p[n],int desired_sum,int current_index,integer_t partial_sum);
// it sould return 1 when the solution is found and 0 otherwise
// note, however, that you may get a faster function by reducing the number of function arguments (maybe a single pointer to a struct?)
//
// nos da arvore representam a soma parcial e a sequencia binaria que esta associada
// int n -> representa o numero de elementos do array do teste que estamos a fazer
// integer_t p[n] -> array de numeros representados por 64 bits de tamanho n
// int desired_sum -> S desejado
// int current_index -> indice atual
// integer_t -> soma parcial
// integer_t b[] -> array de bits

int brute_force(int n,integer_t*p,integer_t desired_sum,int current_index,integer_t partial_sum, integer_t*b){
  int remaining_sum = (desired_sum - partial_sum);

  if( (partial_sum > desired_sum) || (partial_sum + remaining_sum < desired_sum) ){
     for(int i = current_index; i < n; i++){
      b[i]=0;
    } //zerando todos os outros bits do seguinte ao ultimos
    return 1; 
  }
  if(desired_sum == partial_sum){
    for(int i = current_index; i < n; i++){
      b[i]=0;
    } //zerando todos os outros bits do seguinte ao ultimos
    return 1;
  }
  

  if (current_index == n){
    return 0;
  }
  //Nao usar o proximo elemento.(rejeitar o elemento na posicao current_index)
  b[current_index]=0;
  int sol_found = brute_force(n, p, desired_sum, current_index+1, partial_sum, b);
  if (sol_found==1){return 1;}
  //Usar o prox elemento
  b[current_index]=1;
  return brute_force(n, p, desired_sum, current_index+1, partial_sum+p[current_index], b);
}

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
  fprintf(stderr,"Program configuration:\n");
  fprintf(stderr,"  min_n ....... %d\n",min_n);
  fprintf(stderr,"  max_n ....... %d\n",max_n);
  fprintf(stderr,"  n_sums ...... %d\n",n_sums);
  fprintf(stderr,"  n_problems .. %d\n",n_problems);
  fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
  
  integer_t p[4]={1,2,3,4};
  integer_t b[4];
  printf("  brute_force . %d \n", brute_force(4, p, 5, 0, 0, b));
  for (int i = 0; i < 3; i++){
    printf("  Byte Array > index %d = %llu \n",i,b[i]);
  }
  return 0;
}

//  Para Compilar:
//
//  gcc subset_sum_problem.c -Wall -o subset_sum_problem
//  ./subset_sum_problem
//