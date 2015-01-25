//
//  main.cpp
//  BinaryTree
//
//  Created by Orn Gunnarsson on 13/10/2014.
//  Copyright (c) 2014 Orn Gunnarsson. All rights reserved.
//

#include <iostream>
#include <memory>

#include "BinaryTree.h"

void findValue( BinaryTree<int> tree, int value )
{
    BinaryTree<int>::NodePtr findValue = tree.find( tree.getRoot(), value );
    if ( findValue )
        std::cout << "Found: " << findValue->getData() << std::endl;
    else
        std::cout << "Value '"<< value << "' not found." << std::endl;
}

int main( int argc, const char * argv[] )
{
    BinaryTree<int> tree;
    
    tree.add( 4 );
    tree.add( 2 );
    tree.add( 7 );
    tree.add( 1 );
    
    std::cout << "## Pre-Order ##" << std::endl;
    tree.printPreOrder();
    
    std::cout << "## In-Order ##" << std::endl;
    tree.printInOrder();
    
    std::cout << "## Post-Order ##" << std::endl;
    tree.printPostOrder();
    
    std::cout << "Tree size = " << tree.size( tree.getRoot() ) << std::endl;
    std::cout << "Tree maxDepth = " << tree.maxDepth( tree.getRoot() ) << std::endl;
    std::cout << "Tree minDepth = " << tree.minDepth( tree.getRoot() ) << std::endl;
    std::cout << "Tree balanced = " << tree.isBalanced() << std::endl;
    std::cout << "Tree max = " << tree.max( tree.getRoot() ) << std::endl;
    std::cout << "Tree min = " << tree.min( tree.getRoot() ) << std::endl;
    
    findValue( tree, 2 );
    findValue( tree, 5 );
    
    std::cout << "Is BST = " << tree.isBST() << std::endl;
    
    return 0;
}
