/**
 * @file sparse_graph.cpp
 * @author Igor Prado Teixeira Borja (igorpradoborja@gmail.com)
 * @brief Generate graphs where deg(v) < cn for all vertices v, for a 
 * fixed 0 < c < 1. When c << 1, those graphs are very "sparse".
 * @version 0.1
 * @date 2023-02-04
 * 
 * @copyright Copyright (c) 2023
 */

#include "../utils/random_generation.hpp"
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <unordered_set>

int input_validation(int argc, char *argv[], int *n, double *degree_ratio)
{
    assert(argc > 3);
    
    try
    {
        *n = std::atoi(argv[2]);
        assert(*n > 0 && *n < 1e6);
    }
    catch (const std::exception &e)
    {
        printf("Invalid integer: provide integer between 1 and 1e6 (exclusive)\n");
        return -1;
    }

    try
    {
        *degree_ratio = std::atof(argv[3]);
        assert(*degree_ratio > 0.0 && *degree_ratio < 1.0);
    }
    catch (const std::exception &e)
    {
        printf("Invalid degree ratio: provide floating point number between 0 and 1");
        return -1;
    }
    return 0;
}

std::pair<
        std::vector<std::vector<int>>,
        long long
        > 
genSparseGraph(int n, double degree_ratio)
{
    assert(n > 0 && n < 1e6);
    assert(degree_ratio > 0.0 && degree_ratio < 1.0);
    
    std::vector<std::vector<int>> adjacency_list(n);
    int k = std::min((int)(n * degree_ratio), n - 1);

    int indexes[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        indexes[i] = i;
    }

    long long edges = 0;
    for (int i = 0; i < n; i++)
    {
        int deg = randint(0, k);
        edges += (long long)(deg); // the type cast avoids overflow
        // no need to be ordered:
        std::unordered_set<int> adj_i = sample(indexes, indexes + n - 1, deg);
        
        
        // add to adjacency_list, applying shift if necessary to
        // transform [0...n-2] in [0...i-1, i+1, ... n-1]
        for (std::unordered_set<int>::iterator it = adj_i.begin(); it != adj_i.end(); it++)
        {
            if (*it >= i)
            {
                adjacency_list[i].emplace_back((*it) + 1);
            } else 
            {
                adjacency_list[i].emplace_back(*it);
            }
        }
    }
    return std::make_pair(adjacency_list, edges);
}

int main(int argc, char* argv[])
{
    FILE* output;
    int n;
    double degree_ratio;

    if (input_validation(argc, argv, &n, &degree_ratio) == -1)
    {
        printf("Exiting program\n");
        return -1;
    }
    
    output = fopen(argv[1], "w");
    if (output == NULL)
    {
        printf("File not found or invalid. Provide another filename\n");
        printf("Exiting program\n");
        return -1;
    }

    auto [adjacency_list, m] = genSparseGraph(n, degree_ratio);
    /**
     * @brief 
     * since n < 1e6, the number of digits of n is at most 7
     */
    fprintf(output, "%7d %18lld\n", n, m); 

    for (int i = 0; i < n; i++)
    {
        for (int j: adjacency_list[i])
        {
            fprintf(output, "%7d %7d\n", i, j);
        }
    }
    fclose(output);
}

