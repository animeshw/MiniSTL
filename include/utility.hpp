#ifndef _UTILITY_HPP
#define _UTILITY_HPP

namespace ani{
    template <typename T1, typename T2>
    class pair{
        public:
            T1 first;
            T2 second;

        public:
            pair() : first(), second() { }

            pair(const T1& _t1, const T2& _t2) : first(_t1), second(_t2) { }

            pair(const pair& other) : first(other.first), second(other.second) { }

            pair(pair&& other) : first(std::move(other.first)), second(std::move(other.second)) { }

            pair& operator=(const pair& other){
                first = other.first;
                second = other.second;
                return *this;
            }
    };
    
    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 first, T2 second){
        return pair<T1, T2>(first, second);
    }

    template <typename T1, typename T2, typename U1, typename U2>
    bool operator==(const ani::pair<T1, T2>& lhs, const ani::pair<U1, U2>& rhs){
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

    template <typename T1, typename T2, typename U1, typename U2>
    bool operator!=(const ani::pair<T1, T2>& lhs, const ani::pair<U1, U2>& rhs){
        return !(lhs == rhs);
    }

    template <typename T1, typename T2, typename U1, typename U2>
    bool operator<(const ani::pair<T1, T2>& lhs, const ani::pair<U1, U2>& rhs){
        if (lhs.first < rhs.first)
            return true;
        else if(lhs.first > rhs.first)
            return false;
        return lhs.second < rhs.second;
    }

    template <typename T1, typename T2, typename U1, typename U2>
    bool operator<=(const ani::pair<T1, T2>& lhs, const ani::pair<U1, U2>& rhs){
        return !(rhs < lhs);
    }

    template <typename T1, typename T2, typename U1, typename U2>
    bool operator>(const ani::pair<T1, T2>& lhs, const ani::pair<U1, U2>& rhs){
        return rhs < lhs;
    }

    template <typename T1, typename T2, typename U1, typename U2>
    bool operator>=(const ani::pair<T1, T2>& lhs, const ani::pair<U1, U2>& rhs){
        return !(lhs < rhs);
    }

    template <typename T>
    void swap(T& lhs, T& rhs){
        T tmp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(tmp);
    }
}

#endif // _UTILITY_HPP