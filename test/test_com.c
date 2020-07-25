
/*
*si recibe la trama $PING# debe responder con la trama "$PING#\n\r"
*si recibe la trama $APAGAR# debe responder con la trama "$OKA#\n\r", y setear la bandera "banderaApagarSistema"
*si recibe la trama $REINICIAR# debe responder con la trama "$OKR#\n\r", y setear la bandera "banderaReiniciarSistema"
*si recibe la trama $HON# debe responder con la trama "$HON#\n\r", y setear la bandera "bandera_reloj"
*si recibe la trama $HOFF# debe responder con la trama "$HOFF#\n\r", y resetear la bandera "bandera_reloj"
*si recibe la trama $CON# debe responder con la trama "$CON#\n\r", y setear la bandera "bandera_reloj"
*si recibe la trama $COFF# debe responder con la trama "$COFF#\n\r", y resetear la bandera "bandera_clima"
*/



#include "unity.h"
#include "com.h"



void test_recepcion_ping(void)
{
    sprintf(bufferRecepcion,"$PING#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$PING#\n\r",bufferSalida);
}

void test_recepcion_apagar(void)
{
    banderaApagarSistema=0;
    sprintf(bufferRecepcion,"$APAGAR#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$OKA#\n\r",bufferSalida);
    TEST_ASSERT_EQUAL(1,banderaApagarSistema);
}

void test_recepcion_reiniciar(void)
{
    banderaReiniciarSistema=0;
    sprintf(bufferRecepcion,"$REINICIAR#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$OKR#\n\r",bufferSalida);
    TEST_ASSERT_EQUAL(1,banderaReiniciarSistema);
}

void test_recepcion_activar_reloj(void)
{
    bandera_reloj=0;
    sprintf(bufferRecepcion,"$HON#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$HON#\n\r",bufferSalida);
    TEST_ASSERT_EQUAL(1,bandera_reloj);   
}

void test_recepcion_desactivar_reloj(void)
{
    bandera_reloj=1;
    sprintf(bufferRecepcion,"$HOFF#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$HOFF#\n\r",bufferSalida);
    TEST_ASSERT_EQUAL(0,bandera_reloj);   
}

void test_recepcion_activar_clima_info(void)
{
    bandera_clima=0;
    sprintf(bufferRecepcion,"$CON#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$CON#\n\r",bufferSalida);
    TEST_ASSERT_EQUAL(1,bandera_clima);   
}

void test_recepcion_desactivar_clima_info(void)
{
    bandera_clima=1;
    sprintf(bufferRecepcion,"$COFF#");
    procesarUdp();
    TEST_ASSERT_EQUAL_STRING("$COFF#\n\r",bufferSalida);
    TEST_ASSERT_EQUAL(0,bandera_clima);   
}

/*
uint16_t virtuales;

void setUp(void)
{
    LedsCreate(&virtuales);
}

//! @test Todos los leds empiezan apagados
void test_todos_los_leds_inician_apagados(void)
{
    uint16_t virtuales=0xFFFF;
    LedsCreate(&virtuales);
    TEST_ASSERT_EQUAL(0x0000,virtuales);
}
//! @test Encender un led
void test_enceder_un_led(void)
{

    LedsTurnOn(1);
    TEST_ASSERT_EQUAL(0x0001,virtuales);
}
//! @test Encender y apagar un led
void test_encender_y_apagar_un_led(void)
{

        LedsTurnOn(1);
        LedsTurnOff(1);
        TEST_ASSERT_EQUAL(0x0000,virtuales);
}
//! @test Encender y apagar varios leds
void test_prender_y_apagar_varios_leds(void)
{
        LedsTurnOn(3);
        LedsTurnOn(5);
        LedsTurnOff(3);
        TEST_ASSERT_EQUAL(0x0010,virtuales);
}
//! @test Encender dos leds independientes
void test_dos_leds_independientes(void)
{
        LedsTurnOn(4);
        LedsTurnOn(7);
        TEST_ASSERT_EQUAL(0x0048,virtuales);
}
//! @test Encender todos los leds
void test_encender_todos(void)
{
        LedsAllOn(&virtuales);
        TEST_ASSERT_EQUAL(0xFFFF,virtuales);
}
//! @test Apagar todos los leds
void test_apagar_todos(void)
{
        uint16_t virtuales=0xFFFF;
        LedsAllOff(&virtuales);
        TEST_ASSERT_EQUAL(0x0000,virtuales);
}
//! @test Obtener el estado de un led encendido
void test_obtener_estado_led_encendido(void)
{
    uint8_t estado;
    LedsTurnOn(12);
    estado=LedState(12);
    TEST_ASSERT_EQUAL(0x01,estado);
}


//! @test Obtener el estado de un led apagado
void test_obtener_estado_leds_apagado(void)
{
    uint8_t estado;
    LedsTurnOff(8);
    estado=LedState(8);
    TEST_ASSERT_EQUAL(0x00,estado);
}
//! @test Obtener el estado de un led encendido con dos leds encendidos
void test_obtener_estado_led_encendido_con_dos_encendidos(void)
{
    uint8_t estado;
    LedsTurnOn(2);
    LedsTurnOn(13);
    estado=LedState(2);
    TEST_ASSERT_EQUAL(0x01,estado);
}



*/



