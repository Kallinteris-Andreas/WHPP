#include "employee.hpp"

employee::employee(){
	for (int i = 0; i!= NO_WEEKS*7; i++)
		shift[i] = work_shift::nop;
}

work_shift employee::get_work_shift(int day_index){
	assert(day_index >= 0 && day_index < sizeof(shift)/sizeof(work_shift));
	//assert(index > 0 && index < NO_WEEKS*2);
	return shift[day_index];
}

void employee::set_work_shift(int day_index, work_shift ws){shift[day_index] = ws;}

bool employee::works(int day_index){return shift[day_index] != work_shift::nop;};

int employee::total_work_hours(){
	int total_hours = 0;
	for (int day_index = 0; day_index != NO_WEEKS*7; day_index++)
		total_hours += get_shift_duration(shift[day_index]);
	return total_hours;
}

