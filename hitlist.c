/*
 * Filename     : hitlist.c
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

/*------------------------------Standard Headers------------------------------*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*----------------------------User-defined Headers----------------------------*/
#include "sphere.h"
#include "hitlist.h"
#include "material.h"

/*----------------------------Function Definitions----------------------------*/
/* Add comment here */
void list_set(hit_list *hl, sphere **sphs, int n) {
    hl->list = sphs;
    hl->list_n = n;
}

/* Add comment here */
bool hit(hit_list *hl, ray r, float t_min, float t_max, hit_rec *rec) {
    hit_rec tmp;
    bool hit = false;
    float closest = t_max;
    for (int i = 0; i < hl->list_n; i++) {
        if(sph_hit(hl->list[i], r, t_min, closest, &tmp)) {
            hit  = true;
            closest = tmp.t;
            *rec = tmp;
        }
    }
    return hit;
}
 
/* Add comment here */
void list_free(hit_list *hl) {
    if (!hl) return;
    if (hl->list_n) {
        for (int i = 0; i < hl->list_n; i++) {
            sph_free(hl->list[i]);
        }
    }
}
