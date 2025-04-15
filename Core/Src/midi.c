#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <midi.h>

const uint16_t PPQN = 500;
const uint8_t BPM = 120;
const float TEMPO_MKS = 500000;

int parseFile(){
    FILE *fileptr;
    uint8_t *buffer;
    long filelen;
    MidiEvent midiEvents[10000];

    fileptr = fopen("nggyu.mid", "rb");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(buffer, 1, filelen, fileptr); // Read in the entire file

    readHeader(buffer);

    parse_midi(buffer, filelen, midiEvents, 1024);
    for(int i = 0; i < sizeof(midiEvents); i++){
        MidiEvent curEvent = midiEvents[i];
        if(curEvent.type == MIDI_NOTE_OFF)
            printf("MIDI NOTE OFF = %d ON CHANNEL = %d\n", curEvent.data.note.note, curEvent.data.note.channel);
        else if (curEvent.type == MIDI_NOTE_ON)
            printf("MIDI NOTE ON = %d ON CHANNEL = %d\n", curEvent.data.note.note, curEvent.data.note.channel);
        else if (curEvent.type == MIDI_SET_TEMPO)
            printf("MIDI SET TEMPO = %d\n", curEvent.data.tempo.tempo);
        else
            printf("%d\n", curEvent.type);
        
        // if(i == 20)
        //     return 0;
    }
    // for(int i = 0; i < 30; i++){
    //     printf("<0x%x>\n", buffer[i]);
    // }
    fclose(fileptr); // Close the file
}

void readHeader(char *buffer){
    int offset = 0;
    // read Chunk Id
    for(int i = 0; i < 4; i++){
        printf("%c", buffer[i]);
        // printf("%02X\n", filePtr[i]);
    }
    offset += 4;
    printf("\n");

    // read Chunk Size
    // тупое чтение, оно не сработает как значение перестанет храниться в одном байте
    int size;
    for(int i = 4; i < 8; i++){
        size += (int)buffer[i];
        // printf("%d\n", (int)buffer[offset * i]);
        // printf("%02X\n", buffer[i]);
    }
    printf("%d\n", size);

    // read Format Type
    // сейм
    int formatType = 0;
    for(int i = 8; i < 10; i++){
        formatType += (int)buffer[i];
        // printf("%d\n", (int)buffer[offset * i]);
        // printf("%02X\n", buffer[i]);
    }
    printf("%d\n", formatType);

    
    int numberOfTracks = 0;
    for(int i = 10; i < 12; i++){
        numberOfTracks += (int)buffer[i];
        // printf("%d\n", (int)buffer[offset * i]);
        // printf("%02X\n", buffer[i]);
    }
    printf("%d\n", numberOfTracks);
}

// Парсит MIDI-данные и заполняет массив событий
int parse_midi(uint8_t* midi_data, uint32_t data_size, MidiEvent* events, uint32_t max_events) {
    uint32_t pos = 0;
    uint32_t event_count = 0;
    uint32_t delta_time = 0;

    while (pos < data_size && event_count < max_events) {
        // Читаем Delta-Time (переменная длина)
        uint32_t time = 0;
        uint8_t byte;
        do {
            byte = midi_data[pos++];
            time = (time << 7) | (byte & 0x7F);
        } while (byte & 0x80);

        delta_time += time;

        // Читаем статус-байт
        uint8_t status = midi_data[pos++];

        // Note On/Off события
        if ((status & 0xF0) == MIDI_NOTE_ON || (status & 0xF0) == MIDI_NOTE_OFF) {
            uint8_t note = midi_data[pos++];
            uint8_t velocity = midi_data[pos++];

            MidiEvent event;
            if(velocity == 0)
            	event.type = MIDI_NOTE_OFF;
            else if ((status & 0xF0) == MIDI_NOTE_ON) {
                event.type = MIDI_NOTE_ON;
            } else {
                event.type = MIDI_NOTE_OFF;
            }

            event.data.note.channel = status & 0x0F;
            event.data.note.note = note - '0';
            event.data.note.velocity = velocity;

            event.delta_time = delta_time;

            events[event_count++] = event;
            delta_time = 0;
        }
        // Мета-событие: Tempo (0xFF 0x51 0x03 <темп 3 байта>)
        else if (status == 0xFF && midi_data[pos] == 0x51) {
            pos++; // Пропускаем 0x51
            uint8_t meta_len = midi_data[pos++];
            if (meta_len == 3) {
                pos += 3;
                delta_time = 0;
            }
        }
        // Пропускаем другие события (не поддерживаются)
        else {
            // Пропускаем SysEx и другие мета-события
            if (status == 0xFF) {
                uint8_t meta_type = midi_data[pos++];
                uint8_t meta_len = midi_data[pos++];
                pos += meta_len;
            }
            // Пропускаем Control Change, Pitch Bend и т.д.
            else if ((status & 0xF0) >= 0xB0) {
                pos += 2;
            }
        }
    }

    events_post_proccessing(events, event_count);

    return event_count;
}

void events_post_proccessing(MidiEvent* events, int events_size){
    uint32_t current_time = 0;
//    uint32_t artificial_delay = get_note_ticks_delay(event.data.note.note);
    for (int i = 0; i < events_size; i++) {
            current_time += events[i].delta_time;
            events[i].delta_time = current_time;  // Теперь храним абсолютное время
	}

    // 2. Применяем задержки к нотам
	for (int i = 0; i < events_size; i++) {
		if (events[i].type == MIDI_NOTE_ON || events[i].type == MIDI_NOTE_OFF) {
			int delay = get_note_ticks_delay(events[i].data.note.note);
			if(events[i].delta_time < delay){
				AddDelayForAllExcept(delay - events[i].delta_time, i, events, events_size);
				events[i].delta_time = 0;
			}
			else
				events[i].delta_time -= delay;  // Сдвигаем ноту
		}
	}

	// 3. Сортируем события по новому времени (пузырьковая сортировка для простоты)
	for (int i = 0; i < events_size - 1; i++) {
		for (int j = 0; j < events_size - i - 1; j++) {
			if (events[j].delta_time > events[j + 1].delta_time) {
				MidiSwap(events, j, j + 1);
			}
		}
	}

	// 4. Возвращаем delta_time к относительному формату
	current_time = 0;
	for (int i = 0; i < events_size; i++) {
		uint32_t new_delta = events[i].delta_time - current_time;
		current_time = events[i].delta_time;
		events[i].delta_time = new_delta;
	}

//    qsort(events, event_count, events_size, compare_events);
//
//	for(int i = 0; i < events_size; i++){
//		if(events[i].type == MIDI_NOTE_OFF || events[i].type == MIDI_NOTE_ON){
//			if(events[i].delta_time < 0){
//				int indx = i;
//				int delta_time_temp = events[i].delta_time;
//				for(int j = indx - 1; j >= 0; j++){
//					MidiSwap(events, indx, j);
//					indx--;
//					if(events[indx].delta_time >=0)
//						break;
//				}
//			}
//		}
//	}
}

//void MidiSwap(MidiEvent* events, int i, int j){
//	MidiEvent temp = events[i];
//	int32_t diff = events[j].delta_time + temp.delta_time;
//	temp.delta_time = diff;
//	events[j].delta_time -= diff;
//	events[i] = events[j];
//	events[j] = temp;
//}

void AddDelayForAllExcept(int delay, int except, MidiEvent* events, int events_size){
	for(int i = 0; i < events_size; i++){
		if (i == except)
			continue;
		events[i].delta_time += delay;
	}
}

void MidiSwap(MidiEvent* events, int i, int j) {
    MidiEvent temp = events[i];
    events[i] = events[j];
    events[j] = temp;
}

int adjust_delta_time(MidiEvent note){
	int delta = get_note_delay(note.data.note.note);
	note.delta_time -= delta; // MIGHT BE ОТРИЦАТЕЛЬНЫМ(!)  чтобы фиксить - postprocessing
}

int get_note_ticks_delay(uint8_t note){
	NoteDelay delays[] = {
		{0, 300},
		{1, 500},
		{2, 800}
	};
	if(note > 2  || note < 0)
		return 0;
	uint32_t delayVal = delays[note].delta_time;
	int result = count_ticks_of_delay(delays[note].delta_time);
	return result;
}

int count_ticks_of_delay(uint32_t target_delay){
    uint32_t ticks = ((uint64_t)target_delay * 1000 * PPQN) / TEMPO_MKS;
	return ticks; //(ms -> s)
}
