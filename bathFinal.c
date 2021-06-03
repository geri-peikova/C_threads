
//  size kr
//   text	   data	    bss	    dec	    hex	filename
//   3923	    688	    104	   4715	   126b	kr







#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


pthread_t bath_t;
pthread_t addB_t;
pthread_t addG_t;
int girls;
int boys;
int bath_capacity;
int end;
pthread_mutex_t mutex;

void* addGirls(){

	for(int i = 0; i <= 4; i++){
		pthread_mutex_lock(&mutex);
		girls++;
		printf("\n 1 Girl added to queue!\n");
				
		pthread_mutex_unlock(&mutex);sleep(2);
	}
	
	
}

void* addBoys(){
	for(int i = 0; i <= 4; i++){
		pthread_mutex_lock(&mutex);
		boys++;
		printf("\n 1 Boy added to queue!\n");		
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	
	
	
}

void* Bathing(){
	int last;

	while((girls+boys) > 0){
		if(girls > boys){
			last = 0;
			pthread_mutex_lock(&mutex);
				if(girls >= bath_capacity) girls = girls-bath_capacity;
				else if(girls > 0) girls = 0;
				sleep(1);
			pthread_mutex_unlock(&mutex);
			printf("Girls in bathroom!\n");
			printf("Girls left: %d\n", girls);
			printf("Boys left: %d\n\n", boys);
		}else if(boys > girls){
			last = 1;
			pthread_mutex_lock(&mutex);
				if(boys >= bath_capacity) boys = boys-bath_capacity;
				else if(boys > 0) boys = 0;
				sleep(1);
			pthread_mutex_unlock(&mutex);
			printf("Boys in bathroom!\n");
			printf("Girls left: %d\n", girls);
			printf("Boys left: %d\n\n", boys);
		}else{
			if(last == 0){
				pthread_mutex_lock(&mutex);
				if(girls >= bath_capacity) girls = girls-bath_capacity;
				else if(girls > 0) girls = 0;
				sleep(1);
				pthread_mutex_unlock(&mutex);
				printf("Girls in bathroom!\n");
				printf("Girls left: %d\n", girls);
				printf("Boys left: %d\n\n", boys);
			}else{
				pthread_mutex_lock(&mutex);
				if(boys >= bath_capacity) boys = boys-bath_capacity;
				else if(boys > 0) boys = 0;
				sleep(1);
				pthread_mutex_unlock(&mutex);
				printf("Boys in bathroom!\n");
				printf("Girls left: %d\n", girls);
				printf("Boys left: %d\n\n", boys);
			}
		}
	
	}
	printf("Everybody are clean!\n");
	end = 1;
	
}

int main(int argc, char *argv[]){
	pthread_mutex_init(&mutex, NULL);
	int count = 0;
	end = 0;
	
	printf("Girls: ");
	scanf("%d", &girls);
	
	printf("Boys: ");
	scanf("%d", &boys);
	count = girls + boys;
	
	printf("Bath Capacity: ");
	scanf("%d", &bath_capacity);
		
	while(count <= bath_capacity){
		printf("Girls and boys must be more than bath capacity! \n");
	
		printf("Girls: ");
		scanf("%d", &girls);
	
		printf("Boys: ");
		scanf("%d", &boys);
		count = girls + boys;
		printf("Bath Capacity: ");
		scanf("%d", &bath_capacity);
	}
	
		pthread_create(&(addB_t), NULL, &addBoys, NULL);
		pthread_create(&(addG_t), NULL, &addGirls, NULL);
		pthread_create(&(bath_t), NULL, &Bathing, NULL);
			

		pthread_join(addG_t, NULL);
		pthread_join(addB_t, NULL);
		pthread_join(bath_t, NULL);	
		
		if(girls + boys > 0){
			pthread_create(&(bath_t), NULL, &Bathing, NULL);
			pthread_join(bath_t, NULL);
		}
			
	
	pthread_mutex_destroy(&mutex);
	return 0;
}
