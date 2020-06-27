#include "lxcbuff/lxCBuff.h"
#include <string.h>

#define BUFFER_MIN_SIZE 10

struct lxCBuff{
	uint16_t	size;
	uint16_t	head;
	uint16_t	tail;
};

lxCBuff* lxCB_init(void *mem, size_t sz){
	lxCBuff *buffer = mem;
    if(sz <= (sizeof(lxCBuff)+BUFFER_MIN_SIZE)) return NULL;
    if(sz > (sizeof(lxCBuff)+65535)) return NULL;
    uint16_t size = sz - sizeof(lxCBuff);
    buffer->size    = size;
    buffer->head    = 0;
    buffer->tail    = 0;
    return buffer;
}
/**/

void lxCB_clear(lxCBuff* buffer){
    buffer->head    = 0;
    buffer->tail    = 0;
}
/**/

bool lxCB_put(lxCBuff* buffer, void* data, uint8_t sz){
    uint8_t *top    = ((uint8_t*)buffer) + sizeof(lxCBuff);
    uint8_t *ptr    = top + buffer->head;
    uint16_t inc    = (uint16_t)sz + 1;
    uint32_t next   = (uint32_t)buffer->head + inc;
    if(buffer->tail > buffer->head && next >= buffer->tail){
        return false;
    }
    if( next >= buffer->size ){
        next -= buffer->size;
        uint16_t rem = next;
        if(rem >= buffer->tail) return false;
        uint16_t sz0 = inc - rem;
        if(sz0){
            *ptr++ = sz;
            memcpy(ptr, data, --sz0);
        }else{
            *top++ = sz;
            --rem;
        }
	    memcpy(top, data + sz0, rem);
    }else{
        *ptr++ = sz;
	    memcpy(ptr, data, sz);
    }
    buffer->head = next;
    return true;
}
/**/

uint8_t lxCB_get(lxCBuff* buffer, void* data, uint8_t sz){
    if(lxCB_empty(buffer)) return 0;
    uint8_t *top    = ((uint8_t*)buffer) + sizeof(lxCBuff);
    uint8_t *ptr    = top + buffer->tail;
    uint8_t inc     = *ptr++;
    uint32_t next   = (uint32_t)buffer->tail + inc + 1;
    if( next >= buffer->size ){
        next -= buffer->size;
        uint16_t rem = next;
        uint8_t sz0 = inc - rem;
	    memcpy(data, ptr, sz0);
	    memcpy(data + sz0, top, rem);
    }else{
	    memcpy(data, ptr, inc);
    }
    buffer->tail = next;
    return inc;
}

bool lxCB_empty(lxCBuff* buffer){
    return buffer->head == buffer->tail;
}

uint16_t lxCB_free_size(lxCBuff* buffer){
    int32_t size = (int32_t)buffer->tail - buffer->head;
    if(size < 0) size += buffer->size;
    return size;
}
