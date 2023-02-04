#include <vector>
#include <queue>

std::vector<bool> bfs(
                        std::vector<std::vector<int>>* adjacency_list,
                        int source
                    )
{
    int total_nodes = (int)adjacency_list->size();
    std::vector<bool> visited_nodes(total_nodes);
    visited_nodes.assign(total_nodes, false);
    visited_nodes[source] = true;
    
    std::queue<int> Q;
    Q.push(source);
    while (not Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (int v: (*adjacency_list)[u])
        {
            if (not visited_nodes[v])
            {
                visited_nodes[v] = true;
                Q.push(v);
            }
        }
    }
    return visited_nodes;
}