
#ifndef _GPIO_
#define _GPIO_

#ifdef __cplusplus
 extern "C" {
#endif 

extern void portB_as_output(unsigned int port);
extern void set_HIGH_portB(unsigned int port);
extern void set_LOW_portB(unsigned int port);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _GPIO_ */