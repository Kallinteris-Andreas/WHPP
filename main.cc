#include "main.h"

#define GENETIC

int main(){
	srand(0);
#ifdef GENETIC
	genetic_algorithm g(POP_COUNT);
	schedule s = g.whpp();
	s.print();
	std::cout <<s.score() << std::endl;
#else
	int best_score = 0;
	schedule best_sched;
	for (int i = 0; i != 1000000; i++){
		schedule random;
		random.init();
		if (random.score() > best_score){
			best_score = random.score();
			best_sched = random;
		}
	}
	std::cout << "best_score: " << best_score << std::endl;
	best_sched.print();
#endif
}
