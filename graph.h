#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <unordered_map>

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

    struct Label
    {
        std::size_t vertex;
        std::string data;
    };

    struct Labels
    {
        std::unordered_map<std::size_t,Label> data;
    };

    struct Graph
    {
        Vertices vertices;
        Edges    edges;
        Labels   labels;

        Vertex CreateVertex()
        {
            return vertices.data.emplace_back(vertices.data.size());
        }

        Edge CreateEdge(Vertex a, Vertex b)
        {
            return edges.data.emplace_back(Edge{a.id,b.id});
        }

        Label AddLabel(Vertex v, std::string s)
        {
            Label l{v.id,s};
            labels.data[v.id] = l;
            return l;
        }

        void RemoveLabel(Label l)
        {
            auto found = labels.data.find(l.vertex);
            if(found != labels.data.end())
            {
                labels.data.erase(found);
            }
        }
    };
}
