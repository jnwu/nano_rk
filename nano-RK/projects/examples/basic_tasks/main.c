/******************************************************************************
*  Nano-RK, a real-time operating system for sensor networks.
*  Copyright (C) 2007, Real-Time and Multimedia Lab, Carnegie Mellon University
*  All rights reserved.
*
*  This is the Open Source Version of Nano-RK included as part of a Dual
*  Licensing Model. If you are unsure which license to use please refer to:
*  http://www.nanork.org/nano-RK/wiki/Licensing
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, version 2.0 of the License.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*  Contributing Authors (specific to this file):
*  Zane Starr
*******************************************************************************/


#include <nrk.h>
#include <include.h>
#include <ulib.h>
#include <stdio.h>
#include <avr/sleep.h>
#include <hal.h>
#include <nrk_error.h>
#include <nrk_events.h>
#include <nrk_timer.h>


// scheduled tasks
NRK_STK Stack1[NRK_APP_STACKSIZE];
nrk_task_type TaskOne;
void Task1(void);

NRK_STK Stack2[NRK_APP_STACKSIZE];
nrk_task_type TaskTwo;
void Task2 (void);

NRK_STK Stack3[NRK_APP_STACKSIZE];
nrk_task_type TaskThree;
void Task3 (void);

NRK_STK Stack4[NRK_APP_STACKSIZE];
nrk_task_type TaskFour;
void Task4 (void);

void nrk_create_taskset();

// resource locks
nrk_sem_t *r1;
nrk_sem_t *r2;
nrk_sem_t *r3;
 
int main ()
{
  	uint8_t t;
  	nrk_setup_ports();
  	nrk_setup_uart(UART_BAUDRATE_115K2);

  	//printf( "Starting up...\r\n" );

  	nrk_init();

  	nrk_led_clr(ORANGE_LED);
  	nrk_led_clr(BLUE_LED);
  	nrk_led_set(GREEN_LED);
  	nrk_led_clr(RED_LED);
 
  	nrk_time_set(0,0);
  	nrk_create_taskset ();

  	r1 = nrk_sem_create(1,2);
  	r2 = nrk_sem_create(1,2);
  	r3 = nrk_sem_create(1,2);
  	if(!r1 || !r2 || !r3) nrk_kprintf( PSTR("error: sem_create\r\n" ));
	else nrk_start();
  
  	return 0;
}


void Task1()
{
	//uint16_t cnt=0;
	//printf( "My node's address is %d\r\n",NODE_ADDR );	
  	//printf( "Task1 PID=%d\r\n",nrk_get_pid());
	int8_t v;

  	while(1) {
		nrk_led_toggle(ORANGE_LED);
		nrk_wait_until_next_period();

		// acquire lock
		printf("t[%d]: sem_pend\n", nrk_get_pid());
		v = nrk_sem_pend(r1);
		if(v==NRK_ERROR) nrk_kprintf( PSTR("T1 error pend\r\n"));

		// wait some time inside semaphore to show the effect
		printf("t[%d]: sem_acquired\n", nrk_get_pid());
		nrk_spin_wait_us(1000000);

		// release lock
		v = nrk_sem_post(r1);
		if(v==NRK_ERROR) nrk_kprintf( PSTR("T1 error post\r\n"));
		printf("t[%d]: sem_post\n", nrk_get_pid());

		nrk_wait_until_next_period();

		//printf( "Task1 cnt=%d\r\n",cnt );
		//nrk_kprintf( PSTR("Task1 accessing semaphore\r\n"));
		//nrk_kprintf( PSTR("Task1 holding semaphore\r\n"));
		//nrk_kprintf( PSTR("Task1 released semaphore\r\n"));
		//cnt++;
	}
}

void Task2()
{
  	//uint8_t cnt=0;
  	//printf( "Task2 PID=%d\r\n",nrk_get_pid());
  	int8_t v;

  	while(1) {
		nrk_led_toggle(ORANGE_LED);

		// acquire lock
		printf("t[%d]: sem_pend\n", nrk_get_pid());
		v = nrk_sem_pend(r1);
		if(v==NRK_ERROR) nrk_kprintf( PSTR("T2 error pend\r\n"));

		// wait some time inside semaphore to show the effect
		printf("t[%d]: sem_acquired\n", nrk_get_pid());
		nrk_spin_wait_us(1000000);

		// release lock
		v = nrk_sem_post(r1);
		if(v==NRK_ERROR) nrk_kprintf( PSTR("T2 error post\r\n"));
		printf("t[%d]: sem_post\n", nrk_get_pid());

		nrk_wait_until_next_period();


		//printf( "Task2 cnt=%d\r\n",cnt );
		//nrk_kprintf( PSTR("Task2 accessing semaphore\r\n"));
		//nrk_kprintf( PSTR("Task2 holding semaphore\r\n"));
		//nrk_kprintf( PSTR("Task2 released semaphore\r\n"));
        	//cnt++;
        }
}

void Task3()
{
	//uint16_t cnt=0;
  	//printf( "Task3 PID=%d\r\n",nrk_get_pid());
	uint16_t i;

  	while(1) {
		nrk_spin_wait_us(100000);
		nrk_wait_until_next_period();

		printf("t[%d]\n", nrk_get_pid());
		//printf( "Task3 cnt=%d\r\n",cnt );
		//cnt++;
	}
}

void Task4()
{
	//uint16_t i;
	//uint16_t cnt=0;
  	//printf( "Task4 PID=%d\r\n",nrk_get_pid());

  	while(1) {
		nrk_spin_wait_us(100000);
		nrk_wait_until_next_period();

		printf("t[%d]\n", nrk_get_pid());
		//printf( "Task4 cnt=%d\r\n",cnt );
		//cnt++;
	}
}

void nrk_create_taskset()
{
	uint8_t i;

	for (i = 0; i < NRK_MAX_RESOURCE_CNT; i++)
	{
		TaskOne.semaphores[i] = false;
		TaskTwo.semaphores[i] = false;
		TaskThree.semaphores[i] = false;
		TaskFour.semaphores[i] = false;
	}

  	TaskOne.task = Task1;
  	TaskOne.Ptos = (void *) &Stack1[NRK_APP_STACKSIZE];
  	TaskOne.Pbos = (void *) &Stack1[0];
  	//WTaskOne.prio = 2;
  	TaskOne.FirstActivation = TRUE;
  	TaskOne.Type = BASIC_TASK;
  	TaskOne.SchType = PREEMPTIVE;
  	TaskOne.period.secs = 0;
  	TaskOne.period.nano_secs = 250*NANOS_PER_MS;
  	TaskOne.cpu_reserve.secs = 0;
  	TaskOne.cpu_reserve.nano_secs =  50*NANOS_PER_MS;
  	TaskOne.offset.secs = 0;
  	TaskOne.offset.nano_secs= 0;

	// @T3 SRP: Task registers which resources it will use.
  	//          Indices are in order of the created semaphores.
  	TaskOne.semaphores[0] = true;

  	nrk_activate_task (&TaskOne);

  	TaskTwo.task = Task2;
  	TaskTwo.Ptos = (void *) &Stack2[NRK_APP_STACKSIZE];
  	TaskTwo.Pbos = (void *) &Stack2[0];
  	//TaskTwo.prio = 4;
  	TaskTwo.FirstActivation = TRUE;
  	TaskTwo.Type = BASIC_TASK;
  	TaskTwo.SchType = PREEMPTIVE;
  	TaskTwo.period.secs = 0;
  	TaskTwo.period.nano_secs = 100*NANOS_PER_MS;
  	TaskTwo.cpu_reserve.secs = 0;
 	TaskTwo.cpu_reserve.nano_secs = 35*NANOS_PER_MS;
  	TaskTwo.offset.secs = 0;
  	TaskTwo.offset.nano_secs= 0;

	// @T3 SRP: Task registers which resources it will use.
  	//          Indices are in order of the created semaphores.
  	TaskTwo.semaphores[0] = true;

  	nrk_activate_task (&TaskTwo);

  	TaskThree.task = Task3;
  	TaskThree.Ptos = (void *) &Stack3[NRK_APP_STACKSIZE];
  	TaskThree.Pbos = (void *) &Stack3[0];
  	//TaskThree.prio = 3;
  	TaskThree.FirstActivation = TRUE;
  	TaskThree.Type = BASIC_TASK;
  	TaskThree.SchType = PREEMPTIVE;
  	TaskThree.period.secs = 0;
  	TaskThree.period.nano_secs = 500*NANOS_PER_MS;
  	TaskThree.cpu_reserve.secs = 0;
  	TaskThree.cpu_reserve.nano_secs = 100*NANOS_PER_MS;
  	TaskThree.offset.secs = 0;
  	TaskThree.offset.nano_secs= 0;
  	nrk_activate_task (&TaskThree);

  	TaskFour.task = Task4;
  	TaskFour.Ptos = (void *) &Stack4[NRK_APP_STACKSIZE];
  	TaskFour.Pbos = (void *) &Stack4[0];
  	//TaskFour.prio = 4;
  	TaskFour.FirstActivation = TRUE;
  	TaskFour.Type = BASIC_TASK;
  	TaskFour.SchType = PREEMPTIVE;
  	TaskFour.period.secs = 0;
  	TaskFour.period.nano_secs = 400*NANOS_PER_MS;
  	TaskFour.cpu_reserve.secs = 0;
  	TaskFour.cpu_reserve.nano_secs = 100*NANOS_PER_MS;
  	TaskFour.offset.secs = 0;
  	TaskFour.offset.nano_secs= 0;
  	nrk_activate_task (&TaskFour);
}



