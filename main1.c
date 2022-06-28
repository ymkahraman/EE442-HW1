#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
// YUSUF MERT KAHRAMAN
// 230430 HW1 PART 1
// Following commands should be used.
// gcc -o main1 main1.c -pthread -lm
// ./main1 -c 5 -h 6 -o 6 -n 7 -g 100
pthread_mutex_t mutex;
int counter = 0;
int totalAtoms;
int remainingAtoms;
int lookup = 0;
int tubenumber = 1;
int updatedorNot;
struct atom{
	int atomID;
	char atomTYPE; 
};
struct tube{
    int tubeID;
    int tubeTS;
    int moleculeTYPE;
};
struct Information{
    int tubeID;
    struct tube mytube;
};
// The exponential distribtion is taken from
double exponential(double lambda){
	double t;
	t = 0.8; // I choose it as 0.8
	t = 100000*-log(1-t)/lambda;
	return t;
}
// Below function is for funding the suitable tube for the element.
// This is a bit long since it includes all cases. (TS, moleculeTYPES ...)
// There are 8 case for tube combinations. (From 000 to 111).
// Therefore, there are 8 if-elseif blocks mainly.
int ThreeTubeNotEmpty(struct atom *atoms, struct atom element);
struct tube tube1,tube2,tube3;
void *tubeth(void *atomptr){
    tube1.tubeID = 1;
    tube2.tubeID = 2;
    tube3.tubeID = 3;
    tube1.moleculeTYPE = 0;
    tube1.moleculeTYPE = 0;
    tube1.moleculeTYPE = 0;
    tube1.tubeTS = 0;
    tube2.tubeTS = 0;
    tube3.tubeTS = 0;
    struct atom *ptr = (struct atom *)atomptr;
    int prevcounter = 0;
    int tube1counter = 0,tube2counter = 0,tube3counter = 0;
    while(!counter); // If counter is equal to 0 -> Just wait to fulfill.
    while(counter != totalAtoms){
        if((counter - prevcounter) && (counter != totalAtoms)){
            pthread_mutex_lock(&mutex);
            //printf("Tube Number: %d\n",tubenumber);
            prevcounter = counter;
            lookup = counter;
            //printf("%c with ID: %d is created.\n",ptr[counter-1].atomTYPE,ptr[counter-1].atomID);
            if(tubenumber == 1){
            	tube1counter = tube1counter + 1;
            	if(tube1.moleculeTYPE == 1 || tube1.moleculeTYPE == 2 || tube1.moleculeTYPE == 3){
            		if(tube1counter == 3){
            			switch(tube1.moleculeTYPE){
            				case 1:
            					printf("H2O is created in Tube1.\n");
            					break;
            				case 2:
            					printf("CO2 is created in Tube1.\n");
            					break;
            				case 3:
            					printf("NO2 is created in Tube1.\n");
            					break;
            			}
            			tube1.tubeTS = 0;
            			tube1counter = 0;
            			tube1.moleculeTYPE = 0;
            		}
            	}
            	else if(tube1.moleculeTYPE == 4){
            		if(tube1counter == 4){
            			printf("NH3 is created in Tube1.\n");
            			tube1.tubeTS = 0;
            			tube1counter = 0;
            			tube1.moleculeTYPE = 0;
            		}
            	}
            }
            else if(tubenumber == 2){
            	tube2counter = tube2counter + 1;
            	if(tube2.moleculeTYPE == 1 || tube2.moleculeTYPE == 2 || tube2.moleculeTYPE == 3){
            		if(tube2counter == 3){
            			switch(tube2.moleculeTYPE){
            				case 1:
            					printf("H2O is created in Tube2.\n");
            					break;
            				case 2:
            					printf("CO2 is created in Tube2.\n");
            					break;
            				case 3:
            					printf("NO2 is created in Tube2.\n");
            					break;
            			}
            			tube2.tubeTS = 0;
            			tube2counter = 0;
            			tube2.moleculeTYPE = 0;
            		}
            	}
            	else if(tube2.moleculeTYPE == 4){
            		if(tube2counter == 4){
            			printf("NH3 is created in Tube2.\n");
            			tube2.tubeTS = 0;
            			tube2counter = 0;
            			tube2.moleculeTYPE = 0;
            		}
            	}
            }
            else if(tubenumber == 3){
            tube3counter = tube3counter + 1;
            	if(tube3.moleculeTYPE == 1 || tube3.moleculeTYPE == 2 || tube3.moleculeTYPE == 3){
            		if(tube3counter == 3){
            			switch(tube3.moleculeTYPE){
            				case 1:
            					printf("H2O is created in Tube3.\n");
            					break;
            				case 2:
            					printf("CO2 is created in Tube3.\n");
            					break;
            				case 3:
            					printf("NO2 is created in Tube3.\n");
            					break;
            			}
            			tube3.tubeTS = 0;
            			tube3counter = 0;
            			tube3.moleculeTYPE = 0;
            		}
            	}
            	else if(tube3.moleculeTYPE == 4){
            		if(tube3counter == 4){
            			printf("NH3 is created in Tube3.\n");
            			tube3.tubeTS = 0;
            			tube3counter = 0;
            			tube3.moleculeTYPE = 0;
            		}
            	}
            }
            //printf("Tube1TS: %d Tube2TS: %d Tube3TS: %d\n",tube1.tubeTS,tube2.tubeTS,tube3.tubeTS);
            //printf("MT1: %d MT2: %d MT3: %d\n",tube1.moleculeTYPE,tube2.moleculeTYPE,tube3.moleculeTYPE);
            //printf("Tube1:%d Tube2:%d Tube3:%d\n",tube1counter,tube2counter,tube3counter);
            pthread_mutex_unlock(&mutex);
        }
    }
}

int findSuitableTube(struct atom *atoms,struct atom element){
    if(tube1.tubeTS == 0 && tube2.tubeTS == 0 && tube3.tubeTS == 0){
    	// No elements in tubes. Put first empty tube.
    	tube1.tubeTS = element.atomID;
    	return 1;
    }
    else{
        // There are at least one not empty tube.
        // Check the TS smallest one.
        if(tube1.tubeTS != 0 && tube2.tubeTS == 0 && tube3.tubeTS == 0){
            // Tube 1 is not empty but tube 2 and 3 are empty.
            if(tube1.moleculeTYPE == 0){
                if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                    if(element.atomTYPE == 'O'){
                        tube1.moleculeTYPE = 2;
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2; // Put it to second tube.
                    }
                }
                else if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                    if(element.atomTYPE == 'O'){
                        tube1.moleculeTYPE = 1;
                        return 1;
                    }
                    else if(element.atomTYPE == 'N'){
                        tube1.moleculeTYPE = 4;
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
                else if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                    if(element.atomTYPE == 'C'){
                        tube1.moleculeTYPE = 2;
                        return 1;
                    }
                    else if(element.atomTYPE == 'N'){
                        tube1.moleculeTYPE = 3;
                        return 1;
                    }
                    else if(element.atomTYPE == 'H'){
                        tube1.moleculeTYPE = 1;
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                    if(element.atomTYPE == 'H'){
                        tube1.moleculeTYPE = 4;
                        return 1;
                    }
                    else if(element.atomTYPE == 'O'){
                        tube1.moleculeTYPE = 3;
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
            }
            else{
                if(tube1.moleculeTYPE == 1){
                    // Hidrogen gelmisse yolla.
                    if(element.atomTYPE == 'H'){
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
                else if(tube1.moleculeTYPE == 2){
                    if(element.atomTYPE == 'O'){
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
                else if(tube1.moleculeTYPE == 3){
                    if(element.atomTYPE == 'O'){
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
                else if(tube1.moleculeTYPE == 4){
                    if(element.atomTYPE == 'H'){
                        return 1;
                    }
                    else{
                        tube2.tubeTS = element.atomID;
                        return 2;
                    }
                }
            }
        }
        else if(tube1.tubeTS == 0 && tube2.tubeTS != 0 && tube3.tubeTS == 0){
            // Tube 1 and 3 are empty but 2 is not.
            if(tube2.moleculeTYPE == 0){
                
                if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                    if(element.atomTYPE == 'O'){
                        tube2.moleculeTYPE = 2;
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1; // Put it to first tube.
                    }
                }
                else if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                    if(element.atomTYPE == 'O'){
                        tube2.moleculeTYPE = 1;
                        return 2;
                    }
                    else if(element.atomTYPE == 'N'){
                        tube2.moleculeTYPE = 4;
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                    if(element.atomTYPE == 'C'){
                        tube2.moleculeTYPE = 2;
                        return 2;
                    }
                    else if(element.atomTYPE == 'N'){
                        tube2.moleculeTYPE = 3;
                        return 2;
                    }
                    else if(element.atomTYPE == 'H'){
                        tube2.moleculeTYPE = 1;
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                    if(element.atomTYPE == 'H'){
                        tube2.moleculeTYPE = 4;
                        return 2;
                    }
                    else if(element.atomTYPE == 'O'){
                        tube2.moleculeTYPE = 3;
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
            } 
            else{
                // molecule type of 2 is already found.
                if(tube2.moleculeTYPE == 1){
                    // Hidrogen gelmisse yolla.
                    if(element.atomTYPE == 'H'){
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(tube2.moleculeTYPE == 2){
                    if(element.atomTYPE == 'O'){
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(tube2.moleculeTYPE == 3){
                    if(element.atomTYPE == 'O'){
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(tube2.moleculeTYPE == 4){
                    if(element.atomTYPE == 'H'){
                        return 2;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
            }    
    }
        else if(tube1.tubeTS == 0 && tube2.tubeTS == 0 && tube3.tubeTS != 0){
            if(tube3.moleculeTYPE == 0){
                
                if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                    if(element.atomTYPE == 'O'){
                        tube3.moleculeTYPE = 2;
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1; // Put it to first tube.
                    }
                }
                else if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                    if(element.atomTYPE == 'O'){
                        tube3.moleculeTYPE = 1;
                        return 3;
                    }
                    else if(element.atomTYPE == 'N'){
                        tube3.moleculeTYPE = 4;
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                    if(element.atomTYPE == 'C'){
                        tube3.moleculeTYPE = 2;
                        return 3;
                    }
                    else if(element.atomTYPE == 'N'){
                        tube3.moleculeTYPE = 3;
                        return 3;
                    }
                    else if(element.atomTYPE == 'H'){
                        tube3.moleculeTYPE = 1;
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                    if(element.atomTYPE == 'H'){
                        tube3.moleculeTYPE = 4;
                        return 3;
                    }
                    else if(element.atomTYPE == 'O'){
                        tube3.moleculeTYPE = 3;
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                
            }
            else{
                
                if(tube3.moleculeTYPE == 1){
                    // Hidrogen gelmisse yolla.
                    if(element.atomTYPE == 'H'){
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(tube3.moleculeTYPE == 2){
                    if(element.atomTYPE == 'O'){
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(tube3.moleculeTYPE == 3){
                    if(element.atomTYPE == 'O'){
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                else if(tube3.moleculeTYPE == 4){
                    if(element.atomTYPE == 'H'){
                        return 3;
                    }
                    else{
                        tube1.tubeTS = element.atomID;
                        return 1;
                    }
                }
                
            }
        }
        
        else if(tube1.tubeTS != 0 && tube2.tubeTS != 0 && tube3.tubeTS == 0){
            // Tube one and two is not empty.
            if(tube1.tubeTS < tube2.tubeTS){
                // Önce Tube 1 Sonra Tube 2 check edilecek.
                if(tube1.moleculeTYPE == 0){
                    
                    if(element.atomTYPE == 'C'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            tube1.moleculeTYPE = 2;
                            return 1;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 2;
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                    }
                    if(element.atomTYPE == 'H'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            tube1.moleculeTYPE = 1;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                            tube1.moleculeTYPE = 4;
                            return 1;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 4;
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 1){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE = 4){
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    
                    if(element.atomTYPE == 'O'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                            tube1.moleculeTYPE = 1;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                            tube1.moleculeTYPE = 2;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                            tube1.moleculeTYPE = 3;
                            return 1;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                    tube2.moleculeTYPE = 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                                    tube2.moleculeTYPE = 2;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 3;
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 2){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE == 3){
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    if (element.atomTYPE == 'N'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            tube1.moleculeTYPE = 3;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                            tube1.moleculeTYPE = 4;
                            return 1;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 3;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                    tube2.moleculeTYPE = 4;
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                    }
                }
                else{
                    // tube1 moleculeTYPE is not equal to 0. 
                    if(element.atomTYPE == 'C'){
                        if(tube2.moleculeTYPE == 0){
                            if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                tube2.moleculeTYPE = 2;
                                return 2;
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                        else{
                            tube3.tubeTS = element.atomID;
                            return 3;
                        }
                    }
                    else if(element.atomTYPE == 'H'){
                        if(tube1.moleculeTYPE == 1){
                            return 1;
                        }
                        else if(tube1.moleculeTYPE == 4){
                            return 1;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 4;
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 1){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE == 4){
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'O'){
                        if(tube1.moleculeTYPE == 2){
                            return 1;
                        }
                        else if(tube1.moleculeTYPE == 3){
                            return 1;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                    tube2.moleculeTYPE == 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 3;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                                    tube2.moleculeTYPE = 2;
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 2){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE == 3){
                                    return 2;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'N'){
                        if(tube2.moleculeTYPE == 0){
                            if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                tube2.moleculeTYPE = 4;
                                return 2;
                            }
                            else if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                tube2.moleculeTYPE = 3;
                                return 2;
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                        else{
                            tube3.tubeTS = element.atomID;
                            return 3;
                        }
                    }
                }
            }
            else{
                
                
                // İlk önce tube 2 sonra tube1.
                if(tube2.moleculeTYPE == 0){
                    
                    if(element.atomTYPE == 'C'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            tube2.moleculeTYPE = 2;
                            return 2;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                    }
                    if(element.atomTYPE == 'H'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            tube2.moleculeTYPE = 1;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                            tube2.moleculeTYPE = 4;
                            return 2;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 2){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE = 4){
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    
                    if(element.atomTYPE == 'O'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                            tube2.moleculeTYPE = 1;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                            tube2.moleculeTYPE = 2;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                            tube2.moleculeTYPE = 3;
                            return 2;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                    tube1.moleculeTYPE = 1;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 3;
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 2){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE == 3){
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    if (element.atomTYPE == 'N'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            tube2.moleculeTYPE = 3;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                            tube2.moleculeTYPE = 4;
                            return 2;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 3;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                    }
                }
                else{
                    // tube1 moleculeTYPE is not equal to 0. 
                    if(element.atomTYPE == 'C'){
                        if(tube1.moleculeTYPE == 0){
                            if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                tube1.moleculeTYPE = 2;
                                return 1;
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                        else{
                            tube3.tubeTS = element.atomID;
                            return 3;
                        }
                    }
                    else if(element.atomTYPE == 'H'){
                        if(tube2.moleculeTYPE == 1){
                            return 2;
                        }
                        else if(tube2.moleculeTYPE == 4){
                            return 2;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 1;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 1){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE == 4){
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'O'){
                        if(tube2.moleculeTYPE == 2){
                            return 2;
                        }
                        else if(tube2.moleculeTYPE == 3){
                            return 2;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                    tube1.moleculeTYPE = 1;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 2){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE == 3){
                                    return 1;
                                }
                                else{
                                    tube3.tubeTS = element.atomID;
                                    return 3;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'N'){
                        if(tube1.moleculeTYPE == 0){
                            if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                tube1.moleculeTYPE = 4;
                                return 1;
                            }
                            else if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            	 tube1.moleculeTYPE = 3;
                            	 return 1;
                            }
                            else{
                                tube3.tubeTS = element.atomID;
                                return 3;
                            }
                        }
                        else{
                            tube3.tubeTS = element.atomID;
                            return 3;
                        }
                    }
                }
            }
                
            }
            
            
            
            
            else if(tube1.tubeTS == 0 && tube2.tubeTS != 0 && tube3.tubeTS != 0){
            // Tube two and three is not empty.
            if(tube2.tubeTS < tube3.tubeTS){
                // Önce Tube 1 Sonra Tube 2 check edilecek.
                if(tube2.moleculeTYPE == 0){
                    
                    if(element.atomTYPE == 'C'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            tube2.moleculeTYPE = 2;
                            return 2;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                    }
                    if(element.atomTYPE == 'H'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            tube2.moleculeTYPE = 1;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                            tube2.moleculeTYPE = 4;
                            return 2;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 2){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE = 4){
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    
                    if(element.atomTYPE == 'O'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                            tube2.moleculeTYPE = 1;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                            tube2.moleculeTYPE = 2;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                            tube2.moleculeTYPE = 3;
                            return 2;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                    tube3.moleculeTYPE = 1;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 3;
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 2){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE == 3){
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    if (element.atomTYPE == 'N'){
                        if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            tube2.moleculeTYPE = 3;
                            return 2;
                        }
                        else if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                            tube2.moleculeTYPE = 4;
                            return 2;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 3;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                    }
                }
                else{
                    // tube2 moleculeTYPE is not equal to 0. 
                    if(element.atomTYPE == 'C'){
                        if(tube3.moleculeTYPE == 0){
                            if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                tube3.moleculeTYPE = 2;
                                return 3;
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                        else{
                            tube1.tubeTS = element.atomID;
                            return 1;
                        }
                    }
                    else if(element.atomTYPE == 'H'){
                        if(tube2.moleculeTYPE == 1){
                            return 2;
                        }
                        else if(tube2.moleculeTYPE == 4){
                            return 2;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 1;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 1){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE == 4){
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'O'){
                        if(tube2.moleculeTYPE == 2){
                            return 2;
                        }
                        else if(tube2.moleculeTYPE == 3){
                            return 2;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                    tube3.moleculeTYPE = 1;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 3;
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 2){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE == 3){
                                    return 3;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'N'){
                        if(tube3.moleculeTYPE == 0){
                            if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                tube3.moleculeTYPE = 4;
                                return 3;
                            }
                            else if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                tube3.moleculeTYPE = 3;
                                return 3;
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                        else{
                            tube1.tubeTS = element.atomID;
                            return 1;
                        }
                    }
                }
            }
            else{
                
                
                // İlk önce tube 2 sonra tube1.
                if(tube3.moleculeTYPE == 0){
                    
                    if(element.atomTYPE == 'C'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                            tube3.moleculeTYPE = 2;
                            return 3;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 2;
                                    return 1;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                    }
                    if(element.atomTYPE == 'H'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                            tube3.moleculeTYPE = 1;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                            tube3.moleculeTYPE = 4;
                            return 3;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 2;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 4;
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 2){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE = 4){
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    
                    if(element.atomTYPE == 'O'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                            tube3.moleculeTYPE = 1;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                            tube3.moleculeTYPE = 2;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                            tube3.moleculeTYPE = 3;
                            return 3;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                    tube2.moleculeTYPE = 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                                    tube2.moleculeTYPE = 2;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 3;
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 2){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE == 3){
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    if (element.atomTYPE == 'N'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                            tube3.moleculeTYPE = 3;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                            tube3.moleculeTYPE = 4;
                            return 3;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 3;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                    tube2.moleculeTYPE = 4;
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                    }
                }
                else{
                    // tube1 moleculeTYPE is not equal to 0. 
                    if(element.atomTYPE == 'C'){
                        if(tube2.moleculeTYPE == 0){
                            if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                tube2.moleculeTYPE = 2;
                                return 2;
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                        else{
                            tube1.tubeTS = element.atomID;
                            return 1;
                        }
                    }
                    else if(element.atomTYPE == 'H'){
                        if(tube3.moleculeTYPE == 1){
                            return 3;
                        }
                        else if(tube3.moleculeTYPE == 4){
                            return 3;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                                    tube2.moleculeTYPE = 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 4;
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 1){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE == 4){
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'O'){
                        if(tube3.moleculeTYPE == 2){
                            return 3;
                        }
                        else if(tube3.moleculeTYPE == 3){
                            return 3;
                        }
                        else{
                            if(tube2.moleculeTYPE == 0){
                                if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                    tube2.moleculeTYPE = 1;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'C'){
                                    tube2.moleculeTYPE = 2;
                                    return 2;
                                }
                                else if(atoms[tube2.tubeTS-1].atomTYPE == 'N'){
                                    tube2.moleculeTYPE = 3;
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                            else{
                                if(tube2.moleculeTYPE == 2){
                                    return 2;
                                }
                                else if(tube2.moleculeTYPE == 3){
                                    return 2;
                                }
                                else{
                                    tube1.tubeTS = element.atomID;
                                    return 1;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'N'){
                        if(tube2.moleculeTYPE == 0){
                            if(atoms[tube2.tubeTS-1].atomTYPE == 'H'){
                                tube2.moleculeTYPE = 4;
                                return 2;
                            }
                            else if(atoms[tube2.tubeTS-1].atomTYPE == 'O'){
                            	 tube2.moleculeTYPE = 3;
                            	 return 2;
                            }
                            else{
                                tube1.tubeTS = element.atomID;
                                return 1;
                            }
                        }
                        else{
                            tube1.tubeTS = element.atomID;
                            return 1;
                        }
                    }
                }
            }
                
            }
            
            
            // *******************
            else if(tube1.tubeTS != 0 && tube2.tubeTS == 0 && tube3.tubeTS != 0){
            // Tube one and three is not empty.
            if(tube1.tubeTS < tube3.tubeTS){
                // Önce Tube 1 Sonra Tube 2 check edilecek.
                if(tube1.moleculeTYPE == 0){
                    
                    if(element.atomTYPE == 'C'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            tube1.moleculeTYPE = 2;
                            return 1;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                    }
                    if(element.atomTYPE == 'H'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            tube1.moleculeTYPE = 1;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                            tube1.moleculeTYPE = 4;
                            return 1;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 2){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE = 4){
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    
                    if(element.atomTYPE == 'O'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                            tube1.moleculeTYPE = 1;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                            tube1.moleculeTYPE = 2;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                            tube1.moleculeTYPE = 3;
                            return 1;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                    tube3.moleculeTYPE = 1;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 3;
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 2){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE == 3){
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    if (element.atomTYPE == 'N'){
                        if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                            tube1.moleculeTYPE = 3;
                            return 1;
                        }
                        else if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                            tube1.moleculeTYPE = 4;
                            return 1;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 3;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                    }
                }
                else{
                    // tube1 moleculeTYPE is not equal to 0. 
                    if(element.atomTYPE == 'C'){
                        if(tube3.moleculeTYPE == 0){
                            if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                tube3.moleculeTYPE = 2;
                                return 3;
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                        else{
                            tube2.tubeTS = element.atomID;
                            return 2;
                        }
                    }
                    else if(element.atomTYPE == 'H'){
                        if(tube1.moleculeTYPE == 1){
                            return 1;
                        }
                        else if(tube1.moleculeTYPE == 4){
                            return 1;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                    tube3.moleculeTYPE = 1;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 1){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE == 4){
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'O'){
                        if(tube1.moleculeTYPE == 2){
                            return 1;
                        }
                        else if(tube1.moleculeTYPE == 3){
                            return 1;
                        }
                        else{
                            if(tube3.moleculeTYPE == 0){
                                if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                    tube3.moleculeTYPE = 1;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                                    tube3.moleculeTYPE = 2;
                                    return 3;
                                }
                                else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                                    tube3.moleculeTYPE = 4;
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube3.moleculeTYPE == 2){
                                    return 3;
                                }
                                else if(tube3.moleculeTYPE == 3){
                                    return 3;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'N'){
                        if(tube3.moleculeTYPE == 0){
                            if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                                tube3.moleculeTYPE = 4;
                                return 3;
                            }
                            else if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                                tube3.moleculeTYPE = 3;
                                return 3;
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                        else{
                            tube2.tubeTS = element.atomID;
                            return 2;
                        }
                    }
                }
            }
            else{
                
                
                // İlk önce tube 2 sonra tube1.
                if(tube3.moleculeTYPE == 0){
                    
                    if(element.atomTYPE == 'C'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                            tube3.moleculeTYPE = 2;
                            return 3;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                    }
                    if(element.atomTYPE == 'H'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                            tube3.moleculeTYPE = 1;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                            tube3.moleculeTYPE = 4;
                            return 3;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 2){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE = 4){
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    
                    if(element.atomTYPE == 'O'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                            tube3.moleculeTYPE = 1;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'C'){
                            tube3.moleculeTYPE = 2;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'N'){
                            tube3.moleculeTYPE = 3;
                            return 3;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                    tube1.moleculeTYPE = 1;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 3;
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 2){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE == 3){
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    if (element.atomTYPE == 'N'){
                        if(atoms[tube3.tubeTS-1].atomTYPE == 'O'){
                            tube3.moleculeTYPE = 3;
                            return 3;
                        }
                        else if(atoms[tube3.tubeTS-1].atomTYPE == 'H'){
                            tube3.moleculeTYPE = 4;
                            return 3;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 3;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                    }
                }
                else{
                    // tube1 moleculeTYPE is not equal to 0. 
                    if(element.atomTYPE == 'C'){
                        if(tube1.moleculeTYPE == 0){
                            if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                tube1.moleculeTYPE = 2;
                                return 1;
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                        else{
                            tube2.tubeTS = element.atomID;
                            return 2;
                        }
                    }
                    else if(element.atomTYPE == 'H'){
                        if(tube3.moleculeTYPE == 1){
                            return 3;
                        }
                        else if(tube3.moleculeTYPE == 4){
                            return 3;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                    tube1.moleculeTYPE = 1;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 1){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE == 4){
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'O'){
                        if(tube3.moleculeTYPE == 2){
                            return 3;
                        }
                        else if(tube3.moleculeTYPE == 3){
                            return 3;
                        }
                        else{
                            if(tube1.moleculeTYPE == 0){
                                if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                    tube1.moleculeTYPE = 1;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'C'){
                                    tube1.moleculeTYPE = 2;
                                    return 1;
                                }
                                else if(atoms[tube1.tubeTS-1].atomTYPE == 'N'){
                                    tube1.moleculeTYPE = 4;
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                            else{
                                if(tube1.moleculeTYPE == 2){
                                    return 1;
                                }
                                else if(tube1.moleculeTYPE == 3){
                                    return 1;
                                }
                                else{
                                    tube2.tubeTS = element.atomID;
                                    return 2;
                                }
                            }
                        }
                    }
                    else if(element.atomTYPE == 'N'){
                        if(tube1.moleculeTYPE == 0){
                            if(atoms[tube1.tubeTS-1].atomTYPE == 'H'){
                                tube1.moleculeTYPE = 4;
                                return 1;
                            }
                            else if(atoms[tube1.tubeTS-1].atomTYPE == 'O'){
                                tube1.moleculeTYPE = 3;
                                return 1;
                            }
                            else{
                                tube2.tubeTS = element.atomID;
                                return 2;
                            }
                        }
                        else{
                            tube2.tubeTS = element.atomID;
                            return 2;
                        }
                    }
                }
            }
                
            }
            //********************
            
            else if(tube1.tubeTS != 0 && tube2.tubeTS != 0 && tube3.tubeTS != 0){
                int m = ThreeTubeNotEmpty(atoms,element);
                return m;
            }
            
            return 5;
        }
    }
int ThreeTubeNotEmpty(struct atom *atoms,struct atom element){
    struct tube *tube1ptr,*tube2ptr,*tube3ptr;
    int ret1,ret2,ret3;
    if((tube1.tubeTS < tube2.tubeTS) && (tube2.tubeTS < tube3.tubeTS)){
        tube1ptr = &tube1;
        tube2ptr = &tube2;
        tube3ptr = &tube3;
        ret1 = 1;
        ret2 = 2;
        ret3 = 3;
    }
    else if((tube1.tubeTS < tube3.tubeTS) && (tube3.tubeTS < tube2.tubeTS)){
        tube1ptr = &tube1;
        tube2ptr = &tube3;
        tube3ptr = &tube2;
        ret1 = 1;
        ret2 = 3;
        ret3 = 2;
    }
    else if((tube2.tubeTS < tube1.tubeTS) && (tube1.tubeTS < tube3.tubeTS)){
        tube1ptr = &tube2;
        tube2ptr = &tube1;
        tube3ptr = &tube3;
        ret1 = 2;
        ret2 = 1;
        ret3 = 3;
    }
    else if((tube2.tubeTS < tube3.tubeTS) && (tube3.tubeTS < tube1.tubeTS)){
        tube1ptr = &tube2;
        tube2ptr = &tube3;
        tube3ptr = &tube1;
        ret1 = 2;
        ret2 = 3;
        ret3 = 1;
    }
    else if((tube3.tubeTS < tube2.tubeTS) && (tube2.tubeTS < tube1.tubeTS)){
        tube1ptr = &tube3;
        tube2ptr = &tube2;
        tube3ptr = &tube1;
        ret1 = 3;
        ret2 = 2;
        ret3 = 1;
    }
    else if((tube3.tubeTS < tube1.tubeTS) && (tube1.tubeTS < tube2.tubeTS)){
        tube1ptr = &tube3;
        tube2ptr = &tube1;
        tube3ptr = &tube2;
        ret1 = 3;
        ret2 = 1;
        ret3 = 2;
    }
    // At the end of these if else blocks tube1ptr holds the smallest TS one where tube3ptr holds the biggest TS.
    if(element.atomTYPE == 'C'){
        if(tube1ptr->moleculeTYPE == 0){
            // Tube 1 molecule type is not determined yet.
            if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'O'){
                tube1ptr->moleculeTYPE = 2;
                return ret1;
            }
            else{
                if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'O'){
                        tube2ptr->moleculeTYPE = 2;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 2;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                }
                else{
                    if(tube3ptr->moleculeTYPE == 0){
                        if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                            tube3ptr->moleculeTYPE = 2;
                            return ret3;
                        }
                        else{
                            // WASTED.
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                    else{
                        // WASTED.
                        printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                        return 5;
                    }
                }
            }
        }
        else{
            // Tube 1 molecule type is one of the four.
            if(tube2ptr->moleculeTYPE == 0){
                if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'O'){
                    tube2ptr->moleculeTYPE = 2;
                    return ret2;
                }
                else{
                    if(tube3ptr->moleculeTYPE == 0){
                        if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                            tube3ptr->moleculeTYPE = 2;
                            return ret3;
                        }
                        else{
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                    else{
                        printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                        return 5;
                    }
                }
            }
            else{
                if(tube3ptr->moleculeTYPE == 0){
                    if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                        tube3ptr->moleculeTYPE = 2;
                        return ret3;
                    }
                    else{
                        printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                        return 5;
                    }
                }
                else{
                    printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                    return 5;
                }
            }
        }
    }
    if(element.atomTYPE == 'H'){
        if(tube1ptr->moleculeTYPE == 0){
            if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'O'){
                tube1ptr->moleculeTYPE = 1;
                return ret1;
            }
            else if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'N'){
                tube1ptr->moleculeTYPE = 4;
                return ret1;
            }
            else{
                if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'O'){
                        tube2ptr->moleculeTYPE = 1;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'N'){
                        tube2ptr->moleculeTYPE = 4;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 4;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 1){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 4){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
                else{
                    if(tube2ptr->moleculeTYPE == 1){
                        return ret2;
                    }
                    else if(tube2ptr->moleculeTYPE = 4){
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 4;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 1){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 4){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
            }
        }
        else{
            if(tube1ptr->moleculeTYPE == 1){
                return ret1;
            }
            else if(tube1ptr->moleculeTYPE == 4){
                return ret1;
            }
            else{
                if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'O'){
                        tube2ptr->moleculeTYPE = 1;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'N'){
                        tube2ptr->moleculeTYPE = 4;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 4;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 1){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 4){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
                else{
                    if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 4;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 1){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 4){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }   
                }
            }
        }
    }
    if(element.atomTYPE == 'O'){
        if(tube1ptr->moleculeTYPE == 0){
            if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'H'){
                tube1ptr->moleculeTYPE = 1;
                return ret1;
            }
            else if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'C'){
                tube1ptr->moleculeTYPE = 2;
                return ret1;
            }
            else if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'N'){
                tube1ptr->moleculeTYPE = 3;
                return ret1;
            }
            else{
                if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'H'){
                        tube2ptr->moleculeTYPE = 1;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'C'){
                        tube2ptr->moleculeTYPE = 2;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'N'){
                        tube2ptr->moleculeTYPE = 3;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'H'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'C'){
                                tube3ptr->moleculeTYPE = 2;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 3;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 2){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 3){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
                else{
                    if(tube2ptr->moleculeTYPE == 2){
                        return ret2;
                    }
                    else if(tube2ptr->moleculeTYPE == 3){
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'H'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'C'){
                                tube3ptr->moleculeTYPE = 2;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 3;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 2){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 3){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
            }
        }
        else{
            if(tube1ptr->moleculeTYPE == 2){
                return ret1;
            }
            else if(tube1ptr->moleculeTYPE == 3){
                return ret1;
            }
            else{
                if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'H'){
                        tube2ptr->moleculeTYPE = 1;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'C'){
                        tube2ptr->moleculeTYPE = 2;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'N'){
                        tube2ptr->moleculeTYPE = 3;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'H'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'C'){
                                tube3ptr->moleculeTYPE = 2;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 3;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 2){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 3){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
                else{
                    if(tube2ptr->moleculeTYPE == 2){
                        return ret2;
                    }
                    else if(tube2ptr->moleculeTYPE == 3){
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'H'){
                                tube3ptr->moleculeTYPE = 1;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'C'){
                                tube3ptr->moleculeTYPE = 2;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'N'){
                                tube3ptr->moleculeTYPE = 3;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            if(tube3ptr->moleculeTYPE == 2){
                                return ret3;
                            }
                            else if(tube3ptr->moleculeTYPE == 3){
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                    }
                }
            }
        }
    }
    if(element.atomTYPE == 'N'){
        if(tube1ptr->moleculeTYPE == 0){
            if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'O'){
                // NO2
                tube1ptr->moleculeTYPE = 3;
                return ret1;
            }
            else if(atoms[tube1ptr->tubeTS-1].atomTYPE == 'H'){
                // NH3
                tube1ptr->moleculeTYPE = 4;
                return ret1;
            }
            else{
                if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'O'){
                        tube2ptr->moleculeTYPE = 3;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'H'){
                        tube2ptr->moleculeTYPE = 4;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 3;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'H'){
                                tube3ptr->moleculeTYPE = 4;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                }
                else{
                    if(tube3ptr->moleculeTYPE == 0){
                        if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                            tube3ptr->moleculeTYPE = 3;
                            return ret3;
                        }
                        else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                            tube3ptr->moleculeTYPE = 4;
                            return ret3;
                        }
                        else{
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                }
            }
        }
        else{
            if(tube2ptr->moleculeTYPE == 0){
                    if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'O'){
                        tube2ptr->moleculeTYPE = 3;
                        return ret2;
                    }
                    else if(atoms[tube2ptr->tubeTS-1].atomTYPE == 'H'){
                        tube2ptr->moleculeTYPE = 4;
                        return ret2;
                    }
                    else{
                        if(tube3ptr->moleculeTYPE == 0){
                            if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                                tube3ptr->moleculeTYPE = 3;
                                return ret3;
                            }
                            else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'H'){
                                tube3ptr->moleculeTYPE = 4;
                                return ret3;
                            }
                            else{
                                printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                                return 5;
                            }
                        }
                        else{
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                }
                else{
                    if(tube3ptr->moleculeTYPE == 0){
                        if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                            tube3ptr->moleculeTYPE = 3;
                            return ret3;
                        }
                        else if(atoms[tube3ptr->tubeTS-1].atomTYPE == 'O'){
                            tube3ptr->moleculeTYPE = 4;
                            return ret3;
                        }
                        else{
                            printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                            return 5;
                        }
                    }
                    else{
                    	printf("%c with ID:%d is wasted.\n",element.atomTYPE,element.atomID);
                       return 5;
                    }
                }
        }
    }
}
int main(int argc, char *argv[]) {
    int numberOfC = 20;
    int numberOfH = 20;
    int numberOfO = 20;
    int numberOfN = 20;
    unsigned int mainThreadSleepTime = 0;
    double generationRate = 100;
    tube1.tubeID = 1;
    tube2.tubeID = 2;
    tube3.tubeID = 3;
    tube1.moleculeTYPE = 0;
    tube1.moleculeTYPE = 0;
    tube1.moleculeTYPE = 0;
    tube1.tubeTS = 0;
    tube2.tubeTS = 0;
    tube3.tubeTS = 0;
	pthread_t tubethread;
	int opt;
	// Below opt operations is taken from https://pubs.opengroup.org/onlinepubs/9699919799/functions/getopt.html
	// Which is the open-source and not used directly.
	while((opt = getopt(argc,argv,"c:h:o:n:g:")) != -1){
		switch(opt){
			case 'c':
				numberOfC = atoi(optarg);
				break;
			case 'h':
				numberOfH = atoi(optarg);
				break;
			case 'o':
				numberOfO = atoi(optarg);
				break;
			case 'n':
				numberOfN = atoi(optarg);
				break;
			case 'g':
				generationRate = atof(optarg);
				break;
		}
	}
	printf("Generation Rate: %f\n",generationRate);
	printf("Number Of Carbon(C) atoms to be pruced: %d.\n",numberOfC);
	printf("Number Of Hydrogen(H) atoms to be pruced: %d.\n",numberOfH);
	printf("Number Of Oxygen(O) atoms to be pruced: %d.\n",numberOfO);
	printf("Number Of Nitrogen(N) atoms to be pruced: %d.\n",numberOfN);
	totalAtoms = numberOfC + numberOfH + numberOfO + numberOfN;
	struct atom atoms[totalAtoms];
	struct atom *atomptr = atoms;
	pthread_mutex_init(&mutex, NULL);
	srand(time(NULL));
	if (pthread_create(&tubethread,NULL,&tubeth,(void*)atomptr) != 0){
		return 1; // Thread is not created. Indicates an error.
	}
	// Main Thread
	int i = 0;
	int prevlookup = -1;
	remainingAtoms = totalAtoms;
	while(remainingAtoms > 0){
	if((lookup - prevlookup) && (remainingAtoms != 0)){
	    // lock yap.
	    pthread_mutex_lock(&mutex);
	    mainThreadSleepTime = (unsigned int) (exponential(generationRate));
	    prevlookup = prevlookup + 1;
	    counter = counter + 1;
	    int value = (rand() % 4); // 0->C 1->H 2->O 3->N
	    if (value == 0 && numberOfC != 0 ){
	        atoms[i].atomID = i + 1;
	        atoms[i].atomTYPE = 'C';
	        numberOfC = numberOfC - 1;
	        printf("%c with ID: %d is created.\n",atoms[i].atomTYPE,atoms[i].atomID);
	        tubenumber = findSuitableTube(atomptr,atoms[i]);
	        i = i + 1;
	        remainingAtoms = remainingAtoms - 1;
	    }
	    else if(value == 1 && numberOfH != 0){
	        atoms[i].atomID = i + 1;
	        atoms[i].atomTYPE = 'H';
	        numberOfH = numberOfH - 1;
	        printf("%c with ID: %d is created.\n",atoms[i].atomTYPE,atoms[i].atomID);
	        tubenumber = findSuitableTube(atomptr,atoms[i]);
	        i = i + 1;
	        remainingAtoms = remainingAtoms - 1;

	    }
	    else if(value == 2 && numberOfO != 0){
	        atoms[i].atomID = i + 1;
	        atoms[i].atomTYPE = 'O';
	        numberOfO = numberOfO - 1;
	        printf("%c with ID: %d is created.\n",atoms[i].atomTYPE,atoms[i].atomID);
	        tubenumber = findSuitableTube(atomptr,atoms[i]);
	        i = i + 1;
	        remainingAtoms = remainingAtoms - 1;
	    }
	    else if(value == 3 && numberOfN != 0){
	        atoms[i].atomID = i + 1;
	        atoms[i].atomTYPE = 'N';
	        numberOfN = numberOfN - 1;
	        printf("%c with ID: %d is created.\n",atoms[i].atomTYPE,atoms[i].atomID);
	        tubenumber = findSuitableTube(atomptr,atoms[i]);
	        i = i + 1;
	        remainingAtoms = remainingAtoms - 1;
	    }
	    else{
	    	tubenumber = 0;
	        prevlookup = prevlookup - 1;
	        counter = counter - 1;
	    }
	    pthread_mutex_unlock(&mutex);
	    usleep(mainThreadSleepTime);
	}
	}
	if (pthread_join(tubethread, NULL) != 0){
		return 2; // Indicates an error.
	}
	
   	return 0;
}

