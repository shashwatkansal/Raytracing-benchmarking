/*
 * Filename     : sphere.c
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
#include <stdio.h>
#include <stdlib.h>

/*----------------------------User-defined Headers----------------------------*/
#include "sphere.h"
#include "material.h"

/*----------------------------Function Definitions----------------------------*/
/*================================Hit Handler=================================*/
/* Add comment here */
bool sph_hit(sphere *s, ray r, float t_min, float t_max, hit_rec *rec) {
    vec oc = sub(r.ogn, s->cen);
    float a = dot(r.des, r.des);
    float b = dot(oc, r.des);
    float c = dot(oc, oc) - s->rad * s->rad;
    float d = b*b - a*c;
    if (d > 0) {
        float temp = (-b - sqrt(d))/a;
        if (temp < t_max && temp > t_min) {
            rec->t = temp;
            rec->pos = point_at(temp, r);
            rec->nor = div_c(sub(rec->pos, s->cen), s->rad);
            rec->mat = s->mat;
            return true;
        }
        temp = (-b + sqrt(d))/a;
        if (temp < t_max && temp > t_min) {
            rec->t = temp;
            rec->pos = point_at(temp, r);
            rec->nor = div_c(sub(rec->pos, s->cen), s->rad);
            rec->mat = s->mat;
            return true;
        }
    }
    return false;
}

/*===============================Initialisation===============================*/
/* Add comment here */
sphere* sph_set(float x, float y, float z, float rad, material mat) {
    sphere *s = calloc(1, sizeof(*s));

    vec cen;
    vec_set(&cen, x, y, z);

    s->cen = cen;
    s->rad = rad;
    s->mat = mat;

    return s;
}

/*=============================Memory Management==============================*/
/* Add comment here */
void sph_free(sphere *s) {
    if(!s) return;
    free(s);
}
