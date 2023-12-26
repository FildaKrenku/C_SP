#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * op_add
 */
float op_add(float x, float y){
	return x + y;
}
/**
 * op_sub
 */
float op_sub(float x, float y){
	return x - y;
}
/**
 * op_mul
 */
float op_mul(float x, float y){
	return x * y;
}
/**  fe
 * op_div
 */
float op_div(float x, float y){
	return y ? x / y : NAN;
}
/**
 * op_err
 */
float op_err(float x, float y){
	printf("error\n");
	return 0;
}

/**
 * main
 */
int main(){
	float x, y, (*op_gen[]) (float, float) = { op_mul, op_add, op_err, op_sub, op_err, op_div};
	char op;
	int r;
	
	do{
		r = scanf("%f %c %f", &x, &op, &y);
		
		/*
		switch(op){
			case '+': op_gen = op_add; break;
			case '-': op_gen = op_sub; break;
			case '*': op_gen = op_mul; break;
			case '/': op_gen = op_div; break;
			default: op_gen = op_err;
		}
		*/
		
		printf("%f %c %f = %f\n", x, op, y,  op_gen[op >= '*' && op <= '/' ? op - '*' : 2](x, y));
		
		
	} while(r == 3);
	
	
	
	return EXIT_SUCCESS;
}
