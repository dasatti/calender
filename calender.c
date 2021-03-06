#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

/**********************************
*
* Program : calender
* Usage : calender [[day] month year]
* Author: Danish Satti
* email: dasatti@gmail.com
*
***********************************/

int get_total_days(int month,int year){
	
	int days;
	bool isLeap = (year%4==0);
	switch(month){
		case 4:
		case 6:
		case 9:
		case 11:
			days=30;
		break;
		case 2:
			if(isLeap) days=29; else days=28; //check for leap
		break;
		default: days=31;
	}

	return days;
}

int day_of_week(int d, int m, int y)
{
    	//src: http://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/
    	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    	y -= m < 3;
    	return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

void print_month(int date, int month, int year){


	const char *days[] = {"Su","Mo","Tu","We","Th","Fr","Sa"};
	const char *months[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	int t_days = get_total_days(month,year);
	int day = day_of_week(date,month,year);
	int first_day = day_of_week(1,month,year);

	//printf("     %s %d\n",months[month-1],year);
	printf("   %s %d %s %d\n",(days[day]),date,months[month-1],year);
	for(int i=0;i<7;i++) printf("%3s",days[i]);
	printf("\n");
	for(int i=1-first_day;i<=t_days;i++){
		if(i<=0){
			printf("   ");
			continue;
		}
		printf("%3d",i);
		if((i+first_day)%7==0) printf("\n");
	}
	printf("\n");
}

void print_usage(){

	printf("Usage: calender [[day] month year] \n");
}


int main(int argc, char* const argv[]){

	struct timeval tv;
	struct tm* ptm;

	gettimeofday(&tv,NULL);
	ptm = localtime(&tv.tv_sec);
	//printf("Today's date : %d %d %d %d %d\n",ptm->tm_mday,ptm->tm_mon,ptm->tm_year+1900,ptm->tm_wday,ptm->tm_yday);
	int d = ptm->tm_mday, m=ptm->tm_mon+1, y = ptm->tm_year+1900, wd = ptm->tm_wday;

	if(argc>1){
		if(argc == 4){
			d = atoi(argv[1]),m=atoi(argv[2]),y=atoi(argv[3]);
		} else if(argc ==3){
			d = 1,m=atoi(argv[1]),y=atoi(argv[2]);
		} else {
			print_usage();
			return -1;
		}
	}
	

	assert(d>0 && d<=31 && m>0 && m<=12 && y>0);
	print_month(d,m,y);

	return 0;
}
