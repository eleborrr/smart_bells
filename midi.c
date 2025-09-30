#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <midi.h>
#include <flash_service.h>
#include "fatfs.h"
#include "Entities/bell_settings.h"

#define MAX_EVENTS_PER_TRACK 1000
#define BASE_NOTE 72
#define NUM_NOTES 16
#define NOTE_TIMING_FILE "timings.dat"

char consoleOutput[128];

NoteDelay delays[NUM_NOTES] = {
	{72, 0},
	{73, 10},
	{74, 0},
	{75, 0},
	{76, 0},
	{77, 0},
	{78, 0},
	{79, 0},
	{80, 0},
	{81, 0},
	{82, 0},
	{83, 0},
	{84, 0},
	{85, 0},
	{86, 0},
	{87, 0}
};

NoteDelay signals[NUM_NOTES] = {
    {72, 80},
	{73, 70},
	{74, 0},
	{75, 0},
	{76, 0},
	{77, 0},
	{78, 70},
	{79, 80},
	{80, 0},
	{81, 0},
	{82, 0},
	{83, 0},
	{84, 0},
	{85, 0},
	{86, 0},
	{87, 0}
};

MidiMetadata metadata;

extern TIM_HandleTypeDef htim2;
extern MidiPlaybackContext playback_ctx;

uint32_t ticks_to_milliseconds(uint32_t delta_ticks, uint16_t ppqn, uint32_t tempo) {
    // Формула: (delta_ticks * tempo) / (ppqn * 1000)
    uint64_t result = (uint64_t)delta_ticks * tempo;
    result /= (uint64_t)ppqn * 1000UL;
    return (uint32_t)result;
}

void play_midi(char* filename){
	sprintf(consoleOutput, "Начинаем считывать конфиг задержек\n\r");
	send_uart(consoleOutput);
	load_note_timing_from_sd(delays, signals, NUM_NOTES);

	sprintf(consoleOutput, "Начинаем открывать MIDI файл\n\r");
	send_uart(consoleOutput);
	FIL file;
	FRESULT res;
    UINT bytesRead;

	uint8_t fileBuffer[5*1024]; //TODO размеры

	static MidiEvent midiEvents[500]; //TODO размеры

	playback_ctx.events = midiEvents;
	playback_ctx.event_count = 0;
	playback_ctx.current_index = 0;
	playback_ctx.output_state = 0;
	playback_ctx.current_delta_time = 0;
	playback_ctx.htim = &htim2;

	res = f_open(&file, filename, FA_READ);
	if (res != FR_OK) {
		sprintf(consoleOutput, "Ошибка открытия файла: %d\n\r", res);
		send_uart(consoleOutput);
		return;
	}
	sprintf(consoleOutput, "Прочитали MIDI файл\n\r");
	send_uart(consoleOutput);

    res = f_read(&file, fileBuffer, sizeof(fileBuffer), &bytesRead);

	f_close(&file);

	if (read_midi_header(fileBuffer, bytesRead) != 0) {
		sprintf(consoleOutput, "У MIDI файла некорректный заголовок\n\r");
		send_uart(consoleOutput);
		return;
	}

	metadata.tempo = 400000;

	sprintf(consoleOutput, "Сохранили мета информацию о MIDI файле: Num_tracks = %u, tempo = %u, division = %u, format = %u\n\r", metadata.num_tracks, metadata.tempo, metadata.division, metadata.format);
	send_uart(consoleOutput);

	playback_ctx.event_count = parse_midi(fileBuffer, bytesRead, midiEvents, sizeof(midiEvents)/sizeof(MidiEvent));
	if (playback_ctx.event_count == 0) {
		sprintf(consoleOutput, "Нет событий MIDI\n\r");
		send_uart(consoleOutput);
		return;
	}

	clear_shift_reg();
	sprintf(consoleOutput, "Очистили сдвиговые регистры\n\r");
	send_uart(consoleOutput);

	sprintf(consoleOutput, "Начинаем воспроизводить MIDI файл\n\r");
	send_uart(consoleOutput);
    HAL_TIM_Base_Start_IT(playback_ctx.htim);
}

void process_midi_event(MidiPlaybackContext* ctx) {
    MidiEvent* current = &ctx->events[ctx->current_index];

	while(current->delta_time <= ctx->current_delta_time){
		sprintf(consoleOutput, "current ctx delta_time: %d; current note delta_time: %d\n\r", ctx->current_delta_time, current->delta_time);
		send_uart(consoleOutput);
		if (ctx->current_index >= ctx->event_count) {
			sprintf(consoleOutput, "Воспроизведение завершено\n\r");
			send_uart(consoleOutput);
			HAL_TIM_Base_Stop_IT(ctx->htim);
			clear_shift_reg();
			return;
		}

		switch(current->type) {
			case MIDI_NOTE_ON:
				ctx->output_state |= (1 << (current->data.note.note - BASE_NOTE)); // +6 HARDCODE
				sprintf(consoleOutput, "Note on: %d\n\r", current->data.note.note);
				break;

			case MIDI_NOTE_OFF:
				ctx->output_state &= ~(1 << (current->data.note.note - BASE_NOTE)); // +6 HARDCODE
				sprintf(consoleOutput, "Note off: %d\n\r", current->data.note.note);
				break;

			case MIDI_SET_TEMPO:
				//TODO поддержать смену темпа
				sprintf(consoleOutput, "Tempo: %d\n\r", current->data.tempo.tempo);
				break;

			default:
				sprintf(consoleOutput, "Event: %d\n\r", current->type);
		}
		send_uart(consoleOutput);
		ctx->current_index++;
		current = &ctx->events[ctx->current_index];
	}
	put_val_to_shift_reg(ctx->output_state);
	ctx->current_delta_time += count_ticks(5); //TODO переводить ARR в мс и передавать как аргумент в count_ticks
}


void int_to_str(uint16_t num, char* str) {
	uint8_t i = 0;
	do {
		str[i++] = (num % 10) + '0';
		num /= 10;
	} while (num > 0);
	str[i] = '\0';

	for (uint8_t j = 0; j < i / 2; j++) {
		char tmp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = tmp;
	}
}


void edit_parser_settings(){}

uint16_t swap16(uint16_t val) {
    return (val >> 8) | (val << 8);
}

int read_midi_header(uint8_t* midi_data, uint32_t data_size){
	sprintf(consoleOutput, "[in read_midi_header with data_size = %u]\n\r", data_size);
	send_uart(consoleOutput);

	if (data_size < sizeof(MTHD_CHUNK)) {
		printf("Error: File too small!\n");
		return 1;
	}

	MTHD_CHUNK *header = (MTHD_CHUNK *)midi_data;

	if (memcmp(header->ID, "MThd", 4) != 0) {
		printf("Error: Not a MIDI file!\n");
		return 1;
	}

	metadata.format = swap16(header->Format);
	metadata.num_tracks = swap16(header->NumTracks);
	metadata.division = swap16(header->Division);

//	sprintf(consoleOutput, "Спарсили заголовок с format = %u, num_tracks = %u, division = %u]\n\r", metadata->format, metadata->num_tracks, metadata->division);
//	send_uart(consoleOutput);
	return 0;
}

int parse_midi(uint8_t* midi_data, uint32_t data_size, MidiEvent* events, uint32_t max_events) {
	uint32_t pos = 0;
	uint32_t event_count = 0;
	uint32_t delta_time = 0;

	while (pos < data_size && event_count < max_events) {
		uint32_t time = 0;
		uint8_t byte;
		do {
			byte = midi_data[pos++];
			time = (time << 7) | (byte & 0x7F);
		} while (byte & 0x80);

		delta_time += time;

		uint8_t status = midi_data[pos++];
		uint8_t outputType = -1;

		if ((status & 0xF0) == MIDI_NOTE_ON) {
			uint8_t note = midi_data[pos++];
			uint8_t velocity = midi_data[pos++];

            MidiEvent event;
			event.type = MIDI_NOTE_ON;
            event.data.note.channel = 0;
			event.data.note.note = note; // - '0'
			event.data.note.velocity = velocity;

			event.delta_time = delta_time;  // тут стояло time пока я не решил сразу записывать абсолютное время
			events[event_count++] = event;

			// генерирую note off событие
			MidiEvent event2;
			event2.type = MIDI_NOTE_OFF;
			event2.data.note.channel = 0;
			event2.data.note.note = note; // - '0'
			event2.data.note.velocity = velocity;

			event2.delta_time = delta_time;
			events[event_count++] = event2;
		}
		else if (status == 0xFF){
			// Мета-событие: Tempo (0xFF 0x51 0x03 <темп 3 байта>)
			uint8_t meta_type = midi_data[pos++];

		    // Tempo change
		    if (meta_type == 0x51) {
		        uint8_t meta_len = midi_data[pos++];

		        if (meta_len == 3) {
		            uint32_t tempo = (midi_data[pos] << 16) | (midi_data[pos + 1] << 8) | midi_data[pos + 2];
		            pos += 3;

		            MidiEvent event;
		            event.type = MIDI_SET_TEMPO;
		            event.delta_time = time;
		            event.data.tempo.tempo = tempo;

		            events[event_count++] = event;
		        } else {
		            // Skip unexpected length
		            pos += meta_len;
		        }
		    } else {
		        // Unknown meta event — skip it
		        uint8_t meta_len = midi_data[pos++];
		        pos += meta_len;
		    }
		}
		else {
			if (status == 0xFF) {
				uint8_t meta_type = midi_data[pos++];
				uint8_t meta_len = midi_data[pos++];
				pos += meta_len;
			}
			else if ((status & 0xF0) >= 0xB0) {
				pos += 2;
			}
		}
	}
	sprintf(consoleOutput, "Спарсили MIDI файл с event_count = %u\n\r", event_count);
	send_uart(consoleOutput);

	events_post_proccessing(events, event_count);

	return event_count;
}

void apply_note_timing_modifications(MidiEvent* events, int count) {
    for (int i = 0; i < count; ++i) {
        if (events[i].type == MIDI_NOTE_ON) {
            int note = events[i].data.note.note;
            int idx = note - BASE_NOTE;
            if (idx >= 0 && idx < NUM_NOTES) {
            	if(delays[idx].value_ms != 0){
					uint32_t offset = count_ticks(delays[idx].value_ms);
					events[i].delta_time += offset;
            	}
            }

        } else if (events[i].type == MIDI_NOTE_OFF) {
            int note = events[i].data.note.note;
            int idx = note - BASE_NOTE;
            if (idx >= 0 && idx < NUM_NOTES) {
				// Set NOTE OFF time to NOTE ON + delay + signal
				uint32_t signal_ticks = count_ticks(signals[idx].value_ms);
				events[i].delta_time = events[i-1].delta_time + signal_ticks; //
            }

        } else if (events[i].type == MIDI_SET_TEMPO) { //TODO кажется если ноты будут смещаться а событие SET TEMPO нет, то могут быть приколы.
        	sprintf(consoleOutput, "[~~~]MidiMetadata tempo changed to = %d\n\r", events[i].data.tempo);
			send_uart(consoleOutput);
            metadata.tempo = events[i].data.tempo.tempo;
        }
    }
}

int compare_events_by_time(const void* a, const void* b) {
    const MidiEvent* ea = (const MidiEvent*)a;
    const MidiEvent* eb = (const MidiEvent*)b;
    return (int32_t)(ea->delta_time - eb->delta_time);
}

void events_post_proccessing(MidiEvent* events, uint32_t count) {
	sprintf(consoleOutput, "Начинаем обрабатывать MIDI события\n\r");
	send_uart(consoleOutput);

    apply_note_timing_modifications(events, count);
    sprintf(consoleOutput, "Применили задержки и длительности сигналов\n\r");
	send_uart(consoleOutput);

    qsort(events, count, sizeof(MidiEvent), compare_events_by_time);
    sprintf(consoleOutput, "Отсортировали события по абсолютному времени\n\r");
	send_uart(consoleOutput);

    sprintf(consoleOutput, "Закончили обрабатывать MIDI события\n\r");
	send_uart(consoleOutput);
}

NoteDelay* get_note_delays(){
	return delays;
}

void set_note_delay(uint8_t note, uint16_t delta_time){
	if(note > 16 || note < 0)
		return 0;
	delays[note].value_ms = delta_time;
	save_note_timing_to_sd(delays, signals, NUM_NOTES);
}

int get_note_ticks_delay(uint8_t note){
	if(note > 16 || note < 0)
		return 0;
	int result = count_ticks_of_delay(delays[note].value_ms);

	return result;
}

int count_ticks(uint32_t target_delay){
  uint32_t ticks = ((uint64_t)target_delay *1000 * metadata.division) / metadata.tempo ;
  return ticks; //(ms -> s)
}

int load_note_timing_from_sd(NoteDelay* delays, NoteDelay* signals, size_t max_count) {
    FIL file;
    FRESULT res;
    UINT bytes_read;
    BellSettings entry;

    res = f_open(&file, NOTE_TIMING_FILE, FA_READ);
    if (res != FR_OK) {
        sprintf(consoleOutput, "Failed to open timing file: %d\n\r", res);
        send_uart(consoleOutput);
        return -1;
    }

    size_t index = 0;
    while (index < max_count && f_read(&file, &entry, sizeof(BellSettings), &bytes_read) == FR_OK && bytes_read == sizeof(BellSettings)) {
        delays[index].note = BASE_NOTE + entry.num;
        delays[index].value_ms = entry.delay;

        signals[index].note = BASE_NOTE + entry.num;
        signals[index].value_ms = entry.duration;
        index++;
    }

    f_close(&file);
    sprintf(consoleOutput, "Loaded %u note timings from SD.\n\r", index);
    send_uart(consoleOutput);

    return 0;
}

int save_note_timing_to_sd(const NoteDelay* delays, const NoteDelay* signals, size_t count) {
    FIL file;
    FRESULT res;
    UINT bytes_written;
    BellSettings entry;

    res = f_open(&file, NOTE_TIMING_FILE, FA_CREATE_ALWAYS | FA_WRITE);
    if (res != FR_OK) {
        sprintf(consoleOutput, "Failed to open file for writing: %d\n\r", res);
        send_uart(consoleOutput);
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        entry.num = BASE_NOTE + delays[i].note;
        entry.channel = 0; //TODO захардкожено
        entry.delay = delays[i].value_ms;
        entry.duration = signals[i].value_ms;

        res = f_write(&file, &entry, sizeof(BellSettings), &bytes_written);
        if (res != FR_OK || bytes_written != sizeof(BellSettings)) {
            f_close(&file);
            sprintf(consoleOutput, "Write error at index %u: %d\n\r", i, res);
            send_uart(consoleOutput);
            return -2;
        }
    }

    f_close(&file);
    send_uart("Saved note timing to SD.\n\r");
    return 0;
}
