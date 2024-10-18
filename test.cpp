#include <gtest/gtest.h>

#include "graph.h"
using namespace mg;

TEST(GraphTest, CreateVertexTest)
{
    Graph g;
    auto v = g.CreateVertex();
    EXPECT_EQ(g.vertices.data.size(),1);
    EXPECT_EQ(v.id,0);
}

TEST(GraphTest, CreateEdgeTest)
{
    Graph g;
    auto vA = g.CreateVertex();
    auto vB = g.CreateVertex();
    EXPECT_EQ(g.vertices.data.size(),2);
    EXPECT_EQ(vA.id,0);
    EXPECT_EQ(vB.id,1);
    auto e = g.CreateEdge(vA,vB);
    EXPECT_EQ(g.edges.data.size(),1);
    EXPECT_EQ(e.from, vA.id);
    EXPECT_EQ(e.to,vB.id);
}
