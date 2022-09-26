
#ifndef _SO_
#define _SO_

#ifdef __cplusplus
 extern "C" {
#endif 

extern void __syscall(int num);

#define PIOA_ID (0x800U)
#define PIOB_ID (0x800U << 1)
#define PIOC_ID (0x800U << 2)
#define PIOD_ID (0x800U << 3)
#define PIOE_ID (0x800U << 4)
#define PIOF_ID (0x800U << 5)
#define P0 1
#define P1 (1 << 1)
#define P2 (1 << 2)
#define P3 (1 << 3)
#define P4 (1 << 4)
#define P5 (1 << 5)
#define P6 (1 << 6)
#define P7 (1 << 7)
#define P8 (1 << 8)
#define P9 (1 << 9)
#define P10 (1 << 10)
#define P11 (1 << 11)
#define P12 (1 << 12)
#define P13 (1 << 13)
#define P14 (1 << 14)
#define P15 (1 << 15)
#define P16 (1 << 16)
#define P17 (1 << 17)
#define P18 (1 << 18)
#define P19 (1 << 19)
#define P20 (1 << 20)
#define P21 (1 << 21)
#define P22 (1 << 22)
#define P23 (1 << 23)
#define P24 (1 << 24)
#define P25 (1 << 25)
#define P26 (1 << 26)
#define P27 (1 << 27)
#define P28 (1 << 28)
#define P29 (1 << 29)
#define P30 (1 << 30)
#define P31 (1 << 31)

#define PIO_PER_A (unsigned int)(0x400E0E00U)
#define PIO_PER_B (unsigned int)(PIO_PER_A + 0x200)
#define PIO_PER_C (unsigned int)(PIO_PER_B + 0x200)
#define PIO_PER_D (unsigned int)(PIO_PER_C + 0x200)
#define PIO_PER_E (unsigned int)(PIO_PER_D + 0x200)
#define PIO_PER_F (unsigned int)(PIO_PER_E + 0x200)
#define PIO_PDR_A (unsigned int)(0x400E0E04U)
#define PIO_PDR_B (unsigned int)(PIO_PDR_A + 0x200)
#define PIO_PDR_C (unsigned int)(PIO_PDR_B + 0x200)
#define PIO_PDR_D (unsigned int)(PIO_PDR_C + 0x200)
#define PIO_PDR_E (unsigned int)(PIO_PDR_D + 0x200)
#define PIO_PDR_F (unsigned int)(PIO_PDR_E + 0x200)
#define PIO_OER_A (unsigned int)(0x400E0E10U)
#define PIO_OER_B (unsigned int)(PIO_OER_A + 0x200)
#define PIO_OER_C (unsigned int)(PIO_OER_B + 0x200)
#define PIO_OER_D (unsigned int)(PIO_OER_C + 0x200)
#define PIO_OER_E (unsigned int)(PIO_OER_D + 0x200)
#define PIO_OER_F (unsigned int)(PIO_OER_E + 0x200)
#define PIO_SODR_A (unsigned int)(0x400E0E30U)
#define PIO_SODR_B (unsigned int)(PIO_SODR_A + 0x200)
#define PIO_SODR_C (unsigned int)(PIO_SODR_B + 0x200)
#define PIO_SODR_D (unsigned int)(PIO_SODR_C + 0x200)
#define PIO_SODR_E (unsigned int)(PIO_SODR_D + 0x200)
#define PIO_SODR_F (unsigned int)(PIO_SODR_E + 0x200)
#define PIO_CODR_A (unsigned int)(0x400E0E34U)
#define PIO_CODR_B (unsigned int)(PIO_CODR_A + 0x200)
#define PIO_CODR_C (unsigned int)(PIO_CODR_B + 0x200)
#define PIO_CODR_D (unsigned int)(PIO_CODR_C + 0x200)
#define PIO_CODR_E (unsigned int)(PIO_CODR_D + 0x200)
#define PIO_CODR_F (unsigned int)(PIO_CODR_E + 0x200)
#define PMC_PCER0 (unsigned int)(0x400E0610U)


#define ___AT(x) ((unsigned int*)x)

#define __START__  __attribute__ ((section(".so_start")))
#define __EXTERNAL__  __attribute__ ((section(".so_fn")))

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _SO_ */