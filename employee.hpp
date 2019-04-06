#ifndef EMPLOYEE_DEF
#define EMPLOYEE_DEF
#include <cstdint>
#include "rules.h"

class employee {
	private:
		uint8_t hours_worked = 0;
		work_shift shift[NO_WEEKS*7];
	public:
		employee();
		work_shift get_work_shift(int);
		void set_work_shift(int, work_shift);
};
#endif
