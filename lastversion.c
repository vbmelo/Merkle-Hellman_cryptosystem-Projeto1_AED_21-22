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
#define STUDENT_H_FILE "101099.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE
#include <math.h>

#define ARRAYSIZE(a) (sizeof(a)) / (sizeof(a[0]))
#include <string.h>
#include <math.h>

int count;

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

// Sort the array in ascending order
void sort(integer_t *arr, int length)
{
    integer_t temp = 0;

    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

/// ALL SUMS OF AN ARRAY
void subsetSums(integer_t *arr, int l, int r, integer_t sum, int allsums, integer_t *array)
{
    // Print current subset
    if (l > r)
    {
        // printf("%d \n", count);
        array[count] = sum;
        count++;
        return;
    }

    // Subset including arr[l]

    subsetSums(arr, l + 1, r, sum + arr[l], allsums, array);

    // Subset excluding arr[l]
    subsetSums(arr, l + 1, r, sum, allsums, array);
}

void m(integer_t *subsets1, integer_t *subsets2, int sub1size, int sub2size, integer_t desiredsum, integer_t total, int setarraysize, integer_t *set, integer_t *set2, integer_t *b, integer_t *b1, integer_t *b2)
{
    // printf(" \nDesired sum: %lld ", desiredsum);
    if (desiredsum > total)
    {
        printf(" \n No soluction max desired sum");
        exit(1);
    }
    else
    {
        int test = 0;
        int j = sub1size - 1;
        int i = 0;
        while (test == 0)
        {

            if (subsets1[i] + subsets2[j] == desiredsum)
            {
                // printf("\n The soluction {%lld,%lld}", subsets1[i], subsets2[j]);
                if (subsets1[i] != 0)
                {
                    brute_force(setarraysize, set, subsets1[i], 0, 0, b1);
                }
                if (subsets2[j] != 0)
                {
                    brute_force(setarraysize, set2, subsets2[j], 0, 0, b2);
                }

                memcpy(b, b1, setarraysize * sizeof(integer_t)); // copy final_arraysize integer_t's from b1 to b[0]...total[setarraysize]
                memcpy(b + setarraysize, b2, setarraysize * sizeof(integer_t));

                // return b;

                test = 1; // stop the while loop
            }

            if (subsets1[i] + subsets2[j] < desiredsum)
            {
                i++;
            }

            if (subsets1[i] + subsets2[j] > desiredsum)
            {
                j--;
            }

            if (i > sub1size || j < 0)
            {
                printf("\nNO soluction ");
                test = 1;
            }
        }
    }
}

/*program to test printPowerSet*/
int main()
{

    freopen("meet_in_the_middle.txt", "w", stdout);

    // fprintf(stderr, "Program configuration:\n");
    // fprintf(stderr, "  min_n ....... %d\n", min_n);
    // fprintf(stderr, "  max_n ....... %d\n", max_n);
    // fprintf(stderr, "  n_sums ...... %d\n", n_sums);
    // fprintf(stderr, "  n_problems .. %d\n", n_problems);
    // fprintf(stderr, "  integer_t ... %d bits\n", 8 * (int)sizeof(integer_t));

    // printf("\n\t --- MEET IN THE MIDDLE IMPLEMENTATION --- \t\n");

    // set -> sera o array p dado pelo prof do indice 0 ao length(p)/2
    // set2 -> array p do indice lenght(p)/2 ao length(p)

    for (int i = 0; i < n_problems; i++)
    {
        int n = all_subset_sum_problems[i].n;
        int setarraysize = (n / 2) + 1;     // +1 to fix bug
        int allsums = pow(2, setarraysize); // todas as somas possiveis = tamanho do arrayofallsumsSet1
        int final_arraysize = 2 * setarraysize;
        integer_t set[setarraysize];  // the weights from 0 to length(p)/2
        integer_t set2[setarraysize]; // weights from length(p)/2 to length(p)

        for (int k = 0, j = setarraysize; k < setarraysize; k++, j++)
        {
            set[k] = all_subset_sum_problems[i].p[k];
            set2[k] = all_subset_sum_problems[i].p[j];
        }

        // Array com todas as somas possiveis
        integer_t arrayofallsumsSet1[allsums];
        integer_t arrayofallsumsSet2[allsums];

        // find all sums
        subsetSums(set, 0, setarraysize - 1, 0, allsums, arrayofallsumsSet1);
        count = 0; // make count equal to 0 to avoid bug
        subsetSums(set2, 0, setarraysize - 1, 0, allsums, arrayofallsumsSet2);
        count = 0;
        // sort the arrays
        sort(arrayofallsumsSet1, allsums);
        sort(arrayofallsumsSet2, allsums);

        integer_t maxsum = 0;
        for (int i = 0; i < setarraysize; i++)
        {
            maxsum += set[i];
            maxsum += set2[i];
        }
        double somaTempos = 0;
        double tempoMaximo = 0;

        // printf("\n-------------------- Array to work: %d i: %d -------------------\n", n, i);

        for (int j = 0; j < n_sums; j++)
        {

            double time = cpu_time();

            integer_t desiredsum = all_subset_sum_problems[i].sums[j]; // the desired sum

            integer_t *b = malloc(final_arraysize * sizeof(integer_t));
            integer_t *b1 = calloc(setarraysize, sizeof(integer_t));
            integer_t *b2 = calloc(setarraysize, sizeof(integer_t));

            // m(arrayofallsumsSet1, arrayofallsumsSet2, allsums, allsums, desired_sum, maxsum, b);
            m(arrayofallsumsSet1, arrayofallsumsSet2, allsums, allsums, desiredsum, maxsum, setarraysize, set, set2, b, b1, b2);

            int fixbit;
            if (i % 2 == 0)
            {
                fixbit = 2;
            }
            else
            {
                fixbit = 1;
            }

            // printf(" bits: ");
            for (int i = 0; i < (setarraysize * 2) - fixbit; i++) // -fixbits to dont count the last  bits elements that is trash
            {
                // printf("%lld", b[i]);
                printf("%lld", b[i]);
            }

            printf("\n");
            time = cpu_time() - time;
            somaTempos += time;
            if (time > tempoMaximo)
                tempoMaximo = time;

            free(b);
            free(b1);
            free(b2);
        }
    }
    // fim do main
    return 0;
}
