/*
 * Filename     : ray.c
 * Last Modified: 19 June 2020
 * Owner        : Group 20
 * 
 * Description: 
 * This file contains the definitions of the functions whose declarations are
 * specified in ray.h.
 * 
 * Other: 
 * This file is formatted with a tab indent size of 4 and a character
 * restriction of 80/line.
 */

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"
#include "vec.h"

/*---------------------------Function Declarations----------------------------*/
/*================================Constructors================================*/
void ray_set(ray *r, vec ogn, vec des) {
	r->ogn = ogn;
	r->des = des;
}

/*==============================Unary Operations==============================*/
vec point_at(float t, ray r) {
	return add(r.ogn, mul_c(r.des, t));
}
