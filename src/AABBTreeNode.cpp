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


void Node::treeTraverse(){

    if(this->isLeaf()){
        std::cout<<"leaf "<<std::endl;
        return;
    } 
    
    std::cout<<"node "<<std::endl;
    this->left->treeTraverse();
    this->right->treeTraverse();

}


bool Node::isLeaf(){

    if(!right) return true;

    return false;
}

void Node::insertLeaf(ptr& leaf){


    auto temp = this;
    int direction = 0;
    ptr newNode;

    while(!temp->isLeaf()){
        //std::cout<<Combine(this->left->box,leaf->box).getSurface()<<"  "<<Combine(this->right->box,leaf->box).getSurface()<<std::endl;
        if (Combine(this->left->box,leaf->box).getSurface()>Combine(this->right->box,leaf->box).getSurface()){
            temp = temp->right.get();
            direction = 1;
        }
        else {
            temp = temp->left.get();
            direction = 0;
        }

    }

    if (!direction){
        auto parent = temp->parent;
        newNode = std::make_unique<Node>(temp->parent->left,leaf);
        newNode->parent = parent;
        parent->left = std::move(newNode);

    }

    else{
        auto parent = temp->parent;
        newNode = std::make_unique<Node>(temp->parent->right,leaf);
        newNode->parent = parent;
        parent->right = std::move(newNode);

    }
    temp = newNode.get();

    while (temp!=nullptr){
        temp->parent->box = Combine(temp->box,leaf->box);
        temp = temp->parent;

    }

}


