#include "Handlers/bell_settings_handlers.h"
#include "midi.h"

List* handle_get_bell_settings(const Empty* request) {
	NoteDelay* delays = get_note_delays();
	List* res = get_next_list(sizeof(BellSettings));
	for (int i = 0; i < 16; i++) {
		BellSettings setting;
				setting.channel = delays[i].note;
				setting.delay = delays[i].value_ms;
				setting.duration = delays[i].value_ms;
				setting.num = delays[i].note;
				list_add(res, &setting);
	}
	return res;
}

Empty* handle_try_single_bell(const BellSettings* request) {
	NoteDelay* delays = get_note_delays();
	uint8_t output = 0;
	output |= (1 << (request->num));
	put_val_to_shift_reg(output);
	HAL_Delay(request->delay);
	output &= ~(1 << (request->num));
	put_val_to_shift_reg(output);
	return malloc(sizeof(Empty));
}

Empty* handle_compare_two_bells(const TwoBells* request) {
	uint8_t output = 0;

	sort_bells_by_delay(request);

	uint16_t delay1 = request->bell1.delay;
	uint16_t delay2 = request->bell2.delay;

	HAL_Delay(delay1);
	output |= (1 << (request->bell1.num));
	put_val_to_shift_reg(output);

	if(delay1*2 < delay2){
		HAL_Delay(delay1);
		output &= ~(1 << (request->bell1.num));
		put_val_to_shift_reg(output);

		HAL_Delay(delay2 - 2*delay1);
		output |= (1 << (request->bell2.num));
		put_val_to_shift_reg(output);

		HAL_Delay(delay2);
		output &= ~(1 << (request->bell2.num));
		put_val_to_shift_reg(output);
	}
	else{
		HAL_Delay(delay2 - delay1);
		output |= (1 << (request->bell2.num));
		put_val_to_shift_reg(output);

		HAL_Delay(delay1 - (delay2 - delay1));
		output &= ~(1 << (request->bell1.num));
		put_val_to_shift_reg(output);

		HAL_Delay(delay2 - (delay1 - (delay2 - delay1)));
		output &= ~(1 << (request->bell2.num));
		put_val_to_shift_reg(output);

	}

	return malloc(sizeof(Empty));
}

Empty* handle_save_bell_settings(const List* request) {
	BellSettings *cur;
	list_foreach(request, cur) {
		set_note_delay(cur->num, cur->delay);
		cur->channel = 0;
	}
	return malloc(sizeof(Empty));
}

void sort_bells_by_delay(TwoBells* request){
	if (request->bell1.delay >= request->bell2.delay){
		BellSettings bell1Temp = request->bell1;
		request->bell1 = request->bell2;
		request->bell2 = bell1Temp;
	}
}
