//sema çevik 150112077- sibel aymış 150112075
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */

#include <sys/sem.h>

#define SIZE 50000
#define NUM_THREADS 5

typedef struct{
   int    id;
   int    islem;
   int    reserve;
   int   rsrvkltk;
   int    ne;
   int    firma;
   int    ucus;
   int    koltuk;
   pthread_mutex_t    sem;
}cstmr;
int gun=5;



cstmr ID1[SIZE];

typedef struct{
   int    id;
   int    islem;
}offcr;
offcr ID2[SIZE];

 struct Node{
   int    customerid;
    struct Node* next;
   int firma;
   int islem;
   int ucus;
   int koltuk;
}*rear, *front;

 struct Node1{
    int    customerid;
   int    officerid;
    struct Node1* next;
   int firma;
   int islem;
   int ucus;
   int koltuk;
}*rear1, *front1;

 




char *print(char *c);

char ch[SIZE];
char *str;
int a,b,c,p,d,x,t,r;
int set[5][5];
char z[1];
int say=0;
sem_t semid;
sem_t semof;

pthread_mutex_t array[5][5];	
sem_t mutex;  	
pthread_mutex_t mut,mut1,mut2,mut3,mut4,mut5,mutc;

char DST[5];
FILE *file;
	FILE *fp;

void display()
{
     struct Node *var=rear;
     if(var!=NULL)
     {
           printf("\nElements are as:  ");
           while(var!=NULL)
           {
                printf("\t%d, firmaa %d, şu işlem %d, şu uçuş %d, şu koltuk%d\n",var->customerid, var->firma, var->islem, var->ucus, var->koltuk);
                var=var->next;
           }
     printf("\n");
     } 
     else
     printf("\nQueue is Empty");
}
void display1()
{
     struct Node1 *var=rear1;
     if(var!=NULL)
     {
           fprintf(fp,"\nElements are as:  ");
           while(var!=NULL)
           {
                fprintf(fp,"\tcustomer%d - officer%d - %dişlemi - %d koltuk \n",var->customerid, var->officerid, var->islem,var->koltuk);
                var=var->next;
           }
     fprintf(fp,"\n");
     } 
     else
     fprintf(fp,"\nQueue is Empty");
}
void push1(int a,int b,int c,int d)
{
     struct Node1 *temp;
     temp=(struct Node1 *)malloc(sizeof(struct Node1));
     temp->customerid=a;
     temp->officerid=b;
     temp->islem=c;
     temp->koltuk=d;
     if (front1 == NULL)
     {
           front1=temp;
           front1->next=NULL;
           rear1=front1;
     }
     else
     {
           front1->next=temp;
           front1=temp;
           front1->next=NULL;
 }
}





void delQueue(int p)
{ int k,l,m,n,o,i,s,t,x,r,officer;
officer=p;
       struct Node *temp, *var=rear;
      if(var==rear)
      {

k=var->customerid;
	     l=var->firma;
             m=var->islem;
             n=var->ucus;
             o=var->koltuk;
             
             i=ID1[k-1].ne;
//fprintf(stderr,"customer %d  ın random işlemi   %d\n",k, i);

if(i==1){
if(set[l][n] >= o){
pthread_mutex_lock(&array[l][n]);
set[l][n]=set[l][n]-o;
pthread_mutex_unlock(&array[l][n]);
pthread_mutex_lock(&mut2);
push1(ID1[k-1].id,officer,i,o);
display1();
pthread_mutex_unlock(&mut2);
}

else goto ali;
fprintf(stderr,"buy yapıldı\n");
ID1[k-1].islem=ID1[k-1].islem-1;


}

if(i==2){
pthread_mutex_lock(&array[l][n]);
set[l][n]=set[l][n]-o;
pthread_mutex_unlock(&array[l][n]);
ID1[k-1].reserve=ID1[k-1].reserve-o;
ID1[k-1].rsrvkltk=ID1[k-1].rsrvkltk+o;

fprintf(stderr,"reserve yapıldı\n");
pthread_mutex_lock(&mut2);
push1(ID1[k-1].id,officer,i,o);
display1();
pthread_mutex_unlock(&mut2);
ID1[k-1].islem=ID1[k-1].islem-1;
}
if(i==3){
fprintf(stderr,"cancel yapıldı\n");
ID1[k-1].reserve=ID1[k-1].reserve+ID1[k-1].rsrvkltk;
ID1[k-1].rsrvkltk=0;
pthread_mutex_lock(&mut2);
push1(ID1[k-1].id,officer,i,o);
display1();
pthread_mutex_unlock(&mut2);
ID1[k-1].islem=ID1[k-1].islem-1;
}
if(i==4){
ali:
fprintf(stderr,"nothing yapıldı\n");
pthread_mutex_lock(&mut2);
push1(ID1[k-1].id,officer,i,o);
display1();
pthread_mutex_unlock(&mut2);
ID1[k-1].islem=ID1[k-1].islem-1;
}



             rear = rear->next;
 free(var);
display();
fprintf(stderr,"kuyruktan silindi\n");
pthread_mutex_lock(&ID1[k].sem);
      }
      else
      printf("\nQueue Empty");
}

void push(int a, int b, int c, int d, int e)
{
     struct Node *temp;
     temp=(struct Node *)malloc(sizeof(struct Node));
    
     temp->customerid=a;
     temp->firma=b;
     temp->islem=c;
     temp->ucus=d;
     temp->koltuk=e;

     if (front == NULL)
     {
           front=temp;
           front->next=NULL;
           rear=front;
     }
     else
     {
           front->next=temp;
           front=temp;
           front->next=NULL;
 }
}




void *Customer(void *z){
    unsigned int i,k,l,n,s;

	i=(long)z; 
if(ID1[i].islem==0)
ID1[i].islem=3;
if(ID1[i].reserve==0)
ID1[i].reserve=3;
//fprintf(stderr,"customer a geldi\n");  
//fprintf(stderr,"customer reserve  %d\n",ID1[i].reserve);

while(gun == 5){


sem_post(&mutex);
if(ID1[i].islem >0 ) {
 ID1[i].ne= rand() % 4 + 1;

if (ID1[i].ne==1){

 ID1[i].firma = rand() % d + 1;

  ID1[i].ucus= rand() % p+ 1;

k=rand() % 40+ 1;

pthread_mutex_lock (&mutc);
push(i+1,ID1[i].firma, ID1[i].ne,  ID1[i].ucus, k);
display();

sem_post(&semid);
//semm=ID1[i].sem;

pthread_mutex_unlock (&mutc);
pthread_mutex_unlock(&ID1[i].sem);
       }
else if (ID1[i].ne==2){
if(ID1[i].reserve>0){

ID1[i].firma = rand() % d + 1;

  ID1[i].ucus= rand() % p+ 1;
k=rand() % ID1[i].reserve + 1;
//sem_wait(&semof);
pthread_mutex_lock (&mutc);
push(i+1,ID1[i].firma, ID1[i].ne,  ID1[i].ucus, k);
display();
sem_post(&semid);
//semm=ID1[i].sem;
//sem_wait(&semm);

pthread_mutex_unlock (&mutc);
pthread_mutex_unlock(&ID1[i].sem);
}
else goto sema;
}
else if (ID1[i].ne==3){
//sem_wait(&semof);
pthread_mutex_lock (&mutc);
push(i+1,10,10,10,ID1[i].rsrvkltk);
display();
sem_post(&semid);
//semm=ID1[i].sem;
//sem_wait(&semm);

pthread_mutex_unlock (&mutc);
pthread_mutex_unlock(&ID1[i].sem);

}
else if(ID1[i].ne==4){
sema:
//sem_wait(&semof);
pthread_mutex_lock (&mutc);
push(i+1,10,10,10,11);
display();
sem_post(&semid);
//semm=ID1[i].sem;
//sem_wait(&semm);

pthread_mutex_unlock (&mutc);
pthread_mutex_unlock(&ID1[i].sem);

}
ID1[i].islem=ID1[i].islem-1;
}

//printf("işlem bitti");
}


}





void *Officer(void *z){
      
  unsigned int i,k,l,n,s;
	
	i=(long)z;
while(gun ==5 ){
 //sem_post(&semof);

sem_wait(&semid);
printf("officer a geldi\n");
pthread_mutex_lock (&mut);
printf("delqueue ya girdi\n");
delQueue(ID2[i].id);
pthread_mutex_unlock (&mut);

sem_wait(&mutex);
   printf("delqueue dan silindi\n");

}



}



int main(){
	int n,k,l;
long i;
	
	file = fopen("input.txt", "r");
	fp=fopen("code.txt","w");
	str=fgets (ch, SIZE, file);
pthread_mutex_init(&mut, NULL);
	while( str != NULL){
if(say==0){
sscanf(str,"%d %d %d %d %d",&a,&b,&c,&d,&p);

	for(k=0;k<d;k++){
		for(l=0;l<p;l++)
			set[k][l]=40;
	}

	for(i=0;i<a;i++){
		ID1[i].id=i+1;
	}

	for(i=0;i<b;i++){
		ID2[i].id=i+1;
	}
		



}

else if(say==1){
sscanf(str,"%d %d %d",&x,&t,&r);

ID1[x-1].islem=t;
ID1[x-1].reserve=r;
printf("customer islem %d   %d  %d\n",ID1[x].islem,t,r);


}


 str = fgets(ch,SIZE,file);

say=1;
}
sem_init(&mutex, 0, b);
//while(günsayısı<c){
pthread_t Thread[a];
pthread_t Thread1[b];


  for(i=0;i<b;i++){
        pthread_create(&Thread1[i], NULL,Officer, (void *)i);
            
    }

          for(i=0;i<a;i++){
        pthread_create(&Thread[i], NULL,Customer, (void *)i);
            
    }

	/*for(i=0;i<a;i++) {
		pthread_join(Thread[i], NULL);
	}*/
 



sleep(3);
gun=6;
 fclose(fp);
for(i=0;i<a;i++) {
		pthread_join(Thread[i], NULL);
	}
for(i=0;i<b;i++) {
		pthread_join(Thread1[i], NULL);
	}





pthread_mutex_destroy(&mut);
pthread_mutex_destroy(&mutc);
	pthread_exit(NULL);

	fclose(file);
	
		return 0;
}


