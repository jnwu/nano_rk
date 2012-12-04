
/*******************************************************
 *
 *  Switch Routines for EECE 494, Assignment 2
 *
 *  Created by _________, University of British Columbia
 *
 *  This file contains the prototypes for the switch 
 *  routines that you will create.  In addition,
 *  you can add any type information or anything else
 *  to this file that you want.  All the material you
 *  add for Assignment 2 should be in this file and switch.c.
 *  You won't need to modify any of the other other files.
 *
 ******************************************************/




void switch_init();

void switch_add_entry(ip_address_t *address,
                      int port);

void *switch_thread_routine(void *arg);

void switch_free();                      



//for putting packets into virtual queue (VOQ)
void VOQ_enqueue();

//for getting packet out of VOQ
packet_t* VOQ_dequeue (int iPort, int oPort);

//for compute inport status
bool in_port_matched();



//for the ports to iterate through requests and responses starting with its priority
int priority_ring_counter(int currentPriority);

//initialize variables
void init_variables();

//update each in_port's status
void update_port_status();