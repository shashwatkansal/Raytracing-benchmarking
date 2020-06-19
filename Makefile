ppm: ppm.c vec.c ray.c hitlist.c sphere.c camera.c material.c
	gcc -Wall -g ppm.c vec.c ray.c hitlist.c sphere.c camera.c material.c -o ppm -lm

vec-test: vec-test.c vec.c
	gcc -Wall -pedantic -o vec-test vec-test.c vec.c -lm


