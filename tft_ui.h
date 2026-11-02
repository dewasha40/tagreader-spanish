#pragma once
#include <string>
// Renderizador real del firmware. Coordenadas lógicas de 240 × 240 píxeles.
namespace tagreader_tft {
template<class Display, class Font>
void draw(Display &it, Font small, Font title, bool wifi, bool ha,
          const std::string &status, const std::string &uid,
          const std::string &source, const std::string &info, int count, bool present) {
  const auto bg=esphome::Color(9,17,29), panel=esphome::Color(20,35,52);
  const auto white=esphome::Color(235,243,255), muted=esphome::Color(151,173,198);
  const auto green=esphome::Color(74,223,169), orange=esphome::Color(255,186,87);
  it.fill(bg);
  it.print(14,10,title,white,"LECTOR NFC");
  it.printf(14,39,small,wifi?green:orange,"Wi-Fi: %s",wifi?"conectado":"sin conexión");
  it.printf(14,57,small,ha?green:orange,"Home Assistant: %s",ha?"conectado":"sin conexión");
  it.filled_rectangle(12,83,216,54,panel);
  it.print(22,91,small,muted,"ESTADO");
  // Las cadenas de estado están acotadas; no se recorta UTF-8 por bytes.
  it.print(22,111,small,present?green:white,status.c_str());
  it.print(14,146,small,muted,"ÚLTIMA ETIQUETA");
  // El UID hexadecimal es ASCII y cabe en dos líneas incluso con 10 bytes.
  it.print(14,164,small,white,uid.substr(0,26).c_str());
  if(uid.size()>26)it.print(14,179,small,white,uid.substr(26,26).c_str());
  const char *kind=source=="hass"?"Home Assistant":source=="spotify"?"Spotify":
    source=="amusic"?"Apple Music":source=="sonos"?"Sonos":source=="uid"?"UID":"Sin datos";
  it.print(14,200,small,green,kind);
  it.printf(14,220,small,muted,"Lecturas: %d",count);
}
}
