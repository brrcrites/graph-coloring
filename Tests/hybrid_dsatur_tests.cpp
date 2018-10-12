
#include <gtest/gtest.h>

#include "../Header/hybrid_dsatur.hpp"

using GraphColoring::HybridDsatur;

TEST(HybridDsaturTests, HybridDsaturK5ColorTest) {
    vector<string> node_k1 = { "k2", "k3", "k4", "k5" };
    vector<string> node_k2 = { "k1", "k3", "k4", "k5" };
    vector<string> node_k3 = { "k1", "k2", "k4", "k5" };
    vector<string> node_k4 = { "k1", "k2", "k3", "k5" };
    vector<string> node_k5 = { "k1", "k2", "k3", "k4" };
    map<string,vector<string>> k5 = {{"k1", node_k1}, {"k2", node_k2}, {"k3", node_k3}, {"k4", node_k4}, {"k5", node_k5 }};
    
    HybridDsatur* hybrid_dsatur = new HybridDsatur(k5);
    map<string,int> resultant = hybrid_dsatur->color();
    EXPECT_EQ(hybrid_dsatur->get_num_colors(),5);
    delete hybrid_dsatur;
}

TEST(HybridDsaturTests, HybridDsaturK33ColorTest) {
    vector<string> side_a = { "k4", "k5", "k6" };
    vector<string> side_b = { "k1", "k2", "k3" };
    map<string,vector<string>> k33 = { {"k1", side_a}, {"k2", side_a}, {"k3", side_a}, {"k4", side_b}, {"k5", side_b}, {"k6", side_b} };
    
    HybridDsatur* hybrid_dsatur = new HybridDsatur(k33);
    map<string,int> resultant = hybrid_dsatur->color();
    EXPECT_EQ(hybrid_dsatur->get_num_colors(),2);
    delete hybrid_dsatur;
}
