//
// Created by izanagi on 08.04.2022.
//
#include <stdlib.h>
#include <stdio.h>
typedef int bool_t;

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
} node_t;


typedef struct BTree
{
    node_t* root;
} BTree_t;

bool_t __is_empty(BTree_t* BTree)
{
    return NULL == BTree->root;
}



void __print(node_t* node)
{
    if(node)
    {
        __print(node->left);
        printf("%d ", node->data);
        __print(node->right);
    }
}

void __insert(node_t* node, int data)
{
    if(data <= node->data)
    {
        if(node->left)
            __insert(node->left, data);
        else
        {
            node->left = (node_t*)malloc(sizeof(node_t));
            node->left->data = data;
            node->left->right = NULL;
            node->left->left = NULL;
        }
    }
    else
    {
        if(node->right)
            __insert(node->right, data);
        else
        {
            node->right = (node_t*)malloc(sizeof(node_t));
            node->right->data = data;
            node->right->right = NULL;
            node->right->left = NULL;

        }
    }
}

void __delete_if_n_2_child(node_t* node, node_t* prev_node)
{
    if(node->right || node->left)
    {
        if(node->right)
        {
            if(node->data <= prev_node->data) // Тут тоже
                prev_node->left = node->right;
            else
                prev_node->right = node->right;
        }
        else
        {
            if(node->data <= prev_node->data) //Если что убрать равенство
                prev_node->left = node->left;
            else
                prev_node->right = node->left;
        }

    }
    else
    {
        if(node->data <= prev_node->data)
            prev_node->left = NULL;
        else
            prev_node->right = NULL;
    }
    free(node);
}

void __delete(node_t* node, node_t* prev_node)
{
    if( node->right && node->left)
    {
        node_t* cur = node->left;
        node_t* prev = node;
        while(cur->right) {
            prev = cur;
            cur = cur->right;
        }
        node->data = cur->data;
        __delete_if_n_2_child(cur, prev);
    }
    else
        __delete_if_n_2_child(node, prev_node);
}

void __find_and_del(node_t* node, node_t* prev_node, int data)
{
    if (node->left && data < node->data) {
        __find_and_del(node->left, node, data); return;}
    if(node->right && data > node->data) {
        __find_and_del(node->right, node, data); return; }
    if(node->data == data) {
        __delete(node, prev_node); return; }
}

void __terminate(node_t* node)
{
    if(node)
    {
        __terminate(node->left);
        __terminate(node->right);
        free(node);
    }
}

BTree_t* BTree_malloc()
{
    return (BTree_t*) malloc(sizeof(BTree_t));
}



void BTree_destruct(BTree_t* BTree)
{
    __terminate(BTree->root);
}

void BTree_add(BTree_t* BTree, int data)
{
    if(__is_empty(BTree))
    {
        BTree->root = (node_t*)malloc(sizeof(node_t));
        BTree->root->data = data;
        BTree->root->right = NULL;
        BTree->root->left = NULL;
        return;
    }
    __insert(BTree->root, data);
}

void BTree_print(BTree_t* BTree)
{
    if(!__is_empty(BTree))
        __print(BTree->root);
}

bool_t BTree_find(BTree_t* BTree, int data)
{
    node_t* cur = BTree->root;
    while(cur)
    {
        if(data < cur->data)
            cur = cur->left;
        else if(data > cur->data)
            cur = cur->right;
        else
            return 1;
    }
    return 0;
}

void BTree_delete(BTree_t* BTree, int data)
{
    if(!__is_empty(BTree))
    {
        node_t* root = BTree->root;
        if(data == root->data)
        {
           if(root->left && root->right)
           {
                node_t* cur = root->left;
                node_t* prev = root;
               while (cur->right)
               {
                   prev = cur;
                   cur = cur->right;
               }
               root->data = cur->data;
               __delete_if_n_2_child(cur, prev);
           }
           else if (root->left || root->right)
           {
               if(root->left)
                   BTree->root = root->left;
               else
                   BTree->root = root->right;
               free(root);
           }
           else
           {
               BTree->root = NULL;
               free(root);
           }
        }
        else
        {
            if(data <= root->data)
                __find_and_del(root->left, root, data);
            else
                __find_and_del(root->right, root, data);
        }
    }
}
