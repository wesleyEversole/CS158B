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
#define MIDTOPOFTABLEIFA "|  Number |       IP        |\n"
#define TABLESEPARATOR "+---------+-----------------+\n"
#define BOTTOMOFTABLE "\\---------+-----------------/\n"
#define GRAPHSCALE "Mbps  0..1..2..3..4..5..6..7..8..9.10.11.12.13\n"
//.14.15.16.17.18.19.20.21.22.23.24.25.26.27.28.29.30.31.32.33.34.35.36.37.38.39.40\n"
//char length of graph scale
#define CHARLENOFGS 40
typedef struct IP {
	int o1;
	int o2;
	int o3;
	int o4;
} IP;

#define IPOCTET(i) ((i)>=0 && (i)<=255)
#define IPSANITY(ip) (IPOCTET((ip).o1) && IPOCTET((ip).o2) && IPOCTET((ip).o3) && IPOCTET((ip).o4))

void rateChart(int interfaceID, int numSteps,int sizeOfSteps, float * rate) {
	/*
	 * Create a chart of rates per time slot
	 *
	 * Interface #n
	 * Time (s)
	 * 0 ***(1.02)
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
	char line[CHARLENOFGS+1];
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
		line[CHARLENOFGS]= '\0';
		printf("%3d|%s",i*sizeOfSteps,line);
		//might need to do line[39]=='*' for the if statement
		if((CHARLENOFGS/3) < (int)(rate[i])){
			printf(">>>");
		} else if (rate[i]<0) {
			printf("<<<");
		} else  {
			printf("   ");
		}
		printf("(%f)\n",rate[i]);

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
//IFA= interface array
void interfaceChart(int * IFA,int numInterfaces,IP * neighborIP){
	printf(TOPOFTABLE);
	printf(MIDTOPOFTABLEIFA);
	printf(TABLESEPARATOR);
	int i=0;
	for(i=0;i<numInterfaces;i++){
		printf("|%8d | %3d.%3d.%3d.%3d |\n",IFA[i],neighborIP[i].o1,neighborIP[i].o2,neighborIP[i].o3,neighborIP[i].o4);
	}

}

void test0() {
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
	float listMbps[numSteps];
	float *lM=&listMbps[0];
	lM[0]=0.0;
	lM[1]=5.2312;
	lM[2]=13;
	lM[3]=-1.1;
	lM[4]=43.2;
	lM[5]=12.2;
	lM[6]=100.2;
	lM[7]=0;
	lM[8]=8.6;
	lM[9]=9.2;
	rateChart(1,numSteps,stepSize,lM);
	//end of Mbps range test
}

int main(int argc, char *argv[]){

	int interval;
	int numSamples;
	IP agent;

	if (argc != 4) {
		fprintf(stderr,"Usage: %s time_interval #samples agent_IP\n",argv[0]);
		exit(-1);
	}

	// interval check
	if (sscanf(argv[1],"%d",&interval) !=1) {
		fprintf(stderr,"time interval must be a positive integer\n");
		exit(-1);
	}
	if (interval <1) {
		fprintf(stderr,"time interval must be a positive integer\n");
		exit(-1);
	}

	// number of samples
	if (sscanf(argv[2],"%d",&numSamples) !=1) {
		fprintf(stderr,"number of samples must be a positive integer\n");
		exit(-1);
	}
	if (numSamples<1) {
		fprintf(stderr,"number of samples must be a positive integer\n");
		exit(-1);
	}

	// Agent IP
	if (sscanf(argv[3],"%d.%d.%d.%d",&agent.o1, &agent.o2, &agent.o3, &agent.o4)!=4) {
		fprintf(stderr, "agent IP not value must be xxx.xxx.xxx.xxx  where xxx is 0 to 255\n");
		exit(-1);
	}
	// ... check o1,o2,o3,o4 for 0-255
	if (!IPSANITY(agent)) {
		fprintf(stderr, "agent IP not value must be xxx.xxx.xxx.xxx  where xxx is 0 to 255\n");
		exit(-1);
	}

    test0();
return 1;
}
