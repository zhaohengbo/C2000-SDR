# C2000 SDR

This is a FSK transreceiver based on SDR.

I use a DSP from TI, which is called F28335, a series of C2000 DSP.

The IQ modulator/demodulator is SX1255, a very cheap chip originally used in LORA.

Due to the limit of CPU load and the ugly performance of the SX1255,the system can only achieved 9600bps at 433.9M ± 9K(FSK).

Maybe it can do a little bit better when using a better MCU such as RT1052 or F28388D.

Square root rasied cosine filter is used both in tx and rx to reduce side lobe leakage and maxim the SNR.

At burst mode, the signal in frequency domain looks like this:

![Burst Mode](https://github.com/zhaohengbo/C2000-SDR/blob/master/screenshot/1.PNG)

Besides FSK version, QPSK(DSSS) and OFDM(QAM) versions are also in progress.

After THE BIG exam, the version of QPSK may be released if there are few bugs.