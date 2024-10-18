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

    // invalid vertex tests
    // todo
}

TEST(GraphTest, LabelTests)
{
    Graph g;
    auto v = g.CreateVertex();
    EXPECT_EQ(g.vertices.data.size(),1);
    EXPECT_EQ(v.id,0);
    auto l = g.AddLabel(v,"Hi");
    EXPECT_EQ(g.labels.data.size(),1);
    EXPECT_EQ(l.vertex,v.id);
    EXPECT_EQ(l.data,"Hi");

    g.RemoveLabel(l);
    ASSERT_EQ(g.labels.data.size(),0);
}

TEST(GraphTest, ShortestPath)
{
    // Graph:
    //   A -> B
    //   A -> C
    //   B -> C
    //   C -> D
    //   B -> D
    // Labels:
    //   A -> "x"
    //   B -> "y"
    //   C -> "x"
    //   D -> "x"
    // Test:
    //   ShortestPath(A,D,"x")
    // Result:
    //   A(0) -> C(2) -> D(3)

    Graph g;

    auto A = g.CreateVertex(); // 0
    auto B = g.CreateVertex(); // 1
    auto C = g.CreateVertex(); // 2
    auto D = g.CreateVertex(); // 3

    g.CreateEdge(A,B);
    g.CreateEdge(A,C);
    g.CreateEdge(B,C);
    g.CreateEdge(C,D);
    g.CreateEdge(B,D);

    g.AddLabel(A, "x");
    g.AddLabel(B, "y");
    g.AddLabel(C, "x");
    g.AddLabel(D, "x");

    auto adj = g.GetAdjacencies(A);
    EXPECT_EQ(adj.data.size(), 2);
    EXPECT_EQ(adj.data[0].id, B.id);
    EXPECT_EQ(adj.data[1].id, C.id);

    // Result:
    //   A(0) -> C(2) -> D(3)
    auto path = g.ShortestPath(A, D, "x");
    EXPECT_EQ(path.data.size(), 3);
    EXPECT_EQ(path.data[0], 0);
    EXPECT_EQ(path.data[1], 2);
    EXPECT_EQ(path.data[2], 3);
}
