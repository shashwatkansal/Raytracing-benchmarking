#include "vec.h"

void print_vector(vec v) {
	printf("x: %6.4f y: %6.4f z: %6.4f\n", get_x(v), get_y(v), get_z(v));
}

int main(void) {
	vec a, b, c;
	
	// TEST: (Initialisation)
	printf("TEST: (Intialisation)\n");
	vec_init_zero(&a);
	printf("  a - "); print_vector(a);
	vec_init(&b, 1, 1, 1);
	printf("  b - "); print_vector(b);
	vec_init(&c, 2, 3, 5);
	printf("  c - "); print_vector(c);

	// TEST: (Unary Operations)
	printf("TEST: (Unary Operations)\n");
	printf("  Identity: \n");
       	printf("    a - "); print_vector(identity(a));
	printf("    b - "); print_vector(identity(b));
	printf("    c - "); print_vector(identity(c));
	printf("  Negate: \n");
       	printf("    a - "); print_vector(negate(a));
	printf("    b - "); print_vector(negate(b));
	printf("    c - "); print_vector(negate(c));
	printf("  Length: \n");
       	printf("    a - "); printf("%6.4f\n", length(a));
	printf("    b - "); printf("%6.4f\n", length(b));
	printf("    c - "); printf("%6.4f\n", length(c));
	printf("  Squared Length: \n");
       	printf("    a - "); printf("%6.4f\n", squared_length(a));
	printf("    b - "); printf("%6.4f\n", squared_length(b));
	printf("    c - "); printf("%6.4f\n", squared_length(c));
	printf("  Unit Vector: \n");
       	printf("    a - "); print_vector(unit_vector(a));
	printf("    b - "); print_vector(unit_vector(b));
	printf("    c - "); print_vector(unit_vector(c));
	
	// TEST: (Binary Operations)
	printf("TEST: (Binary Operations)\n");
	printf("  Add: \n");
       	printf("    a + b - "); print_vector(add(a, b));
	printf("    b + c - "); print_vector(add(b, c));
	printf("    c + a - "); print_vector(add(c, a));
	printf("  Subtract: \n");
       	printf("    a - b - "); print_vector(subtract(a, b));
	printf("    b - c - "); print_vector(subtract(b, c));
	printf("    c - a - "); print_vector(subtract(c, a));
	printf("  Multiply: \n");
       	printf("    a * b - "); print_vector(multiply(a, b));
	printf("    b * c - "); print_vector(multiply(b, c));
	printf("    c * a - "); print_vector(multiply(c, a));
	printf("  Multiply (Constant): \n");
       	printf("    a * 5 - "); print_vector(multiply_const(a, 5));
	printf("    b * 5 - "); print_vector(multiply_const(b, 5));
	printf("    c * 5 - "); print_vector(multiply_const(c, 5));
	printf("  Divide: \n");
       	printf("    a / b - "); print_vector(divide(a, b));
	printf("    b / c - "); print_vector(divide(b, c));
	printf("    c / a - "); print_vector(divide(c, a));
	printf("  Divide (Constant): \n");
       	printf("    a / 5 - "); print_vector(divide_const(a, 5));
	printf("    b / 5 - "); print_vector(divide_const(b, 5));
	printf("    c / 5 - "); print_vector(divide_const(c, 5));
	
	// TEST: (Special Binary Operations)
	printf("TEST: (Special Binary Operations)\n");
	printf("  Dot Product: \n");
       	printf("    a . b - "); printf("%6.4f\n", dot_product(a, b));
	printf("    b . c - "); printf("%6.4f\n", dot_product(b, c));
	printf("    c . a - "); printf("%6.4f\n", dot_product(c, a));
	printf("  Cross Product: \n");
       	printf("    a x b - "); print_vector(cross_product(a, b));
	printf("    b x c - "); print_vector(cross_product(b, c));
	printf("    c x a - "); print_vector(cross_product(c, a));
	
	return 0;
}
