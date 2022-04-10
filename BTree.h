//
// Created by izanagi on 08.04.2022.
//
#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H
typedef int bool_t;
struct node_t;
struct BTree_t;
struct BTree_t* BTree_malloc();
void BTree_add(struct BTree_t* BTree, int data);
void BTree_print(struct BTree_t* BTree);
bool_t BTree_find(struct BTree_t* BTree, int data);
void BTree_delete(struct BTree_t* BTree, int data);
void BTree_construct(struct BTree_t* BTree);
void BTree_destruct(struct BTree_t* BTree);
#endif //BTREE_BTREE_H
