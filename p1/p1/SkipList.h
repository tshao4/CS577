//
//  SkipList.h
//  p1
//
//  Created by Terry Shao on 3/24/14.
//  Copyright (c) 2014 Terry Shao. All rights reserved.
//

#ifndef p1_SkipList_h
#define p1_SkipList_h

#define SKIPLIST_MAXLEVEL 100
#define PROB 0.5
#define MinInf -2147483647

#include "pthread.h"
#include "spin.h"

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
    struct node *up;
    struct node *down;
    spinlock_t lock;
}Node;

typedef struct skiplist {
    Node *root;
    int level;
}Skiplist;

void SL_Init(Skiplist *lst);

void SL_Insert(Skiplist *sl, int t);

int SL_Delete(Skiplist *sl, int t);

int SL_Search(Skiplist *sl, int t, int * moves);

void SL_Print(Skiplist *sl);

#endif
