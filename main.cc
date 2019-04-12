#include "main.h"
//using namespace std;
int main(){
	int pop = 16;
	genetic_algorithm g(pop);
	//schedule s = g.whpp();
	//s.print();
	//cout<<s.score()<<endl;
	int max_score = 0;
	for (int i = 0; i != 4; i++){
		schedule s = g.whpp();
		if (max_score<s.score())
			max_score = s.score();
	}


	std::cout << max_score << std::endl;

	return 0;
}
