#include <18F4550.h>
#fuses HSPLL, PLL5, USBDIV, NOWDT, CPUDIV1, NOPROTECT, NODEBUG, NOPBADEN, NOLVP, NOVREGEN
#use delay(clock = 48MHz)
#define LCD_DATA_PORT getenv("SFR:PORTB")
#include <lcd.c>
#include "KBD4x4.c"

void main(void) {
    char tecla;
    char Password[4];
    int dir = 0;

    lcd_init();
    kbd_init();

    while (true) {
        lcd_gotoxy(1, 1);
        lcd_putc("INGRESE PASSWORD: ");
        lcd_gotoxy(1, 2);
        dir = 0; // Reiniciar el �ndice para el nuevo intento

        while (dir < 4) {
            tecla = kbd_getc();
            if (tecla != 0) {
                Password[dir] = tecla;
                lcd_putc(tecla);
                delay_ms(50);
                dir++;
            }
        }

        // Verificar la contrase�a
        if (Password[0] == '1' && Password[1] == '2' && Password[2] == '3' && Password[3] == '4') {
            lcd_gotoxy(1, 1);
            lcd_putc("CODIGO CORRECTO ");
            output_high(PIN_A1);
            delay_ms(10000); // Esperar 10 segundos
            output_low(PIN_A1);
        } else {
            lcd_gotoxy(1, 1);
            lcd_putc("CODIGOINCORRECTO");
            lcd_gotoxy(1, 2);
            lcd_putc("                "); // Limpiar la l�nea 2
            delay_ms(200); // Esperar 2 segundos
        }

        // Al final de un intento (correcto o incorrecto), se limpia la pantalla
        lcd_gotoxy(1, 1);
        lcd_putc("INGRESE PASSWORD: "); // Mensaje para reiniciar
    }
}


