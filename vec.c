/*
 * Filename     : vec.c
 * Last Modified: 19 June 2020
 * Owner        : Group 20
 * 
 * Description: 
 * This file contains the definitions of the functions whose declarations are 
 * specified in vec.h.
 * 
 * Other: 
 * This file is formatted with a tab indent size of 4 and a character
 * restriction of 80/line.
 */

/*------------------------------Standard Headers------------------------------*/
#include <math.h>

/*----------------------------User-defined Headers----------------------------*/
#include "vec.h"

/*----------------------------Function Definitions----------------------------*/
/*================================Constructors================================*/
void vec_set_zero(vec *vp) {
	vec_set(vp, 0.0, 0.0, 0.0);
}

void vec_set(vec *vp, const float x, const float y, const float z) {
	vp->x = x; vp-> y = y; vp->z = z;
}

/*==============================Unary Operations==============================*/
vec id(vec v) {
	return v;
}

vec neg(vec v) {
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return v;
}

float len(vec v) {
	return sqrt(sq_len(v));
}

float sq_len(vec v) {
	return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
}

vec unit(vec v) {
	const float s = 1.0 / len(v);
	return mul_c(v, s);
}

/*=============================Binary Operations==============================*/
vec add(vec v1, vec v2) {
	vec res;
	vec_set(&res, v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return res;	
}

vec sub(vec v1, vec v2) {
	return add(v1, neg(v2));
}

vec mul_v(vec v1, vec v2) {
	vec res;
	vec_set(&res, v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	return res;
}

vec mul_c(vec v, const float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return v;
}

vec div_v(vec v1, vec v2) {
	vec res;
	vec_set(&res, v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
	return res;
}

vec div_c(vec v, const float s) {
	return mul_c(v, 1.0/s);
}

/*==========================Special Binary Functions==========================*/
float dot(vec v1, vec v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;	
}

vec cross(vec v1, vec v2) {
	vec res;
	vec_set(&res, v1.y * v2.z - v2.y * v1.z, 
		       v2.x * v1.z - v1.x * v2.z,
		       v1.x * v2.y - v2.x * v1.y);
	return res;
}
