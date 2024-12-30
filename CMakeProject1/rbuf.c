#include "rbuf.h"

size_t rbuf_init(rbuf_t* rbuf, void* memory, size_t bytes) {
	if (rbuf == NULL || memory == NULL || bytes == 0)
		return 0;
	rbuf->tail = 0;
	rbuf->head = 0;
	rbuf->buffer = (uint8_t*)memory;
	rbuf->size = bytes;
	return bytes - 1;
}

void rbuf_reset(rbuf_t* rbuf, int type)
{
	if (type == 1)
	{
		rbuf->tail = rbuf->head;
	}
	else if (type == 2)
	{
		rbuf->head = rbuf->tail;
	}
	else
	{
		rbuf->head = 0;
		rbuf->tail = 0;
	}
}

size_t rbuf_count(rbuf_t* rbuf)
{
	size_t h = rbuf->head;
	size_t t = rbuf->tail;
	return h >= t ? h - t : rbuf->size - t + h;
}

size_t rbuf_space(rbuf_t* rbuf)
{
	size_t h = rbuf->head;
	size_t t = rbuf->tail;
	return h >= t ? rbuf->size - 1 - h + t : t - h - 1;
}

size_t rbuf_size(rbuf_t* rbuf)
{
	return rbuf->size - 1;
}

size_t rbuf_write(rbuf_t* rbuf, const void* data, size_t bytes)
{
	size_t i = 0;
	for (; i < bytes && rbuf_space(rbuf) > 0; i++)
	{
		rbuf->buffer[rbuf->head] = ((const uint8_t*)data)[i];
		rbuf->head = (rbuf->head + 1) % rbuf->size;
	}
	return i;
}

size_t rbuf_read(rbuf_t* rbuf, void* data, size_t bytes)
{
	size_t i = 0;
	for (; i < bytes && rbuf_count(rbuf) > 0; i++)
	{
		((uint8_t*)data)[i] = rbuf->buffer[rbuf->tail];
		rbuf->tail = (rbuf->tail + 1) % rbuf->size;
	}
	return i;
}

size_t rbuf_peek(rbuf_t* rbuf, void* data, size_t bytes)
{
	size_t i = 0;
	size_t t = rbuf->tail;
	size_t c = rbuf_count(rbuf);
	for (; i < bytes && i < c; i++)
	{
		((uint8_t*)data)[i] = rbuf->buffer[(t + i) % rbuf->size];
	}
	return i;
}