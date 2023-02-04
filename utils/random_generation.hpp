#include <vector>
#include <random>
#include <time.h>
#include <assert.h>
#include <set>
#include <unordered_set>

long double get_seed()
{
    return (long double)(clock());
}

typedef std::mt19937 rng_type;
rng_type rng;
rng_type::result_type const s = get_seed();


int randint(int a, int b)
{
    assert(a <= b);
    std::uniform_int_distribution<rng_type::result_type> uniform_dist(a, b);
    return (int)(uniform_dist(rng));
}

long long randint(long long a, long long b)
{
    assert(a <= b);
    std::uniform_int_distribution<rng_type::result_type> uniform_dist(a, b);
    return (long long)(uniform_dist(rng));
}

/**
 * @brief
 * Chooses pseudo-random subset of k elements from the collection of values from the address
 * pointed by first to the address pointed by last - 1 (inclusive).
 * NOTE:
 * This will not choose duplicates, so in a collection with duplicates
 * the behavior is unknown (UNDEFINED BEHAVIOR), since it might generate
 * less than k elements, even if there are k or more distinct elements.
 * @tparam T: type of the elements
 * @tparam BiDirIterator: type of iterator.
 * Has to be bidirectional (support both forward and backwards movement).
 * Example: std::vector::begin() and its shifts
 * @param first
 * Iterator pointing to the start of the collection
 * @param last
 * Iterator pointing PAST the end of the collection
 * (to the memory address after the last element)
 * @param k
 * Sample size
 * @param ordered
 * If true: return std::set (the chosen subset is ordered), assuming existence of <
 * operator between type T elements.
 * If false: return std::unordered_set (the elements appears in the order
 * they were chosen).
 * Defaults to false.
 * @return std::set<T>
 * Ordered set of chosen values
 *
 */
template <typename BiDirIterator>
auto sample(BiDirIterator first, BiDirIterator last, int k, bool ordered = false)
{
    int n = last - first; // size
    assert(n >= k);

    typedef typename std::iterator_traits<BiDirIterator>::value_type T;
    if (not ordered)
    {
        std::unordered_set<T> sampled_values;
        for (int i = n - k; i < n; i++)
        {
            std::uniform_int_distribution<rng_type::result_type> udist(0, i - 1);
            int val = udist(rng);
            if (!std::get<bool>(sampled_values.insert(*(first + val))))
            {
                // already present
                // but the i-th element is not
                // since all values added to that point were in positions <= i - 1
                sampled_values.insert(*(first + i));
            }
        }
        return sampled_values;
    }
    else 
    {
        std::unordered_set<T> sampled_values;
        for (int i = n - k; i < n; i++)
        {
            std::uniform_int_distribution<rng_type::result_type> udist(0, i - 1);
            int val = udist(rng);
            if (!std::get<bool>(sampled_values.insert(*(first + val))))
            {
                // already present
                // but the i-th element is not
                // since all values added to that point were in positions <= i - 1
                sampled_values.insert(*(first + i));
            }
        }
        return sampled_values;
    }
}
