#include "bst.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (true) // make false to run unit-tests
    {
        BST bst {};
        BST bs3 { std::move(bst) };
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(53);
        bst.add_node(15);
        bst.add_node(7);
        bst.add_node(8);
        bst.add_node(9);
        BST bst2 { std::move(bst) };
        
        // //  delete[] bst.get_root();
        // // nodes.clear();
        std::cout <<**bst2.find_successor(10)<< std::endl;
         std::cout << bst2 << std::endl;
        //  std::cout<<bst2<<std::endl;

        // EXPECT_TRUE(bst.delete_node(53)); // leaf node
        //  std::cout<<**(bst2.find_node(25))<<std::endl;
        // EXPECT_EQ(bst.length(), 7);
        // EXPECT_EQ(bst.get_root()->right->right, nullptr);
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