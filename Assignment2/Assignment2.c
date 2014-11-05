//may need flags for gcc to work
/*
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>



/*
#define DEMO_USE_SNMP_VERSION_1
#ifdef DEMO_USE_SNMP_VERSION_1
*/
#define MAX_OCTET 255
#define TOPOFTABLE "/---------+-----------------\\\n"
#define MIDTOPOFTABLE "|Interface|   Neighbor      |\n"
#define TABLESEPARATOR "+---------+-----------------+\n"
#define BOTTOMOFTABLE "\\---------+-----------------/\n"
#define GRAPHSCALE "   0..1..2..3..4..5..6..7..8..9.10.11.12.13\n"
//.14.15.16.17.18.19.20.21.22.23.24.25.26.27.28.29.30.31.32.33.34.35.36.37.38.39.40\n"
//char length of graph scale
#define CHARLENOFGS 40
typedef struct IP {
	int o1;
	int o2;
	int o3;
	int o4;
}IP;


void rateChart(int interfaceID, int numSteps,int sizeOfSteps, float * rate) {
	/*
	 * Create a chart of rates per time slot
	 *
	 * Interface #n
	 * Time (s)
	 * 0***(1.02)
	 * 2 *********(4.12)
	 * 4 *******(3.4)
	 * 6 *****************...(32.45)
	 * 8 *(0)
	 *   0 1 2 3 4 5 6 7 8
	 *         Mbps/s
	 */
	//char line[55];

	printf("Interface %d\n",interfaceID);
	printf("Time (s)\n");
	int i=0;
	//40 is the char len of GRAPHSCALE
	char line[CHARLENOFGS];
	int j=0;
	for(i=0;i<numSteps;i++){

		//40 is the char len of GRAPHSCALE
		for(j=0;j<CHARLENOFGS;j++){
			//may need to fix this float coming from rate!!! look here if '******' is not being made right to the correct length
			//3 should be the char spacing between numbers on GRAPHSCALE
			if(j/3<=floor(rate[i])){
			line[j]='*';
			}else{
				line[j]='-';
			}
		}
		printf("%d|%s",i*sizeOfSteps,line);
		//might need to do line[39]=='*' for the if statement
		if((CHARLENOFGS/3) > floor(rate[i])){
			printf("...(%f)\n",rate[i]);
		}else{
			printf("\n");
		}
	}
	printf(GRAPHSCALE);

}

void neighborChart(int interfaceID, int numNieghbors, IP * neighborIP) {
	/**
	 * NEIGHBORS
	 * /---------+-----------------\
	 * |Interface|   Neighbor      |
	 * +---------+-----------------+
	 * |       1 | 192.168.128.128 |
	 * |       1 | 192.168.003.001 |
	 * |       1 | 192.168.  3.  2 |
	 * \---------+-----------------/
	 *
	 */

	printf(TOPOFTABLE);
	printf(MIDTOPOFTABLE);
	printf(TABLESEPARATOR);
	int n;

	for(n=0; n<numNieghbors; n++) {
		printf("|%8d | %3d.%3d.%3d.%3d |\n",interfaceID,neighborIP[n].o1,neighborIP[n].o2,neighborIP[n].o3,neighborIP[n].o4);
	}
	printf(BOTTOMOFTABLE);

}
float rand_lim(float limit) {
/* return a random number between 0 and limit inclusive.
 */

    float divisor = RAND_MAX/(limit+1.0);
    float retval;

    do {
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

int main(int argc, char *argv[]){
	//simple print test for neighborChar
	IP IPTest;
	IP IParray [MAX_OCTET];
	IP *IPA=&IParray[0];
	int i=0;
	for(i=0;i<MAX_OCTET;i++){
		IPTest.o1=i;
		IPTest.o2=i;
		IPTest.o3=i;
		IPTest.o4=i;
		IParray[i]=IPTest;
	}
	neighborChart(1,MAX_OCTET,IPA);
	//end of neighborChar test
	//Simple Mbps range test
	srand(time(NULL));

	int numSteps=10;
	int stepSize = numSteps/5;
	float listMbps[numSteps/stepSize];
	float *lM=&listMbps[0];
	int j=0;
	for(j=0;j<numSteps/stepSize;j++){
		listMbps[j]=rand_lim(40.0);
	}

	rateChart(1,numSteps,2,lM);
	//end of Mbps range test
return 1;
}
