#include "stm32f4xx_hal.h"

typedef struct
{
   /* Here's the 8 byte header that all chunks must have */
   char     ID[4];  /* This will be 'M','T','h','d' */
   uint32_t Length; /* This will be 6 */

   uint16_t Format;
   uint16_t NumTracks;
   uint16_t Division;
} MTHD_CHUNK;

typedef enum {
    MIDI_NOTE_OFF = 0x80,
    MIDI_NOTE_ON = 0x90,
    MIDI_SET_TEMPO = 0xFF51
} MidiEventType;

typedef struct {
    uint8_t channel;
    uint8_t note;
    uint8_t velocity;
} MidiNoteEvent;

typedef struct {
    uint32_t tempo;
} MidiTempoEvent;

typedef struct {
    MidiEventType type;
    uint32_t delta_time;
    union {
        MidiNoteEvent note;
        MidiTempoEvent tempo;
    } data;
} MidiEvent;

typedef struct {
	uint8_t note;
	uint16_t value_ms;
} NoteDelay;

typedef struct {
    MidiEvent* events;
    uint16_t event_count;
    uint16_t current_index;
    uint8_t output_state;
    uint32_t current_delta_time;
    TIM_HandleTypeDef* htim;
} MidiPlaybackContext;

typedef struct {
    uint16_t format;          // MIDI format (0, 1, 2)
    uint16_t num_tracks;      // Number of tracks in the MIDI file
    uint16_t division;        // PPQN (Pulses Per Quarter Note)
    uint32_t tempo;             // Beats per minute (tempo)
} MidiMetadata;

void play_midi(char* filename);
void set_note_delay(uint8_t note, uint16_t delta_time);
int get_note_ticks_delay(uint8_t note);
void events_post_proccessing(MidiEvent* events, uint32_t count);
uint32_t count_arr(uint16_t delta_ms);
int read_midi_header(uint8_t* midi_data, uint32_t data_size);
void MidiSwap(MidiEvent* events, int i, int j);
void AddDelayForAllExcept(int delay, int except, MidiEvent* events, int events_size);
int adjust_delta_time(MidiEvent note);
int get_note_ticks_delay(uint8_t note);
int count_ticks_of_delay(uint32_t target_delay);
void set_bell_impulse(uint8_t bell_number, short on);
