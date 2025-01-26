#ifndef _NUMERIC_HPP
#define _NUMERIC_HPP

namespace ani{
    template <typename InputIt, typename T>
    T accumulate(InputIt first, InputIt last, T init_val){
        for(; first != last; ++first)
            init_val += *first;
        return init_val;
    }

    template <typename InputIt, typename T, typename BinaryOps>
    T accumulate(InputIt first, InputIt last, T init_val, BinaryOps ops){
        for(; first != last; ++first)
            init_val = ops(init_val, *first);
        return init_val;
    }
}

#endif // _NUMERIC_HPP