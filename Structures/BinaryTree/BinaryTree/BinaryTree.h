//
//  BinaryTree.h
//  BinaryTree
//
//  Created by Orn Gunnarsson on 13/10/2014.
//  Copyright (c) 2014 Orn Gunnarsson. All rights reserved.
//

#ifndef BinaryTree_BinaryTree_h
#define BinaryTree_BinaryTree_h

#include <iostream>
#include <memory>
#include <limits>
#include <algorithm>
#include <vector>

template <typename T>
class BinaryNode
{
public:
    BinaryNode() {}

    BinaryNode( const T& data ) : data( data )
    {
        //std::cout << "Construct node with data: " << data << std::endl;
    }
    
    virtual ~BinaryNode()
    {
        //std::cout << "Destruct node with data: " << data << std::endl;
    }
    
    T getData()
    {
        return data;
    }
    
    void printPreOrder() const
    {
        // Node, Left, Right
        
        std::cout << data << std::endl;
        
        if ( left )
        {
            left->printPreOrder();
        }
        
        if ( right )
        {
            right->printPreOrder();
        }
    }

    void printInOrder() const
    {
        // Left, Node, Right
        
        if ( left )
        {
            left->printInOrder();
        }

        std::cout << data << std::endl;

        if ( right )
        {
            right->printInOrder();
        }
    }

    void printPostOrder() const
    {
        // Left, Right, Node
        
        if ( left )
        {
            left->printPostOrder();
        }
        
        if ( right )
        {
            right->printPostOrder();
        }
        
        std::cout << data << std::endl;
    }

public:
    typedef std::shared_ptr<BinaryNode> Ptr;
    
    T data;
    
    Ptr left;
    Ptr right;
};

template <typename T>
class BinaryTree
{
public:
    typedef BinaryNode<T> Node;
    typedef typename BinaryNode<T>::Ptr NodePtr;

    BinaryTree()
    {
        //std::cout << "Construct tree: root address = " << &root << std::endl;
    }

    virtual ~BinaryTree()
    {
        //std::cout << "Destruct tree" << std::endl;
    }

    NodePtr getRoot()
    {
        return root;
    }
    
    void add( NodePtr& node, const T& data )
    {
        std::cout << "Add node: data = " << data << std::endl;
        if ( !node )
        {
            //std::cout << "-> Current node is not valid, create a new node [" << data << "]" << std::endl;
            node = std::make_shared<Node>( data );
        }
        else
        {
            if ( data >= node->data )
            {
                //std::cout << "-> [" << data << "] is larger than current node's value of [" << node->data << "] -> Go right\n";
                add( node->right, data );
            }
            else
            {
                //std::cout << "-> [" << data << "] is smaller than current node's value of [" << node->data << "] -> Go left\n";
                add( node->left, data );
            }
        }
    }

    void add( const T& data )
    {
        add( root, data );
    }

    void printPreOrder() const
    {
        if ( root )
        {
            root->printPreOrder();
        }
    }

    void printInOrder() const
    {
        if ( root )
        {
            root->printInOrder();
        }
    }

    void printPostOrder() const
    {
        if ( root )
        {
            root->printPostOrder();
        }
    }
    
    int size( NodePtr node )
    {
        if ( node )
        {
            return 1 + size( node->left ) + size( node->right );
        }
        
        return 0;
    }
    
    int maxDepth( NodePtr node )
    {
        if ( !node || ( !node->left && !node->right ) )
        {
            return 0;
        }
        
        int left = maxDepth( node->left );
        int right = maxDepth( node->right );
        
        return 1 + std::max( left, right );
    }

    int minDepth( NodePtr node )
    {
        if ( !node || ( !node->left && !node->right ) )
        {
            return 0;
        }
        
        int left = minDepth( node->left );
        int right = minDepth( node->right );
        
        return 1 + std::min( left, right );
    }
    
    bool isBalanced()
    {
        if ( maxDepth( root ) - minDepth( root ) <= 1 )
        {
            return true;
        }
        
        return false;
    }
    
    NodePtr leftMostNode( NodePtr node )
    {
        if ( !node ) return NULL;
        
        while ( node->left )
        {
            node = node->left;
        }
        
        return node;
    }
    
    NodePtr rightMostNode( NodePtr node )
    {
        if ( !node ) return NULL;
        
        while ( node->right )
        {
            node = node->right;
        }
        
        return node;
    }

    T max( NodePtr node )
    {
        NodePtr maxNode = rightMostNode( node );
        if ( !maxNode ) return T();
        
        return maxNode->getData();
    }
    
    T min( NodePtr node )
    {
        NodePtr minNode = leftMostNode( node );
        if ( !minNode ) return T();
        
        return minNode->getData();
    }
    
    NodePtr find( NodePtr node, const T& key )
    {
        if ( !node ) return NULL;
        
        if ( key == node->getData() )
        {
            return node;
        }
        else
        {
            if ( key > node->getData() )
            {
                return find( node->right, key );
            }
            else
            {
                return find( node->left, key );
            }
        }
    }
    
    void pathToRoot( NodePtr node, std::vector<T>& path )
    {
        if ( node == root ) return;
        
        
    }

private:
    NodePtr root;
};

#endif
