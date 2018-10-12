
#include <gtest/gtest.h>

#include "../Header/tabucol.hpp"

using GraphColoring::Tabucol;

TEST(TabucolTests, TabucolK5ColorTest) {
    vector<string> node_k1 = { "k2", "k3", "k4", "k5" };
    vector<string> node_k2 = { "k1", "k3", "k4", "k5" };
    vector<string> node_k3 = { "k1", "k2", "k4", "k5" };
    vector<string> node_k4 = { "k1", "k2", "k3", "k5" };
    vector<string> node_k5 = { "k1", "k2", "k3", "k4" };
    map<string,vector<string>> k5 = {{"k1", node_k1}, {"k2", node_k2}, {"k3", node_k3}, {"k4", node_k4}, {"k5", node_k5 }};
    
    Tabucol* tabucol = new Tabucol(k5,5);
    map<string,int> resultant = tabucol->color();
    EXPECT_EQ(tabucol->get_num_colors(),5);
    delete tabucol;
}

TEST(TabucolTests, TabucolK33ColorTest) {
    vector<string> side_a = { "k4", "k5", "k6" };
    vector<string> side_b = { "k1", "k2", "k3" };
    map<string,vector<string>> k33 = { {"k1", side_a}, {"k2", side_a}, {"k3", side_a}, {"k4", side_b}, {"k5", side_b}, {"k6", side_b} };
    
    Tabucol* tabucol = new Tabucol(k33,2);
    map<string,int> resultant = tabucol->color();
    EXPECT_EQ(tabucol->get_num_colors(),2);
    delete tabucol;
}

TEST(TabucolTests, TabucolEmptyGraphTest) {
    map<string,vector<string>> empty = map<string,vector<string>>();

    Tabucol* tabucol = new Tabucol(empty,INT_MAX);
    map<string,int> resultant = tabucol->color();
    EXPECT_EQ(resultant.size(), empty.size());
    delete tabucol;
}
