#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  












int main(){
	char *question;
	question=(char*)malloc( 1000 * sizeof(char) );
	char *answer;
	answer=(char*)malloc(1000 * sizeof(char) );
	
	int i=0,k=0,l=0;
	
	FILE *fp2=fopen("test.txt","r");
	while(!feof(fp2)){
		fscanf(fp2,"%s",answer);
	}
	printf("%s\n",answer);

	fclose(fp2);
	
	FILE *fp=fopen("test.txt","a");
	
	
	printf("要問什麼問題:");
	fprintf(fp,"要問的問題:");
	for(i=0;;i++){
		scanf("%c",&question[i]);
		fprintf(fp,"%c",question[i]);
		if(question[i]=='\n'){
			printf("提問成功\");
			break;	
		} 
		else if(i>1000){
			question = (char*)realloc(question, i * sizeof(char));
		}
	}
	fclose(fp); 
}
	
