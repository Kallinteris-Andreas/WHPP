#include "main.h"
//using namespace std;
int main(){
	int pop = 100;
	
	genetic_algorithm g(pop);
	cout<<g.selection()<<endl;
	
	return 0;
}
