#ifndef DRIVERS_SPI_H_
#define DRIVERS_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

int16 spia_xmit(int16 spiTxData);
void spia_init(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* DRIVERS_SPI_H_ */
