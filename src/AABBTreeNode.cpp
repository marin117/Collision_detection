#include "AABBTreeNode.h"
#include <iostream>


Node::Node(const AABB_box bbox){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        box = bbox;
        height = 0;
}

Node::Node (ptr& left,ptr& right){

    this->box = Combine(left->box,right->box);
    left->parent = right->parent = this;
    this->height = std::max(left->height,right->height)+1;
    this->left =std::move(left);
    this->right = std::move(right);



}


void treeTraverse(ptr& root){

    if(root->isLeaf()){
        std::cout<<"leaf "<<std::endl;
        return;
    } 
    
    std::cout<<"node "<<std::endl;
    treeTraverse(root->left);
    treeTraverse(root->right);

}


bool Node::isLeaf(){

    if(!right) return true;

    return false;
}

void Node::balanceTree(){

}


