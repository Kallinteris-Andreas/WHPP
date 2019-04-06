#include "schedule.hpp"

int schedule::score(){
	int total_score = 0;
	
	for (int worker_index = 0; worker_index != NO_WORKERS; worker_index){
		//Max 70 work Hours -- 1000 points
		{
		}
		//Max 7 consecutive work days -- 1000 points
		{
		}
		//Max 4 consecutive work night shifts -- 1000 points
		{
		}
		//Do not work morning shift after night shift -- 1000 points
		{
		}
		//Do not work morning shift after afternoon shift -- 800 points
		{
		}
		//Do not work afternoon shift after night shift -- 600 points
		{
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

