#include "RandomGraphs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(int arc, char *argv[]){
   
   int n,k;
   float p;
   int num_of_experiments;
   printf("insert the number of vertices:");
   scanf("%d",&n);

   printf("insert the probability for an edge:");
   scanf("%f",&p);

   printf("insert number of experminent:");
   scanf("%d", &num_of_experiments);
   printf("expected size for the click that will be found by the first heuristic: %Lf\n",  heuristic_expected_click_size(n)); 

   if(!argv[1]){
	   exit(1);
   }
   if(!argv[2]){
          exit(1);
   }
   FILE *file1 = fopen(argv[1],"w+");
   FILE *file2=fopen(argv[2],"w+");
   int i;
   long double average1=0;
   long double average2=0;
   long double results=0;
   srand(time(NULL));
   fprintf(file1," Experiment with first heuristic, with n = %d and p=%f\n",n,p);
   fprintf(file2,"Experiment with second heuristic, with n = %d and p=%f\n",n,p);
   Random_Graph *G= Create_Graph(n,p);
  
   for(i=0;i<num_of_experiments;i++){
        init_graph(G);
	
	results = click_size(G);
	average1 = results/num_of_experiments +average1;
	fprintf(file1,"results of the %d  experiment with first heuristic: click of size: %Lf \n",i+1,results);


	results = click_size_new_heuristic(G);
	average2 = results/num_of_experiments+average2;
	fprintf(file2,"results of the %d  experiment with second heuristic: click of size %Lf \n",i+1, results);

   }

   fprintf(file1,"average click size of first heuristic: %Lf \n", average1);
   fprintf(file2,"average click size of second heuristic: %Lf \n", average2);


   
   printf("average size of click on the first experiment: %Lf, avrage size of click on the second experiment: %Lf \n", average1,  average2);
}
