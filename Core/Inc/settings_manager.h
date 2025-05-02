#include <stdint.h>

typedef struct {
    uint8_t BPM;
    uint16_t PPQN;
} Settings;

void LoadSettings(Settings *settings);
