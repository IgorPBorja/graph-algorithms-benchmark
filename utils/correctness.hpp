#include <vector>
#include <initializer_list>

template <typename T, typename ...Args>
std::pair<bool, std::vector<T>>
matchFunctionOutputs(T (*), 
                    Args... input_args)//, Args... input_args)
{   
    std::vector<T> results;
    bool matching = true;
    for (const auto f: functions)
    {
        results.push_back(f(input_args...));
    }
    for (int i = 0; i < (int)results.size() - 1; i++)
    {
        matching = matching && (results[i] == results[i + 1]);
    }
    return std::make_pair(matching, results);
}