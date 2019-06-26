#ifndef LIBS_FSK_FSK_FILTER_H_
#define LIBS_FSK_FSK_FILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

void fsk_rx_filter(short_complex_t *buf, const int16* filter_table, Uint16 count);
void fsk_tx_filter(short_complex_t *buf, const int16* filter_table, Uint16 count);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_FILTER_H_ */
