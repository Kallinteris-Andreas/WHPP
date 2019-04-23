#include "schedule.hpp"

#define CUR_WORKER workers[worker_index]

//Note max Total Score is 165180
int schedule::score(){
	int total_score = 0;
	
	for (int worker_index = 0; worker_index != NO_WORKERS; worker_index++){
		total_score += score_individual(worker_index);
	}

	return total_score;
}

//Note max Total Score is 5506
int schedule::score_individual(int worker_index){
		int total_score = 0;
		//Max 70 work Hours -- 1000 points
		{
			total_score += (CUR_WORKER.total_work_hours() <= 70)*1000;
		}
		//Max 7 consecutive work days -- 1000 points
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				for (int i = 0; i != 7; i++){
					if (!CUR_WORKER.works((day_index+i) % NO_DAYS))
						break;
					goto no_points2;
				}
			}
			total_score += 1000;
			no_points2:;
		}
		//Max 4 consecutive work night shifts -- 1000 points
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				for (int i = 0; i != 4; i++){
					if (CUR_WORKER.get_work_shift((day_index+i)%NO_DAYS) != 
							work_shift::night)
						break;
					goto no_points3;
				}
			}
			total_score += 1000;
			no_points3:;
		}
		//Do not work morning shift after night shift -- 1000 points
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				if (CUR_WORKER.get_work_shift(day_index) == work_shift::night && 
					CUR_WORKER.get_work_shift((day_index+1)%NO_DAYS)==work_shift::morning)
					goto no_points4;
			}
			total_score += 1000;
			no_points4:;
		}
		//Do not work morning shift after afternoon shift -- 800 points
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				if (CUR_WORKER.get_work_shift(day_index) == work_shift::afternoon && 
					CUR_WORKER.get_work_shift((day_index+1)%NO_DAYS)==work_shift::morning)
					goto no_points5;
			}
			total_score += 800;
			no_points5:;
		}
		//Do not work afternoon shift after night shift -- 600 points
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				if (CUR_WORKER.get_work_shift(day_index) == work_shift::night && 
					CUR_WORKER.get_work_shift((day_index+1)%NO_DAYS) == work_shift::afternoon)
					goto no_points6;
			}
			total_score += 600;
			no_points6:;
		}
		//At least 2 free days after 4 consecutive night shifts -- 100 points
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				for (int i = 0; i != 4; i++){
					if (CUR_WORKER.get_work_shift((day_index+i)%NO_DAYS) != work_shift::night)
						goto next7;
				}
				for (int i = 4; i != 6; i++)
					if (CUR_WORKER.get_work_shift((day_index+i)%NO_DAYS) != work_shift::nop)
						goto next7;
				total_score += 100;
				goto done7;
				next7:;
			}
			done7:;
		}
		//At least 2 free days after 7 consecutive shifts -- 1 point
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				for (int i = 0; i != 7; i++){
					if (!CUR_WORKER.works((day_index+i)%NO_DAYS))
						goto next8;
				}
				for (int i = 7; i != 9; i++)
					if (CUR_WORKER.works((day_index+i)%NO_DAYS))
						goto next8;
				total_score += 1;
				goto done8;
				next8:;
			}
			done8:;
		}
		//Avoid {Work, No Work, Work} Pattern -- 1 point
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				if (CUR_WORKER.works(day_index) && !CUR_WORKER.works((day_index+1)%NO_DAYS)
						&& CUR_WORKER.works((day_index+2)%NO_DAYS))
					goto done9;
			}
			total_score++;
			done9:;
		}
		//Avoid {No Work, Work, No Work} Pattern -- 1 point
		{
			for (int day_index = 0; day_index != NO_DAYS; day_index++){
				if (!CUR_WORKER.works(day_index) && CUR_WORKER.works((day_index+1)%NO_DAYS)
						&& !CUR_WORKER.works((day_index+2)%NO_DAYS))
					goto done10;
			}
			total_score++;
			done10:;
		}
		//Work both days of a weekend -- 2 points
		{
			if((CUR_WORKER.works(5) && CUR_WORKER.works(6)) || 
					(CUR_WORKER.works(12) && CUR_WORKER.works(13)))
				total_score+=2;
		}
		//Work Max at 1 weekend -- 1 point 
		{
			if(!((CUR_WORKER.works(5) || CUR_WORKER.works(6)) &&
					(CUR_WORKER.works(12)||CUR_WORKER.works(13))))
				total_score++;
		}
		return total_score;
}
