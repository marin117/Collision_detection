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
    this->parent = nullptr;
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
    AABB_box leaf_box = leaf->box;

    while(!temp->isLeaf()){

        std::cout<<Combine(this->left->box,leaf->box).getSurface()<<"  "<<Combine(this->right->box,leaf->box).getSurface()<<std::endl;
        if (Combine(this->left->box,leaf->box).getSurface()>Combine(this->right->box,leaf->box).getSurface())
        {
            temp = temp->right.get();
            direction = 1;
        }
        else {   
            temp = temp->left.get();
            direction = 0;
        }
    }

    auto tempParent = temp->parent;

    if (!direction){
        newNode = std::make_unique<Node>(temp->parent->left,leaf);
        newNode->parent = tempParent;
        tempParent->left = std::move(newNode);


    }

    else{

        newNode = std::make_unique<Node>(temp->parent->right,leaf);
        newNode->parent = tempParent;
        tempParent->right = std::move(newNode);

    }
    temp = tempParent;

    while (temp!=nullptr){

        temp->box = Combine(temp->box,leaf_box);
        temp = temp->parent;

    }


}

void Node::mergeTree(ptr &root){

    if (root == nullptr) return;

    if (root->left->isLeaf()){

        this->insertLeaf(root->left);
        root->left = nullptr;


    }
    if (root->right->isLeaf()){

        this->insertLeaf(root->right);
        root->right = nullptr;

    }


    this->mergeTree(root->left);
    this->mergeTree(root->right);


}



