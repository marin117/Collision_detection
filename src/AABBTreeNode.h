#ifndef _AABBTreeNode_h
#define _AABBTreeNode_h


#include "point.h"
#include "AABB_box.h"
#include <vector>
#include <memory>



class Node{
    typedef std::unique_ptr<Node> ptr;
public:

    AABB_box box;
    ptr left;
    ptr right;
    Node *parent;
    int height;

    Node()=default;
    

    Node(const AABB_box bbox);
    Node (ptr& left,ptr& right);
    bool isLeaf();
    void insertLeaf(ptr& leaf);
    void treeTraverse();



    
};

typedef std::unique_ptr<Node> ptr;

#endif

