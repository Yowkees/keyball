#include "transactions.h"

typedef struct {
    enum ball_state state;
} to_slave_t;

void rpc_get_ball_state_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data)
{
    state = ((to_slave_t*)in_data)->state;
}

void init_rpc(void)
{
    if (!is_keyboard_master())
    {
        transaction_register_rpc(MY_GET_BALL_STATE, rpc_get_ball_state_handler);
    }
}

void rpc_get_ball_state_invoke(void)
{
#if 0
    static uint32_t last_invoke = 0;
    static const uint32_t invoke_interval = 0;
    if (timer_elapsed32(last_invoke) >= invoke_interval)
    {
        to_slave_data.state = state;
        if (transaction_rpc_send(MY_GET_BALL_STATE, sizeof(to_slave_data), &to_slave_data))
        {
            last_invoke = timer_read32();
            dprintf("MY_GET_BALL_STATE is success state:%d\n", (uint32_t)to_slave_data.state);
        }
        else {
            dprint("MY_GET_BALL_STATE is failed\n");
        }
    }
#else
    to_slave_t to_slave_data = {
        .state = state,
    };
    transaction_rpc_send(MY_GET_BALL_STATE, sizeof(to_slave_data), &to_slave_data);
#endif
}


void housekeeping_task_user(void)
{
    if (is_keyboard_master())
    {
        //rpc_get_ball_state_invoke();
    }
}
