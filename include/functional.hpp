#ifndef _FUNCTIONAL_HPP
#define _FUNCTIONAL_HPP

namespace ani{
    template <typename T>
    class equal_to{
        public:
            bool operator()(const T& left, const T& right) const { return left == right; }
    };

    template <typename T>
    class not_equal_to{
        public:
            bool operator()(const T& left, const T& right) const { return left != right; }
    };

    template <typename T>
    class less{
        public:
            bool operator()(const T& left, const T& right) const { return left < right; }
    };

    template <typename T>
    class greater{
        public:
            bool operator()(const T& left, const T& right) const { return left > right; }
    };

    template <typename T>
    class less_equal{
        public:
            bool operator()(const T& left, const T& right) const { return left <= right; }
    };

    template <typename T>
    class greater_equal{
        public:
            bool operator()(const T& left, const T& right) const { return left >= right; }
    };
}

#endif // _FUNCTIONAL_HPP