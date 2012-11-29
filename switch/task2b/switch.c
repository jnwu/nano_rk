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





//define VOQ data structure
packet_t *VOQ_queue[4][4]; //for each in_port, 4 queues are needed for each out_port VOQ_queue[in_port#][out_port#]

//Define priority variables
int in_prio[4];
int out_prio[4];

//define global data structure for sending / receiving requests
bool request_queue[4][4];//for in_port to send request; request_queue[in_port#][out_port#]
bool response_queue[4][4]; //for out_port to send response; response_queue[in_port#][out_port#]

//in_port busy flag
bool in_port_avail[4]; // has packet to be send?


//match output port to inport
int out_match_in[4]; //out_match_in[outport#] = inport#;


void *switch_thread_routine(void *arg)
{
   /* Add your code here */
	int i,k;
	int to_port;
	int from_port;
	int cnt = 0;
	int a;
	int result;
	BOOL in_progress = TRUE;
	packet_t *packet;   /* Temporary packet that will hold the packet between in port and out port */

	int count;
	int priority_pos;

	init_variables();	

	while(1) {
	
		for (i=0; i<4; i++){

			for (k=0; k<4; k++){
				response_queue[i][k]=false;			
			}
		}
		
		
		//for each input port, put incoming packets in the corresponding output_port queue
		for(i=0 ; i<4 ; i++) {

			/* Cycle through the ports and check if any in ports have a packet waiting to be switched */
			
			//change the content below to put packets into VOQ
			if(in_port[i].flag) { //if flag is set
					port_lock(&(in_port[i])); //lock in_port

					/* New packet to be passed to the out port */

					packet = (packet_t *) malloc(sizeof(packet_t)); //locate memory for tmp packet

					packet_copy(&(in_port[i].packet),
               					packet); //copy incoming packet to tmp packet holder
				    
					result = cam_lookup_address(&(packet->address)); //get the destination port
					
      				from_port = packet->payload & 3; //get the source port
      				to_port = (packet->payload / 4) & 3; //get the port to send the packet to

      				if (from_port != i) { //if the source port does not match, report error

         				printf("Error: received packet from port %d when it should have come on port %d\n",
                     			from_port, i);
         				
         			} else { // if no error

      					VOQ_enqueue(i,result, packet); //add the packet to the destination address's queue

      				}

  					in_port[i].flag = FALSE; //clear the in_port's busy flag
					port_unlock(&(in_port[i])); // free the in_port
			}
		}

		
		//for each input port, send request to the corresponding output port
		for(i=0 ; i<4 ; i++) {
			for (k=0; k<4; k++){
				if(VOQ_queue[i][k]){
					request_queue[i][k] = false;
					in_port_avail[i]=false;
				}
			}
		}
		
		
		
	
	//if there are still packet to route 
	while ( !in_port_matched()){
		
		
		
		
		//for each output port, check incoming request and reply with Yes / No response
		for (i=0; i<4; i++){
		
			count = 0;
			priority_pos = out_prio[i];
			while (count < 4 && request_queue[priority_pos][i]) {
				
				priority_pos = priority_ring_counter(priority_pos);
				count++;
			}
			
			if (count != 4)
				response_queue[priority_pos][i]=true;
			
		   
			
		}
		
		

		

		//for each input port, if it's not matched yet, check response from the output port, if match, send the packet with highest priority, increment input port priority, increment output port priority

		for (i = 0; i<4; i++){
		   if(!in_port_avail[i]){
			count = 0;
			priority_pos = in_prio[i];
			while(count < 4 && !response_queue[i][priority_pos]){
				priority_pos = priority_ring_counter(priority_pos);
				count++;
			}
			
			if (count != 4){
				//clear request for packets going to other ports & clear requests for packets from other in_ports to this out_port
				for (k=0; k<4; k++){
					request_queue[i][k] = true;
					request_queue[k][priority_pos]=true;
				}
				
				


				//record the match
				out_match_in[priority_pos]=i;

				//update in_port priority pointer
				in_prio[i]=priority_ring_counter(priority_pos);

				//update out_port priority pointer
				out_prio[i]=priority_ring_counter(i);

				

				
			}
		    }
			
		}

		//update each in / out port's status
		update_port_status();	
		
	}

	
	for(i=0 ; i<4 ; i++) {
			
			if(out_match_in[i]!=-1 && !(out_port[i].flag)) { //if there is packet scheduled for this port

					port_lock(&(out_port[i])); //get a hold of the out_port

					/* New packet to be passed to the out port */

					packet = VOQ_dequeue(out_match_in[i],i); //obtain packet from the queue

					to_port = (packet->payload / 4) & 3; //calculate which port the packet is destined to

      				if (to_port != i) { //if the destined port is not the current port, report error

         				printf("Error: received packet to port %d when it should have come on port %d\n",
                     			to_port, i);
         			}

					packet_copy(packet,
               					&(out_port[i].packet)); // if not error, copy the packet to out_port to be sent

					out_port[i].flag = TRUE; //flag outport to be busy

					port_unlock(&(out_port[i])); //send packet
					
					out_match_in[i]=-1;
			}
		}
		
		
	}
}


void switch_init()
{


   /* Add your code here.  At the very least, you probably
      want to include a call to cam_init() */
	cam_init();

   //also, initializing the global variables here

	
	
	
	
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




void VOQ_enqueue(int iPort, int oPort, packet_t *packet){

	packet_t *tmp = VOQ_queue[iPort][oPort]; //obtain a copy of the queue for packets from in_port# going to out_port#
	packet->next = NULL; //make the passed in packet's next packet to be null


	if(!VOQ_queue[iPort][oPort]) {
		VOQ_queue[iPort][oPort] = packet; //if the current queue is empty, then add packet as the only element of the queue
		return;		
	}

	while(tmp) //try to reach the last element of the linked list
	{
		if(!(tmp->next))
			break;
		tmp=tmp->next;
	}

	tmp->next = packet; //insert packet to be the end of the queue
	
	
}

packet_t* VOQ_dequeue (int iPort, int oPort){
	packet_t *packet = NULL; //create a packet place holder

	if(VOQ_queue[iPort][oPort]) { //if queue is not empty
		packet = VOQ_queue[iPort][oPort];  //obtain the head of the queue
		VOQ_queue[iPort][oPort] = VOQ_queue[iPort][oPort]->next; //the second element is the new head of the queue
	}

	return packet; //return the obtained packet
}


//for compute inport status
bool in_port_matched(){
	
	return in_port_avail[0]&&in_port_avail[1]&&in_port_avail[2]&&in_port_avail[3];
}


int priority_ring_counter(int currentPriority){
	if (currentPriority == 3) return 0;
	else
		return ++currentPriority;
}

//update each in_port's status
void update_port_status(){
	int i;
	for (i = 0; i<4; i++){
		in_port_avail[i] = request_queue[i][0] && request_queue[i][1] && request_queue[i][2] && request_queue[i][3];
		
	}
}

void init_variables(){
	int i, k;
	for (i=0; i<4; i++){
		for (k=0; k<4; k++){
			request_queue[i][k]=true;
			//response_queue[i][k]=false;
			//VOQ_queue[i][k] = NULL;
		}
		in_port_avail[i]=true;
		in_prio[i]=0;
		out_prio[i]=0;
		out_match_in[i]=-1;
	}

}
