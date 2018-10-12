
#include <gtest/gtest.h>

#include "../Header/mcs.hpp"

using GraphColoring::Mcs;

TEST(McsTests, McsK5ColorTest) {
    vector<string> node_k1 = { "k2", "k3", "k4", "k5" };
    vector<string> node_k2 = { "k1", "k3", "k4", "k5" };
    vector<string> node_k3 = { "k1", "k2", "k4", "k5" };
    vector<string> node_k4 = { "k1", "k2", "k3", "k5" };
    vector<string> node_k5 = { "k1", "k2", "k3", "k4" };
    map<string,vector<string>> k5 = {{"k1", node_k1}, {"k2", node_k2}, {"k3", node_k3}, {"k4", node_k4}, {"k5", node_k5 }};
    
    Mcs* mcs = new Mcs(k5);
    map<string,int> resultant = mcs->color();
    EXPECT_EQ(mcs->get_num_colors(),5);
    delete mcs;
}
