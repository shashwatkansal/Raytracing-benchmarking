/*
 * Filename     : hitlist.h
 * Last Modified: 19 June 2020
 * Owner        : Group 20
 * 
 * Description: 
 * to be updated ...
 * 
 * Other: 
 * This file is formatted with a tab indent size of 4 and a character
 * restriction of 80/line.
 */

#ifndef HITLIST_H
#define HITLIST_H

/*------------------------------Standard Headers------------------------------*/
#include <stdbool.h>

/*----------------------------User-defined Headers----------------------------*/
#include "sphere.h"
#include "material.h"

/*-----------------------------User-defined Types-----------------------------*/
typedef struct {
    sphere **list;  /* A list containing pointers to the hit-able spheres */
    int list_n;     /* The number of spheres in the list */
} hit_list;

/*---------------------------Function Declarations----------------------------*/
/* Add comment here */
void list_set(hit_list *hl, sphere **sphs, int n);

/* Add comment here */
bool hit(hit_list *hl, ray r, float t_min, float t_max, hit_rec *rec);

/* Add comment here */
void list_free(hit_list *hl);

#endif
