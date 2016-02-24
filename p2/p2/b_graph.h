//
//  b_graph.h
//  p2
//
//  Created by Terry Shao on 4/17/14.
//  Copyright (c) 2014 Terry Shao. All rights reserved.
//

#ifndef p2_b_graph_h
#define p2_b_graph_h

#define NUM_ARTISTS 40

typedef enum age_group{

    __12_17 = 0,
    __18_24 = 1,
    __25_34 = 2,
    __35_44 = 3,
    __45_54 = 4,
    __55_64 = 5,
    __65P   = 6
}age_t;

typedef enum countrys{
    USA = 0,
    ENGLAND = 1,
    BRAZIL = 2,
    CHINA = 3,
    AUSTRALIA = 4
}country_t;

typedef enum genders{
    MALE = 0,
    FEMALE = 1
}gen_t;

typedef struct age_node{

    age_t age;
    struct artist_node * edges[NUM_ARTISTS];
    int weight[NUM_ARTISTS];
}age_node_t;

typedef struct country_node{
    
    country_t country;
    struct artist_node * edges[NUM_ARTISTS];
    int weight[NUM_ARTISTS];
}country_node_t;

typedef struct gender_node{
    
    gen_t gender;
    struct artist_node * edges[NUM_ARTISTS];
    int weight[NUM_ARTISTS];
}gen_node_t;

typedef struct artist_node{
    
    char name[32];
    struct age_node * edges[7];
    struct gender_node * edges_g[2];
    struct country_node * edges_c[5];
    
    int weight[7];
    int weight_g[2];
    int weight_c[5];
}artist_node_t;

typedef struct graph{

    age_node_t * age_nodes[7];
    artist_node_t * artist_nodes[NUM_ARTISTS];
    country_node_t * country_nodes[5];
    gen_node_t * gender_nodes[2];
}graph_t;

#endif
