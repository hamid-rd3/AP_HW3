#include "bst.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (false) // make false to run unit-tests
    {
    //    std::function <int(int)> f= [] (int x){return x%2;};
    //     std::cout<<f(51)<<std::endl;
    //     BST::Node* node =new BST::Node {5,nullptr,nullptr}; 
    //   BST bst{};
    // bst.add_node(10);
    // bst.add_node(20);
    
    // bst.add_node(5);
    // std::cout << bst.add_node(21)<<std::endl;
    std::cout<<std::left<<std::setw(17)<<1234567890<<std::setw(16)<<"=> value:"<<12<<std::setw(13)<<"left:"<<1234567890<<std::setw(12)<<"right:"<<1234567890<<std::endl;

    } else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret { RUN_ALL_TESTS() };
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}