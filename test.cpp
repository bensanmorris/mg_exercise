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
