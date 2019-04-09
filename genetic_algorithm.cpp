#include "genetic_algorithm.hpp"

schedule genetic_algorithm::whpp(){
	int iter_max = 200;
	float mutation_prob = 0.3;
	int counter = 0;
	int best_chromosomes_to_pass = 0.99; // x%

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
		for(int i =0;i<pop/2;i++){
			a = selection();
			b = selection();

			crossbreed_vertical(a,b,i*2);

			//mutation_reversal(mutation_prob,i*2);
			//mutation_reversal(mutation_prob,i*2+1);

			mutation_random_column_random_reverse(mutation_prob,i*2);
			mutation_random_column_random_reverse(mutation_prob,i*2+1);
			cout<<new_population[i*2].score()<<endl;
			cout<<new_population[i*2+1].score()<<endl;
			if(new_population[i*2].score()<=best_weight){
				best_weight = new_population[i].score();
				best_schedule = new_population[i];
			}
			if(new_population[i*2+1].score()<=best_weight){
				best_weight = new_population[i*2+1].score();
				best_schedule = new_population[i*2+1];
			}

		}
		//fitness_function(int pass_present);
		population = new_population;
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
		cout<<population[i].score()<<endl;
		assert(population[i].satisfy_constraint());
	}
	
};
default_random_engine dr (chrono::steady_clock::now().time_since_epoch().count());
int rand(int lim){
	uniform_int_distribution<int> uid {0,lim};
	return uid(dr);
}

void genetic_algorithm::fitness_function(int pass_present){
	schedule* temp_population = (schedule*)calloc(pop,sizeof(schedule));
	int min;
	schedule val;

	for(int i =0;i<pop;i++){
		min = MAX_INT;

		for(int j =0;j<2*pop;j++){
			if(min>population[i].score()){

			}
		}
	}

	free(temp_population);
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
	cout<<r<<endl;
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
	cout<<a<<" "<<b<<endl;
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