
/*
*si recibe la trama $PING# debe responder con la trama "$PING#\n\r" hacia el puerto 9091
*si recibe la trama $APAGAR# debe responder con la trama "$OKA#\n\r" hacia el puerto 9091, y setear la bandera "banderaApagarSistema"
*si recibe la trama $REINICIAR# debe responder con la trama "$OKR#\n\r" hacia el puerto 9091, y setear la bandera "banderaReiniciarSistema"
*si recibe la trama $HON# debe responder con la trama "$HON#\n\r" hacia el puerto 9091, y setear la bandera "bandera_reloj"
*si recibe la trama $HOFF# debe responder con la trama "$HOFF#\n\r" hacia el puerto 9091, y resetear la bandera "bandera_reloj"
*si recibe la trama $CON# debe responder con la trama "$CON#\n\r" hacia el puerto 9091, y setear la bandera "bandera_reloj"
*si recibe la trama $COFF# debe responder con la trama "$COFF#\n\r" hacia el puerto 9091, y resetear la bandera "bandera_clima"
*si recibe cualquier otra trama debe responder con la trama "$NACK#" hacia el puerto 9091
*/



#include "unity.h"
#include "com.h"
#include "mock_externa.h"


static uint16_t temp;

void setUp(void)
{
     temp=htons(9091);
}
//! @test  correspondiente al mensaje "PING"
void test_recepcion_ping(void)
{
    sprintf(bufferRecepcion,"$PING#");
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$PING#\n\r",bufferSalida);
    
}

//! @test  correspondiente al mensaje "$APAGAR#"
void test_recepcion_apagar(void)
{
    banderaApagarSistema=0;
    sprintf(bufferRecepcion,"$APAGAR#");
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$OKA#\n\r",bufferSalida);
    TEST_ASSERT_TRUE(banderaApagarSistema);
}

//! @test  correspondiente al mensaje "$REINICIAR#"
void test_recepcion_reiniciar(void)
{
    banderaReiniciarSistema=0;
    sprintf(bufferRecepcion,"$REINICIAR#");
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$OKR#\n\r",bufferSalida);
    TEST_ASSERT_TRUE(banderaReiniciarSistema);
}

//! @test  correspondiente al mensaje "$HON"
void test_recepcion_activar_reloj(void)
{
    bandera_reloj=0;
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    sprintf(bufferRecepcion,"$HON#");
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$HON#\n\r",bufferSalida);
    TEST_ASSERT_TRUE(bandera_reloj);   
}

//! @test  correspondiente al mensaje "$HOFF#"
void test_recepcion_desactivar_reloj(void)
{
    bandera_reloj=1;
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    sprintf(bufferRecepcion,"$HOFF#");
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$HOFF#\n\r",bufferSalida);
    TEST_ASSERT_FALSE(bandera_reloj);   
}

//! @test  correspondiente al mensaje "$CON#"
void test_recepcion_activar_clima_info(void)
{
    bandera_clima=0;
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    sprintf(bufferRecepcion,"$CON#");
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$CON#\n\r",bufferSalida);
    TEST_ASSERT_TRUE(bandera_clima);   
}

//! @test  correspondiente al mensaje "$COFF#"
void test_recepcion_desactivar_clima_info(void)
{
    bandera_clima=1;
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    sprintf(bufferRecepcion,"$COFF#");
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$COFF#\n\r",bufferSalida);
    TEST_ASSERT_FALSE(bandera_clima);   
}

//! @test  correspondiente al mensaje "$NACK#"
void test_trama_incorrecta(void)
{
    
    sprintf(bufferRecepcion,"$NACK#");
    recvfrom_IgnoreAndReturn(sizeof(bufferRecepcion));
    procesarUdp();
    TEST_ASSERT_EQUAL_UINT16(temp,from.sin_port);
    TEST_ASSERT_EQUAL_STRING("$NACK#\n\r",bufferSalida);  
}





