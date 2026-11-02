# Pantalla TFT a color

## Configuración preparada

`tagreader-tft.yaml` incluye el lector completo y añade una TFT ST7789V por SPI, de 240 × 240 píxeles, con búfer de color de 8 bits para limitar el consumo de RAM del ESP32-WROOM. El controlador se ha configurado con `ili9xxx`, soportado por ESPHome 2026.10.1; ESPHome recomienda `mipi_spi` para nuevos diseños. Se mantiene esta configuración hasta validar el módulo físico elegido.

| Señal TFT | GPIO ESP32 |
| --- | --- |
| SCK / CLK | 18 |
| MOSI / SDA / DIN | 23 |
| CS | 5 |
| DC / A0 | 27 |
| RESET / RES | 26 |
| BL / retroiluminación | 25 |
| GND | GND común |

El pin BL es una señal de control; si el módulo expone directamente los LED de retroiluminación, utiliza el circuito de control apropiado y no alimentes esa carga desde un GPIO. La alimentación depende del módulo; confirma su tensión y la compatibilidad de sus señales antes de conectarlo. GPIO5 también participa en el arranque: revisa las resistencias del módulo.

El PN532 conserva SDA21/SCL22 y no comparte el bus SPI. El zumbador12 y el LED15 permanecen como en el montaje original.

## Datos mostrados

- Wi-Fi conectado o desconectado.
- Conexión de Home Assistant mediante el sensor de estado de ESPHome.
- Espera, etiqueta detectada, escritura pendiente, borrado pendiente, operación terminada pendiente de verificar, cancelación y retirada.
- Último UID, repartido en dos líneas si es largo.
- Tipo de etiqueta: UID, Home Assistant, Spotify, Apple Music o Sonos.
- Contador de lecturas desde el encendido; no se guarda en la memoria flash.

Los datos se actualizan desde las mismas acciones y eventos del PN532 del firmware. No se necesita pantalla táctil; las órdenes de escritura proceden de Home Assistant. La retroiluminación aparece como una entidad independiente.

## Adaptación a otra pantalla

Los pines se cambian en `substitutions`. Para otro controlador hay que ajustar `display.model`; para otro tamaño hay que adaptar también `dimensions` y las coordenadas de `tft_ui.h`. Algunos ST7789 requieren desplazamiento vertical 80, inversión o rotación diferente. La configuración de referencia usa desplazamientos cero y colores invertidos; queda pendiente comprobarlos en el módulo real.

No se presupone compatibilidad directa con las pantallas AMOLED, QSPI o redondas de otros proyectos. La carcasa original necesita una modificación para alojar la TFT. No se han modificado los STL ni se ha realizado una prueba física.

Documentación del controlador: https://esphome.io/components/display/ili9xxx/
