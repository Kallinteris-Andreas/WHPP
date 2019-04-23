#include "genetic_algorithm.hpp"

#define ROUNDS_WITHOUT_IMPROVEMENT 256
#define MAX_NO_ITERATIONS 16384
#define ELITISM //IF new child is worse than parent kill it
#define PROB_MUTATION 128 // out of 128
#define PROB_CROSS 128 // out of 128
#define PROB_SELECT 128 // out of 128
//#define SELECT_BEST_ONLY

#define LOG
#define PRINT_TERM
//define one of the following
#define CROSSBREEDING_INTERLEVED
//#define CROSSBREEDING_RANDOM

schedule genetic_algorithm::whpp(){
#ifdef LOG
	std::ofstream log_file("log.bat", ios::trunc);
	log_file << "Best" << '\t' << "Average" << '\n';
#endif
	int impr_counter = ROUNDS_WITHOUT_IMPROVEMENT;

	schedule best_schedule = population[best_person()];
	int best_weight = best_schedule.score();

	for(int counter = 0; counter != MAX_NO_ITERATIONS; counter++){
		long sum_of_scores = 0;
		for(int i = 0; i != pop; i++)
			sum_of_scores += population[i].score();
	int average = sum_of_scores/pop;

#ifdef PRINT_TERM
		std::cout << counter << ".======================= best is: " << best_weight << std::endl
		<< "Average Of Scores: " << average << std::endl;
#endif
#ifdef LOG
		log_file << best_weight << '\t' << average << '\n';
#endif

		int a = rand() % (pop-1)+1;
		int b = rand() % (pop-1) + 1;
		for(int i = 0; i != pop/2; i++){
			//select 2 persons to crossbreed
			if (PROB_SELECT > rand()%128){
				#ifdef SELECT_BEST_ONLY
					a = best_person();
				#else
					a = rand() % (pop-1)+1;
				#endif
				b = rand() % (pop-1) + 1;
			}

			crossbreed_vertical(a,b,i*2);

			//mutation_reversal(i*2);
			//mutation_reversal(i*2+1);
			//mutation_daily(i*2);
			//mutation_daily(i*2+1);
			mutation_random_column_random_reverse(i*2);
			mutation_random_column_random_reverse(i*2+1);

			if(new_population[i*2].score()>best_weight){
				best_weight = new_population[i*2].score();
				best_schedule = new_population[i*2];
				impr_counter = ROUNDS_WITHOUT_IMPROVEMENT;
			}
			if(new_population[i*2+1].score()>best_weight){
				best_weight = new_population[i*2+1].score();
				best_schedule = new_population[i*2+1];
				impr_counter = ROUNDS_WITHOUT_IMPROVEMENT;
			}
		}

		if(--impr_counter == 0){
			std::cout << "Exited, beacause of stagnation" << std::endl;
			return best_schedule;
		}
		//natural_selection();
		memcpy(population,new_population,sizeof(population));
	}

	return best_schedule;
}

genetic_algorithm::genetic_algorithm(int popp){
	assert(popp%2 == 0 && "Population Count must be an even number");
	pop = popp;
	population = (schedule*)malloc(pop*sizeof(schedule));
	new_population = (schedule*)malloc(pop*sizeof(schedule));

	for(int i=0;i<pop;i++){
		population[i] = schedule();
		new_population[i] = schedule();
		population[i].init();
		assert(population[i].satisfy_constraint());
	}
}


void genetic_algorithm::crossbreed_vertical(int a ,int b,int index){
	if (rand()%128 >= PROB_CROSS){
		for (int i = 0; i != pop; i++)
			new_population[i] = population[i];
		return;
	}

	schedule parentA = population[a];
	schedule parentB = population[b];

	schedule kid1 = schedule();
	schedule kid2 = schedule();


#ifdef CROSSBREEDING_RANDOM
	for(int i=0; i<NO_WEEKS*7;i++){
		if(rand(MAX_INT)%(NO_WEEKS*7)>i){
			for(int j=0;j<NO_WORKERS;j++){
				(kid1.get_worker(j))->set_work_shift(i,(parentB.get_worker(j))->get_work_shift(i));
				(kid2.get_worker(j))->set_work_shift(i,(parentA.get_worker(j))->get_work_shift(i));
			}
		}else{
			for(int j=0;j<NO_WORKERS;j++){
				(kid1.get_worker(j))->set_work_shift(i,(parentA.get_worker(j))->get_work_shift(i));
				(kid2.get_worker(j))->set_work_shift(i,(parentB.get_worker(j))->get_work_shift(i));
			}
		}
	}
#elif defined CROSSBREEDING_INTERLEVED
	for(int i=0; i<NO_WEEKS*7;i++){
		if(i%2 == 0){
			for(int j=0;j<NO_WORKERS;j++){
				(kid1.get_worker(j))->set_work_shift(i,(parentB.get_worker(j))->get_work_shift(i));
				(kid2.get_worker(j))->set_work_shift(i,(parentA.get_worker(j))->get_work_shift(i));
			}
		}else{
			for(int j=0;j<NO_WORKERS;j++){
				(kid1.get_worker(j))->set_work_shift(i,(parentA.get_worker(j))->get_work_shift(i));
				(kid2.get_worker(j))->set_work_shift(i,(parentB.get_worker(j))->get_work_shift(i));
			}
		}
	}
#else
#error
#endif


#ifdef ELITISM
	if(kid1.score()>parentA.score())
		new_population[index] = kid1;
	else
		new_population[index] = parentA;
	if(kid2.score()>parentB.score())
		new_population[index+1] = kid2;
	else
		new_population[index+1] = parentB;
#else
		new_population[index] = kid1;
		new_population[index+1] = kid2;
#endif

}

void genetic_algorithm::mutation_reversal(int index){
	schedule parent = new_population[index];
	schedule kid = new_population[index];


	if(rand()%128 <= PROB_MUTATION)
		for(int i =0;i<NO_WORKERS;i++)
			kid.set_worker(NO_WORKERS-i-1,*(parent.get_worker(i)));

	assert(kid.satisfy_constraint());
	new_population[index] = kid;
}

//Randomly change the workers who works in a shift
void genetic_algorithm::mutation_daily(int index){
	if (rand()%128 >= PROB_MUTATION)
		return;
	int day = rand() % NO_DAYS;
	work_shift ws = random_shift();

	schedule old = new_population[index];
	
	//find a worker at that shift
	int w_id;
	for (w_id=rand()%NO_WORKERS; old.get_worker(w_id)->get_work_shift(day) != ws; w_id=rand()%NO_WORKERS);

	int random_w_id = rand() % NO_WORKERS;
	//swap with a random worker
	{
		work_shift temp_s = old.get_worker(random_w_id)->get_work_shift(day);
		old.get_worker(random_w_id)->set_work_shift(day,old.get_worker(w_id)->get_work_shift(day));
		old.get_worker(w_id)->set_work_shift(day, temp_s);
		assert(new_population[index].satisfy_constraint());
	}

	if (new_population[index].score() < old.score())
		new_population[index] = old;
}

void genetic_algorithm::mutation_random_column_random_reverse(int index){
	schedule parent = new_population[index];
	schedule kid = new_population[index];
	int r0, r1;
	for(int i= 0; i<NO_WEEKS*7; i++)
		if(rand()%128 < PROB_MUTATION){
			r0 = rand()%NO_WORKERS;
			r1 = rand()%NO_WORKERS;

			(kid.get_worker(r0))->set_work_shift(i,(parent.get_worker(r1))->get_work_shift(i));
			(kid.get_worker(r1))->set_work_shift(i,(parent.get_worker(r0))->get_work_shift(i));
		}

	//rarely happens
	if (!kid.satisfy_constraint()){
		new_population[index] = parent;
		return;
	}


#ifdef ELITISM
	if(kid.score()>parent.score())
		new_population[index] = kid;
	else
		new_population[index] = parent;
#else
		new_population[index] = parent;
#endif
}

int genetic_algorithm::best_person(){
	schedule* best_person = population;
	int best_score = population->score();
	for (int i = 0; i != pop; i++){
		int c_score = population[i].score();
		if (c_score > best_score){
			best_person = population+i;
			best_score = c_score;
		}
	}

	return best_person - population;
}


//everthing below here is deprecated
//everthing below here is deprecated
//everthing below here is deprecated
//everthing below here is deprecated
//everthing below here is deprecated
#ifdef LEGACY
int genetic_algorithm::selection(){
	int sum = 0;
	int weights[pop];

	for (int i = 0; i != pop; i++){
		weights[i] = population[i].score();
		sum += weights[i];
	}
	int r = rand(sum);
	int cur_sum = 0;
	for (int i = 0; i != pop; i++){
		if(r<cur_sum){
			return i;
		}else{
			cur_sum +=weights[i];
		}
	}
	return pop-1;
}
#define pass_present 10
void genetic_algorithm::natural_selection(){
	//schedule* temp_population = (schedule*)calloc(pop,sizeof(schedule));
	int old_min;int old_index;
	int new_max;int new_index;
	schedule old_val;
	schedule new_val;

	//for(int i =0;i<pop*(pass_present/100);i++){
	for(int i =0;i<pass_present;i++){
		cout<<i<<endl;
		old_min = MAX_INT;
		new_max = 0;
		for(int j =0;j<pop;j++){
			
			if(old_min>population[j].score()){
				old_min = population[j].score();
				old_val = population[j];
				old_index = j;
			}
			if(new_max<new_population[j].score()){
				new_max = new_population[j].score();
				new_val = new_population[j];
				new_index = j;
			}
		}
		cout<<old_min<<"  "<<new_max<<endl;
		new_population[new_index] = old_val;
		population[old_index] = new_val;
	}
}
#endif
