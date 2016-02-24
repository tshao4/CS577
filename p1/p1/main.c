//
//  main.c
//  p1
//
//  Created by Terry Shao on 3/24/14.
//  Copyright (c) 2014 Terry Shao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SkipList.h"
#include "HBTree.h"

#define SL
//#define HBT

int count = 10000;
Skiplist * sl;
int moves = 0;
int avg = 0;

int main() {
    srand((unsigned)time(NULL));

#ifdef SL
    printf("### Function Test ###\n");
    
    int i = 0;
    
    printf("=== Init Skip List ===\n");
    sl = (Skiplist*)malloc(sizeof(Skiplist));
    SL_Init(sl);
    
    for ( i = 0; i < count; i++) {
        SL_Insert(sl,rand()%count);
    }
    
    printf("=== Print Skip List ===\n");
    SL_Print(sl);
    
    printf("=== Search Skip List ===\n");
    
    for (i = 0; i < count; i++) {
        //int value = rand()%(count+10);
        moves = 0;
        printf("Search[%d]: %s\t\tMoves: %d\n", i, (SL_Search(sl, i, &moves) + 1) ? "Found" : "Not Found", moves);
        avg += moves;
    }
    
    printf("Avg: %d\n", avg/count);
    
//    printf("=== Delete Skip List ===\n");
//    for (i = 0; i < count+10; i+=2) {
//        printf("Delete[%d]: %s\n", i, SL_Delete(sl, i)?"SUCCESS":"NOT FOUND");
//    }
//    SL_Print(sl);
#endif
    
#ifdef HBT
    int i;
    key_t key;
    rb_node_t* root = NULL;
    
    for (i = 1; i < count; ++i){
        
        key = rand() % count;
        
        if ((root = rb_insert(key, i, root))){
            //printf("[i = %d] insert key %d success!\n", i, key);
        }
        else{
            
            printf("[i = %d] insert key %d error!\n", i, key);
            exit(-1);
        }
        
//        if (!(i % 10)){
//            
//            if ((root = rb_erase(key, root))){
//                
//                printf("[i = %d] erase key %d success\n", i, key);
//            }else{
//                
//                printf("[i = %d] erase key %d error\n", i, key);
//            }
//        }
    }
    
    for (i = 1; i < count; ++i) {
        
        moves = 0;
        printf("Search[%d]: %s\t\t Moves: %d\n", i, rb_search(i, root, &moves)? "Found" : "Not Found", moves);
        avg += moves;
    }
    
    printf("Avg: %d\n", avg/count);

#endif
    return 0;
}
