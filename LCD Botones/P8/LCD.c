#include <18F4550.h>
#use delay(clock=4000000)
#include <lcd.c>

int A = 0;

void main() {
    set_tris_A(0xFF); // RA0-RA3 como entradas
    set_tris_B(0x00); // RB como salidas
    lcd_init();
    output_B(0x00);
    
    // Inicializar el mensaje fijo en la l�nea 1
    lcd_gotoxy(1, 1);
    printf(lcd_putc, "Pulsa un Boton");
    
    do {
        // Leer el estado de los botones
        if (!input(pin_A0)) { // Bot�n para A = 1
            A = 1;
            delay_ms(200); // Antirrebote
        }
        
        if (!input(pin_A1)) { // Bot�n para A = 2
            A = 2;
            delay_ms(200); // Antirrebote
        }
        
        if (!input(pin_A2)) { // Bot�n para A = 3
            A = 3;
            delay_ms(200); // Antirrebote
        }
        
        if (!input(pin_A3)) { // Bot�n para A = 4
            A = 4;
            delay_ms(200); // Antirrebote
        }

        // Actualizar solo la l�nea 2 seg�n el valor de A
        lcd_gotoxy(1, 2); // Ir a la segunda l�nea
        switch (A) {
            case 0:
                printf(lcd_putc, "                "); // Borrar la l�nea
                break;
            case 1:
                printf(lcd_putc, "Pulsaste Boton 1 <-");
                break;
            case 2:
                printf(lcd_putc, "Pulsaste Boton 2 <-");
                break;
            case 3:
                printf(lcd_putc, "Pulsaste Boton 3 <-");
                break;
            case 4:
                printf(lcd_putc, "Pulsaste Boton 4 <-");
                break;
        }
        
    } while (true);
}
