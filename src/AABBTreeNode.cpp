#include "AABBTreeNode.h"
#include "AABB_box.h"
#include <iostream>

Node::Node(const AABB_box bbox){
        child.reserve(2);
        box = bbox;
}

void treeTraverse(Node& root){
    if(root.isLeaf()){
        std::cout<<"leaf "<<root.idx<<std::endl;
        return;
    } 
    
    std::cout<<"node "<<root.idx<<std::endl;
    treeTraverse(root.child[0]);
    treeTraverse(root.child[1]);

}

void setIndex(Node& root,int index){
    if(root.isLeaf()){
        root.idx = index;
        return;
    } 
    
    root.idx = index;
    setIndex(root.child[0],++index);
    setIndex(root.child[1],++index);

}

bool Node::isLeaf(){

    if(!child.size()) return true;

    return false;
}

Node buildTree(Node& left,Node& right){

    Node root;
    root.child.reserve(2);
    root.box = Combine(left.box,right.box);
    root.child.emplace_back(left);
    root.child.emplace_back(right);
    return root;
}
