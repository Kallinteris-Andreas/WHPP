#include "schedule.hpp"

using namespace std;

employee temp_workers[NO_WORKERS];
default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());
int random(int lim){
	uniform_int_distribution<int> uid {0,lim};
	return uid(dre);
}
void schedule::whpp_algorithm(){
	init();
	print();
	employee best_plan_workers[NO_WORKERS];
	int min_weight=MAX_INT;

	if (satisfy_constraint(workers)){
		std::cout << "The current schedule DOES satisfy the constraint" << std::endl;
		std::cout << "The current score is: " << score() << std::endl;
	}
	else
		std::cout << "The current schedule DOES NOT satisfy the constraint" << std::endl;
	min_weight = score();
	memcpy(best_plan_workers,workers,sizeof(workers));

	int iter_max = 2000;
	bool flag = true;
	int iterations =0;
	int* picks ;
	float mutation_prob = 0.2;

	while(flag){

		for(int i=0;i<NO_WORKERS/2;i++){
			memcpy(temp_workers,workers,sizeof(workers));
			picks = selection();
			crossbreed_vertical(picks[0],picks[1],i*2);
			//crossbreed_horizontal(picks[0],picks[1],i*2);
		}		
		//mutation_reversal(mutation_prob);
		//mutation_random_genes(mutation_prob);
		if (satisfy_constraint(temp_workers)){
			std::cout << "The current schedule DOES satisfy the constraint" << std::endl;
			memcpy(workers,temp_workers,sizeof(workers));
			//print();
			std::cout << "The current score is: " << score() << std::endl;

		}
		else
			//std::cout << "The current schedule DOES NOT satisfy the constraint" << std::endl;

		if(score()<min_weight){
			min_weight = score();
			memcpy(best_plan_workers,workers,sizeof(workers));

		}
		iterations ++;
		flag = iterations < iter_max && true;// to be improved

	}

	cout<<"Best Cost is: "<<min_weight<<endl;
}

int* schedule::selection(){
	int total_score = score();
	float sum = 0;float x = 0;
	//float* weights = (float*)malloc(sizeof(float)*NO_WORKERS);
	float weights[NO_WORKERS];
	int* parents = (int*)malloc(sizeof(int)*2);
	
	for (int worker_index = 0; worker_index != NO_WORKERS; worker_index++){
		weights[worker_index] = score_individual(worker_index)/(float)total_score;
		sum += weights[worker_index];
		//cout<<worker_index<<" . score : "<<weights[worker_index]<<endl;
		//cout<<worker_index<<" . score : "<<sum<<endl;
	}

	
	float r ;

	for(int y = 0;y<2;y++){
		srand(y+time(NULL));
		//r = (float)rand()/RAND_MAX ;
		r = (float)random(MAX_INT)/MAX_INT;
		sum = 0 ;

		for (int worker_index = 0; worker_index != NO_WORKERS; worker_index++){
			sum+=weights[worker_index];
			if(sum>r){
				parents[y] = worker_index;
				break;
			}			
		}
		//cout<<"random num is : "<<r<<" and index is: "<<parents[y]<<endl;
	}

	return parents;
}
void schedule::crossbreed_vertical(int a,int b,int position){
	employee workerA = workers[a];
	employee workerB = workers[b];

	employee wA = employee();
	employee wB = employee();
	srand(time(NULL));

	int r = random(MAX_INT)%(NO_WEEKS*7) + 1;

	for(int i=0; i<NO_WEEKS*7;i++){
		if(i<r){
			wA.set_work_shift(i,workerB.get_work_shift(i));
			wB.set_work_shift(i,workerA.get_work_shift(i));
		}else{
			wA.set_work_shift(i,workerA.get_work_shift(i));
			wB.set_work_shift(i,workerB.get_work_shift(i));
		}
	} 
	temp_workers[position] = wA;
	temp_workers[position+1] = wB;

}
void schedule::crossbreed_horizontal(int a,int b,int position){
//TO BE IMPLEMENTED
}

void schedule::mutation_reversal(int possibility){
	srand(time(NULL));
	float r = (float)rand()/RAND_MAX ;
	employee w;

	for (int worker_index = 0; worker_index != NO_WORKERS; worker_index++){
		r = (float)rand()/RAND_MAX ;

		if(r<possibility){
			w = employee();

			for(int i=0; i<NO_WEEKS*7;i++){
				w.set_work_shift(NO_WEEKS*7-i-1,temp_workers[worker_index].get_work_shift(i));
			}	
			temp_workers[worker_index] = w;
		}
	}

}
void schedule::mutation_random_genes(int possibility){
	srand(time(NULL));
	float r = (float)rand()/RAND_MAX ;
	int pr;
	employee w;
	int pick;

	for (int worker_index = 0; worker_index != NO_WORKERS; worker_index++){
		r = (float)rand()/RAND_MAX ;

		if(r<possibility){
			w = employee();
			pr = rand()%(NO_WEEKS*7) + 1;
			w = temp_workers[worker_index];
			pick = rand()%(4);

			switch(pick){
				case 0:
					w.set_work_shift(pr,work_shift::morning);
					break;
				case 1:
					w.set_work_shift(pr,work_shift::afternoon);
					break;
				case 2:
					w.set_work_shift(pr,work_shift::night);
					break;
				case 3:
					w.set_work_shift(pr,work_shift::nop);
					break;
				default:
					assert(0);
			}

			temp_workers[worker_index] = w;
		}
	}
}















