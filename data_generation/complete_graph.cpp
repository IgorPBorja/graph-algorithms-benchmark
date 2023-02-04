/**
 * @file complete_graph.cpp
 * @author Igor Prado Teixeira Borja (igorpradoborja@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-03
 */
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <cstdlib> // for std::atoi (string to int)
#include <string> // for std::to_string

int input_validation(int argc, char *argv[], int* n)
{
    assert(argc > 2);
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
    return 0;
}

int main(int argc, char* argv[])
{
    int n;
    FILE *output;
    /**
     * @brief 
     * the file validation has to be inside main
     * otherwise the pointer will be corrupted when switching context
     * (after returning from the auxiliary function)
     */
    try
    {
        output = fopen(argv[1], "w");
        if (output == NULL)
        {
            printf("Could not open file.\n");
            return -1;
        }
    }
    catch (const std::exception &e)
    {
        printf("Invalid file name.\n");
        return -1;
    }

    if (input_validation(argc, argv, &n) == -1)
    {
        printf("Exiting program\n");
        return -1;
    }
    
    /**
     * @brief 
     * At this point it is guaranteed 0 < n < 1e6 (n has at most five digits)
     * Since the number of edges is m = n(n-1) < n^2 < 1e12, it has at most 12 digits
     * So 5 (n) + 1 (whitespace) + 12 (m) + 1 (\n) + 1 (null termination) = 20 is enough
     * For safety, we use 50.
     */
    char initial_info[50];
    long long m = (long long)n * (long long)(n-1);
    snprintf(initial_info, 50, "%d %lld\n", n, m);
    fprintf(output, "%s", initial_info);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                char edge[50];
                snprintf(edge, 50, "%d %d\n", i, j);
                fprintf(output, "%s", edge);
            }
        }
    }
    fclose(output);
}