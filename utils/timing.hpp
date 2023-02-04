#include <time.h>
#include <exception>

/**
 * @brief 
 * Measures the time it takes to execute a function with a certain set
 * of arguments.
 * Achieves generality through the use of variadic templates.
 * \n
 * If an exception was raised when executing the function,
 * returns -1.0. 
 */
template <typename T, typename ...Args>
long double time_function(T (*f)(Args... f_args), Args... input)
{
    try{
        clock_t init = clock();
        T result = f(input...);
        clock_t end = clock();
        long double time_elapsed = (long double)(end - init)/(long double)CLOCKS_PER_SEC;
        return time_elapsed;
    } catch(const std::exception& e)
    {
        return -1.0;
    }
}