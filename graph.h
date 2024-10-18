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

    struct Graph
    {
        Vertices vertices;

        Vertex CreateVertex()
        {
            return vertices.data.emplace_back(vertices.data.size());
        }
    };
}
