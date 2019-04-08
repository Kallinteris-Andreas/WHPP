#include "genetic_algorithm.hpp"

genetic_algorithm::genetic_algorithm(int popp){
	pop = popp;
	population = (schedule*)calloc(pop,sizeof(schedule));

	for(int i=0;i<pop;i++){
		population[i] = schedule();
		population[i].init();
		//population[i].print();
		cout<<population[i].score()<<endl;
	}
	
};
default_random_engine dr (chrono::steady_clock::now().time_since_epoch().count());
int rand(int lim){
	uniform_int_distribution<int> uid {0,lim};
	return uid(dr);
}

int genetic_algorithm::selection(){
	int sum = 0;
	float weights[pop];

	for (int i = 0; i != pop; i++){
		weights[i] = population[i].score();
		sum += weights[i];
	}
	int r = rand(sum);
	cout<<r<<endl;
	int cur_sum = 0;
	for (int i = 0; i != pop; i++){
		if(r<cur_sum){
			return i;
		}else{
			cur_sum +=weights[i];
		}
	}
	return NO_WORKERS;

}