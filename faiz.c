#include<stdio.h>
#include<stdlib.h>
struct process
{
	int pid;
	int at;
	int bt;
	int qno;
	int time;
	int rem;
}pr[5]={{0,9,4,0,0,4},{1,0,8,0,0,8},{2,6,8,0,0,8},{3,3,4,0,0,4},{4,6,2,0,0,2}};

typedef struct
{
	int pno;
	int st;
	int et;
}chart;

chart gc[1000];

struct queue
{
	int qno;
	int qt;
	int f;
	int r;
	struct process p[50];

}q1,q2,q3,q4;

int ar[5]={0},cm[5]={0};
int ct=0,k=0,queue=1;
int get_comp_no()
{
	int i=0,count=0;
	for(i=0;i<5;i++)
	{
		if(cm[i]==1)
			count+=1;
	
	}
	return count;
}

void enque(struct process,int);
int deque(int);
void printoutput();

void arrive()
{
	int i;//=0
	for(i=0;i<5;i++)
	{
		if(ct >= pr[i].at && ar[i] != 1)
		{
			ar[i]=1;
			pr[i].qno =1;
			enque(pr[i],1);
			queue =1;
		}
	}

}
void who_ex()
{	
	switch(queue)
	{
		case 1:
		{
			gc[k].pno = q1.p[q1.f].pid;
			gc[k].st =ct;
			gc[k].et =ct+1;
			pr[q1.p[q1.f].pid].rem -=1;
			pr[q1.p[q1.f].pid].time +=1;
			
			int id = q1.p[q1.f].pid;
			if(pr[id].rem >0 && pr[id].time ==q1.qt)
			{
				pr[id].time =0;
				enque(pr[id],2); 
				deque(1);
			}
			else if(pr[id].rem <=0)
			{
				cm[id]=1;
				deque(1);
			}
			if(q1.f==-1)
			{
				queue =2;
			}
			k+=1;
			break;
		
		}
		
		case 2:
		{
			
			gc[k].pno =q2.p[q2.f].pid;
			gc[k].st = ct;	
			gc[k].et =ct+1;	
			
			pr[q2.p[q2.f].pid].rem -=1;
			pr[q2.p[q2.f].pid].time +=1; 
			
			int id = q2.p[q2.f].pid;
			
			if(pr[id].rem >0 && pr[id].time == q2.qt)
			{
				enque(pr[id],3);
				deque(2);
				pr[id].time =0;
			}
			else if(pr[id].rem ==0)
			{
				cm[id] =1;
				deque(2);
			}
			if(q2.f ==-1)
			{
				queue =3;
			}
			k+=1;
			break;
			
		}
	
		case 3:
		{
			int id = q3.p[q3.f].pid;
			gc[k].pno = pr[id].pid; 
			gc[k].st = ct;
			gc[k].et =ct+1;
			
			pr[id].rem -=1;
			pr[id].time +=1;
			
			if(pr[id].rem >=0 && pr[id].time == q3.qt)
			{
				enque(pr[id],3);
				deque(2);
				pr[id].time =0;
			}
			else if(pr[id].rem ==0)
			{
				cm[id] =1;
				deque(3);	
			}
			if(q3.f ==-1)
			{
				queue =4;
			}
			k+=1;
			break;
			
		
		
		}
		
		case 4:
		{
			int id = q4.p[q4.f].pid;
			gc[k].pno =pr[id].pid;
			gc[k].st =ct;
			gc[k].et =ct+1;
			
			pr[id].rem -=1;
			pr[id].time +=1;
			
			if(pr[id].rem >0 && pr[id].time ==q4.qt)
			{
				enque(pr[id],1);
				pr[id].time =0;
				deque(4);
				queue =1;
			}
			else if(pr[id].rem <=0)
			{	
				cm[id] =1;
				deque(4);
			}
			
			if(q4.f == -1)
			{
				queue =1;
			}
			k+=1;
			
			break;
		}
				
	
	}
	
}


int main()
{	
	q1.f = q1.r =-1;
	q2.f = q2.r =-1;
	q3.f = q3.r =-1;
	q4.f = q4.r =-1;
	
	q1.qt =2 , q2.qt =4, q3.qt =6 , q4.qt =10;//assigning quantum time to each queue
	
	q1.qno =1 ,q2.qno =2, q3.qno =3 ,q4.qno=4;//assigning queue number to each queue
	
	while(get_comp_no() <5)
	{	
		printf("%d ",get_comp_no());
		arrive();
		who_ex();
		//ct+=1;
		//printf("%d ",get_comp_no());
		ct+=1;
	}
	
	//printoutput();
	
	return 0;
}


void enque(struct process p,int qno)
{
	if(qno == q1.qno)
	{
		if(q1.f ==-1)
		{	
			q1.f = q1.r =0;
			p.qno =1;//q1.qno
			q1.p[q1.r] =p;	
		
		}
		else
		{
			q1.r+=1;
			p.qno =1;//q1.qno
			q1.p[q1.r] =p;
		
		}
	
	}
	else if(qno == q2.qno)//2
	{
		if(q2.f == -1)
		{
			q2.f =q2.r =0;
			p.qno =2;//q2.qno
			q2.p[q2.r] =p;
		
		}
		else
		{
			q2.r+=1;
			p.qno =2;//q2.qno	
			q2.p[q2.r] =p;
		}
		
	}
	else if(qno == q3.qno)//3
	{
		if(q3.f ==-1)
		{
			q3.f =q3.r =0;
			p.qno =3;//q3.qno
			q3.p[q3.r] =p;
		}
		else
		{
			q3.r+=1;
			p.qno =3;//q3.qno
			q3.p[q3.r] =p;
		
		}
	
	}
	else
	{
		if(q4.f ==-1)
		{
			q4.f =q4.r =0;
			p.qno =4;//q4.qno
			q4.p[q4.r] =p;		
		}
		else
		{
			q4.r+=1;
			p.qno =4;//q4.qno
			q4.p[q4.qno] =p;
		
		}
	
	}

}

int deque(int qno)
{
	if(qno == q1.qno)//1
	{
		if(q1.r ==-1)
		{
			//printf("QUEUE 1 is empty!");
			return 0;
		}
		else if(q1.f == q1.r)
		{
			q1.f =q1.r =-1;	
		
		}
		else
		{
			q1.f=q1.f+1;
		}
	
	}
	
	else if(qno == q2.qno)//2
	{
		if(q2.r ==-1)
		{
			//printf("QUEUE 2 is empty!");
			return 0;
		}
		else if(q2.f ==q2.r)
		{
			q2.f =q2.r =0;
		}
		else
		{
			q2.f=q2.f+1;	
		}
	
	}
	
	else if(qno == q3.qno)//3
	{
		if(q3.r ==-1)
		{
			//printf("QUEUE 3 is empty");
			return 0;
		}
		else if(q3.f == q3.r)
		{
			q3.f =q3.r =0;
		}
		else
		{
			q3.f=q3.f+1;
		}
	
	}
	
	else
	{
		if(q4.r == -1)
		{
			return 0;
		}
		else if(q4.f == q4.r)
		{
			q4.f = q4.r =0;
		}
		else
		{
			q4.f=q4.f+1;
		}
	
	}

}


void printoutput()
{
	for(int i=0;i<k;i++)
	{
		
		printf("%d %d %d",gc[i].pno,gc[i].st,gc[i].et);
	
	}

}









