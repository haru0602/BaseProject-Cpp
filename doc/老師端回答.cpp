#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  












int main(){
	char *question;
	question=(char*)malloc( 50 * sizeof(char) );
	int i=0,j=0,k=0,l=0;
	
	
	
	FILE *fp=fopen("test.txt","a");
	
	fprintf(fp,"¦^µª:");
	for(i=0;;i++){
		scanf("%c",&question[i]);
		
		fprintf(fp,"%c",question[i]);
		if(question[i]=='\n'){
			break;
		} 
		else if(i>50){
			question = (char*)realloc(question, i * sizeof(char));
		}
	}
}
