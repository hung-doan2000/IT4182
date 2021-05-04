#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Btree.c"
#define MAX 100000

int main() {
	FILE *fp1 ,*fp2;
	fp1 = fopen("alice30.txt", "r");
	fp2 = fopen("stopw.txt", "r");

	if (fp1 == NULL || fp2 == NULL) {
		printf("Khong the mo file.\n");
		return(0);
	}
	TreeType root = NULL;
	TreeType tmp;

	char stop[17][20];
	for (int i = 0; i < 17; i++) {
		fscanf(fp2,"%s\n", stop[i]);
	}
	int count;
	char a;
	char word[MAX][20];
	char cache[100];
	int n1 = 0, n2 = 0,dong = 1;
	int b = 0;
	do {
		a = fgetc(fp1);
		if (feof(fp1))
			break;
		if (a == '\n'){
			dong++;
		}
		if( (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a == '\0') ){
			cache[n1] = a;
			n1++;
		}
		else {
			cache[n1] = '\0';
			for(int i = 0; i < n1; i++) {
				cache[i] = tolower(cache[i]);
			}
			if(cache[0] != '\0'){
				strcpy(word[n2],cache);
				for(int i =0;i<17;i++){
				    if(strcmp(word[n2],stop[i]) == 0) b = 1;
				    }
				if(b != 1){
				            if (Search(word[n2], root) == NULL){
					            KeyType new;
					            new.count = 1;
					            strcpy(new.ma,word[n2]);
					            new.line = makenewNode(dong);
					            insertNode(new, &root);
					           }
				            else {  
					            tmp = Search(word[n2], root);
					            insertTail(dong,tmp->key.line);
					            tmp->key.count ++;
					            }
					  }
				b = 0;	  
				n2++;
				}
			strcpy(cache,"");
			n1 = 0;
			}
	}while(1);
	inorderprint(root);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
