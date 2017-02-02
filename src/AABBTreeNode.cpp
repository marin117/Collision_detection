#include "AABBTreeNode.h"
#include "AABB_box.h"
#include <iostream>


Node::Node(const AABB_box bbox){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        box = bbox;
}

Node::Node (ptr& left,ptr& right){


    this->left =std::move(left);
    this->right = std::move(right);
    //left->parent = right->parent = this;

}


void treeTraverse(ptr& root){

    if(root->isLeaf()){
        std::cout<<"leaf "<<root->idx<<std::endl;
        return;
    } 
    
    std::cout<<"node "<<root->idx<<std::endl;
    treeTraverse(root->left);
    treeTraverse(root->right);

}

void setIndex(ptr& root,int index){

    if(root->isLeaf()){
        root->idx = index;
        return;
    } 
    
    root->idx = index;
    setIndex(root->left,++index);
    setIndex(root->right,++index);

}

bool Node::isLeaf(){

    if(!right) return true;

    return false;
}



