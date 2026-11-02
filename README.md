# Lector NFC para Home Assistant · Castellano y TFT a color

Basado en el trabajo de [adonno](https://github.com/adonno/tagreader) y el montaje ESP32 de [leinich](https://github.com/leinich/tagreader). Este fork conserva sus modelos, esquemas, fotos y funciones NFC; incorpora traducción al castellano, compatibilidad con ESPHome 2026.10.1 y una variante con pantalla TFT a color.

El lector utiliza un ESP32, un PN532 por I2C y [ESPHome](https://esphome.io) para integrarse con [Home Assistant](https://www.home-assistant.io).

![Fotografía del lector terminado](docs/tagreader_esp32_final.png)

## Material necesario

- ESP32; el montaje original utiliza un D1 ESP32 Mini Wroom USB-C.
- Lector NFC PN532.
- Un LED WS2812.
- Zumbador piezoeléctrico; el montaje original cita el KY-012.
- Opcional: pantalla TFT ST7789V de 240 × 240 por SPI para la variante preparada.

## Montaje del lector

![Esquema de conexiones original](Schematics/tagreader_esp32_schema.png)
![Fotografía de las soldaduras](Schematics/tagreader_esp32_solder.png)

Configura el PN532 en I2C: interruptor 1 activado (arriba), interruptor 2 desactivado (abajo). Esto permite la comunicación por GPIO21 y GPIO22.

| Componente | ESP32 |
| --- | --- |
| PN532 SDA | GPIO21 |
| PN532 SCL | GPIO22 |
| Zumbador | GPIO12 |
| Datos WS2812 | GPIO15 |

Comparte la masa entre los módulos. Revisa los requisitos de alimentación del módulo exacto y utiliza señales de 3,3 V compatibles con el ESP32. Los GPIO12 y GPIO15 se mantienen del montaje original y afectan al arranque del ESP32; evita resistencias externas que fuercen niveles inadecuados al encender.

![Carcasa abierta](docs/tagreader_esp32_opencase.png)
![Vista de la carcasa abierta](docs/tagreader_esp32_rendering.png)
![Segunda vista del montaje](docs/tagreader_esp32_rendering2.png)

Los modelos de carcasa están en [STLs](STLs), en STL multicolor y 3MF. La referencia original indica una impresión de unas 2 h 25 min en Bambu Lab para tapa, base y caja de almacenamiento. Conservamos los nombres de archivo para mantener las referencias originales.

Referencia de montaje aportada por el usuario: [NFC Tag Reader ESP32 USB-C en MakerWorld](https://makerworld.com/es/models/194671-nfc-tag-reader-esp32-usb-c#profileId-215124). El acceso automatizado devuelve 403; no se han podido descargar ni comparar imágenes adicionales de esa página. Las seis imágenes anteriores ya estaban en el fork. La carcasa original no incorpora un hueco para la TFT: habrá que adaptarla cuando se elija el módulo.

## Configuración de Home Assistant

La documentación original indica Home Assistant 0.115 o posterior como mínimo histórico para etiquetas. Esta adaptación valida ESPHome 2026.10.1; no se ha probado con una instalación real de Home Assistant.

1. Copia `secrets.example.yaml` como `secrets.yaml` y rellena Wi-Fi, clave de recuperación, clave de cifrado de API y contraseña OTA. Genera una clave de API única de 32 bytes en base64; el ejemplo de ceros es deliberadamente inválido y debe sustituirse.
2. Elige `tagreader.yaml` para el lector sin pantalla o `tagreader-tft.yaml` para el lector con TFT. Mantén los archivos del proyecto juntos, incluidas `fonts/` y `tft_ui.h` para la TFT.
3. Valida con `esphome config tagreader-tft.yaml` y compila con `esphome compile tagreader-tft.yaml`, utilizando ESPHome 2026.10.1. Para instalar sin TFT, cambia el nombre del archivo en esos comandos.
4. Instala el firmware cuando hayas revisado el módulo y sus conexiones. No se realiza ninguna carga automática desde este paquete.
5. Home Assistant detectará el lector cuando esté en la misma red. Completa la integración desde su interfaz. Si falla el Wi-Fi, el lector ofrece un punto de acceso con portal cautivo para introducir las credenciales.

Se utiliza DHCP para evitar reutilizar la dirección IP fija de la vivienda del autor. Se conserva `nfckizi1` como nombre técnico para mantener la compatibilidad con el ejemplo de automatización; el nombre visible es «Lector NFC».

## Uso

Gestiona las etiquetas desde la sección Etiquetas de Home Assistant; en la documentación original aparece como Configuración → Etiquetas. El lector admite UID, etiquetas NDEF de Home Assistant, Spotify, Apple Music y Sonos.

Los controles visibles están en castellano: zumbador, LED, escritura aleatoria, borrado, cancelación y reinicio. Los servicios técnicos `write_tag_id`, `write_music_tag`, `play_rtttl`, `rfidreader_tag_ok` y `rfidreader_tag_ko` conservan sus identificadores para no romper automatizaciones. También se conservan los eventos `esphome.music_tag` y `esphome.tag_removed` y los campos `reader`, `source`, `url` e `info`.

Las automatizaciones traducidas están en [blueprints](blueprints). `PlayMusicTag.yaml` es un plano reutilizable; `automation.yaml` es el ejemplo concreto del autor, con el reproductor `media_player.kinderzimmer_1`, que debes cambiar por el tuyo. El plano reutilizable solicita también el nombre técnico del lector (`substitutions.name`); así el filtro de eventos funciona aunque el nombre visible esté traducido.

Se corrige además la extracción del identificador de una etiqueta de Home Assistant: ahora se elimina la longitud real del prefijo URL en lugar de un desplazamiento fijo que truncaba el identificador.

## TFT a color

Consulta [PANTALLA-TFT.md](PANTALLA-TFT.md) para el cableado, resolución, información mostrada y límites de la adaptación. La variante tiene un renderizador real de ESPHome; no es únicamente una maqueta.

## Simulador ESP32

La carpeta [simulator](simulator) contiene un panel funcional local y el perfil `tagreader.sim.json`. El paquete Windows que acompaña a esta entrega es una copia del ESP32 Simulador con soporte para este proyecto; el ejecutable anterior no reconoce identificadores de proyecto nuevos solo por añadir un JSON.

Abre `Abrir-Lector-NFC.cmd` en el paquete `ESP32Simulador-NFC`, selecciona una etiqueta y pulsa «Acercar etiqueta». Para escribir o borrar, retírala, prepara la operación, acércala y retírala otra vez. Una segunda lectura permite comprobar el contenido grabado. Puedes probar desconexión, desactivar LED y zumbador y ver los eventos simulados.

«Solo pantalla» oculta los controles; un doble clic los recupera. El simulador ejecuta una lógica funcional JavaScript y una previsualización del panel; no ejecuta el binario ESPHome, no emula eléctricamente el PN532 y no se conecta a Home Assistant. La TFT física utiliza `tft_ui.h`; su renderizado no se sustituye por el panel web.

## Autoría y licencia

Consulta [AUTHORS.md](AUTHORS.md). Se conserva íntegra la licencia [GPL-3.0](LICENSE) en su texto legal original. Las marcas, enlaces, identificadores de API y formatos técnicos no se traducen.
