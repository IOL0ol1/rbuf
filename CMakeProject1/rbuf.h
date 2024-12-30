#ifndef _SYS_RINGBUF_h
#define _SYS_RINGBUF_h

#include <stdint.h> // for uint8_t
#include <stddef.h> // for size_t

#ifdef __cplusplus  // Provide C++ Compatibility
extern "C" {
#endif
 
	/// <summary>
	/// ring buffer context
	/// </summary>
	typedef struct {
		uint8_t* buffer; // buffer memory
		size_t size; // buffer size
		volatile size_t head; // index of head
		volatile size_t tail; // index of tail
	}rbuf_t;

	/// <summary>
	/// init ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <param name="buf">buffer memory</param>
	/// <param name="buf_size">buffer byte size</param>
	/// <returns>total byte size = buffer size - 1</returns>
	size_t rbuf_init(rbuf_t* rbuf, void* memory, size_t bytes);

	/// <summary>
	/// reset ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <param name="type">0:head=tail=0, 1:tail=head, 2:head=tail</param>
	void rbuf_reset(rbuf_t* rbuf, int type);

	/// <summary>
	/// get byte count of ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <returns></returns>
	size_t rbuf_count(rbuf_t* rbuf);

	/// <summary>
	/// get byte space of ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <returns></returns>
	size_t rbuf_space(rbuf_t* rbuf);

	/// <summary>
	/// get total byte size of ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <returns></returns>
	size_t rbuf_size(rbuf_t* rbuf);

	/// <summary>
	/// write data (change head) to ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <param name="data">data</param>
	/// <param name="bytes">data byte size</param>
	/// <returns>actual write byte size</returns>
	size_t rbuf_write(rbuf_t* rbuf, const void* data, size_t bytes);

	/// <summary>
	/// read data (change tail) from ring buffer
	/// </summary>
	/// <param name="rb"></param>
	/// <param name="data">data</param>
	/// <param name="bytes">data byte size</param>
	/// <returns>actual read byte size</returns>
	size_t rbuf_read(rbuf_t* rbuf, void* data, size_t bytes);

	/// <summary>
	/// peek data from ring buffer
	/// </summary>
	/// <param name="rbuf"></param>
	/// <param name="data"></param>
	/// <param name="bytes"></param>
	/// <returns>actual peek byte size</returns>
	size_t rbuf_peek(rbuf_t* rbuf, void* data, size_t bytes);

#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif
