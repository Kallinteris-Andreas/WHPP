#include "main.h"
//using namespace std;
int main(){
	genetic_algorithm g(POP_COUNT);
	//schedule s = g.whpp();
	//s.print();
	//cout<<s.score()<<endl;
	schedule s = g.whpp();

	return 0;
}
