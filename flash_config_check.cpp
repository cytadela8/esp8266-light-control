#include "flash_config_check.h"

#include <ESP8266WiFi.h>

String flashConfigCache = "";

String& flashChipConfigCheck() {
  if (flashConfigCache.length() == 0) {
    uint32_t realSize = ESP.getFlashChipRealSize();
    uint32_t ideSize = ESP.getFlashChipSize();
    FlashMode_t ideMode = ESP.getFlashChipMode();
    char buffer[128];
    sprintf(buffer, "Flash real id:   %08X\n", ESP.getFlashChipId());
    flashConfigCache += buffer;
    sprintf(buffer, "Flash real size: %u bytes\n\n", realSize);
    flashConfigCache += buffer;
    sprintf(buffer, "Flash ide  size: %u bytes\n", ideSize);
    flashConfigCache += buffer;
    sprintf(buffer, "Flash ide speed: %u Hz\n", ESP.getFlashChipSpeed());
    flashConfigCache += buffer;
    sprintf(buffer, "Flash ide mode:  %s\n",
            (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" :
                                                                       ideMode == FM_DOUT ? "DOUT"
                                                                                          : "UNKNOWN"));
    flashConfigCache += buffer;

    if (ideSize != realSize) {
      flashConfigCache += "Flash Chip configuration wrong!\n";
    } else {
      flashConfigCache += "Flash Chip configuration ok.\n";
    }
  }

  return flashConfigCache;
}
