#ifndef RULES_DEF
#define RULES_DEF
#include <cassert>
#include <cstdlib>

#define NO_WORKERS 30
#define NO_WEEKS 2
#define NO_DAYS NO_WEEKS*2

enum class work_shift {
	morning,
	afternoon,
	night,
	nop,
};

enum class day {
	monday,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday,
};

int get_shift_duration(work_shift ws);

int get_no_shifts(day d, work_shift ws);

day get_day_type(int day_index);

char get_day_char(day d);
char get_work_shift_char(work_shift ws);

work_shift random_shift();
#endif
