#include "stdint.h"
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>


#define BASEPORT 9091




void LedsCreate(uint16_t * direccion);
void LedsTurnOn(uint8_t led);
void LedsTurnOff(uint8_t led);
void LedsAllOn(uint16_t * direccion);
void LedsAllOff(uint16_t * direccion);
uint8_t LedState(uint8_t nled);


extern uint8_t bufferRecepcion[20];
extern uint8_t bufferSalida[20];

extern uint8_t banderaApagarSistema;
extern uint8_t banderaReiniciarSistema;
extern uint8_t bandera_reloj;
extern uint8_t bandera_clima;

extern struct sockaddr_in server, from;


extern void procesarUdp(void);