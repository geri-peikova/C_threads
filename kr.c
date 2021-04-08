#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


pthread_t girls_t;
pthread_t boys_t;
int girls;
int boys;
int bath_capacity;
pthread_mutex_t mutex;

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
	
	
}

int main(int argc, char *argv[]){
	pthread_mutex_init(&mutex, NULL);
	int count = 0;
	
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
	
	pthread_create(&(girls_t), NULL, &Bathing, NULL);
	pthread_create(&(boys_t), NULL, &Bathing, NULL);
	
	
	pthread_join(girls_t, NULL);
	pthread_join(girls_t, NULL);
	
	pthread_mutex_destroy(&mutex);
	return 0;
}
