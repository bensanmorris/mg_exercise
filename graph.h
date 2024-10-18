#pragma once

#include <algorithm>
#include <map>
#include <queue>
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
            // TODO: throw std::invalid_argument() if vertices do not exist
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

        Vertices GetAdjacencies(Vertex v)
        {
            Vertices adj;
            for(auto e : edges.data)
            {
                if(e.from == v.id)
                {
                    adj.data.emplace_back(e.to);
                }
            }
            return adj;
        }

        struct Path
        {
            std::vector<size_t> data;
        };
        Path ShortestPath(Vertex a, Vertex b, std::string l)
        {
            // ref: https://github.com/GenoWong/IntroductionToAlgorithms/blob/main/Introduction.to.Algorithms.4th.pdf
            // Based on recipe in chapter 22.3

            std::queue<Vertex> q;
            q.push(a);

            std::multimap<size_t, size_t> predecessors;
            bool finished = false;
            while(!q.empty())
            {
                auto top = q.front();
                q.pop();
                auto adj = GetAdjacencies(top);
                for(auto adjacency : adj.data)
                {
                    if(labels.data[adjacency.id].data == l)
                    {
                        predecessors.insert({adjacency.id,top.id});
                        q.push(adjacency);
                    }
                    if(adjacency.id == b.id)
                    {
                        predecessors.insert({b.id,adjacency.id});
                        finished = true;
                    }
                }
                if(finished)
                {
                    break;
                }
            }

            Path path;
            auto predecessor = b.id;
            path.data.emplace_back(predecessor);
            while(true)
            {
                auto nextPredecessor = predecessors.find(predecessor);
                if(nextPredecessor == predecessors.end())
                {
                    break;
                }
                else
                {
                    // nb. potentially there will be many paths i.e.
                    // many entries in the predecessor map for a given
                    // predecessor. owing to time constraints I will only
                    // process the first
                    path.data.emplace_back(nextPredecessor->second);
                    predecessor = nextPredecessor->second;
                }
            }

            std::reverse(path.data.begin(),path.data.end());
            return path;
        }
    };
}
