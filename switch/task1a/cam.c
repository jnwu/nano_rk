
/*******************************************************
 *
 *  Routing Table Routines for EECE 494, Assignment 2.
 *
 *  Created by _________, University of British Columbia
 *
 *  This is where you will put your routines to implement
 *  the routing table.  You should use the headers as
 *  supplied.  All your code will go in this
 *  file (and in cam.h)
 *
 ******************************************************/

#include "defs.h"

/* Note that you probably want to have a data structure
   that is accessable to all routines in this file.  To do
   this, you probably would define some structure (perhaps
   called cam_t in the file cam.h.  Then you could 
   create a variable of this type here by using:

   cam_t cam;

   This will create  a variable called cam (of type cam_h)
   that can be accessed by any routine in this file.  */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

struct entry_s {
	ip_address_t *key;
	int value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct cam_s {
	int size;
	struct entry_s **table;	
};

typedef struct cam_s hashtable_t;

hashtable_t *hashtable;

ip_address_t* copy_ip_address(ip_address_t *address)
{
	ip_address_t * new = malloc(sizeof(ip_address_t));
	ip_address_copy(address,new);
	return new; 
}


/* Create a new hashtable. */
hashtable_t *ht_create( int size ) {

	hashtable_t *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	/* Allocate the table itself. */
	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	/* Allocate pointers to the head nodes. */
	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;	
}

/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, ip_address_t *key ) {

	unsigned long int hashval;
	int i = 0;

	hashval = key->n1 * key->n2 * key->n3 * key->n4;

	return hashval % hashtable->size;
}

/* Create a key-value pair. */
entry_t *ht_newpair( ip_address_t *key, int value ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	newpair->key = copy_ip_address(key);
	if (newpair->key == NULL)
		return NULL;

	newpair->value = value;

	newpair->next = NULL;

	return newpair;
}

void cam_init()
{
   hashtable = ht_create( 400000 );
}


void cam_add_entry(ip_address_t *key, int port)
{
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && compareAddresses( key, next->key ) == 0 ) {
		last = next;
		next = next->next;
	}

	/* There's already a pair.  Let's replace that string. */
	if( next != NULL && next->key != NULL && compareAddresses( key, next->key ) != 0 ) {

		next->value = port;

	/* Nope, could't find it.  Time to grow a pair. */
	} else {
		newpair = ht_newpair( key, port );

		/* We're at the start of the linked list in this bin. */
		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;

		/* We're at the end of the linked list in this bin. */
		} else if ( next == NULL ) {
			last->next = newpair;

		/* We're in the middle of the list. */
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

int compareAddresses(ip_address_t *key, ip_address_t *compare)
{
	return (key->n1 == compare->n1 && key->n2 == compare->n2 && key->n3 == compare->n3 && key->n4 == compare->n4);
}

int cam_lookup_address(ip_address_t *address)
{
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, address );

	/* Step through the bin, looking for our value. */
	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && compareAddresses( address, pair->key ) == 0 ) {
		pair = pair->next;
	}

	/* Did we actually find anything? */
	if( pair == NULL || pair->key == NULL || compareAddresses( address, pair->key ) == 0 ) {
		return -1;
	} else {
		return pair->value;
	}
}

void cam_free()
{
	
	int i;
	for (i = 0; i < hashtable->size; i++)
	{
		entry_t * entry = hashtable->table[i];
		while (entry != NULL && entry->key != NULL)
		{
			entry_t *list = entry;
			free(entry->key);
			entry = entry->next;
			free(list);
		}
	}
	
	free(hashtable);
	
}	
