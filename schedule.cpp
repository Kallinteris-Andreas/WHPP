#include "schedule.hpp"

schedule::schedule(){};

void schedule::print(){
	std::cout << "   ";
	for (int i = 0; i != NO_WEEKS*7; i++)
		std::cout << "   " << get_day_char(get_day_type(i));

	std::cout << std::endl;
	for (int i = 0; i != NO_WORKERS; i++){
		printf("#%2d", i);
		for (int j = 0; j != NO_WEEKS*7; j++)
			std::cout << "   " << get_work_shift_char(workers[i].get_work_shift(j));
		std::cout << std::endl;
	}
}

void schedule::init(){
	for (int day_index = 0; day_index != NO_WEEKS*7; day_index++){
		int slots_left = get_no_shifts(get_day_type(day_index), work_shift::morning);
		//std::cout << slots_left << std::endl;
		for (;slots_left != 0; slots_left--){
			int worker_index = rand() % NO_WORKERS;
			while (workers[worker_index].get_work_shift(day_index) != work_shift::nop)
				worker_index = rand() % NO_WORKERS;
			workers[worker_index].set_work_shift(day_index, work_shift::morning);
		}

		slots_left = get_no_shifts(get_day_type(day_index), work_shift::afternoon);
		for (;slots_left != 0; slots_left--){
			int worker_index = rand() % NO_WORKERS;
			while (workers[worker_index].get_work_shift(day_index) != work_shift::nop)
				worker_index = rand() % NO_WORKERS;
			workers[worker_index].set_work_shift(day_index, work_shift::afternoon);
		}

		slots_left = get_no_shifts(get_day_type(day_index), work_shift::night);
		for (;slots_left != 0; slots_left--){
			int worker_index = rand() % NO_WORKERS;
			while (workers[worker_index].get_work_shift(day_index) != work_shift::nop)
				worker_index = rand() % NO_WORKERS;
			workers[worker_index].set_work_shift(day_index, work_shift::night);
		}
	}
}

bool schedule::satisfy_constraint(employee* workers_table){
	for (int day_index = 0; day_index != NO_WEEKS*7; day_index++){
		int morning_shifts = get_no_shifts(get_day_type(day_index), work_shift::morning);
		int afternoon_shifts = get_no_shifts(get_day_type(day_index), work_shift::afternoon);
		int night_shifts = get_no_shifts(get_day_type(day_index), work_shift::night);
		int cur_morning_shifts = 0;
		int cur_afternoon_shifts = 0;
		int cur_night_shifts = 0;

		for (int worker_index = 0; worker_index != NO_WORKERS; worker_index++){
			switch(workers_table[worker_index].get_work_shift(day_index)){
				case work_shift::morning: cur_morning_shifts++;
					break;
				case work_shift::afternoon: cur_afternoon_shifts++;
					break;
				case work_shift::night: cur_night_shifts++;
					break;
			}
		}

		if (cur_morning_shifts != morning_shifts)
			return false;
		if (cur_afternoon_shifts != afternoon_shifts)
			return false;
		if (cur_night_shifts != night_shifts)
			return false;
	}
	return true;
}

