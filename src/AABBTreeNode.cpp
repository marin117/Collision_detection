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



    auto curr = this;
    int direction = 0;
    ptr newNode;
    AABB_box leaf_box = leaf->box;

    while(!curr->isLeaf()){

        std::cout<<Combine(this->left->box,leaf->box).getSurface()<<"  "<<Combine(this->right->box,leaf->box).getSurface()<<std::endl;
        if (Combine(this->left->box,leaf->box).getSurface()>Combine(this->right->box,leaf->box).getSurface())
        {
            curr = curr->right.get();
            direction = 1;
        }
        else {   
            curr = curr->left.get();
            direction = 0;
        }
    }

    auto currParent = curr->parent;

    if (!direction){
        newNode = std::make_unique<Node>(curr->parent->left,leaf);
        newNode->parent = currParent;
        currParent->left = std::move(newNode);


    }

    else{

        newNode = std::make_unique<Node>(curr->parent->right,leaf);
        newNode->parent = currParent;
        currParent->right = std::move(newNode);

    }
    curr = currParent;

    while (curr!=nullptr){

        curr->box = Combine(curr->box,leaf_box);
        curr->height++;
        curr = curr->parent;

    }


}

void Node::mergeTree(ptr &root){

    if (root->isLeaf()){
        this->insertLeaf(root);
        return;
    }

    this->mergeTree(root->left);
    this->mergeTree(root->right);


}



