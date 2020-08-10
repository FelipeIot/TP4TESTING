#include "stdint.h"
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>


#define BASEPORT 9091


extern void procesarUdp(void);




extern uint8_t bufferRecepcion[20];
extern uint8_t bufferSalida[20];

extern uint8_t banderaApagarSistema;
extern uint8_t banderaReiniciarSistema;
extern uint8_t bandera_reloj;
extern uint8_t bandera_clima;

extern struct sockaddr_in server, from;


void procesarUdp(void);