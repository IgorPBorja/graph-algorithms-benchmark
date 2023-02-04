#include <vector>
#include <stack>

void __recursiveDfs(
                    std::vector<std::vector<int>>* adjacency_list,
                    int source, 
                    std::vector<bool>& visited_nodes
                    )
{
    for (int u: (*adjacency_list)[source])
    {
        if (not visited_nodes[u])
        {
            visited_nodes[u] = true;
            __recursiveDfs(adjacency_list, u, visited_nodes);
        }
    }
}

std::vector<bool> recursiveDfs(
                                std::vector<std::vector<int>>* adjacency_list,
                                int source
                            ) 
{
    int total_nodes = (int)(adjacency_list->size());
    std::vector<bool> visited_nodes(total_nodes);
    visited_nodes.assign(total_nodes, false);
    visited_nodes[source] = true;
    __recursiveDfs(adjacency_list, source, visited_nodes);

    return visited_nodes;
}

std::vector<bool> stackBasedDFS(
                                std::vector<std::vector<int>>* adjacency_list,
                                int source
                                )
{
    int total_nodes = (int)adjacency_list->size();
    std::vector<bool> visited_nodes(total_nodes);
    visited_nodes.assign(total_nodes, false);
    // source starts as unvisited in order to make the if statment work

    std::stack<int> S;
    S.push(source);
    while (not S.empty())
    {
        int u = S.top();
        S.pop();
        if (not visited_nodes[u])
        {
            visited_nodes[u] = true;
            for (int v : (*adjacency_list)[u])
            {
                if (not visited_nodes[v])
                {
                    S.push(v);
                }
            }
        }
    }
    return visited_nodes;
}