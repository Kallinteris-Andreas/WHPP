#include "genetic_algorithm.hpp"

#define rounds_without_improvement 50
#define pass_present 5

schedule genetic_algorithm::whpp(){
	int iter_max = 20;
	float mutation_prob = 1.5;
	int counter = 0;
	int impr_counter = rounds_without_improvement;
	

	schedule best_schedule;
	int best_weight = MAX_INT;
	int a,b;
	for(int i =0;i<pop;i++){
		if(best_weight>population[i].score()){
			best_weight = population[i].score();
			best_schedule = population[i];
		}
	}
	while(counter<=iter_max){
		cout<<"======================="<<endl;
		for(int i =0;i<pop/2;i++){
			a = selection();
			b = selection();

			crossbreed_vertical(a,b,i*2);

			mutation_reversal(mutation_prob,i*2);
			mutation_reversal(mutation_prob,i*2+1);

			//mutation_random_column_random_reverse(mutation_prob,i*2);
			//mutation_random_column_random_reverse(mutation_prob,i*2+1);
			cout<<new_population[i*2].score()<<endl;
			cout<<new_population[i*2+1].score()<<endl;
			if(new_population[i*2].score()<=best_weight){
				best_weight = new_population[i].score();
				best_schedule = new_population[i];
				impr_counter = rounds_without_improvement;
			}
			if(new_population[i*2+1].score()<=best_weight){
				best_weight = new_population[i*2+1].score();
				best_schedule = new_population[i*2+1];
				impr_counter = rounds_without_improvement;
			}

		}
		impr_counter --;
		if(impr_counter == 0){
			cout<<"Exited, beacause of stagnation"<<endl;
			return best_schedule;
		}
		natural_selection();
		memcpy(population,new_population,sizeof(population));
		counter++;
	}


	return best_schedule;
}

genetic_algorithm::genetic_algorithm(int popp){
	pop = popp;
	population = (schedule*)calloc(pop,sizeof(schedule));
	new_population = (schedule*)calloc(pop,sizeof(schedule));

	for(int i=0;i<pop;i++){
		population[i] = schedule();
		new_population[i] = schedule();
		population[i].init();
		//cout<<population[i].score()<<endl;
		assert(population[i].satisfy_constraint());
	}
	
};
default_random_engine dr (chrono::steady_clock::now().time_since_epoch().count());
int rand(int lim){
	uniform_int_distribution<int> uid {0,lim};
	return uid(dr);
}

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

int genetic_algorithm::selection(){
	int sum = 0;
	float weights[pop];

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

void genetic_algorithm::crossbreed_vertical(int a ,int b,int index){
	schedule parentA = population[a];
	schedule parentB = population[b];

	schedule kid1 = schedule();
	schedule kid2 = schedule();

	int r = rand(MAX_INT)%(NO_WEEKS*7);
	
	for(int i=0; i<NO_WEEKS*7;i++){
		if(r>i){
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
	
	assert(kid1.satisfy_constraint());
	assert(kid2.satisfy_constraint());

	new_population[index] = kid1;
	new_population[index+1] = kid2;
}

void genetic_algorithm::mutation_reversal(int possibility,int index){
	schedule parent = new_population[index];
	schedule kid = new_population[index];

	float r = rand(1);

	if(r <= possibility){
		for(int i =0;i<NO_WORKERS;i++){
			kid.set_worker(NO_WORKERS-i-1,*(parent.get_worker(i)));
		}
	}
	assert(kid.satisfy_constraint());
	new_population[index] = kid;
}

void genetic_algorithm::mutation_random_column_random_reverse(int possibility,int index){
	schedule parent = new_population[index];
	schedule kid = new_population[index];
	float r = rand(1);

	if(r <= possibility){

		int rr = rand(MAX_INT)%(NO_WEEKS*7);
		int r2 = rand(MAX_INT)%(NO_WEEKS*7);
		int r3 = rand(MAX_INT)%(NO_WEEKS*7);

		(kid.get_worker(r2))->set_work_shift(rr,(parent.get_worker(r3))->get_work_shift(rr));
		(kid.get_worker(r3))->set_work_shift(rr,(parent.get_worker(r2))->get_work_shift(rr));


	}
	assert(kid.satisfy_constraint());
	new_population[index] = kid;

}