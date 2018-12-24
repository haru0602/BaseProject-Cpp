#include<stdio.h>
#include<string.h>
#include<stdlib.h>



void teacherAnswer();







/*int main(){
	teacherAnswer();
}*/

void teacherAnswer(){
char *question;
	question=(char*)malloc( 1000 * sizeof(char) );
	char *answer;
	answer=(char*)malloc(1000 * sizeof(char) );
	int i=0,j=0,k=0,l=0;

	FILE *fp=fopen("test.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%s",question);

	}
	printf("%s\n",question);
	fclose(fp);


	FILE *fp2=fopen("test.txt","a");



	printf("Enter Answer:");

	fprintf(fp2,"Answer:");
	for(i=0;;i++){
		scanf("%c",&answer[i]);

		fprintf(fp2,"%c",answer[i]);
		if(answer[i]=='\n'){
			printf("Answer Complete\n");
			break;
		}
		else if(i>50){
			answer = (char*)realloc(answer, i * sizeof(char));
		}
	}
	fclose(fp2);
	}
