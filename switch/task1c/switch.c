/*******************************************************
 *
 *  Switch Routines for EECE 494, Assignment 2.
 *
 *  Created by _________, University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the switch routines.  You should use the headers as
 *  supplied.  All your code for Assignment 2 will go in this
 *  file (and possibly in switch.h)
 *
 ******************************************************/

#include "defs.h"

packet_t *queue[4];

void *switch_thread_routine(void *arg)
{
   /* Add your code here */
	int i;
	int to_port;
	int from_port;
	int cnt = 0;
	int a;
	int result;
	BOOL in_progress = TRUE;
	packet_t *packet;   /* Temporary packet that will hold the packet between in port and out port */

	while(1) {
		for(i=0 ; i<4 ; i++) {

			/* Cycle through the ports and check if any in ports have a packet waiting to be switched */

			if(in_port[i].flag) {
					port_lock(&(in_port[i]));

					/* New packet to be passed to the out port */

					packet = (packet_t *) malloc(sizeof(packet_t));

					packet_copy(&(in_port[i].packet),
               					packet);
				    
					result = cam_lookup_address(&(packet->address));

      				from_port = packet->payload & 3;
      				to_port = (packet->payload / 4) & 3;

      				if (from_port != i) {

         				printf("Error: received packet from port %d when it should have come on port %d\n",
                     			from_port, i);
         				
         			} else {

      					switch_enqueue(result, packet);

      				}

  					in_port[i].flag = FALSE;
					port_unlock(&(in_port[i]));
			}
		}


		for(i=0 ; i<4 ; i++) {
			if(queue[i] && !(out_port[i].flag)) {

					port_lock(&(out_port[i]));

					/* New packet to be passed to the out port */

					packet = switch_dequeue(i);

					to_port = (packet->payload / 4) & 3;

      				if (to_port != i) {

         				printf("Error: received packet to port %d when it should have come on port %d\n",
                     			to_port, i);
         			}

					packet_copy(packet,
               					&(out_port[i].packet));

					out_port[i].flag = TRUE;

					port_unlock(&(out_port[i]));
			}
		}
	}
}


void switch_init()
{
   /* Add your code here.  At the very least, you probably
      want to include a call to cam_init() */
	cam_init();
}

void switch_add_entry(ip_address_t *address,
                      int port)
{
   /* Add your code here.  It might be as simple as adding
      a call to cam_add_entry() */
	cam_add_entry(address, port);
}

void switch_free()
{
   /* add your code (if any) here */
	cam_free();
}

void switch_enqueue(int i, packet_t *packet) 
{
	packet_t *tmp = queue[i];
	packet->next = NULL;

	if(!queue[i]) {
		queue[i] = packet;
		return;		
	}

	while(tmp)
	{
		if(!(tmp->next))
			break;
		tmp=tmp->next;
	}

	tmp->next = packet;
}


packet_t* switch_dequeue (int i)
{
	packet_t *packet = NULL;

	if(queue[i]) {
		packet = queue[i];
		queue[i] = queue[i]->next;
	}

	return packet;
}