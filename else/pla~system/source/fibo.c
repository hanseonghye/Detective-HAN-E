#include <stdio.h>

int fibo(int num){
	if(num==0) return 0;
	else if (num==1) return 1;
	else return fibo(num-1) + fibo(num-2);
}

int main(void){
	int num;
	int i;
	printf("ddd");
	scanf("%d", &num);

	printf("\n %d",fibo(num));
	return 0;
}
