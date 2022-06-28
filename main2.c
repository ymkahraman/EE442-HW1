#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <semaphore.h>
// YUSUF MERT KAHRAMAN
// 2304830 HW1 PART 2
// Following commands should be used.
// gcc -o main2 main2.c -pthread -lm
// ./main2 -m 40 -g 10
// Each thread has some delay in front of them.
// This is because I dont want to start always producing C atom.
// Since my programme first create Produce_C thread in main function, I create a random delay for all of 4 produce threads.
unsigned int sleeptime = 0;
sem_t C,H,O,N;
sem_t mutex;
double generationRate = 100;
int numberOfC = 0;
int numberOfH = 0;
int numberOfO = 0;
int numberOfN = 0;
int perAtom;
int total = 40; // as default
int instantaneoustotal = 0;
struct atom{
	int atomID;
	char atomTYPE; 
};
double exponential(double lambda){
	double t;
	t = rand() / (RAND_MAX);
	//t = 0.8; // Too see slow, t = 0.8 can be choosen.
	t = 100000*(-log(1-t)/lambda);
	return t;
}
void *Produce_C(){
	usleep(rand()/RAND_MAX);
	while(1){
		int semvalC;
		sem_getvalue(&C,&semvalC);
		if(semvalC == perAtom){
			break;
		}
		sem_wait(&mutex);
		sem_post(&C);
		printf("C with ID:%d is created.\n",instantaneoustotal);
		numberOfC = numberOfC + 1;
		instantaneoustotal = instantaneoustotal + 1;
		sem_post(&mutex);
		sleeptime = 1000 * exponential(generationRate);
		usleep(sleeptime);
	}
}
void *Produce_H(){
	usleep(rand()/RAND_MAX);
	while(1){
		int semvalH;
		sem_getvalue(&H,&semvalH);
		if(semvalH == perAtom){
			break;
		}
		sem_wait(&mutex);
		sem_post(&H);
		printf("H with ID:%d is created.\n",instantaneoustotal);
		numberOfH = numberOfH + 1;
		instantaneoustotal = instantaneoustotal + 1;
		sem_post(&mutex);
		sleeptime = 1000 * exponential(generationRate);
		usleep(sleeptime);
		
	}
}
void *Produce_O(){
	usleep(rand()/RAND_MAX);
	while(1){
		int semvalO;
		sem_getvalue(&O,&semvalO);
		if(semvalO == perAtom){
			break;
		}
		sem_wait(&mutex);
		sem_post(&O);
		printf("O with ID:%d is created.\n",instantaneoustotal);
		numberOfO = numberOfO + 1;
		instantaneoustotal = instantaneoustotal + 1;
		sem_post(&mutex);
		sleeptime = 1000 * exponential(generationRate);
		usleep(sleeptime);
	}
}
void *Produce_N(){
	usleep(rand()/RAND_MAX);
	while(1){
		int semvalN;
		sem_getvalue(&N,&semvalN);
		if(semvalN == perAtom){
			break;
		}
		sem_wait(&mutex);
		sem_post(&N);
		printf("N with ID:%d is created.\n",instantaneoustotal);
		numberOfN = numberOfN + 1;
		instantaneoustotal = instantaneoustotal + 1;
		sem_post(&mutex);
		sleeptime = 1000 * exponential(generationRate);
		usleep(sleeptime);

	}
}
void *Composer_H2O(){
	while(1){
		sem_wait(&mutex);
		if(numberOfH >= 2 && numberOfO >= 1){
			numberOfH = numberOfH - 2;
			numberOfO = numberOfO - 1;
			printf("H2O is generated.\n");
		}
		else{
			if(instantaneoustotal == total){
				sem_post(&mutex);
				break;
			}
		}
		sem_post(&mutex);
	}

}
void *Composer_NO2(){
	while(1){
		sem_wait(&mutex);
		if(numberOfO >= 2 && numberOfN >= 1){
			numberOfO = numberOfO - 2;
			numberOfN = numberOfN - 1;
			printf("NO2 is generated.\n");
		}
		else{
			if(instantaneoustotal == total){
				sem_post(&mutex);
				break;
			}
		}
		sem_post(&mutex);
	}
}
void *Composer_CO2(){
	while(1){
		sem_wait(&mutex);
		if(numberOfO >= 2 && numberOfC >= 1){
			numberOfO = numberOfO - 2;
			numberOfC = numberOfC - 1;
			printf("CO2 is generated.\n");
		}
		else{
			if(instantaneoustotal == total){
				sem_post(&mutex);
				break;
			}
		}
		sem_post(&mutex);
	}

}
void *Composer_NH3(){
	while(1){
		sem_wait(&mutex);
		if(numberOfN >= 1 && numberOfH >= 3){
			numberOfH = numberOfH - 3;
			numberOfN = numberOfN - 1;
			printf("NH3 is generated.\n");
		}
		else{
			if(instantaneoustotal == total){
				sem_post(&mutex);
				break;
			}
		}
		sem_post(&mutex);
	}

}
int main(int argc, char *argv[]) {
	pthread_t generationThreads[4]; // tubethread ismi.
	pthread_t consumerThreads[4];
	int opt;
	while((opt = getopt(argc,argv,"m:g:")) != -1){
		switch(opt){
			case 'm':
				total = atoi(optarg);
				break;
			case 'g':
				generationRate = atof(optarg);
				break;
		}
	}
	perAtom = total / 4;
	//struct atom atoms[m];
	//struct atom *atomptr = atoms;
	sleeptime = exponential(generationRate);
	printf("Generation Rate: %f\n",generationRate);
	printf("Number Of atoms to be pruced: %d.\n",total);
	srand(time(NULL));
	sem_init(&C,perAtom,0);
	sem_init(&H,perAtom,0);
	sem_init(&O,perAtom,0);
	sem_init(&N,perAtom,0);
	sem_init(&mutex,0,1);
	// Belows for consumer threads.
	if(pthread_create(&consumerThreads[0],NULL,&Composer_H2O,NULL) != 0){
		return 1;
	}
	if(pthread_create(&consumerThreads[1],NULL,&Composer_CO2,NULL) != 0){
		return 1;
	}
	if(pthread_create(&consumerThreads[2],NULL,&Composer_NO2,NULL) != 0){
		return 1;
	}
	if(pthread_create(&consumerThreads[3],NULL,&Composer_NH3,NULL) != 0){
		return 1;
	}
	// Belows are produce threads.
	if(pthread_create(&generationThreads[0],NULL,&Produce_C,NULL) != 0){
		return 1;
	}
	if(pthread_create(&generationThreads[1],NULL,&Produce_H,NULL) != 0){
		return 1;
	}
	if(pthread_create(&generationThreads[2],NULL,&Produce_O,NULL) != 0){
		return 1;
	}
	if(pthread_create(&generationThreads[3],NULL,&Produce_N,NULL) != 0){
		return 1;
	}

	for(int i = 0; i < 4 ; i++){
		if (pthread_join(generationThreads[i], NULL) != 0){
			return 2; // Indicates an error.
		}
	}
	for(int i = 0; i < 4 ; i++){
		if (pthread_join(consumerThreads[i], NULL) != 0){
			return 2; // Indicates an error.
		}
	}
	
   	return 0;
}

