#include<stdio.h>
#include <stdlib.h>
#include <time.h>


int min = 0;
int max = 100; 
// Generates and prints 'count' random
// numbers in range [min, max].
int generateRandoms() {
        int rd_num = rand() % (max - min + 1) + min;
        return rd_num;
    
}



void allocation(int num, int memory[],int start){
	int count=0;
	if(num == 1){printf("file1.txt\tstart: %d\t", start);}
	else if(num == 2){printf("file2.txt\tstart: %d\t", start);}
	for(int i=0; i<100; i++){
		if(memory[i]==num){
			printf("%d-> ",i);
			count++;
		}
	}
	printf("NULL ");
	printf("Count: %d\n",count);
}






int main(){

int memory[100] = {0};

for(int i=20; i<31; i++){
	memory[i] = 1;
}

for(int i=40; i<51; i++){

	memory[i] = 2;
}
int choice, start1, start2;


// this is for memory Allocatoin of file1.txt
for(int i=0; i<10; i++){
	if(i==0){
		while(1){
			int value = generateRandoms();
			if(memory[value]!=1||memory[value]!=2){
				start1 = value;
				memory[value] = 1;
				break;
			}
		}
	}
	else{
		while(1){
			int value = generateRandoms();
				if((memory[value]!=1 || memory[value] != 2) && value > start1){
					memory[value] = 1;
					break;
			}
		}
	}
}

//This is for memory Allocation for of file2.txt
for(int i=0; i<10; i++){
	if(i==0){
		while(1){
			int value = generateRandoms();
			if(memory[value]!=1||memory[value]!=2){
				start2 = value;
				memory[value] = 2;
				break;
			}
		}
	}
	else{
		while(1){
			int value = generateRandoms();
			
				if((memory[value]!=1 || memory[value] != 2) && value>start2){
					memory[value] = 2;
					break;
			}
		
		}
	}
}

printf("1.File1.txt\n2.File2.txt\n3.exit\n");


while(1){
printf("Enter the choice of file data allocations to be viewed: ");
scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("The link file allocation of the file1.txt is:\n");
			allocation(1, memory, start1);
			break;
		case 2:
			printf("The link file allocation of the file1.txt is:\n");
			allocation(2, memory, start2);
			break;
		case 3:
			return 0;
	}
     }
    }
    
    
    
    
    
    
    
    
