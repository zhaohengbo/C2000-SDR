#ifndef LIBS_LINK_LINK_RX_H_
#define LIBS_LINK_LINK_RX_H_

#ifdef __cplusplus
extern "C" {
#endif

void link_rx_layer_init(void);
int16 link_rx_layer_recv_cb(fsk_frame_t * recv_frame);
void link_rx_loop(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_LINK_LINK_RX_H_ */
