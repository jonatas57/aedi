#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
	int lcd[16][9]={{0,1,0,1,0,1,1,1,1},{0,0,0,0,0,1,0,0,1},{0,1,0,0,1,1,1,1,0},{0,1,0,0,1,1,0,1,1},{0,0,0,1,1,1,0,0,1},{0,1,0,1,1,0,0,1,1},{0,1,0,1,1,0,1,1,1},{0,1,0,0,0,1,0,0,1},{0,1,0,1,1,1,1,1,1},{0,1,0,1,1,1,0,1,1},{0,1,0,1,1,1,1,0,1},{0,0,0,1,1,0,1,1,1},{0,1,0,1,0,0,1,1,0},{0,0,0,0,1,1,1,1,1},{0,1,0,1,1,0,1,1,0},{0,1,0,1,1,0,1,0,0}};
	unsigned long long int n;
	char hex[17], lin[3][49];
	scanf("%llu", &n);
	sprintf(hex, "%llx", n);
	int i;
	for (i = 0;hex[i]!='\0'; i++) {
		if(isdigit(hex[i])){
			hex[i]-=48;
		}
		else{
			hex[i]-=87;
		}
		char std[10]={" _ |_||_|"};
		for(int j=0;j<9;j++){
			if(lcd[hex[i]][j]){
				lin[j/3][i*3+(j%3)]=std[j];
			}
			else{
				lin[j/3][i*3+(j%3)]=' ';
			}
		}
	}
	i*=3;
	for(int j=0;j<3;j++){
		for(int k=0;k<i;k++){
			printf("%c", lin[j][k]);
		}
		printf("\n");
	}
	return 0;
}
