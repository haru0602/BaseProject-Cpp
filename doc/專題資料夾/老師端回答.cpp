#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  












int main(){
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
	
	
	
	printf("請輸入答案:");
	
	fprintf(fp2,"回答:");
	for(i=0;;i++){
		scanf("%c",&answer[i]);
		
		fprintf(fp2,"%c",answer[i]);
		if(answer[i]=='\n'){
			printf("回答成功\");
			break;
		} 
		else if(i>50){
			answer = (char*)realloc(answer, i * sizeof(char));
		}
	}
	fclose(fp2);
}
