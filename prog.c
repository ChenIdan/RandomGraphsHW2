#include "RandomGraphs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define VERTICES 1000
#define PROB 0.5
#define EXPERIMENTS 10000

#define Q2_P1 "Q2_P1"
#define Q2_P2 "Q2_P2"
#define Q3_P2 "Q3_P2"

void main(int arc, char *argv[]){
   
   int i,k;

   FILE *file1, *file2, *file3;

   long double average1=0;
   long double average2=0;
   long double results=0;
   
   printf("expected size for the click that will be found by the first heuristic: %Lf\n",  heuristic_expected_click_size(VERTICES)); 
       
   
   file1 = fopen( Q2_P1, "w+");	
   file2 = fopen( Q2_P2, "w+"); 
   file3 = fopen(Q3_P2,"w+");
   
   if(!file1||!file2||!file3){
   	fprintf(stderr,"%s\n","Opening of one of the output files had failed\n");
	exit(1);
   }

   
   srand(time(NULL));
   
   fprintf(file3,"expected size for the click that will be found by the first heuristic: %Lf\n",  heuristic_expected_click_size(VERTICES)); 
   
   fprintf(file1," Experiment with first heuristic, with n = %d and p=%f\n",VERTICES,PROB);
   fprintf(file2,"Experiment with second heuristic, with n = %d and p=%f\n",VERTICES,PROB);
   
   Random_Graph *G= Create_Graph(VERTICES,PROB);
  
   for(i=0;i<EXPERIMENTS;i++){
        init_graph(G);
	
	results = click_size(G);
	average1 = results/EXPERIMENTS +average1;
	fprintf(file1,"results of the %d  experiment with first heuristic: click of size: %Lf \n",i+1,results);


	results = click_size_new_heuristic(G);
	average2 = results/EXPERIMENTS+average2;
	fprintf(file2,"results of the %d  experiment with second heuristic: click of size %Lf \n",i+1, results);
   }

   fprintf(file1,"average click size of first heuristic: %Lf \n", average1);
   fprintf(file2,"average click size of second heuristic: %Lf \n", average2);

   printf("average size of click on the first experiment: %Lf, avrage size of click on the second experiment: %Lf \n", average1,  average2);
}
