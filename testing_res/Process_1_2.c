#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BILLION  1000000000L;
#include <time.h>
#include <sched.h>


int main(int argc, char const *argv[])
{

	compile(0,1,1);
	
	return 0;
}
void compile(int OTHER_policy,int RR_policy,int FIFO_policy){
	printf("%d\n",OTHER_policy);printf("%d\n",RR_policy);printf("%d\n",FIFO_policy);
	struct timespec st_a,st_b,st_c,sp_a,sp_b,sp_c;
	pid_t pid_parent,pid_child1,pid_child2,pid_child3;
	struct sched_param param_a,param_b,param_c;
	int start,stop;
	double time;
	
	int f = fork();
	if(f<0){
		printf("Fork Failed\n");
	}else if(f==0){
		int g = fork();
		if(g<0){
			printf("Fork Failed\n");
		}else if(g==0){
			
			//Scheduling to OTHER
			pid_child3=getpid();
			param_a.sched_priority=OTHER_policy;
			int check2 = sched_setscheduler(pid_child3,SCHED_OTHER,&param_a);

			start = clock_gettime(CLOCK_REALTIME,&st_a);
			execvp("../res/kernel_1.sh",NULL);
		}else {

			//Scheduling to FIFO
			pid_child1=getpid();
			param_b.sched_priority=FIFO_policy;
			int check = sched_setscheduler(pid_child1,SCHED_FIFO,&param_b);
			
			start = clock_gettime(CLOCK_REALTIME,&st_b);
			execvp("../res/kernel_2.sh",NULL);
		}
	}else{
		
		int h = fork();
		if(h<0){
			printf("Fork Failed\n");
		}else if(h==0){
			
			//SCehduling to RR
			pid_child2=getpid();
			param_c.sched_priority=RR_policy;
			int check1 = sched_setscheduler(pid_child2,SCHED_RR,&param_c);

			start = clock_gettime(CLOCK_REALTIME,&st_c);
			execvp("../res/kernel_3.sh",NULL);
		}else {
			
			pid_t rw_c1,rw_c2,rw_c3;

			rw_c1 = waitpid(pid_child1,NULL,NULL);
			stop = clock_gettime(CLOCK_REALTIME,&sp_a);
			rw_c2 = waitpid(pid_child2,NULL,NULL);
			stop = clock_gettime(CLOCK_REALTIME,&sp_b);
			rw_c3 = waitpid(pid_child3,NULL,NULL);
			stop = clock_gettime(CLOCK_REALTIME,&sp_c);
			
			double time_a = (( sp_a.tv_sec - st_a.tv_sec ) + (double)( sp_a.tv_nsec - st_a.tv_nsec )) / (double)BILLION;
			printf("Time Taken A:%lf\n",time_a);
			

			double time_b = (( sp_b.tv_sec - st_b.tv_sec ) + (double)( sp_b.tv_nsec - st_b.tv_nsec )) / (double)BILLION;
			printf("Time Taken B:%lf\n",time_b);
			

			double time_c = (( sp_c.tv_sec - st_c.tv_sec ) + (double)( sp_c.tv_nsec - st_c.tv_nsec )) / (double)BILLION;
			printf("Time Taken C:%lf\n",time_c);

			//FILE I/O
			FILE *fp;
			fp = fopen("data.csv","a+");
			fprintf(fp,"%lf",time_a);fprintf(fp,",");
			fprintf(fp,"%lf",time_b);fprintf(fp,",");
			fprintf(fp,"%lf",time_c);fprintf(fp,"\n");
			fclose(fp);
		}
	}
}