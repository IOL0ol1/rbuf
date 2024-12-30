
#include "main.h"
#include "rbuf.h"

using namespace std;

typedef struct {
	uint32_t id;
	byte ext;
	byte rtr;
	byte dlc;
	byte data[8];
} can_msg_t;

#define MSG_BUF_LEN 64
byte msg_memory[sizeof(can_msg_t) * MSG_BUF_LEN + 1]; // must sizeof(struct) * len + 1
rbuf_t msg_buf;

#define B_BUF_SIZE 64
byte b_memory[B_BUF_SIZE];
rbuf_t b_buf;



int main()
{
	char c = '0';

	rbuf_init(&msg_buf, msg_memory, sizeof(msg_memory));
	rbuf_init(&b_buf, b_memory, sizeof(b_memory));

	while ((true))
	{
		/////////////// frame example //////////////////
		can_msg_t msg
		{
			.id = 0x80,
			.ext = (byte)0,
			.rtr = (byte)0,
			.dlc = (byte)4,
			.data = { (byte)c, (byte)0x02, (byte)0x03, (byte)0x04 },
		};

		// CAN interrupt
		if (rbuf_space(&msg_buf) >= sizeof(can_msg_t))
			rbuf_write(&msg_buf, &msg, sizeof(can_msg_t));

		memset(&msg, 0, sizeof(can_msg_t));

		// main loop
		if (rbuf_count(&msg_buf) >= sizeof(can_msg_t))
		{
			rbuf_read(&msg_buf, &msg, sizeof(can_msg_t));
			printf("id:%d,ext:%d,rtr:%d,dlc:%d,data:%02X %02X %02X %02X\n",
				msg.id, msg.ext, msg.rtr, msg.dlc, msg.data[0], msg.data[1], msg.data[2], msg.data[3]);
		}

		///////////// stream example /////////////
		if (c++ > 'Z') c = '0';

		// serial interrupt 
		rbuf_write(&b_buf, &c, 1);

		// main loop
		char cc = 0;
		if (rbuf_read(&b_buf, &cc, 1) > 0)
			printf("c:%c\n", cc);

		_sleep(1000);

	}
	return 0;
}
