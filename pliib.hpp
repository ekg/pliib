#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <omp.h>
#include <functional>

using namespace std;
/**
 * This function takes a vector v and applies a lambda
 * function L to each of its elements. It returns a vector v'
 * of |v| where v'[i] = L(v[i]). It computes results synchronously
 * (i.e. v'[1] is computed before [v'2].
 *
 */
//template <typename DataType, typename A>
//std::vector<DataType, A> p_vv_map( std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda);

template <typename DataType, typename A>
inline std::vector<DataType, A> p_vv_map(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    std::vector<DataType> results(v.size());
    int i;
    // As we guarantee synchronicity,
    //     // we should TODO something to guarantee it.
    #pragma omp parallel for if (v.size() > 1000)
    for (i = 0; i < v.size(); i++){
        auto r = lambda(v[i]);
        //#pragma omp critical
        results[i] = r;
    }

    return results;
}


/**
 * This function follows the same pattern as above but permits asynchronous
 * computation (i.e. there is not guarantee that v'[1] is computed before v'[2].
 */
template <typename DataType, typename A>
inline std::vector<DataType, A> p_vv_map_async(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    std::vector<DataType, A> results(v.size());
    int i;
    cerr << "Asynchronous map is currently broken" << endl;
    exit(-1);
    for (i = 0; i < v.size(); i++){
        #pragma omp task 
        {results[i] = lambda(v[i]);}
    }
    
    return results;

}


/**
 * This function applies a lambda function L to all elements of
 * vector v, modifying the elements of v in place.
 */
template<typename DataType, typename A>
inline void p_vv_apply(std::vector<DataType, A> &v, typename std::function<DataType(DataType)> lambda){
    #pragma omp parallel for //private(i)
    for (int i = 0; i < v.size(); i++){
        auto r = lambda(v[i]);
        
        #pragma omp atomic write
        v[i] = r;
    }
}


/**
 * Takes a lambda function and applies it across v, then reduces the result
 * to a single <T> value.
 */
template<typename DataType, typename A>
inline DataType p_vv_reduce(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    DataType x;
    return x;
}


/**
 * Applies a bool std::function L across elements in a vector.
 * All elements for which L returns true are return in a new vector.
 */
template<typename DataType, typename A>
std::vector<DataType, A> p_vv_filter(std::vector<DataType, A> v, typename std::function<bool(DataType)> lambda){
    std::vector<DataType, A> results;
    cerr << "p_vv_filter not implemented" << endl;
    exit(-1);
    return results;
}


