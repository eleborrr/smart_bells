typedef struct MTHD_CHUNK
{
   /* Here's the 8 byte header that all chunks must have */
   char           ID[4];  /* This will be 'M','T','h','d' */
   unsigned long  Length; /* This will be 6 */

   /* Here are the 6 bytes */
   unsigned short Format;
   unsigned short NumTracks;
   unsigned short Division;
};

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
	uint32_t delta_time;
} NoteDelay;

void readHeader(char *buffer);
void events_post_proccessing(MidiEvent* events, int events_size);
int parse_midi(uint8_t* midi_data, uint32_t data_size, MidiEvent* events, uint32_t max_events);
void MidiSwap(MidiEvent* events, int i, int j);
void AddDelayForAllExcept(int delay, int except, MidiEvent* events, int events_size);
int adjust_delta_time(MidiEvent note);
int get_note_ticks_delay(uint8_t note);
int count_ticks_of_delay(uint32_t target_delay);
void set_bell_impulse(uint8_t bell_number, short on);
