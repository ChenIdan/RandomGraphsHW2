#include "RandomGraphs.h"
#include "random.h"


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 

#define MAX_VERTICES 1000000 /*maximum number of verticex */ 
#define PRECISION 10000000 /*precision of bernouli experiment*/


long double click_prob[2000][2000];

bool is_click(bool *click, Random_Graph *G);
int largest(int verticesay[], int n);
void quickSort(int vertices[],int degrees[], int low, int high);
float click_prob1(unsigned int n, unsigned int k);
float click_prob2(unsigned int n, unsigned int k);




int Binomial_Coefficient(unsigned long int n, unsigned long int k){
	return n*(n-1)/2 ;
}
Random_Graph* Create_Graph(int n, double p){
	 int i,j;
	 Random_Graph* G= malloc(sizeof(Random_Graph));
	 if(!G){
	 	fprintf(stderr,"Allocation of random graph failed\n");
		return NULL;
	 }
         if(n>MAX_VERTICES){
	        fprintf(stderr,"Number of requiered vertices in random graphs is: %d, and the maximum number of vertices is :%d\n", n,MAX_VERTICES);
	        return NULL;
	  }
	  bool **edges= malloc(n*sizeof(bool*));
	  if (!edges){
	  	fprintf(stderr,"Failed in allocating random graph\n");
		return NULL;
	  }

	  
	  for(i=0; i<n;i++){
		edges[i] = malloc(n*sizeof(bool));
		if(!edges[i]){
		    fprintf(stderr,"Failed in allocating random graph\n");
		    return NULL;
		}
	  }
          G->n = n;
	  G->edges = edges;
	  G->p = p;
	  G->e = 0;
	  G->initialized = false;
	  return G;
}
void init_graph(Random_Graph* G){
	int e=0; //counter for the number of edges
	if(!G){
	  printf("G in init_graph is not initialized\n");
	  exit(0);
	}
	bool **edges=G->edges;
        int i,j;
	float p = G->p;
	long int n=G->n;
	 for(i=0;i<n;i++){	
	  	for(j=0;j<i;j++){
		     if(edges[i][j] = Bernoulli(p,PRECISION)){
		         e++;
		     }

		     edges[j][i] = edges[i][j];

		}
	  }

	 G->e = e;
	 G->initialized = true;

}



int click_size(Random_Graph *G){
	int n=G->n;
	int vertices[n];
	bool click[n];
	bool** edges= G->edges;
	int i,j;
	int click_size =n;
	
	for(i=0;i<n;i++){
	       vertices[i]= i;
	       click[i]=true;
	}
        shuffle(vertices,n);
        for (i=0;i<n;i++){
             if(click[vertices[i]]==true){
                for(j=i+1;j<n;j++){
		  if(click[vertices[j]]==true){
		           click[vertices[j]] =edges[vertices[i]][vertices[j]];
		           if(click[vertices[j]]==false){	   
			   	click_size--;
			   }
                         
		        
	
              }

                }
	}

          
	}

	assert(is_click(click,G)==true);

         
	
	return click_size;
}

void print_graph(Random_Graph *G){

	int i,j,n;
	printf("Probability:%f \n", G->p);
	printf("Number of vertices:%lu\n", G->n);

	printf("Number_of_edges : %lu\n", G->e);
	
	bool **edges = G->edges;

        n=G->n;

	for(i=0;i<n;i++){	
		for(j=0;j<i;j++){
   		        if(edges[i][j]){
			    printf("(%d,%d)",i+1,j+1); 
			
			}
			assert(edges[i][j]==edges[j][i]);

		    }
	
		}


	
}
int largest(int vertices[], int n)
{
    int i;

    // Initialize maximum element
    int max = 0;

    // Traverse verticesay elements from second and
    // compare every element with current max
    for (i = 0; i < n; i++)
        if (vertices[i] > vertices[max])
            max = i;

    return max;
}

int choose(int n, int k){
    if (k == 0){
            return 1;
    }
    return (n * choose(n - 1, k - 1)) / k;
}


float click_prob2(unsigned int n, unsigned int k){

        if(n<k){
            return 0;
        }

	if(k==n){
	         return  pow(0.5,(n*(n-1)/2));
	}

        else{
                double prob =0;
                double p = pow(0.5,n-1);
                return (p*click_prob2(n-1,k-1) + (1-p)*click_prob2(n-1,k));
                return prob;
        }
}

//dynamic programming version
void click_prob_dynamic(int n){
        int i,j,cur;
        /*
	for(i=0;i<n+1;i++){
		for(j=0;j<n+1;j++){
			click_prob[i][j]=0;
		}
	}*/

	for (i=0;i<n+1;i++){
               click_prob[i][i] = pow(0.5,i*(i-1)/2);
        }

	for(i=1;i<n+1;i++){
	     double p = pow(0.5,i-1);
	     for(j=1;j<i;j++){
	        for (int v = j-1;v<i;v++){
			click_prob[i][j] = click_prob[i][j] + choose(i-1,v)*click_prob[v][j-1];
		}
		click_prob[i][j]=p*click_prob[i][j];
		
	     
	     }
	          
	     
	   
	}

}

float click_prob1(unsigned int n, unsigned int k){

        if(n<k){
            return 0;
        }

        else if(k==n){
            return pow(0.5,(n*(n-1)/2));
        }

        else{
                double prob =0;
                double p = pow(0.5,n-1);

		for(int v=k-1;v<n;v++){
		      	prob = prob + choose(n-1,v)*click_prob1(v,k-1);
			
		}
                return p*prob;
        }
}



long double  heuristic_expected_click_size3(int n){
      int  k;
     
      long double expected_size =0;
      click_prob_dynamic(n);

      for (k=1;k<n+1;k++){
            expected_size = expected_size + ((double)k)*click_prob[n][k];
      }

      return expected_size;



}


float heuristic_expected_click_size2(int n){
      int k;

      float expected_size =0;

      for (k=1;k<n+1;k++){
            expected_size = expected_size + k*click_prob2(n,k);
      }

      return expected_size;



}


float heuristic_expected_click_size(int n){
      int k;

      float expected_size =0;

      for (k=1;k<n+1;k++){
            expected_size = expected_size + k*click_prob1(n,k);
      }

      return expected_size;



}


/*probability for the heuristic finding a click of size k in G(n,0.5) graph  according to the recursive relation found in assigmnet 2 Q2 */


int* vertex_degrees(Random_Graph *G){
       int i,j;
       int n = G->n;
       bool **edges = G->edges;
       int *vertex_degrees= malloc(n*sizeof(int));
       int max=0;
       
       for (i=0;i<n;i++){
	     vertex_degrees[i] = 0;  
             for(j=0;j<i;j++){
	          if(edges[i][j]){
		      vertex_degrees[i]++;
		      vertex_degrees[j]++;
		  }
	     }

       
       }
       return vertex_degrees;

}

int click_size_new_heuristic(Random_Graph *G){
        int n=G->n;
	int vertices[n];
        bool click[n];
        bool** edges= G->edges;
        int i,j;
        int click_size =n;
	

	int *vertices_degrees=vertex_degrees(G);
        
	

        for(i=0;i<n;i++){
               vertices[i]= i;
	       click[i]=true;
	       
        }
	quickSort(vertices,vertices_degrees,0,n-1);
          for (i=0;i<n;i++){
             if(click[vertices[i]]){
                for(j=i+1;j<n;j++){
		   if(click[vertices[j]]){
			click[vertices[j]] = click[vertices[j]] && edges[vertices[i]][vertices[j]];
                        if(click[vertices[j]]==false){
                         	 click_size--;
			}


                   }
                    
                   }

                }
        }
	assert(is_click(click,G)==true);
        return click_size;
}

bool is_click(bool *click,Random_Graph *G ){
  	int i,j;
	int n = G->n;
	bool **edges = G->edges;
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			if(click[i]&click[j]&&!edges[i][j]){
				return false;
			}
		}
	}
	return true;
}

static void swap(int vertices[], int degrees[], int i,int j){
        int tmp_vertex = vertices[i];

        int tmp_degree = degrees[i];

        vertices[i] = vertices[j];
        degrees[i]=degrees[j];

        vertices[j]=tmp_vertex;
        degrees[j]=tmp_degree;

}


int partition (int vertices[],int degrees[], int low, int high) 
{ 
    int pivot = degrees[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (degrees[j] > pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(vertices, degrees,i,j);
        } 
    } 
    swap(vertices, degrees, high, i+1);
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 vertices[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int vertices[],int degrees[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, vertices[p] is now 
           at right place */
        int pi = partition(vertices, degrees,low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(vertices, degrees,low, pi - 1); 
        quickSort(vertices,degrees, pi + 1, high); 
    } 
} 


