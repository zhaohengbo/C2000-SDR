#ifndef LIBS_FSK_FSK_TABLE_H_
#define LIBS_FSK_FSK_TABLE_H_

#ifdef __cplusplus
extern "C" {
#endif

extern const short_complex_t sampleTable[];
extern const int32 atan2buf[];
extern const Uint16 scrambleTable[];
extern const int16 filterTable[];

int16 atan2_table_16(int16 x,int16 y);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* LIBS_FSK_FSK_TABLE_H_ */
