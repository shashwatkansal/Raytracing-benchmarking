/*
 * Filename     : vec.h
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

#ifndef VEC_H
#define VEC_H

/*------------------------------Standard Headers------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdint.h>

/*-----------------------------User-defined Types-----------------------------*/
typedef struct {
	float x;
	float y;
	float z;
} vec;

/*---------------------------Function Declarations----------------------------*/
/*================================Constructors================================*/
void vec_set_zero(vec *v);
void vec_set(vec *v, const float x, const float y, const float z);

/*==============================Unary Operations==============================*/
vec id(vec v);
vec neg(vec v);
float len(vec v);
float sq_len(vec v);
vec unit(vec v);

/*=============================Binary Operations==============================*/
vec add(vec v1, vec v2);
vec sub(vec v1, vec v2);
vec mul_v(vec v1, vec v2);
vec mul_c(vec v, const float s);
vec div_v(vec v1, vec v2);
vec div_c(vec v, const float s);

/*=========================Special Binary Operations==========================*/
float dot(vec v1, vec v2);
vec cross(vec v1, vec v2);

#endif
