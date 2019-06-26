# C2000 SDR

This is a FSK transreceiver based on SDR.
I use a DSP from TI, which is called F28335, a series of C2000 DSP.
The IQ modulator/demodulator is SX1255, a very cheap chip originally used in LORA.

Due to the limit of CPU load and the ugly performance of the SX1255,the system can only achieved 9600bps using 433.9M ± 9K.

Maybe when using a better MCU such as RT1052 or F28388D can do a little bit better.

Square root rasied cosine filter is used both in tx and rx to reduce side lobe leakage and maxim the SNR.

At burst mode, the signal in frequency domain looks like this:

![Burst Mode](https://github.com/zhaohengbo/C2000-SDR/blob/master/screenshot/1.PNG)