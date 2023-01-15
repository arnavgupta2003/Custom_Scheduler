#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BILLION 1000000000L;
#define POW 4294967296L;
#include <time.h>

void* Thr_A(void* in);
void* Thr_B(void* in);
void* Thr_C(void* in);
void countA();
void countB();
void countC();
void start(int OTHER_policy,int RR_policy,int FIFO_policy);
struct timespec st_a,st_b,st_c,sp_a,sp_b,sp_c;

int main(int argc, char const *argv[])
{
	printf("Run1\n");
	start(0,1,1);
	printf("Run2\n");
	start(0,2,3);
	printf("Run3\n");
	start(0,3,3);
	printf("Run4\n");
	start(0,1,32);
	printf("Run5\n");
	start(0,24,35);
	printf("Run6\n");
	start(0,23,13);
	
	return 0;
}

void start(int OTHER_policy,int RR_policy,int FIFO_policy){
	pthread_t tid_a,tid_b,tid_c;
	struct sched_param param_a,param_b,param_c;
	

	int a = pthread_create(&tid_a,NULL,&Thr_A,NULL);
	param_a.sched_priority=OTHER_policy;
	int ret_a = pthread_setschedparam(tid_a,SCHED_OTHER,&param_a);

	if(ret_a!=0){
		printf("Scehd error in A:%d\n",ret_a);
	}

	int b = pthread_create(&tid_b,NULL,&Thr_B,NULL);
	param_b.sched_priority=RR_policy;
	int ret_b = pthread_setschedparam(tid_b,SCHED_RR,&param_b);
	
	if(ret_b!=0){
		printf("Scehd error in B:%d\n",ret_b);
	}


	int c = pthread_create(&tid_c,NULL,&Thr_C,NULL);
	param_c.sched_priority=FIFO_policy;
	int ret_c = pthread_setschedparam(tid_c,SCHED_FIFO,&param_c);

	if(ret_c!=0){
		printf("Scehd error in C\n");
	}


	pthread_join(tid_a,NULL);
	double time_a = ( sp_a.tv_sec - st_a.tv_sec )
          + ( sp_a.tv_nsec - st_a.tv_nsec ) / (double)BILLION;
	printf("Time Taken by A:%lf\n",time_a);

	pthread_join(tid_b,NULL);
	double time_b = ( sp_b.tv_sec - st_b.tv_sec )
          + ( sp_b.tv_nsec - st_b.tv_nsec ) / (double)BILLION;
	printf("Time Taken by B:%lf\n",time_b);

	pthread_join(tid_c,NULL);
	double time_c = ( sp_c.tv_sec - st_c.tv_sec )
          + ( sp_c.tv_nsec - st_c.tv_nsec ) / (double)BILLION;
	printf("Time Taken by C:%lf\n",time_c);

	FILE *fp;
	fp = fopen("data.csv","a+");
	fprintf(fp,"%lf",time_a);fprintf(fp,",");
	fprintf(fp,"%lf",time_b);fprintf(fp,",");
	fprintf(fp,"%lf",time_c);fprintf(fp,"\n");
	fclose(fp);

}


void* Thr_A(void* in){
	countA();

}
void* Thr_B(void* in){
	countB();
}
void* Thr_C(void* in){
	countC();
}

void countA(){
	int start_a = clock_gettime(CLOCK_REALTIME,&st_a);
	for(long i=1;i<4294967296;i++){
		//printf("A:%d\n",i);
	}
	int stop_a = clock_gettime(CLOCK_REALTIME,&sp_a);
}
void countB(){
	int start_b = clock_gettime(CLOCK_REALTIME,&st_b);
	for(long i=1;i<4294967296;i++){
		//printf("B:%d\n",i);
	}
	int stop_b = clock_gettime(CLOCK_REALTIME,&sp_b);
}
void countC(){
	int start_c = clock_gettime(CLOCK_REALTIME,&st_c);
	for(long i=1;i<4294967296;i++){
		//printf("C:%d\n",i);
	}
	int stop_c = clock_gettime(CLOCK_REALTIME,&sp_c);
}