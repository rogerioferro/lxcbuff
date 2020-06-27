/***********************************************
* Author	: Rogério Ferro do Nascimento
* Date		: 13/01/2020
* Version	: 0.0.1
* Note:
*	Circular Buffer
************************************************/

#ifndef __LX_CBUFFER__
#define __LX_CBUFFER__

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct lxCBuff lxCBuff;

/*
lxCB_init:
	Init CBuff
	Parameters:
				mem:
						Pointer to the memory allocated.
						min size: 16 bytes
						max size: 65286 bytes
				sz:
						Size of memory.
	Return:
				lxCBuff*
*/
lxCBuff* lxCB_init(void *mem, size_t sz);

/*
lxCB_clear:
	Clear buffer.

	Parameters:
				buffer:
						Pointer to the lxCBuff.
	Return:
				void
*/
void lxCB_clear(lxCBuff* buffer);

/*
lxCB_put:
	Add data to the buffer.

	Parameters:
				buffer:
                    Pointer to the lxCBuff.
				data:
						Pointer to the data source.
				sz:
						Size of data (max 255).
	Return:
				true on success
*/
bool lxCB_put(lxCBuff* buffer, void* data, uint8_t sz);

/*
lxCB_get:
	Retrieve a value from the buffer.

	Parameters:
				buffer:
                    Pointer to the lxCBuff.
				data:
						Pointer to the data source.
				sz:
						Size of data.
	Return:
				size of retrieved data
*/
uint8_t lxCB_get(lxCBuff* buffer, void* data, uint8_t sz);

/*
lxCB_empty:
	Check if the buffer is Empty.

	Parameters:
				buffer:
                    Pointer to the lxCBuff.
	Return:
				true: 	If buffer is Empty.
				false:	If buffer is not Empty.
*/
bool lxCB_empty(lxCBuff* buffer);

/*
lxCB_free_size:
	return the free size of buffer.

	Parameters:
				buffer:
                    Pointer to the lxCBuff.
	Return:
				free size of the buffer.
*/
uint16_t lxCB_free_size(lxCBuff* buffer);


#endif /*__FIFO__*/
