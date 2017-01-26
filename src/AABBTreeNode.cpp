#include "AABBTreeNode.h"
#include "AABB_box.h"
#include <iostream>

Node::Node(const AABB_box bbox){
        parent = NULL;
        left = NULL;
        right = NULL;
        box = bbox;
}

void treeTraverse(Node* root){
    if(root->isLeaf()){
        std::cout<<"leaf "<<root->idx<<std::endl;
        return;
    } 
    
    std::cout<<"node "<<root->idx<<std::endl;
    treeTraverse(root->left);
    treeTraverse(root->right);

}

void setIndex(Node* root,int index){
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

Node buildTree(Node* left,Node* right){

    Node root(Combine(left->box,right->box));
    root.left = left;
    root.right = right;
    left->parent = right->parent = &root;
    return root;

}


