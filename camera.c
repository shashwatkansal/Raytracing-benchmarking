/*
 * Filename     : camera.c
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
#include <math.h>

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"
#include "camera.h"

/*----------------------------Function Definitions----------------------------*/
/* Add comment here */
void camera_set(camera *cam, vec lf, vec la, vec up, float vfov,
        float ar, float apt, float fd) {
    float theta = vfov * M_PI/180.0; /* conversion to radians */
    float half_height = 2 * tan(theta/2);
    float half_width = ar * half_height;
    
    cam->rad = apt/2;
    cam->w = unit(sub(lf, la));
    cam->u = unit(cross(up, cam->w));
    cam->v = cross(cam->w, cam->u);
    cam->ogn = lf;
    cam->hor = mul_c(cam->u, half_width * fd);
    cam->ver = mul_c(cam->v, half_height * fd);
    
    vec tmp1 = div_c(cam->hor, 2);
    vec tmp2 = div_c(cam->ver, 2);
    vec tmp3 = add(tmp1, add(tmp2, mul_c(cam->w, fd)));
    cam->llc = sub(cam->ogn, tmp3);
}

/* Add comment here */
ray get_ray(camera *cam, float s, float t) {
    vec rd = mul_c(rndm_unit_disk(), cam->rad),
        off = add(mul_c(cam->u, rd.x), mul_c(cam->v, rd.y)),
	    tmp = add(mul_c(cam->hor, s), mul_c(cam->ver, t)),
        ogn = add(cam->ogn, off);
    ray r;
    ray_set(&r, ogn, sub(add(cam->llc, tmp), ogn));
    return r;
}

vec rndm_unit_disk() {
    vec p, tmp;
    vec_set(&tmp, 1, 1, 0);
    do {
        vec rand;
        vec_set(&rand, drand48(), drand48(), 0);
        p = sub(mul_c(rand, 2), tmp);
    } while (dot(p, p) >= 1);
    return p;
}
