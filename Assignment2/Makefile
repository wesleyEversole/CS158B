
CC=gcc

OBJS1=snmpdemoapp.o
OBJS2=example-demon.o nstAgentSubagentObject.o
OBJS3=asyncapp.o
TARGETS=example-demon snmpdemoapp asyncapp

CFLAGS=-I. `net-snmp-config --cflags`
BUILDLIBS=`net-snmp-config --libs`
BUILDAGENTLIBS=`net-snmp-config --agent-libs`

# shared library flags (assumes gcc)
DLFLAGS=-fPIC -shared

as2:
	$(CC) $(CFLAGS) -o as2 assignment2aw.c $(BUILDLIBS)

all: $(TARGETS)

snmpdemoapp: $(OBJS1)
	$(CC) -o snmpdemoapp $(OBJS1) $(BUILDLIBS)

asyncapp: $(OBJS3)
	$(CC) -o asyncapp $(OBJS3) $(BUILDLIBS)

example-demon: $(OBJS2)
	$(CC) -o example-demon $(OBJS2)  $(BUILDAGENTLIBS)

clean:
	rm $(OBJS2) $(OBJS2) $(TARGETS)

nstAgentPluginObject.so: nstAgentPluginObject.c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o assign.o assignment2aw.c
	$(CC) $(CFLAGS) $(DLFLAGS) -o nstAgentPluginObject.so assignment2.o
