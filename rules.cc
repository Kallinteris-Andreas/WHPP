#include "rules.h"
int get_shift_duration(work_shift ws){
	switch(ws) {
		case work_shift::morning: return 8;
		case work_shift::afternoon: return 8;
		case work_shift::night: return 10;
		case work_shift::nop: return 0;
		default: assert(!"NOT A VALID WORK SHIFT");
	}
}

int get_no_shifts(day d, work_shift ws){
	switch(d) {
		case day::monday:
			switch(ws){
				case work_shift::morning: return 10;
				case work_shift::afternoon: return 10;
				case work_shift::night: return 5;
				default: assert(!"NOT A VALID WORK SHIFT");
			}
		case day::tuesday:
			switch(ws){
				case work_shift::morning: return 10;
				case work_shift::afternoon: return 10;
				case work_shift::night: return 5;
				default: assert(!"NOT A VALID WORK SHIFT");
			}
		case day::wednesday:
			switch(ws){
				case work_shift::morning: return 5;
				case work_shift::afternoon: return 10;
				case work_shift::night: return 5;
				default: assert(!"NOT A VALID WORK SHIFT");
			}
		case day::thursday:
			switch(ws){
				case work_shift::morning:
				case work_shift::afternoon:
				case work_shift::night: return 5;
				default : assert(!"NOT A VALID WORK SHIFT");
			}
		case day::friday:
			switch(ws){
				case work_shift::morning: return 5;
				case work_shift::afternoon: return 10;
				case work_shift::night: return 5;
				default: assert(!"NOT A VALID WORK SHIFT");
			}
		case day::saturday:
			switch(ws){
				case work_shift::morning:
				case work_shift::afternoon:
				case work_shift::night: return 5;
				default: assert(!"NOT A VALID WORK SHIFT");
			}
		case day::sunday:
			switch(ws){
				case work_shift::morning:
				case work_shift::afternoon:
				case work_shift::night: return 5;
				default: assert(!"NOT A VALID WORK SHIFT");
			}
		default: assert(!"NOT A VALID DAY");
	}
}

day get_day_type(int day_index){
	switch(day_index%7){
		case 0: return day::monday;
		case 1: return day::tuesday;
		case 2: return day::wednesday;
		case 3: return day::thursday;
		case 4: return day::friday;
		case 5: return day::saturday;
		case 6: return day::sunday;
	}
	assert(!"how did you get here?");
}

char get_day_char(day d){

	switch (d){
		case day::monday: return 'M';
		case day::tuesday: return 'T';
		case day::wednesday: return 'W';
		case day::thursday: return 'T';
		case day::friday: return 'F';
		case day::saturday: return 'S';
		case day::sunday: return 'S';
		default: assert(!"NOT A VALID DAY");
	}
}

char get_work_shift_char(work_shift ws){
	switch(ws) {
		case work_shift::morning: return 'M';
		case work_shift::afternoon: return 'A';
		case work_shift::night: return 'N';
		case work_shift::nop: return '-';
		default: assert(!"NOT A VALID WORK SHIFT");
	}
}

work_shift random_shift(){
	switch(rand()%3) {
		case 0: return work_shift::morning;
		case 1: return work_shift::afternoon;
		case 2: return work_shift::night;
	}
}
