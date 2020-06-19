/*
 * Filename     : sphere.h
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

#ifndef SPHERE_H
#define SPHERE_H

/*------------------------------Standard Headers------------------------------*/
#include <stdbool.h>

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"
#include "material.h"

/*-----------------------------User-defined Types-----------------------------*/
typedef struct {
    vec      cen;
    float    rad;
    material mat;
} sphere;

/*---------------------------Function Declarations----------------------------*/
/*================================Hit Handler=================================*/
/* Add comment here */
bool sph_hit(sphere *s, ray r, float t_min, float r_max, hit_rec *rec);

/*==================================Setters===================================*/
/* Add comment here */
sphere *sph_set(float x, float y, float z, float rad, material mat);

/*=============================Memory Management==============================*/
/* Add comment here */
void sph_free(sphere *s);

#endif
