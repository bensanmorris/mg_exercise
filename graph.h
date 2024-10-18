#pragma once

#include <vector>

namespace mg
{
    struct Vertex
    {
        std::size_t id;
        Vertex(std::size_t id_) : id(id_)
        {}
    };

    struct Vertices
    {
        std::vector<Vertex> data;
    };

    struct Edge
    {
        std::size_t from;
        std::size_t to;

        Edge(std::size_t from_, std::size_t to_) : from(from_), to(to_)
        {}
    };

    struct Edges
    {
        std::vector<Edge> data;
    };

    struct Graph
    {
        Vertices vertices;
        Edges    edges;

        Vertex CreateVertex()
        {
            return vertices.data.emplace_back(vertices.data.size());
        }

        Edge CreateEdge(Vertex a, Vertex b)
        {
            return edges.data.emplace_back(Edge{a.id,b.id});
        }
    };
}
