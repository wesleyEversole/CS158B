//may need flags for gcc to work
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>



/*
#define DEMO_USE_SNMP_VERSION_1
#ifdef DEMO_USE_SNMP_VERSION_1
*/

typedef struct IP {
	int o1;
	int o2;
	int o3;
	int o4;
}IP;





void rateChart(int interfaceID, int numSteps, float rate[]) {
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

void neighborChart(int interfaceID, int numNieghbors, IP neighborIP[]) {
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
		printf("|%8d | %3d.%3d.%3d.%3d |\n",interfaceID,neighborIP[n].o1,nieghboorIP[n].o2,nieghboorIP[n].o3,nieghboorIP[n].o4);
	}
	printf("\\---------+-----------------/");

}
