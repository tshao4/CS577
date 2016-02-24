//
//  SkipList.c
//  p1
//
//  Created by Terry Shao on 3/24/14.
//  Copyright (c) 2014 Terry Shao. All rights reserved.
//

#include "SkipList.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define COIN
//#define ONELEVEL

void Node_Init(Node *init, int data){
    
    init->data = data;
    init->lock = 0;
    init->up = NULL;
    init->down = NULL;
    init->left = NULL;
    init->right = NULL;
}

void SL_Init(Skiplist *lst){
    
    lst->root = (Node*)malloc(sizeof(Node));
    Node_Init(lst->root, MinInf);
}

void SL_FreeNode(Node *sn){
    
    free(sn);
}

int generateLevel(){

#ifdef COIN
    int level = 0;
    while(rand()%100 < PROB*100)
        level += 1;
    //printf("level : %d\n", level);
    return (level < SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
#endif
    
#ifdef ONELEVEL
    static int level = 0;
    int tmp = 0;
    while(rand()%100 < PROB*100)
        tmp++;
    if (tmp > level && level < SKIPLIST_MAXLEVEL){
        level++;
    }
    //printf("level : %d\n", tmp);
    return (tmp < level)? tmp : level;
#endif
}

void update(Skiplist *sl, int l){
    
    if (sl->level < l && sl->level < SKIPLIST_MAXLEVEL){
        int i;
        Node *r = sl->root;
        for (i = sl->level; i < l; i++) {
            Node *tmp = (Node*)malloc(sizeof(Node));
            Node_Init(tmp, MinInf);

            tmp->down = r;
            r->up = tmp;
            r = tmp;
        }
        sl->level = l;
        sl->root = r;
    }
}

void SL_Insert(Skiplist *sl, int t){
    
    Node *new = malloc(sizeof(Node));
    Node_Init(new, t);
    int newlevel = generateLevel();
    update(sl, newlevel);
    
    Node *tmp = sl->root;
    Node *tp;
    while (1) {
        
        while (tmp->right != NULL && t > tmp->right->data) {
            tmp = tmp->right;
        }
        if (tmp->down != NULL) {
            tmp = tmp->down;
        }else{
            break;
        }
    }
    
    int i;
    
    for (i = 0; i <= newlevel; i++) {
        
        if (i == 0) {
            new->left = tmp;
            new->right = tmp->right;
            if(tmp->right != NULL) {
                tmp->right->left = new;
            }
            tmp->right = new;
        }else{
            Node *dup = (Node*)malloc(sizeof(Node));
            Node_Init(dup, new->data);
            
            dup->left = tmp;
            dup->right = tmp->right;
            dup->down = new;
            new->up = dup;
            if(tmp->right != NULL) {
                tmp->right->left = dup;
            }
            tmp->right = dup;

            new = dup;
        }
        
        if (i == newlevel) {
            break;
        }
        
        if (tmp->up != NULL) {
            tp = tmp;
            tmp = tmp->up;
        }else{
            tp = tmp;
            tmp = tmp->left;
            while (tmp->up == NULL) {
                tp = tmp;
                tmp = tmp->left;
            }
            tmp = tmp->up;
        }
    }
}

Node *find(Skiplist *sl, int t, int * moves){
    
    Node *tmp = sl->root;
    
    while (1) {
        
        while (tmp->right != NULL && t > tmp->right->data) {
            tmp = tmp->right;
            (*moves)++;
        }
        if (tmp->down != NULL) {
            tmp = tmp->down;
            (*moves)++;
        }else{
            break;
        }
    }
    
    if (tmp->right == NULL) {
        return NULL;
    }else if (tmp->right->data == t) {
        (*moves)++;
        return tmp->right;
    }else {
        return NULL;
    }
}

int SL_Delete(Skiplist *sl, int t){
    
    Node *tmp = NULL;
    int moves = 0;
    if ((tmp = find(sl, t, &moves))) {
        
        while (tmp != NULL) {
            
            if (tmp->left != NULL && tmp->right != NULL) {
                
                tmp->left->right = tmp->right;
                tmp->right->left = tmp->left;
            }
            else if (tmp->left != NULL){
                
                tmp->left->right = tmp->right;
            }
            else if (tmp->right != NULL){
                
                tmp->right->left = tmp->left;
            }
            Node *f = tmp;

            tmp = tmp->up;
            SL_FreeNode(f);
        }
        
        return 1;
    }
    return 0;
}

int SL_Search(Skiplist *sl, int t, int * moves) {
    
    Node *tmp = find(sl, t, moves);
    return (tmp == NULL)? -1 : tmp->data;
}

void SL_Print(Skiplist *sl){
    
    Node *tmp = sl->root;
    Node *lev = sl->root;
    int i;
    for (i = 0; i <= sl->level; i++) {
        printf("level[%d]:", i);
        while (tmp != NULL) {
            
            printf("%d->", tmp->data);
            tmp = tmp->right;
        }
        printf("NULL\n");
        lev = lev->down;
        tmp = lev;
    }
}