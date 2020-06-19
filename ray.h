/*
 * Filename     : ray.h
 * Last Modified: 19 June 2020
 * Owner        : Group 20
 * 
 * Description: 
 * This file contains the type definition and function declarations used to
 * represent a ray.
 * 
 * Other: 
 * This file is formatted with a tab indent size of 4 and a character
 * restriction of 80/line.
 */

#ifndef RAY_H
#define RAY_H

/*----------------------------User-defined Headers----------------------------*/
#include "vec.h"

/*-----------------------------User-defined Types-----------------------------*/
typedef struct Ray {
	vec ogn; /* The origin vector of the ray */
	vec des; /* The destination vector of the ray */
} ray;

/*---------------------------Function Declarations----------------------------*/
/*================================Constructors================================*/
void ray_set(ray *r, vec ogn, vec des);

/*==============================Unary Operations==============================*/
vec point_at(float d, ray r);

#endif
