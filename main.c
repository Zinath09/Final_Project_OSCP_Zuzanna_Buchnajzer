#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


//initiating
int max1, max2; //capacity of room A and room B
int n;         //number of visitors

sem_t sem1; //checks how many visitors can go to the room A
sem_t sem2; //checks how many visitors can go to the room B
sem_t sem3; //checks how many visitors can go out of the room A

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER; //protects against thread overlap

struct room{
int wantin; //number of people who want to visit the room
int wantout;//number of people who want to leave the room
};
struct room A;
struct room B;

////THE PROGRAMM FOR EACH THREAD

void* planAB(void * person){
    long *tid = (long *) person; //the unique number for the thread
    
//entering the room A/////////////////////
    sem_wait(&sem1);
    
    //deadlock preventing
    pthread_mutex_lock(&m1);
        int loop_count=0;
        //dedlock threat checking
        //if there are no people leaving the museum and everyone in room A wants to go to B and everyone in room B wants to leave, 
        //after adding the last (to the maximum size of room A) person (this person-threat), there will be a deadlock        
        while (A.wantout==0 && B.wantout==max2 && (B.wantout==B.wantin || B.wantout<B.wantin)){ 
	    if (loop_count==0)
	        sem_post(&sem1); //we increase sem1, but unneceserly, because the thread hasn't come yet.
	        pthread_mutex_unlock(&m1);
	        sleep(1); //giving other threads a chance to leave rooms.
	        pthread_mutex_lock(&m1);
	    loop_count++;}
    
    //if there is no deadlock, go to the room A
    A.wantin--;
    B.wantin++;
    printf("%ld in A!      \t A=%d, B=%d \n", *tid, A.wantout+B.wantin,B.wantout);
    
    pthread_mutex_unlock(&m1);
    
//being in room A/////////////////////////
    sleep(rand()%2+1); //time of watching exhibition by visitor

//deciding whether a thread wants to go to room B or not  
if(rand()%2==0){
//////////A->B////////
    sem_wait(&sem2); //if there is space for entering room 2
    pthread_mutex_lock(&m1);
        B.wantin--;
        B.wantout++;
        printf("%ld in B!       \t A=%d, B=%d\n", *tid, A.wantout+B.wantin,B.wantout);
    sem_post(&sem1); //We increase the semaphore 1, because we leave room A and an extra person can enter it.
pthread_mutex_unlock(&m1);

//being in B/////////
    sleep(rand()%2+1); //time of watching exhibition by visitor
//coming back from B to A////////
    sem_wait(&sem1);
    pthread_mutex_lock(&m1);
        B.wantout--;
        A.wantout++;
        printf("%ld back in A!   \t A=%d, B=%d\n", *tid, A.wantout+B.wantin,B.wantout);
        sem_post(&sem2); //We increase the semaphore 2, because we leave room B and an extra person can enter it.
    pthread_mutex_unlock(&m1);
}
//leaving the museum////////A->////////
    pthread_mutex_lock(&m1);
        A.wantout--;
        n--; 
        printf("%ld is free! \t A=%d, B=%d\n", *tid, A.wantout+B.wantin,B.wantout);
        sem_post(&sem1);    //We increase the semaphore 1, because we leave room A and an extra person can enter it.
    pthread_mutex_unlock(&m1);
}

int main(){
    max1=5;
    max2=2;
    int n=10;
    pthread_t thread[n];

    sem_init(&sem1,0,max1);
    sem_init(&sem2,0,max2);


    A.wantin= n;
    A.wantout=0;

    for (int i=0;i<n;i++){
        pthread_create(&thread[i],NULL, planB, (void*) (&thread[i]));
    }
    pthread_exit(NULL);
    return 0;
}
