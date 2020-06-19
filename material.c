/*
 * Filename     : material.c
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
#include <stdlib.h>

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"
#include "vec.h"
#include "material.h"

/*----------------------------Function Definitions----------------------------*/
/* Add comment here */
void mat_set(material *m, vec abdo, float fuzz, float rfix, mat_type type){
    m->abdo = abdo; /* Set the albedo of the material */
    m->fuzz = fuzz; /* Set the 'fuzziness' of the material */
    m->rfix = rfix; /* Set the refractive index of the material */
    m->type = type; /* Set the type of material - DIFFUSE, METAL, or GLASS */
}

/* Add comment here */
bool scatter_diffuse(material *m, hit_rec rec, vec *att, ray *r_out) {
    vec tgt = add(rec.nor, add(rec.pos, random_point()));
    ray_set(r_out, rec.pos, sub(tgt, rec.pos));
    *att = m->abdo; /* Set the attenuation to the material's albedo */
    return true;
} 

/* Add comment here */
bool scatter_metal(material *m, ray r_in, hit_rec rec, vec *att, ray *r_out) {
    vec reflected = reflect(unit(r_in.des), rec.nor);
    vec temp = add(reflected, mul_c(random_point(), m->fuzz));
    ray_set(r_out, rec.pos, temp);
    *att = m->abdo; /* Set the attenuation to the material's albedo */
    return (dot(r_out->des, rec.nor) > 0);
}

/* Add comment here */
bool scatter_glass(material *m, ray r_in, hit_rec rec, vec *att, ray *r_out) {
    vec on; /* Outward normal */
    vec reflected = reflect(r_in.des, rec.nor);
    float nint;
    vec_set(att, 1, 1, 1);
    vec refracted;
    float cos;
    float rp;  /* Refracted probability */
    if (dot(r_in.des, rec.nor) > 0) {
        on = neg(rec.nor);
        nint = m->rfix;
        cos = m->rfix * dot(r_in.des, rec.nor) / len(r_in.des);
    } else {
        on = rec.nor;
        nint = 1 / m->rfix;
        cos = -dot(r_in.des, rec.nor) / len(r_in.des);
    }
    if (refract(r_in.des, on, nint, &refracted)) {
        rp = schlick(cos, m->rfix);
    } else {
        ray_set(r_out, rec.pos, reflected);
        rp = 1;
    }
    if (drand48() < rp) {
        ray_set(r_out, rec.pos, reflected); 
    } else {
        ray_set(r_out, rec.pos, refracted);
    }
    return true;
}

/* Add comment here */
bool scatter(material *m, ray r_in, hit_rec rec, vec *att, ray *r_out) {
    switch(m->type) {
        case DIFFUSE:
            return scatter_diffuse(m, rec, att, r_out);
        case METAL:
            return scatter_metal(m, r_in, rec, att, r_out);
        case GLASS:
            return scatter_glass(m, r_in, rec, att, r_out);
        default:
            printf("Error: Material type invalid!\n");
            exit(EXIT_FAILURE);
    }
}

/* Add comment here */
vec random_point() {
    vec p;
    do {
        vec rand;
        vec_set(&rand, drand48(), drand48(), drand48());
        vec unit;
        vec_set(&unit, 1, 1, 1);
        p = sub(mul_c(rand, 2), unit);
    } while (sq_len(p) >= 1);
    return p;
}

/* Add comment here */
vec reflect(vec v, vec n) {
    return sub(v, mul_c(n, 2 * dot(n, v)));
}

/* Add comment here */
bool refract(vec v, vec n, float nint, vec *refracted) {
    vec uv = unit(v);
    float dt = dot(uv, n);
    float d = 1 - nint * nint * (1 - dt * dt);
    if (d > 0) {
        vec temp = mul_c(sub(uv, mul_c(n , dt)), nint);
        *refracted = sub(temp, mul_c(n, sqrt(d)));
        return true;
    }
    return false;
}

/* Add comment here */
float schlick(float cos, float ri) {
    float r0 = (1 - ri) / (1 + ri);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow(1 - cos, 5);
}
