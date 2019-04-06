#include "schedule.hpp"

int schedule::score(){
	int total_score = 0;
	
	for (int worker_index = 0; worker_index != NO_WORKERS; worker_index){
		//Max 70 work Hours -- 1000 points
		{
			total_score += (workers[worker_index].get_total_work_hours() <= 70)*1000;
		}
		//Max 7 consecutive work days -- 1000 points
		{
			for (int day_index; day_index != NO_WEEKS*7; day_index++){
				for (int i = 0; i != 7; i++){
					if (!workers[(worker_index+i) % NO_DAYS].works(day_index))
						break;
					goto no_points2;
				}
			}
			total_score += 1000;
			no_points2:
		}
		//Max 4 consecutive work night shifts -- 1000 points
		{
			for (int day_index; day_index != NO_DAYS; day_index++){
				for (int i = 0; i != 4; i++){
					if (workers[(worker_index+i) % NO_DAYS].get_work_shift(day_index) 
						!= work_shift::night);
						break;
					goto no_points3;
				}
			}
			total_score += 1000;
			no_points3:
		}
		//Do not work morning shift after night shift -- 1000 points
		{
			for (int day_index; day_index != NO_DAYS; day_index++){
				if (workers[day_index] == work_shift::night && 
					workers[(day_index+1) % NO_DAYS] == work_shift::morning)
					goto no_points4;
			}
			total_score += 1000;
			no_points4:
		}
		//Do not work morning shift after afternoon shift -- 800 points
		{
			for (int day_index; day_index != NO_DAYS; day_index++){
				if (workers[day_index] == work_shift::afternoon && 
					workers[(day_index+1) % NO_DAYS] == work_shift::morning)
					goto no_points5;
			}
			total_score += 800;
			no_points5:
		}
		//Do not work afternoon shift after night shift -- 600 points
		{
			for (int day_index; day_index != NO_DAYS; day_index++){
				if (workers[day_index] == work_shift::night && 
					workers[(day_index+1) % NO_DAYS] == work_shift::afternoon)
					goto no_points5;
			}
			total_score += 600;
			no_points5:
		}
		//At least 2 free days after 4 consecutive night shifts -- 100 points
		{
		}
		//At least 2 free days after 7 consecutive shifts -- 1 point
		{
		}
		//Avoid {Work, No Work, Work} Pattern -- 1 point
		{
		}
		//Avoid {No Work, Work, No Work} Pattern -- 1 point
		{
		}
		//Work both days of a weekend -- 2 points
		{
		}
		//Work Max at 1 weekend -- 1 point 
		{
		}
	}

	return total_score;
}

