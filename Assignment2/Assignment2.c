//may need flags for gcc to work
/*
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
*/
#include <stdio.h>



/*
#define DEMO_USE_SNMP_VERSION_1
#ifdef DEMO_USE_SNMP_VERSION_1
*/
#define MAX_OCTET 255
typedef struct IP {
	int o1;
	int o2;
	int o3;
	int o4;
}IP;


void rateChart(int interfaceID, int numSteps, float *rate) {
	/*
	 * Create a chart of rates p[er time slot
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

	printf("/---------+-----------------\\\n");
	printf("|Interface|   Neighbor      |\n");
	printf("+---------+-----------------+\n");
	int n;

	for(n=0; n<numNieghbors; n++) {
		printf("|%8d | %3d.%3d.%3d.%3d |\n",interfaceID,neighborIP[n].o1,neighborIP[n].o2,neighborIP[n].o3,neighborIP[n].o4);
	}
	printf("\\---------+-----------------/\n");

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
	//end of Mbps range test
return 1;
}
