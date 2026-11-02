# Integración en ESP32 Simulador

El perfil de este proyecto usa el identificador `tagreader`. La versión anterior del simulador solo admite los identificadores registrados en `Projects.Supported`, por lo que copiar el JSON sin actualizar el programa no basta.

La entrega Windows incluye una copia del simulador con estos cambios:

- Registro de `tagreader` y descripción del panel TFT en `Core.cs`.
- Recursos de esta carpeta empaquetados en `payload.zip`, bajo `web/tagreader/`.
- Selección de escenarios: preparado, lectura, escritura pendiente y sin conexión.
- Inicio con `--tagreader --demo` y prueba completa con `--tagreader-smoke-test CARPETA`.
- Pruebas funcionales JavaScript, capturas de pantalla, detener y volver a iniciar.

Para compilar la copia completa, utiliza `dotnet publish source/app/ESP32Simulador.csproj -c Release -o app`, desde la carpeta de la entrega Windows. El proyecto necesita .NET SDK 10. Se incluyen los recursos y los avisos originales del simulador.

Esta entrega tiene su propia carpeta y perfil; no sustituye la instalación de los demás proyectos. Los recursos web originales siguen dentro del ejecutable. No representa una emulación del procesador ni del firmware ESPHome.

Los controles de prueba son ficticios. Las melodías se indican visualmente y no se reproducen por el altavoz. «Solo pantalla» muestra la composición de la TFT; haz doble clic para recuperar los controles.

Pruebas disponibles: identificador de Home Assistant completo, ausencia de lecturas duplicadas mientras una etiqueta sigue presente, retirada, UID, Spotify, Apple Music, Sonos, escritura y relectura de identificador, borrado conservando UID, cancelación, identificador aleatorio, escritura musical y desconexión.
