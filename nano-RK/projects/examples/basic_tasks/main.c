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
*******************************************************************************/

#include <nrk.h>
#include <include.h>
#include <ulib.h>
#include <stdio.h>
#include <hal.h>
#include <nrk_error.h>
#include <nrk_timer.h>
#include <nrk_stack_check.h>
#include <nrk_stats.h>


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

int
main ()
{
	nrk_setup_ports();
  	nrk_setup_uart(UART_BAUDRATE_115K2);

  	nrk_init();

  	nrk_led_clr(ORANGE_LED);
  	nrk_led_clr(BLUE_LED);
  	nrk_led_clr(GREEN_LED);
  	nrk_led_clr(RED_LED);
 
  	nrk_time_set(0,0);
  	nrk_create_taskset ();
  	nrk_start();
  
  	return 0;
}

void Task1()
{
	nrk_time_t t;
	uint16_t cnt;
	uint8_t val;
	cnt=0;
	//nrk_kprintf( PSTR("Nano-RK Version ") );
	printf( "%d\r\n",NRK_VERSION );

	//printf( "t1[addr]:%u\r\n",NODE_ADDR );
	//printf( "t1[pid]:%u\r\n",nrk_get_pid());
	t.secs=5;
	t.nano_secs=0;

	// setup a software watch dog timer
	nrk_sw_wdt_init(0, &t, NULL);
	nrk_sw_wdt_start(0);

  	while(1) {
		// Update watchdog timer
		nrk_sw_wdt_update(0);
		nrk_led_toggle(ORANGE_LED);

		// Button logic is inverter 0 means pressed, 1 not pressed
		//printf( "t1[cnt]:%u\nt1[button_state]:%u\r\n\n",cnt,val );
		nrk_wait_until_next_period();
		cnt++;
	}
}

void Task2()
{
	int16_t cnt;
  	//printf( "t2[pid]:%u\r\n",nrk_get_pid());
 	cnt=0;
 	while(1) {
		nrk_led_toggle(BLUE_LED);
		//printf( "t2[cnt]:%d\r\n\n",cnt );
		//nrk_stats_display_pid(nrk_get_pid());
		nrk_wait_until_next_period();
		cnt--;
	}
}

void Task3()
{
	uint16_t cnt;
 // 	printf( "Task3 PID=%u\r\n",nrk_get_pid());
  	cnt=0;
  	while(1) {
	nrk_led_toggle(GREEN_LED);
//	printf( "Task3 cnt=%u\r\n",cnt );
	nrk_wait_until_next_period();
	cnt++;
	}
}

void Task4()
{
	uint16_t cnt;

 //	printf( "Task4 PID=%u\r\n",nrk_get_pid());
 	cnt=0;
  	while(1) {
		nrk_led_toggle(RED_LED);
//		printf( "Task4 cnt=%u\r\n",cnt );
		nrk_wait_until_next_period();
		cnt++;
	}
}

void
nrk_create_taskset()
{
	nrk_task_set_entry_function( &TaskOne, Task1);
  	nrk_task_set_stk( &TaskOne, Stack1, NRK_APP_STACKSIZE);
  	TaskOne.prio = 3;
  	TaskOne.FirstActivation = TRUE;
  	TaskOne.Type = BASIC_TASK;
  	TaskOne.SchType = PREEMPTIVE;
  	TaskOne.period.secs = 0;
  	TaskOne.period.nano_secs = 200*NANOS_PER_MS;
  	TaskOne.cpu_reserve.secs = 50*NANOS_PER_MS;
  	TaskOne.cpu_reserve.nano_secs = 0;
  	TaskOne.offset.secs = 0;
  	TaskOne.offset.nano_secs= 0;
  	nrk_activate_task (&TaskOne);

  	nrk_task_set_entry_function( &TaskTwo, Task2);
  	nrk_task_set_stk( &TaskTwo, Stack2, NRK_APP_STACKSIZE);
  	TaskTwo.prio = 1;
  	TaskTwo.FirstActivation = TRUE;
  	TaskTwo.Type = BASIC_TASK;
  	TaskTwo.SchType = PREEMPTIVE;
  	TaskTwo.period.secs = 0;
  	TaskTwo.period.nano_secs = 150*NANOS_PER_MS;
  	TaskTwo.cpu_reserve.secs = 50*NANOS_PER_MS;
  	TaskTwo.cpu_reserve.nano_secs = 0;
  	TaskTwo.offset.secs = 0;
  	TaskTwo.offset.nano_secs = 0;
  	nrk_activate_task (&TaskTwo);

	nrk_task_set_entry_function( &TaskThree, Task3);
  	nrk_task_set_stk( &TaskThree, Stack3, NRK_APP_STACKSIZE);
  	TaskThree.prio = 3;
  	TaskThree.FirstActivation = TRUE;
  	TaskThree.Type = BASIC_TASK;
  	TaskThree.SchType = PREEMPTIVE;
  	TaskThree.period.secs = 0;
  	TaskThree.period.nano_secs = 100*NANOS_PER_MS;
  	TaskThree.cpu_reserve.secs = 50*NANOS_PER_MS;
  	TaskThree.cpu_reserve.nano_secs = 0;
  	TaskThree.offset.secs = 0;
  	TaskThree.offset.nano_secs= 0;
  	nrk_activate_task (&TaskThree);
/*
  	nrk_task_set_entry_function( &TaskFour, Task4);
  	nrk_task_set_stk( &TaskFour, Stack4, NRK_APP_STACKSIZE);
  	TaskFour.prio = 3;
  	TaskFour.FirstActivation = TRUE;
  	TaskFour.Type = BASIC_TASK;
  	TaskFour.SchType = PREEMPTIVE;
  	TaskFour.period.secs = 3;
  	TaskFour.period.nano_secs = 0;
  	TaskFour.cpu_reserve.secs = 0;
  	TaskFour.cpu_reserve.nano_secs = 100*NANOS_PER_MS;
  	TaskFour.offset.secs = 0;
  	TaskFour.offset.nano_secs= 0;
  	nrk_activate_task (&TaskFour);
*/

	printf("done activate!\n");
}

uint8_t kill_stack(uint8_t val)
{
	char bad_memory[10];
	uint8_t i;
	
	for(i=0; i<10; i++ ) bad_memory[i]=i;
	for(i=0; i<10; i++ ) printf( "%d ", bad_memory[i]);
   	printf( "Die Stack %d\r\n",val );
	
	if(val>1) kill_stack(val-1);
	return 0;
}