//
//  HBTree.h
//  p1
//
//  Created by Terry Shao on 3/24/14.
//  Copyright (c) 2014 Terry Shao. All rights reserved.
//

#ifndef p1_HBTree_h
#define p1_HBTree_h

typedef int key_t;
typedef int data_t;

typedef enum color_t{
    
    RED = 0,
    BLACK = 1
}color_t;

typedef struct rb_node_t{
    
    struct rb_node_t *left, *right, *parent;
    key_t key;
    data_t data;
    color_t color;
}rb_node_t;

rb_node_t* rb_insert(key_t key, data_t data, rb_node_t* root);
rb_node_t* rb_search(key_t key, rb_node_t* root, int * moves);
rb_node_t* rb_erase(key_t key, rb_node_t* root);

#endif
