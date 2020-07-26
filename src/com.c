#include "com.h"



#define LEDS_ALL_OFF    0x0000
#define LEDS_ALL_ON     0xFFFF
#define LED_STATE_ON    1
#define LED_STATE_OFF   0 

void procesarUdp(void);

uint8_t bufferRecepcion[20];
uint8_t bufferSalida[20];


uint8_t banderaApagarSistema;
uint8_t banderaReiniciarSistema;
uint8_t bandera_reloj;
uint8_t bandera_clima;

struct sockaddr_in server, from;
int m;
int sock;


void procesarUdp(void)
{
    			if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='P')&&(bufferRecepcion[2]=='I')&&(bufferRecepcion[3]=='N')&&(bufferRecepcion[4]=='G')&&(bufferRecepcion[5]=='#'))
				{
					sprintf(bufferSalida,"$PING#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);
					


				}
                
                else if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='A')&&(bufferRecepcion[2]=='P')&&(bufferRecepcion[3]=='A')&&(bufferRecepcion[4]=='G')&&(bufferRecepcion[5]=='A')&&(bufferRecepcion[6]=='R')&&(bufferRecepcion[7]=='#'))
				{
					banderaApagarSistema=1;
                    sprintf(bufferSalida,"$OKA#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);


				}
                
                else if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='R')&&(bufferRecepcion[2]=='E')&&(bufferRecepcion[3]=='I')&&(bufferRecepcion[4]=='N')&&(bufferRecepcion[5]=='I')&&(bufferRecepcion[6]=='C')&&(bufferRecepcion[7]=='I')&&(bufferRecepcion[8]=='A')&&(bufferRecepcion[9]=='R')&&(bufferRecepcion[10]=='#'))
				{
					banderaReiniciarSistema=1;
                    sprintf(bufferSalida,"$OKR#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);

				}
                
                else if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='H')&&(bufferRecepcion[2]=='O')&&(bufferRecepcion[3]=='N')&&(bufferRecepcion[4]=='#'))
				{
					bandera_reloj=1;
					sprintf(bufferSalida,"$HON#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);
				}
				
                else if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='H')&&(bufferRecepcion[2]=='O')&&(bufferRecepcion[3]=='F')&&(bufferRecepcion[4]=='F')&&(bufferRecepcion[5]=='#'))
				{
					bandera_reloj=0;
                    sprintf(bufferSalida,"$HOFF#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);
					
				}

                else if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='C')&&(bufferRecepcion[2]=='O')&&(bufferRecepcion[3]=='N')&&(bufferRecepcion[4]=='#'))
				{
					bandera_clima=1;
                    sprintf(bufferSalida,"$CON#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);
					
					


				}

                else if((bufferRecepcion[0]=='$')&&(bufferRecepcion[1]=='C')&&(bufferRecepcion[2]=='O')&&(bufferRecepcion[3]=='F')&&(bufferRecepcion[4]=='F')&&(bufferRecepcion[5]=='#'))
				{
					bandera_clima=0;
                    sprintf(bufferSalida,"$COFF#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);
					


				}

                else
                {
                    sprintf(bufferSalida,"$NACK#\n\r");
					from.sin_port = htons(BASEPORT);
					m=sendto(sock, bufferSalida, strlen(bufferSalida),0,(const struct sockaddr *)&from, 30);
                }
                
}




static uint16_t * puerto;


/**
 * @brief Obtiene el número de bit 
 * @param led numero de led
 * @return número de bit
 */
uint8_t ledTOBit(uint8_t led)
{
    return (led-1);
}

/**
 * @brief mascara a partir de el número de bit 
 * @param bit numero de bit
 * @return mascara
 */
uint16_t BitMask(uint8_t bit)
{
    return(1<<bit);
}

/**
 * @brief Asigna de direccion del puerto 
 * @param direccion la dirección del puerto
 */
void LedsCreate(uint16_t * direccion)
{   
    puerto=direccion;
    *puerto=LEDS_ALL_OFF;
}


/**
 * @brief Enciende un led específico 
 * @param led número de led
 */
void LedsTurnOn(uint8_t led)
{
    *puerto |=BitMask(ledTOBit(led));
}

/**
 * @brief Apaga un led específico 
 * @param led número de led
 */
void LedsTurnOff(uint8_t led)
{
    *puerto &=~BitMask(ledTOBit(led));
}

/**
 * @brief Enciende todos los leds
 * @param direccion la dirección del puerto
 */

void LedsAllOn(uint16_t * direccion)
{
    puerto=direccion;
    *puerto=LEDS_ALL_ON;
}

/**
 * @brief Apaga todos los leds
 * @param direccion la dirección del puerto
 */
void LedsAllOff(uint16_t * direccion)
{
    puerto=direccion;
    *puerto=LEDS_ALL_OFF;
}


/**
 * @brief Obtine el estado de un led específico
 * @param nled número de led
 * @return estado del led 
 */
uint8_t LedState(uint8_t nled)
{
    static uint8_t vretorno;

    if(*puerto & BitMask(ledTOBit(nled)))
    {
        vretorno=LED_STATE_ON;
    }
    else
    {
        vretorno=LED_STATE_OFF;
    }
    
    return vretorno;
}