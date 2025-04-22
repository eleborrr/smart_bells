#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <midi.h>
#include <flash_service.h>
#include "fatfs.h"
#include <settings_manager.h>

uint16_t PPQN = 500;
const uint8_t BPM = 120;
const float TEMPO_MKS = 500000;

void test_midi_play(){
    uint32_t currentTime = 0; // Текущее время в тиках

    FIL file;
    FRESULT res;
    UINT bytesRead, bytesWritten;
	char consoleOutput[128];

    uint8_t fileBuffer[1024];

	MidiEvent midiEvents[100];


	res = f_open(&file, "random.mid", FA_READ);
	if (res != FR_OK) {
		sprintf(consoleOutput, "Ошибка открытия файла: %d\n\r", res);
		send_uart(consoleOutput);
		return;
	}

	int c = 0;
	while (1) {
		res = f_read(&file, fileBuffer, sizeof(fileBuffer), &bytesRead);

		// Проверяем ошибки и конец файла
		if (res != FR_OK || bytesRead == 0 || c == 1024) {
			break;
		}
		c++;

		// Обрабатываем прочитанные данные
//		send_uart("Прочитано %d байт:\n", bytesRead);
//		for (UINT i = 0; i < bytesRead; i++) {
//			send_uart("%02X ", fileBuffer[i]);
//		}
		send_uart("\n\r");
	}

	// Закрываем файл
	f_close(&file);

	read_midi_header(fileBuffer, 1024);
    parse_midi(fileBuffer, 1024, midiEvents, 1024);
    uint16_t output = 0;
    clear_shift_reg();


    for(int i = 0; i < sizeof(midiEvents); i++){
    	currentTime += midiEvents[i].delta_time;

		while (HAL_GetTick() < currentTime) {}

		MidiEvent curEvent = midiEvents[i];
		if (curEvent.type == MIDI_NOTE_ON){
			output = output | (1 << (curEvent.data.note.note % 48));
			put_val_to_shift_reg(output);
			sprintf(consoleOutput, "MIDI NOTE ON = %d ON CHANNEL = %d\n\r", curEvent.data.note.note, curEvent.data.note.channel);
			send_uart(consoleOutput);
			sprintf(consoleOutput, "output = %d\n\r", output);
			send_uart(consoleOutput);

		} else  if(curEvent.type == MIDI_NOTE_OFF){
			if (output > 0)
				output = output & (~(1 << curEvent.data.note.note % 48));
			sprintf(consoleOutput, "MIDI NOTE OFF = %d ON CHANNEL = %d\n\r", curEvent.data.note.note, curEvent.data.note.channel);
			send_uart(consoleOutput);
			put_val_to_shift_reg(output);
			sprintf(consoleOutput, "output = %d\n\r", output);
			send_uart(consoleOutput);
		}
		else if (curEvent.type == MIDI_SET_TEMPO){
			sprintf(consoleOutput, "MIDI SET TEMPO = %d\n\r", curEvent.data.tempo.tempo);
			send_uart(consoleOutput);
		}
		else{
			sprintf(consoleOutput, "%d\n\r", curEvent.type);
			send_uart(consoleOutput);
		}
    }
    clear_shift_reg();
}

void init_parser(){
	FIL file;
	FRESULT res;
    UINT br, bw;         /* File read/write count */
    Settings settings;
    BYTE buffer[512];   /* File copy buffer */
    char line[16];
    char output[64];

    settings.BPM = BPM;
    settings.PPQN = PPQN;

	res = f_open(&file, "settings.txt", FA_READ | FA_WRITE);
	sprintf(output, "res = %d\n\r", res);
	send_uart(output);
	if (res != FR_OK) {
		f_open(&file, "settings.txt", FA_WRITE | FA_CREATE_ALWAYS);
		int_to_str(settings.BPM, line);
		f_write(&file, line, strlen(line), &bw);

		sprintf(line, "\n");
		f_write(&file, line, strlen(line), &bw);

		int_to_str(settings.PPQN, line);
		f_write(&file, line, strlen(line), &bw);
	}
	else {
		if (f_gets(line, sizeof line, &file)) {
			sprintf(output, "line = %s\n\r", line);
				send_uart(output);
			}

		if (f_gets(line, sizeof(line), &file)) {
			settings.PPQN = (uint16_t)atoi(line);
		}
	}
    f_close(&file);
    sprintf(output, "closedd\n\r");
    send_uart(output);
}

void int_to_str(uint16_t num, char* str) {
    uint8_t i = 0;
    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);
    str[i] = '\0';

    // Разворачиваем строку (т.к. цифры записаны в обратном порядке)
    for (uint8_t j = 0; j < i / 2; j++) {
        char tmp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = tmp;
    }
//    str[i+1] = '\n';
}

void edit_parser_settings(){}

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

void read_midi_header(uint8_t* midi_data, uint32_t data_size){
    if (data_size < sizeof(MTHD_CHUNK)) {
        printf("Error: File too small!\n");
        return;
    }

    MTHD_CHUNK *header = (MTHD_CHUNK *)midi_data;

    // Проверяем сигнатуру "MThd"
    if (memcmp(header->ID, "MThd", 4) != 0) {
        printf("Error: Not a MIDI file!\n");
        return;
    }

    PPQN = header->Division;
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
        if ((status & 0xF0) == MIDI_NOTE_ON) {
            uint8_t note = midi_data[pos++];
            uint8_t velocity = midi_data[pos++];

            MidiEvent event;
            if(velocity == 0)
            	continue;

            event.type = MIDI_NOTE_ON;
            event.data.note.channel = status & 0x0F;
            event.data.note.note = note - '0';
            event.data.note.velocity = velocity;

            event.delta_time = delta_time;

            events[event_count++] = event;

            MidiEvent noteOffEvent;

            noteOffEvent.type = MIDI_NOTE_ON;
            noteOffEvent.data.note.channel = status & 0x0F;
            noteOffEvent.data.note.note = note - '0';
            noteOffEvent.data.note.velocity = velocity;

            noteOffEvent.delta_time = delta_time;

			events[event_count++] = noteOffEvent;
        }
        // Мета-событие: Tempo (0xFF 0x51 0x03 <темп 3 байта>)
        else if (status == 0xFF && midi_data[pos] == 0x51) {
            pos++; // Пропускаем 0x51
            uint8_t meta_len = midi_data[pos++];
            if (meta_len == 3) {
                pos += 3;
//                delta_time = 0;
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
//    uint32_t current_time = 0;
//    for (int i = 0; i < events_size; i++) {
//            current_time += events[i].delta_time;
//            events[i].delta_time = current_time;  // Теперь храним абсолютное время
//	}

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
	uint32_t current_time = 0;
	for (int i = 0; i < events_size; i++) {
		uint32_t new_delta = events[i].delta_time - current_time;
		current_time = events[i].delta_time;
		events[i].delta_time = new_delta;
	}
}

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
		{0, 100},
		{1, 200},
		{2, 800}
	};
	if(note > 2  || note < 0)
		return 0;
	int result = count_ticks_of_delay(delays[note].delta_time);
	return result;
}

int count_ticks_of_delay(uint32_t target_delay){
    uint32_t ticks = ((uint64_t)target_delay * 1000 * PPQN) / TEMPO_MKS;
	return ticks; //(ms -> s)
}
