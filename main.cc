#include "main.h"
//using namespace std;
int main(){
	int pop = 100;
	genetic_algorithm g(pop);
	schedule s = g.whpp();
	s.print();
	cout<<s.score()<<endl;

	return 0;
}
