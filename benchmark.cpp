#include "algorithms/bfs.hpp"
#include "algorithms/dfs.hpp"
#include "utils/timing.hpp"
// #include "utils/correctness.hpp"
#include <stdio.h>
#include <assert.h>
#include <utility> // pairs

// use file scanf (fscanf) to read input
/**
 * @brief
 * Reads a single graph adjacency list from a file in the following format
 * n m
 * a_1 b_1
 * ...
 * a_m b_m
 * Where n is the number of vertices and m is the number of edges
 * Limits: 1 <= n < 1e6
 *         m >= 1
 *         0 <= a_i, b_i < n
 * Returns the number of edges also, for performance reasons (avoid calculating it)
 * @param input_file
 * @return const std::pair<std::vector<std::vector<int>>, long long>
 */
const std::pair< std::vector<std::vector<int>>, long long>
readGraphFromFile(FILE* input_file,
                const bool directed = false
                )
{  
    int n; long long m;
    // m < n^2 < 1e12
    fscanf(input_file, "%6d%18lld", &n, &m);
    assert(n > 0 && n < 1e6 && m > 0);
    
    std::vector<std::vector<int>> adjacency_list(n);
    int a, b;
    for (int i = 0; i < m; i++){
        fscanf(input_file, "%6d%6d", &a, &b);
        assert(a >= 0 && a < n);
        assert(b >= 0 && b < n);
        adjacency_list[a].push_back(b);
        if (not directed)
        {
            adjacency_list[b].push_back(a);
        }
    }
    return make_pair(adjacency_list, m);
}

long double
benchmarkGraphAlgorithm(std::vector<std::vector<int>>& adjacency_list,
                        std::vector<bool> (*graph_algorithm)
                            (
                            std::vector<std::vector<int>> *,
                            int
                            )
                        )
{
    long double total = 0.0;

    const int n = (int)adjacency_list.size();
    long double times[n];
    for (int i = 0; i < n; i++)
    {
        times[i] = time_function(graph_algorithm, &adjacency_list, i);
        total += times[i];
    }
    return total/(long double)n;
}

int main(int argc, char* argv[]){
    assert(argc > 1);
    FILE* input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("File '%s' does not exist.\nProvide another file.\n", argv[1]);
        return -1;
    }
    else 
    {
        // read directed graph
        auto [adjacency_list, m] = readGraphFromFile(input_file, true);
        int n = (int)adjacency_list.size();
        
        printf("Graph size: %d vertices, %lld edges\n", n, m);

        for (int i = 0; i < n; i++)
        {
            std::vector<bool> result_rec_dfs = recursiveDfs(&adjacency_list, i),
                              result_iter_dfs = stackBasedDFS(&adjacency_list, i),
                              result_bfs = bfs(&adjacency_list, i);
            bool match_i1 = (result_rec_dfs == result_iter_dfs);
            bool match_i2 = (result_iter_dfs == result_bfs);
            bool match_i3 = (result_bfs == result_rec_dfs);
            if (not match_i1)
            {
                printf("The recursive dfs and the iterative dfs did not match in the %d-th iteration\n", i);
                return -1;
            }
            if (not match_i2)
            {
                printf("The iterative dfs and the bfs did not match in the %d-th iteration\n", i);
                return -1;
            }
            if(not match_i3)
            {
                printf("The recursive dfs and the bfs did not match in the %d-th iteration\n", i);
                return -1;
            }
        }
        printf("All results matched\n");
 
        // recursive dfs
        printf("Recursive dfs: %.10Lf milisseconds\n", 1000 * benchmarkGraphAlgorithm(adjacency_list, recursiveDfs));

        // stack based / iterative dfs
        printf("Iterative dfs: %.10Lf milisseconds\n", 1000*benchmarkGraphAlgorithm(adjacency_list, stackBasedDFS));

        // bfs
        printf("BFS: %.10Lf milisseconds\n", 1000*benchmarkGraphAlgorithm(adjacency_list, bfs));
    }

    fclose(input_file); // TODO review closing files
}