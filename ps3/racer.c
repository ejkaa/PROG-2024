#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct racer
{
  int s;
  int v;
};

int main (){
    int n, time1;
    scanf ("%d %d", &n, &time1);

    struct racer list[n];

    for (int i = 0; i < n; i++){
      scanf ("%d %d", &list[i].s, &list[i].v);
    }


    double max = 2000000;
    double min = 1000000;
    for (int i = 0; i < n; i++){
        if (list[i].v < min)
	    min = list[i].v;
    }
	min = -min;
    // printf("%lf\n", min);


	double k = (max + min) / 2;
    // printf ("%f\n", k);


  	double time_sum = 0;
  	while (max >= min){
      	time_sum = 0.0;
      	for (int i = 0; i < n; i++){
	    	time_sum += (double)(list[i].s) / (double)(list[i].v + (k));
		}

        if (time_sum == time1 || (fabs(max - min)  < 0.0000001)){
    // 	  printf ("%f %.6lf\n", time_sum, k);
    	  break;
	    }
	    
        else if (time_sum > time1){
    	  min = k;
    	  k = (max + min) / 2;
    // 	  printf ("%f %f\n", time_sum, k);
	    }
	    
        else{
	        max = k;
	        k = (max + min)/2;
	    }
    }

    printf("%.6f\n", k);

  return 0;
}