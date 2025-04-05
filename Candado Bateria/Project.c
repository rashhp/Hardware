#include <18F4550.h>
#fuses HSPLL, PLL5, USBDIV, NOWDT, CPUDIV1, NOPROTECT, NODEBUG, NOPBADEN, NOLVP, NOVREGEN
#use delay(clock = 48MHz)
#define LCD_DATA_PORT getenv("SFR:PORTB")
#include <lcd.c>
#include "KBD4x4.c"

// Calibraci?n
float calibracion = 4.0; // Ajustar seg?n la referencia de voltaje

float leer_voltaje() {
    int16 valor = read_adc(); // Leer ADC
    return (valor * calibracion * 5.0) / 1023.0; // Convertir a voltaje
}

void mostrar_menu(int dir) {

output_low(PIN_A1);
    // Mostrar las opciones del men? en las l?neas 1 y 2
    lcd_gotoxy(1, 1);
    lcd_putc("PASSWORD        ");
    
    lcd_gotoxy(1, 2);
    lcd_putc("BATERIA         ");

    // Mostrar el indicador "<--" seg?n la opci?n seleccionada
    if (dir == 0) {
        lcd_gotoxy(1, 1); // Colocar el indicador en la opci?n "PASSWORD"
        lcd_putc("PASSWORD<--     ");
    } else if (dir == 1) {
        lcd_gotoxy(1, 9); // Colocar el indicador en la opci?n "BATERIA"
        lcd_putc("BATERIA<--      ");
    }
}

void ingresar_password() {
    char tecla;
    char Password[4];
    int dir = 0;  // Reiniciar dir a 0 siempre al iniciar el ingreso de contrase?a
    
    lcd_gotoxy(1, 2);
    lcd_putc("                ");
    
    lcd_gotoxy(1, 1);
    lcd_putc("INGRESE PASSWORD: ");
    lcd_gotoxy(1, 2);
    dir = 0; // Reiniciar el ?ndice para el nuevo intento

    while (dir < 4) {
        tecla = kbd_getc();
        if (tecla != 0) {
            Password[dir] = tecla;
            lcd_putc("*"); // Mostrar '' en lugar del car?cter
            delay_ms(50);
            dir++;
        }
    }

    // Verificar las contrase?as
    if (Password[0] == '1' && Password[1] == '2' && Password[2] == '3' && Password[3] == '4') {
        lcd_gotoxy(1, 1);
        lcd_putc("VERDE           ");
        output_high(PIN_C0); // Encender C0
        delay_ms(300); // Esperar 10 segundos
        output_low(PIN_C0);
    } 
    else if (Password[0] == '4' && Password[1] == '3' && Password[2] == '2' && Password[3] == '1') {
        lcd_gotoxy(1, 1);
        lcd_putc("AZUL            ");
        output_high(PIN_C1); // Encender C1
        delay_ms(300); // Esperar 10 segundos
        output_low(PIN_C1);
    }
    else if (Password[0] == '5' && Password[1] == '6' && Password[2] == '7' && Password[3] == '8') {
        lcd_gotoxy(1, 1);
        lcd_putc("NARANJA         ");
        output_high(PIN_C2); // Encender C2
        delay_ms(300); // Esperar 10 segundos
        output_low(PIN_C2);
    } 
    else if (Password[0] == '8' && Password[1] == '7' && Password[2] == '6' && Password[3] == '5') {
        lcd_gotoxy(1, 1);
        lcd_putc("ROSA            ");
        output_high(PIN_C4); // Encender C4
        delay_ms(300); // Esperar 10 segundos
        output_low(PIN_C4);
    } 
    else {
        lcd_gotoxy(1, 1);
        lcd_putc("ERROR           ");
        output_high(PIN_A1);
        delay_ms(200); // Esperar 2 segundos
        output_low(PIN_A1);
    }

    // Regresar al men? principal con la opci?n "PASSWORD" seleccionada
    mostrar_menu(0);  // Siempre comenzar desde "PASSWORD"
}

void mostrar_bateria() {
    float voltaje = leer_voltaje(); // Leer el voltaje
    int porcentaje = ((voltaje / 5) * 100); // Calcular el porcentaje de bater?a



    // Limitar el porcentaje entre 0 y 100
    if (porcentaje > 100) {
        porcentaje = 100;  // Asegurarse de que el porcentaje no supere 100%
    } else if (porcentaje < 0) {
        porcentaje = 0;    // Asegurarse de que el porcentaje no sea negativo
    }

    // Mostrar el voltaje y el porcentaje de bater?a
    lcd_gotoxy(1, 1);
    lcd_putc("BATERIA:        ");
    lcd_gotoxy(1, 2);
    printf(lcd_putc, "%d%%             ", porcentaje); // Mostrar el porcentaje en el LCD

    // Verificar si el porcentaje de bater?a es menor al 15%
    if (porcentaje < 25) {
        output_high(PIN_A1); // Encender el LED en RA1
        lcd_gotoxy(1, 1);
    lcd_putc("CAMBIAR BATERIA:");
         delay_ms(400);
         
         
    } else {
        output_low(PIN_A1);  // Apagar el LED en RA1
        
    }

    delay_ms(300); // Esperar 2 segundos

    // Regresar al men? principal con la opci?n "PASSWORD" seleccionada
    mostrar_menu(0);  // Siempre comenzar desde "PASSWORD"
}

void main(void) {
    int dir = 0;  // Inicializar dir a 0 para que la opci?n "PASSWORD" siempre est? seleccionada al inicio
    char boton;

    // Configurar puertos
    set_tris_E(0x03); // RE0 y RE1 como entradas (botones)
    set_tris_A(0xFF); // RA0 como entrada (potenci?metro)
    set_tris_D(0x00); // RD como salidas (LCD)
    set_tris_A(0xFD); // RA1 como salida (LED)

    lcd_init();       // Inicializar el LCD

    // Inicializar ADC
    setup_adc(ADC_CLOCK_DIV_2);  // Configura la frecuencia del ADC
    setup_adc_ports(AN0); // Configura RA0 como entrada anal?gica

    mostrar_menu(dir);  // Mostrar el men? principal
    
    
    
    
    
    
   

  
    //

    while (true) {
        // Leer los botones RE0 y RE1
        boton = input(PIN_E0); // Bot?n de direcci?n (RE0)
        if (boton == 0) { // Si el bot?n est? presionado
            dir = (dir == 0) ? 1 : 0; // Cambiar de opci?n entre 0 y 1
            delay_ms(100); // Debounce
            mostrar_menu(dir); // Actualizar la pantalla
        }

        boton = input(PIN_E1); // Bot?n de selecci?n (RE1)
        if (boton == 0) { // Si el bot?n est? presionado
            if (dir == 0) {
                ingresar_password(); // Ingresar contrase?a
            } else if (dir == 1) {
                mostrar_bateria(); // Mostrar el estado de la bater?a
            }

            dir = 0; // Regresar a la opci?n "PASSWORD"
            delay_ms(100); // Debounce
            mostrar_menu(dir); // Actualizar la pantalla para mostrar "PASSWORD"
            
             
        }
        
         //
    float voltaje1 = leer_voltaje(); // Leer el voltaje


    // Limitar el porcentaje entre 0 y 100
    if (voltaje1 < 1) {
          output_high(PIN_A1); // Encender el LED en RA1 // Asegurarse de que el porcentaje no supere 100%
          lcd_gotoxy(1, 1);
    lcd_putc("PRECAUCION !!!  ");
     lcd_gotoxy(1, 2);
    lcd_putc("RECARGAR BATERIA");
    } else {
         output_low(PIN_A1);// Encender el LED en RA1    // Asegurarse de que el porcentaje no sea negativo
         mostrar_menu(dir);
    }
    }
}

