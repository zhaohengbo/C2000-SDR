#ifndef DRIVERS_SX1255_RX_H_
#define DRIVERS_SX1255_RX_H_

#ifdef __cplusplus
extern "C" {
#endif

interrupt void SX1255_RX_DMA_ISR(void);
void sx1255_rx_reset_state(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* DRIVERS_SX1255_RX_H_ */
