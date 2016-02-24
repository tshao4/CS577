//
//  main.c
//  p2
//
//  Created by Terry Shao on 4/17/14.
//  Copyright (c) 2014 Terry Shao. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "b_graph.h"

graph_t g;

float standard_deviation(artist_node_t * t)
{
    float mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<7;++i)
    {
        mean+=t->weight[i];
    }
    mean=mean/7;
    for(i=0; i<7;++i)
        sum_deviation+=(t->weight[i]-mean)*(t->weight[i]-mean);
    return sqrt(sum_deviation/7);
}

float standard_deviation_g(artist_node_t * t)
{
    float mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<2;++i)
    {
        mean+=t->weight_g[i];
    }
    mean=mean/2;
    for(i=0; i<2;++i)
        sum_deviation+=(t->weight_g[i]-mean)*(t->weight_g[i]-mean);
    return sqrt(sum_deviation/2);
}

float standard_deviation_c(artist_node_t * t)
{
    float mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<5;++i)
    {
        mean+=t->weight_c[i];
    }
    mean=mean/5;
    for(i=0; i<5;++i)
        sum_deviation+=(t->weight_c[i]-mean)*(t->weight_c[i]-mean);
    return sqrt(sum_deviation/5);
}


void parse(char * input, int index){
    
    strtok(input, "\t");
    
    char name[32];
    
    strcpy(name, strtok(NULL, "\t"));
    
    artist_node_t * node = (artist_node_t*)malloc(sizeof(artist_node_t));
    
    strcpy(node->name, name);
    
    for (int i = 0; i < 7; i++) {
        node->edges[i] = g.age_nodes[i];
        node->weight[i] = atoi(strtok(NULL, "\t"));
        g.age_nodes[i]->edges[index] = node;
        g.age_nodes[i]->weight[index] = node->weight[i];
    }
    
    g.artist_nodes[index] = node;
}

void parse_g(char * input, int index){
    
    strtok(input, "\t");
    
    strtok(NULL, "\t");
    
    for (int i = 0; i < 2; i++) {
        g.artist_nodes[index]->edges_g[i] = g.gender_nodes[i];
        g.artist_nodes[index]->weight_g[i] = atoi(strtok(NULL, "\t"));
        g.gender_nodes[i]->edges[index] = g.artist_nodes[index];
        g.gender_nodes[i]->weight[index] = g.artist_nodes[index]->weight_g[i];
    }
}

void parse_c(char * input, int index){
    
    strtok(input, "\t");
    
    strtok(NULL, "\t");
    
    for (int i = 0; i < 5; i++) {
        g.artist_nodes[index]->edges_c[i] = g.country_nodes[i];
        g.artist_nodes[index]->weight_c[i] = atoi(strtok(NULL, "\t"));
        g.country_nodes[i]->edges[index] = g.artist_nodes[index];
        g.country_nodes[i]->weight[index] = g.artist_nodes[index]->weight_c[i];
    }
}

void graph_init(){
    
    FILE * fp = fopen("dataset", "r");
    
    char buffer[128];
    
    fgets(buffer, 128, fp);
    
    for (int i = 0; i < 7; i++) {
        
        age_node_t * node = (age_node_t*)malloc(sizeof(age_node_t));
        node->age = i;
        g.age_nodes[i] = node;
    }
    
    for (int i = 0; i < 2; i++) {
        
        gen_node_t * node = (gen_node_t*)malloc(sizeof(gen_node_t));
        node->gender = i;
        g.gender_nodes[i] = node;
    }

    for (int i = 0; i < 5; i++) {
        
        country_node_t * node = (country_node_t*)malloc(sizeof(country_node_t));
        node->country = i;
        g.country_nodes[i] = node;
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++){
        
        fgets(buffer, 128, fp);
        parse(buffer, i);
    }
    
    fclose(fp);
    
    fp = fopen("dataset-gender", "r");
    
    fgets(buffer, 128, fp);
    
    for (int i = 0; i < 2; i++) {
        
        gen_node_t * node_g = (gen_node_t*)malloc(sizeof(gen_node_t));
        node_g->gender = i;
        g.gender_nodes[i] = node_g;
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++){
        
        fgets(buffer, 128, fp);
        parse_g(buffer, i);
    }
    
    fclose(fp);
    
    fp = fopen("dataset-country", "r");
    
    fgets(buffer, 128, fp);
    
    for (int i = 0; i < 2; i++) {
        
        country_node_t * node_c = (country_node_t*)malloc(sizeof(country_node_t));
        node_c->country = i;
        g.country_nodes[i] = node_c;
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++){
        
        fgets(buffer, 128, fp);
        parse_c(buffer, i);
    }
    
    fclose(fp);
}

void generateQ1(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};

    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 && (sorted_list[d]->weight[__12_17] - sorted_list[d]->weight[__55_64])
               < (sorted_list[d-1]->weight[__12_17] - sorted_list[d-1]->weight[__55_64])) {
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generateQ2(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        
        
        while ( d > 0 &&  (sorted_list[d]->weight[__12_17] + sorted_list[d]->weight[__55_64])
               < (sorted_list[d-1]->weight[__12_17] + sorted_list[d-1]->weight[__55_64])) {
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generateQ3(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 && (sorted_list[d]->weight[__12_17] +
                          sorted_list[d]->weight[__18_24] +
                          sorted_list[d]->weight[__25_34] +
                          sorted_list[d]->weight[__35_44] +
                          sorted_list[d]->weight[__45_54] +
                          sorted_list[d]->weight[__55_64] +
                          sorted_list[d]->weight[__65P]) *
                          standard_deviation(sorted_list[d])
                       < (sorted_list[d-1]->weight[__12_17] +
                          sorted_list[d-1]->weight[__18_24] +
                          sorted_list[d-1]->weight[__25_34] +
                          sorted_list[d-1]->weight[__35_44] +
                          sorted_list[d-1]->weight[__45_54] +
                          sorted_list[d-1]->weight[__55_64] +
                          sorted_list[d-1]->weight[__65P]) *
                          standard_deviation(sorted_list[d])) {
                           
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generate_gen_1(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 && (sorted_list[d]->weight_g[MALE] - sorted_list[d]->weight_g[FEMALE])
               < (sorted_list[d-1]->weight_g[MALE] - sorted_list[d-1]->weight_g[FEMALE])) {
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generate_gen_2(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 && (sorted_list[d]->weight_g[MALE] +
                          sorted_list[d]->weight_g[FEMALE]) *
               standard_deviation_g(sorted_list[d])
               < (sorted_list[d-1]->weight_g[MALE] +
                  sorted_list[d-1]->weight_g[FEMALE]) *
               standard_deviation_g(sorted_list[d])) {
            
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generate_con_1(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 && (sorted_list[d]->weight_c[USA] - sorted_list[d]->weight_c[CHINA])
               < (sorted_list[d-1]->weight_c[USA] - sorted_list[d-1]->weight_c[CHINA])) {
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generate_con_2(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 &&  (sorted_list[d]->weight_c[USA] + sorted_list[d]->weight_c[CHINA])
               < (sorted_list[d-1]->weight_c[USA] + sorted_list[d-1]->weight_c[CHINA])) {
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

void generate_con_3(){
    
    artist_node_t * sorted_list[NUM_ARTISTS] = {NULL};
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        sorted_list[i] = g.artist_nodes[i];
    }
    
    int c, d;
    artist_node_t * tmp;
    
    for (c = 1 ; c < NUM_ARTISTS; c++) {
        d = c;
        
        while ( d > 0 && (sorted_list[d]->weight_c[USA] +
                          sorted_list[d]->weight_c[ENGLAND] +
                          sorted_list[d]->weight_c[BRAZIL] +
                          sorted_list[d]->weight_c[CHINA] +
                          sorted_list[d]->weight_c[AUSTRALIA]) *
               standard_deviation_c(sorted_list[d])
               < (sorted_list[d-1]->weight_c[USA] +
                  sorted_list[d-1]->weight_c[ENGLAND] +
                  sorted_list[d-1]->weight_c[BRAZIL] +
                  sorted_list[d-1]->weight_c[CHINA] +
                  sorted_list[d-1]->weight_c[AUSTRALIA]) *
               standard_deviation_c(sorted_list[d])) {
            
            tmp        = sorted_list[d];
            sorted_list[d]   = sorted_list[d-1];
            sorted_list[d-1] = tmp;
            
            d--;
        }
    }
    
    for (int i = 0; i < NUM_ARTISTS; i++) {
        printf("%s\n", sorted_list[i]->name);
    }
}

int main(int argc, const char * argv[])
{
    graph_init();
    
    //Age
    printf("List of artists that 13 years olds like and 64 years olds dislike\n");
    generateQ1();
    
    printf("\nList of artists that both 13 years olds and 64 years olds like\n");
    generateQ2();
    
    printf("\nList of artists that all age groups like\n");
    generateQ3();
    
    //Gender
    printf("\nList of artists that male like and female dislike\n");
    generate_gen_1();
    printf("\nList of artists that both male female like\n");
    generate_gen_2();
    //Country
    printf("\nList of artists that USA like and China dislike\n");
    generate_con_1();
    printf("\nList of artists that both USA and China like\n");
    generate_con_2();
    printf("\nList of artists that all countries like\n");
    generate_con_3();
    return 0;
}