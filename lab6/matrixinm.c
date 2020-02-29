#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 

void* mult(void* arg)
{ 
	int *data = (int *)arg; 
	int k = 0, i = 0; 
	
	int x = data[0]; 
	for (i = 1; i <= x; i++) 
		k += data[i]*data[i+x]; 
	
	int* p = (int*)malloc(sizeof(int));
		*p = k; 
	
	pthread_exit(p); 
} 

int main() 
{ 
	int r1, r2, c1, c2;
	scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
	
	if(r2 != c1)
	{
		printf("Matricile nu pot fi inmultite!");
		return 0;
	}
	
	int a[r1][c1]; 
	int b[r2][c2]; 
	int c[r1][c2];
	
	int i,j,k; 

	for (i = 0; i < r1; i++) 
			for (j = 0; j < c1; j++) 
				scanf("%d", &a[i][j]);

	for (i = 0; i < r1; i++) 
			for (j = 0; j < c1; j++) 
				scanf("%d", &b[i][j]);
	
	int max = r1*c2; 
	
	pthread_t *threads; 
	threads = (pthread_t*)malloc(max*sizeof(pthread_t)); 
	
	int count = 0; 
	int* data = NULL; 
	for (i = 0; i < r1; i++) 
	{
		for (j = 0; j < c2; j++) 
		{ 
		data = (int *)malloc((r1+c2+1)*sizeof(int)); 
		data[0] = c1; 
	
		for (k = 0; k < c1; k++) 
			data[k+1] = a[i][k]; 
	
		for (k = 0; k < r2; k++) 
			data[k+c1+1] = b[k][j]; 
			
		pthread_create(&threads[count++], NULL, mult, (void*)(data)); 
		} 
	}
	int indicei = 0, indicej = 0;
	printf("Inmultirea rezultata: \n"); 
	for (i = 0; i < max; i++) 
	{ 
		void *k; 
		pthread_join(threads[i], &k); 
	
		c[indicei][indicej] = *((int*)k);
		indicej++;
		if ((i + 1) % c2 == 0) 
		{
			indicei++;
			indicej=0;
		}
	} 
	for(int i=0; i<r1; i++)
	{
		for(int j=0; j<c2; j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}

return 0; 
}
