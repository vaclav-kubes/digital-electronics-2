|    |    | 1    | 8     | 32   | 64    | 128   | 256   | 1024  |
|----|----|------|-------|------|-------|-------|-------|-------|
| T0 | 8  | 16u  | 128u  | --   | 1.02m | --    | 4.10m | 16.4m |
| T1 | 16 | 4.1m | 32.8m | --   | 262m  | --    | 1.05  | 4.19  |
| T2 | 8  | 16u  | 128u  | 512u | 1.02m | 2.05m | 4.10m | 16.4m |

f_clk = 16 MHz


T0: 
- presc:TCCR0B bits CS02 CS01 CS00 (000: stopped, 001: 1, 010: 8, 011: 64, 100: 256, 101: 1024)
- 8bit data value: TCNT0
- int enable: TIMSK0 bit TOIE0 (1: enable, 0: disable)

T2:
- presc:TCCR2B bits CS22 CS21 CS20
- 8bit data value: TCNT2
- int enable: TIMSK2 bit TOIE0 (1: enable, 0: disable)

0 0 0 No clock source (Timer/Counter stopped).
0 0 1 clkT2S/(no prescaling)
0 1 0 clkT2S/8 (from prescaler)
0 1 1 clkT2S/32 (from prescaler)
1 0 0 clkT2S/64 (from prescaler)
1 0 1 clkT2S/128 (from prescaler)
1 1 0 clkT2S/256 (from prescaler)
1 1 1 clkT2S/1024 (from prescaler)