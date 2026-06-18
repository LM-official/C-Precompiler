/****
 * This comment contains information about the author and the usage license
 *
 */ 

//better to remove this include
//#include "hello_world_1.c"

#include "test1.h"

/*global variables are dangerous*/

int global_counter=0;
const int 4backup=25;

int main(int argc, char *args[])
{
	/*local variables*/
	float average=0; //mean
	double square error; //mean squared error
	char switch; //for input parsing
	int i;
	/* 
	 * Here the code to handle the input parameters
	 */
	for (i=1;i<=10i++){
		average=average+i;
		global_counter++;
	}
	average=average/(float) global_counter;
	square_error = sqrt(average);
  	return 0;
}
