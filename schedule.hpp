#ifndef SCHEDULE_DEF
#define SCHEDULE_DEF
#include <iostream>
#include <cstdint>
#include <cstdio>
#include "employee.hpp"
#include "rules.h"

class schedule {
	private:
		employee workers[NO_WORKERS];
		//morning_assignments
	public:
		schedule();
		void print();
		void init();
		bool satisfy_constraint();
		int score();
};
#endif
