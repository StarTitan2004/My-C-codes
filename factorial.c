//factorial of a number
#include<stdio.h>
int main(){
	int n,i;
	printf("Enter Number");
	scanf("%d",&n);
	int fact=1;
	for(i=1;i<n+1;i++){
			fact=fact*i;
	}
	printf("%d",fact);
}
