#include "AABBTreeNode.h"
#include <iostream>
#include <stack>


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
        std::cout<<"########leaf##########"<<std::endl;
        std::cout<<this->box.center.x<<std::endl;
        std::cout<<this->box.center.y<<std::endl;
        std::cout<<this->box.center.z<<std::endl;
        return;
    } 
    std::cout<<"#######node###########"<<std::endl;
    std::cout<<this->box.center.x<<std::endl;
    std::cout<<this->box.center.y<<std::endl;
    std::cout<<this->box.center.z<<std::endl;
    this->left->treeTraverse();
    this->right->treeTraverse();

}


bool Node::isLeaf(){

    if(!right) return true;

    return false;
}

void Node::insertLeaf(ptr& leaf){
    auto curr = this;
    bool direction = 0;
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


void Node::buildTree(int i){
    if(this->isLeaf()){
        if (i==0){

            float leftX = (this->box.center.x - this->box.r[0])/2;
            float rightX =(this->box.center.x + this->box.r[0])/2;
            ptr left = std::make_unique<Node>(AABB_box(leftX,this->box.center.y,this->box.center.z,this->box.r[0]/2));
            ptr right =std::make_unique<Node>(AABB_box(rightX,this->box.center.y,this->box.center.z,this->box.r[0]/2));
            left->parent = right->parent = this;
            this->left = std::move(left);
            this->right = std::move(right);

        }


        else if(i==1){

            float leftY = (this->box.center.y - this->box.r[1])/2;
            float rightY =(this->box.center.y + this->box.r[1])/2;
            ptr left = std::make_unique<Node>(AABB_box(this->box.center.x,leftY,this->box.center.z,this->box.r[1]/2));
            ptr right =std::make_unique<Node>(AABB_box(this->box.center.x,rightY,this->box.center.z,this->box.r[1]/2));
            left->parent = right->parent = this;
            this->left = std::move(left);
            this->right = std::move(right);


        }

        else {

            float leftZ = (this->box.center.z - this->box.r[2])/2;
            float rightZ =(this->box.center.z + this->box.r[2])/2;
            ptr left = std::make_unique<Node>(AABB_box(this->box.center.x,this->box.center.y,leftZ,this->box.r[0]/2));
            ptr right =std::make_unique<Node>(AABB_box(this->box.center.x,this->box.center.y,rightZ,this->box.r[0]/2));
            left->parent = right->parent = this;
            this->left = std::move(left);
            this->right = std::move(right);

        }


        return;


    }


    this->left->buildTree(i);
    this->right->buildTree(i);

}

bool Node::treeOverlap(ptr &root){
    return isOverlap(this->box,root->box);
}

bool Node::treeCollision(ptr &root){
    if (!this->treeOverlap(root)) return false;


    if(this->isLeaf() && root->isLeaf()){
        std::cout<<this->box.center.y<<std::endl;
        std::cout<<root->box.center.y<<std::endl;
        return true;
    }

    else {

        if (root->isLeaf()){
            this->left->treeCollision(root);
            this->right->treeCollision(root);

        }

        else{
            this->treeCollision(root->left);
            this->treeCollision(root->right);
        }
    }
   return true;

}

