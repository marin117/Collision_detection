#ifndef _AABBTreeNode_h
#define _AABBTreeNode_h


#include "point.h"
#include "AABB_box.h"
#include <vector>


class Node{
public:
    AABB_box box;
    std::vector<Node> child;
    int idx;

    Node()=default;
    

    Node(const AABB_box bbox);
    bool isLeaf();
    
};

void setIndex(Node& root,int index);
Node buildTree(Node& left,Node& right);
void treeTraverse(Node& root);


#endif

