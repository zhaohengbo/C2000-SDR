#ifndef LIBS_LINK_LINK_TX_H_
#define LIBS_LINK_LINK_TX_H_

#ifdef __cplusplus
extern "C" {
#endif

void link_tx_layer_init(void);
int16 link_tx_layer_send_cb(fsk_frame_t * send_frame);
void link_tx_loop(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_LINK_LINK_TX_H_ */
