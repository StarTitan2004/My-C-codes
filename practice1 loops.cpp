#include <stdio.h>
int main(){
	int i;
	for(i=5;i<51;i++){
	if(i%2!=0){
		if(i==3){
			continue;
		}	
		printf("%d\n",i);
	}}return 0;
}


