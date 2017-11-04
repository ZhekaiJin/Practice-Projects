#include<stdio.h>
#include<stdlib.h>

int main(){
	double num1;
	double num2;
	char operation;
    int i;

	while(1){
		printf("Please Enter an operation you'd like to perform\n");
        i=scanf("%lf%c%lf\n",&num1,&operation,&num2);//bad code here
		if(i!=3){
            printf("i=%d",i);
            if (i==EOF){
                puts("Bye");
                return(0);
            }else{
                puts("Wrong format");
                fflush(stdin);// very wrong here undefined behavior
                exit(-1);
            }
		}

		switch(operation){
			case '+':
				printf("=%lf\n",num1+num2);
				break;
			case '-':
				printf("=%lf\n",num1-num2);
				break;
			case '*':
				printf("=%lf\n",num1*num2);
				break;
			case '%':
				if(!(long)num2){
					fprintf(stderr,"Division by zero\n");
				}else{
                    printf("=%li\n",(long)num1%(long)num2);
				}
				break;
			case '/':
				if(num2==0)
					fprintf(stderr,"Division by zero\n");
				else
					printf("=%1f\n",num1/num2);
				break;
			default:
				printf("\n\n %cOperation not supported.\n",operation);
				break;
		}
	}
	return 0;
}
