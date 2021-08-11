#include<string.h>
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int dsize,csize,rsize,lsize,tsize,tnum1,tnum2,b,tc[20]; 
struct college
    {
   		struct
   		{
       		char tname[20];
       		int  teachsubs;
       		int totcre;
  		}
		teach[20];
    	struct 
    	{
    		
    		char cname[20];
			int r;
			int totsub;	
			int sumcre;
    		struct
    		{	
    			int  tcode;
        		char tname[20];
        		char sname[20];
        		int credit;
    		}
    		tsub[20];
    	}
    	co[20];
       	int room[20];
    };
    struct college col;
struct tlist
{
	struct 
	{
		struct 
		{
			struct 
			{
				bool busy;
			}busy[20];
			struct 
			{
				char fsubject[20]={'N'};
				char fName[20]={'N'};
			}
			teacher[20];
		}
		lect[20];
	}
	day[20];
};
struct tlist tt[20];
void input()              
{    
    printf("enter total days,lectures,cources,teachers,rooms");
    scanf("%d %d %d %d %d",&dsize,&lsize,&csize,&tsize,&rsize);
    for(int i=0;i<rsize;i++)
    {
    	printf(" enter room number %d",i+1);
    	scanf("%d",&col.room[i]);
	}
    for(int i=0;i<tsize;i++)
    {
        printf("enter teachr name %d ",i);
        scanf("%s",col.teach[i].tname);
    }
    //courses
    for(int i=0;i<csize;i++)
    {
    	
        printf("enter course name ");
        scanf("%s",col.co[i].cname);
       // printf("\nenter a room for this course");
        //for(int j=0;j<rsize;j++)
        //{
         //   printf(" room %d %s",j,col.room[j]);
       // }
        //scanf("%d",&tnum2);
      //  col.co[i].r=col.room[tnum2];
        printf("enter total subjects ");//less than m x n
        scanf("%d",&col.co[i].totsub);        
        for(int j=0;j<col.co[i].totsub;j++)
        {
            printf("enter subject name ");
            char temp[20];
            scanf("%s", temp);
        	printf("select a teacher for subject %d",j);
            for(int k=1;k<=tsize;k++)
            printf("\n%d %s\n",k,col.teach[k-1].tname);
            scanf("%d",&tnum1);
     	    //col.co[i].subj[j].tcode=tnum1-1;
            strcpy(col.co[i].tsub[tnum1-1].sname,temp);
            printf("enter subject creadit ");
            scanf("%d",&col.co[i].tsub[tnum1-1].credit);
            
            col.co[i].sumcre+=col.co[i].tsub[tnum1-1].credit;//less than m x m
     	    col.co[i].tsub[tnum1-1].tcode=tnum1-1;
            strcpy(col.co[i].tsub[tnum1-1].tname,col.teach[tnum1-1].tname);
            col.teach[tnum1-1].teachsubs++;
			col.teach[tnum1-1].totcre=col.teach[tnum1-1].totcre+col.co[i].tsub[tnum1-1].credit;    //    less than m x n
            //th[tmptch].allsub+=co[i].creadit[j];
            if(col.co[i].sumcre>lsize*dsize)
            {
            	cout<<"THE TOTAL CREDITS IN THE COURSE ARE MORE THAN LIMITED";
            	exit(0);
			}
            if(col.teach[tnum1-1].totcre>lsize*dsize-dsize)//check total sub limit for a teacher
            {
                printf("more than limited sub to a teacher");
                exit(0);
            }
            
        }
    }  
}
int  check(int i,int j,int n,int l)
{
	for(int z=0;z<=n;z++)
	{
		if(tt[z].day[i].lect[j].busy[l].busy==true)
		{
			l=l+1;
			if(l==tsize)
				l=0;
			check(i,j,n,l);	
		}
	}	
	return l;
}
void generate()
{
	int c,t;
	for(int n=0;n<csize;n++)
	{
		tc[n]=col.co[n].sumcre;
			for(int k=0;k<col.co[n].totsub;k++)
			{	 
				int m=k;
				while(col.co[n].tsub[m].credit<=0)
				{
					m=m+1;
				}
			
				for(int i=0,j=0;i<dsize;j++,i++)
				{	
					if(n>0)
					{
						m=check(i,j,n-1,m);
					}
						if(j==lsize)
						{
							j=0;
						}
						while(tt[n].day[i].lect[j].teacher[j].fName[0]!='N')
						{
								j++;
						}	
						if(col.co[n].tsub[m].credit>0)
						{
							strcpy(tt[n].day[i].lect[j].teacher[j].fName,col.co[n].tsub[m].tname);
							strcpy(tt[n].day[i].lect[j].teacher[j].fsubject,col.co[n].tsub[m].sname);
							tt[n].day[i].lect[j].busy[m].busy=true;
							col.co[n].tsub[m].credit--;
							tc[n]--;			
						}	
					}
			}
	}
}
void print()
{
	for(int n=0;n<csize;n++)
	{
		printf("\t\t\tCOURSE %9s TIMETABLE",col.co[n].cname);
		printf("\n-------------------------------------------------------------------------\n\t");
		for(int k=0;k<lsize;k++)
		{
			if(k==lsize/2)
			{
				printf("\t");		
			}
			printf("      lecture %d    ",k+1);
				
		}
		printf("\n-------------------------------------------------------------------------");
		for(int i=0;i<dsize;i++)
		{
			printf("\nday %d ",i+1);
			for(int j=0;j<lsize;j++)
			{
				if(j==lsize/2)
				{
					printf("  LUNCH");
				}
				printf("%9s",tt[n].day[i].lect[j].teacher[j].fName);
				printf("-%9s",tt[n].day[i].lect[j].teacher[j].fsubject);	
			}
		}
		printf("\n------------------------------------------------------------------------");
		printf("\n------------------------------------------------------------------------\n\n");
	}
	
}
int main()
{
	input();
	generate();
	print();
}
