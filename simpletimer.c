#include	<unistd.h>
#include	<sys/time.h>


/*
Simple timer that returns time of day as a double.

Sample timing use:

double start, stop;
...
start = simpletimer();
function_or_code_section_to_be_timed();
stop = simpletimer();
printf("Elapsed time: %f ms\n", stop - start);

*/

double simpletimer(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return (double)tv.tv_sec*1000 + (double)tv.tv_usec * 1E-3;
}


