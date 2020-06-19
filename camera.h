/*
 * Filename     : camera.h
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
#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"

/*-----------------------------User-defined Types-----------------------------*/
/* Add comment here */
typedef struct {
    vec   ogn,  /* Add comment here */ 
          llc,  /* Add comment here */
          hor,  /* Add comment here */
          ver,  /* Add comment here */
          u,    /* Add comment here */
          v,    /* Add comment here */
          w;    /* Add comment here */
    float rad;  /* Add comment here */
} camera;

/*---------------------------Function Declarations----------------------------*/
/* Add comment here */
void camera_set(camera *cam, vec lf, vec la, vec up, float vfov, 
        float ar, float apt, float fd); 

/* Add comment here */
ray get_ray(camera *cam, float u, float v);

/* Add comment here */
vec rndm_unit_disk();
