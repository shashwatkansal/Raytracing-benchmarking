/*
 * Filename     : ppm.c
 * Last Modified: 19 June 2020
 * Owner        : Group 20
 * 
 * Description: 
 * This file contains the functions, definitions, and main code block to
 * generate a ray-traced ppm image file..
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
#include <time.h>
#include <string.h>

/*----------------------------User-defined Headers----------------------------*/
#include "ray.h"
#include "vec.h"
#include "sphere.h"
#include "hitlist.h"
#include "camera.h"
#include "material.h"

/*-------------------------Pre-processor Definitions--------------------------*/
#define WIDTH   384      /* The width of the image */
#define HEIGHT  216      /* The height of the image */
#define ASPECT  16.0/9.0 /* The aspect ratio of the image */ 
#define SAMPLES 25      /* The number of samples for anti-aliasing */
#define SPHERES 26        /* The number of spheres in the scene */

/*---------------------------Function Declarations----------------------------*/
vec color(ray r, hit_list *world, int depth);

/*------------------------------------Main------------------------------------*/
int main(void) {
    /* Start the clock */
    clock_t begin = clock();

    /* Benchmark scene construction: */
    sphere *sphs[SPHERES];

    vec abdo;  /* The colour vector */
    material m;  /* Material for the spheres */

    /* Create the base surface */
    vec_set(&abdo, 0.15, 0.15, 0.15);            /* Light grey tone */
    mat_set(&m, abdo, 0, 0, DIFFUSE);    /* Diffuse material */
    sphs[0] = sph_set(0, -1000, 0, 1000, m);

    /* Create the center metallic mirror sphere */
    vec_set(&abdo, 0.5, 0.5, 0.5);
    mat_set(&m, abdo, 0, 0, METAL);
    sphs[1] = sph_set(0, 1, 0, 1, m);

    /* Create the imperial blue edge spheres */
    vec_set(&abdo, 0.1, 0.3, 0.5);
    mat_set(&m, abdo, 0, 0, METAL);
    sphs[2] = sph_set(3.5, 0.3, 3.5, 0.3, m);
    sphs[3] = sph_set(3.5, 0.3, -3.5, 0.3, m);
    sphs[4] = sph_set(-3.5, 0.3, 3.5, 0.3, m);
    sphs[5] = sph_set(-3.5, 0.3, -3.5, 0.3, m);

    /* Create the cherry red fuzzy metallic spheres */
    vec_set(&abdo, 0.9, 0.1, 0.2);
    mat_set(&m, abdo, 0.3, 0, METAL);
    sphs[6] = sph_set(2, 0.5, 0, 0.5, m);
    sphs[7] = sph_set(-2, 0.5, 2, 0.5, m);
    sphs[8] = sph_set(-2, 0.5, -2, 0.5, m);

    /* Create the aquamarine spheres */
    vec_set(&abdo, 0, 0.96, 0.63);
    mat_set(&m, abdo, 0, 0, DIFFUSE);
    sphs[9] = sph_set(-2, 0.5, 0, 0.5, m);
    sphs[10] = sph_set(2, 0.5, -2, 0.5, m);
    sphs[11] = sph_set(2, 0.5, 2, 0.5, m);

    /* Create the glass spheres */
    vec_set_zero(&abdo);
    mat_set(&m, abdo, 0, 1.5, GLASS);
    sphs[12] = sph_set(0, 0.4, 2, 0.4, m);
    sphs[13] = sph_set(0, 0.4, -2, 0.4, m);
    sphs[14] = sph_set(3.5, 0.3, -2, 0.3, m);
    sphs[15] = sph_set(-3.5, 0.3, -2, 0.3, m);
    sphs[16] = sph_set(3.5, 0.3, 2, 0.3, m);
    sphs[17] = sph_set(-3.5, 0.3, 2, 0.3, m);
    sphs[18] = sph_set(2, 0.3, -3.5, 0.3, m);
    sphs[19] = sph_set(-2, 0.3, -3.5, 0.3, m);
    sphs[20] = sph_set(2, 0.3, 3.5, 0.3, m);
    sphs[21] = sph_set(-2, 0.3, 3.5, 0.3, m);

    /* Create the jet black fuzzy metallic spheres */
    vec_set(&abdo, 0.05, 0.05, 0.05);
    mat_set(&m, abdo, 0.1, 0, METAL);
    sphs[22] = sph_set(-3.5, 0.3, 0, 0.3, m);
    sphs[23] = sph_set(0, 0.3, -3.5, 0.3, m);

    /* Create the purple diffuse spheres */
    vec_set(&abdo, 0.5, 0, 0.76);
    mat_set(&m, abdo, 0, 0, DIFFUSE);
    sphs[24] = sph_set(0, 0.3, 3.5, 0.3, m);
    sphs[25] = sph_set(3.5, 0.3, 0, 0.3, m);

    hit_list world;
    list_set(&world, sphs, SPHERES);

    /* Camera setup */
    camera cam;
 
    srand48(time(NULL));

    const char *fext = ".ppm";

    for (int d = 0; d < 360; d++) {
        /* Create Output File */
        char fname[20];
        snprintf(fname, 14, "video/img-%03i", d);
        FILE* fptr = fopen(strcat(fname, fext), "w");

        /* Initial Sanity Check */
        if (fptr == NULL) {
            printf("File couldn't be opened/created!\n");
            exit(EXIT_FAILURE);
        }
        
        vec lf, la, up;
        vec_set(&lf, 16*sin(d * M_PI/180), 8, 16*cos(d * M_PI/180));
        vec_set(&la, 0, 0, 0);   /* Look at */
        vec_set(&up, 0, 1, 0);   /* Vertical */

        float focus = 18.76;
        float aperture = 0.1;

        camera_set(&cam, lf, la, up, 20, ASPECT, aperture, focus);

        /* Image Signature Output: */
        fprintf(fptr, "P3\n%i %i\n255\n", WIDTH, HEIGHT);

        /* Pixel Array Data */
        for(int row  = HEIGHT - 1; row >= 0; row--) {
            for(int column = 0; column < WIDTH; column++) { 
                vec col; /* The colour vector of the pixel */
                vec_set_zero(&col);

                /* The anti-aliasing sample pass - reduces noise in the image */
                for (int sample = 0; sample < SAMPLES; sample++) {
                    /* These values range from 0.0 to 1.0 */
                    float u = (float) (column + drand48()) / (WIDTH - 1);
                    float v = (float) (row + drand48()) / (HEIGHT - 1);

                    ray r = get_ray(&cam, u, v);
                    col = add(col, color(r, &world, 0));
                }

                col = div_c(col, SAMPLES);
                /* Gamma correction - set the gamma value to 2 */
                vec_set(&col, sqrt(col.x), sqrt(col.y), sqrt(col.z));

                /* These values range from 0 to 255 */
                int r = (int) 255.99 * col.x;
                int g = (int) 255.99 * col.y;
                int b = (int) 255.99 * col.z;

                /* Pixel Data */
                fprintf(fptr, "%i %i %i\n", r, g, b);
            }
        }   

        printf("\r%3.2f %% completed", (float) d * 5.0/18.0);
        fflush(stdout);
        fclose(fptr);
    }

    list_free(&world);

    /* Benchmark Result */  
    clock_t end = clock();
    float time_spent = (float) (end - begin)/CLOCKS_PER_SEC;
    FILE *fptr = fopen("tracer-result.txt", "w");
    if (fptr == NULL) {
        printf("Benchmark result couldn't be written!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fptr, "%f", time_spent);
    fclose(fptr);
    return 0;
}

/*----------------------------Function Definitions----------------------------*/
vec color(ray r, hit_list *world, int depth) {
    hit_rec rec;
    if (hit(world, r, 0.001, FLT_MAX, &rec)) {
        ray r_out;
        vec att; 
        if (depth < 50 && scatter(&rec.mat, r, rec, &att, &r_out)) {
            return mul_v(att, color(r_out, world, depth + 1));
        }
        vec res;
        vec_set_zero(&res);
        return res;
    }  
    /* Ray doesn't intersect the sphere - draw the background gradient */
    vec u = unit(r.des);
    float t = 0.5 * (u.y + 1);
    vec a, b;
    vec_set(&a, 1, 1, 1);
    vec_set(&b, 0.5, 0.7, 1);
    return add(mul_c(a, (1.0 - t)), mul_c(b, t)); 
}
