#ifndef _GRAPH_EXCEPTIONS_HPP
#define _GRAPH_EXCEPTIONS_HPP

#include <stdexcept>

namespace ani{
    class graph_vertex_exists : public std::runtime_error{
        public:
            graph_vertex_exists() : std::runtime_error("Vertex already exists in graph"){ }
    };

    class graph_vertex_invalid : public std::runtime_error{
        public:
            graph_vertex_invalid() : std::runtime_error("Vertex is not present in graph"){ }
    };

    class graph_edge_exists : public std::runtime_error{
        public:
            graph_edge_exists() : std::runtime_error("Edge already exists in graph"){ }
    };

    class graph_edge_invalid : public std::runtime_error{
        public:
            graph_edge_invalid() : std::runtime_error("Edge is not present in graph"){ }
    };

    class graph_corrupted : public std::runtime_error{
        public:
            graph_corrupted() : std::runtime_error("Graph is corrupted"){ }
    };

    class graph_negative_cycle : public std::runtime_error{
        public:
            graph_negative_cycle() : std::runtime_error("Graph contains negative cycle"){ }
    };
}

#endif // _GRAPH_EXCEPTIONS_HPP