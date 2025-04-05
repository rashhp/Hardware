#include <18F4550.h>
#use delay(clock=4000000)
#include <lcd.c>

void main() {
    float voltaje;
    int16 valor;
    float calibracion = 4.0; // Ajusta este valor para calibrar la lectura

    // Configurar puertos
    set_tris_A(0xFF); // RA0 como entrada (potenciómetro)
    set_tris_D(0x00); // RD como salidas (LCD)
    lcd_init();       // Inicializar el LCD

    // Inicializar ADC
    setup_adc(ADC_CLOCK_DIV_2);  // Configura la frecuencia del ADC
    setup_adc_ports(AN0); // Configura RA0 como entrada analógica

    // Mensaje inicial en el LCD
    lcd_gotoxy(1, 1);
    printf(lcd_putc, "VOLTAJE:  ");

    while (true) {
        // Leer el valor del ADC
        valor = read_adc(); // Leer ADC de RA0

        // Convertir el valor a voltaje con calibración
        voltaje = (valor * calibracion * 5.0) / 1023.0; // Ajustar según la calibración

        // Mostrar el voltaje en el LCD
        lcd_gotoxy(1, 2); // Ir a la segunda línea
        printf(lcd_putc, "%.2f V       ", voltaje); // Mostrar el voltaje con dos decimales

        delay_ms(500); // Esperar medio segundo antes de la siguiente lectura
    }
}

