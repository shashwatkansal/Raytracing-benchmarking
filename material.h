/*
 * Filename     : material.h
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

#ifndef MATERIAL_H
#define MATERIAL_H

/*------------------------------Standard Headers------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"
#include "vec.h"

/*-----------------------------User-defined Types-----------------------------*/
typedef enum {
    DIFFUSE,
    METAL, 
    GLASS
} mat_type;

typedef struct {
    vec      abdo; /* The albedo of the material */
    float    fuzz; /* The 'fuzziness` of the material */
    float    rfix; /* The refractive index of the material */ 
    mat_type type;
} material;

typedef struct {
    float    t;    /* The ray parameter */
    vec      pos;  /* The position where the ray hits the surface */
    vec      nor;  /* The surface normal at the hit position */
    material mat;  /* The material of the surface */
} hit_rec;

/*---------------------------Function Declarations----------------------------*/
/* Add comment here */
void mat_set(material *m, vec abdo, float fuzz, float rfix, mat_type type);

/* Add comment here */
bool scatter_diffuse(material *m, hit_rec rec, vec *att, ray *r_out);

/* Add comment here */
bool scatter_metal(material *m, ray r_in, hit_rec rec, vec *att, ray *r_out);

/* Add comment here */
bool scatter_glass(material *m, ray r_in, hit_rec rec, vec *att, ray *r_out);

/* Add comment here */
bool scatter(material *m, ray r_in, hit_rec rec, vec *att, ray *r_out);

/* Add comment here */
vec reflect(vec v, vec n);

/* Add comment here */
bool refract(vec v, vec n, float nint, vec *ref);

/* Add comment here */
float schlick(float cos, float rfix);

/* Add comment here */
vec random_point();

#endif
