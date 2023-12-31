#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1048576
#define NAME_SIZE 1024
const char typeName[]=".uc!";
char buffer[BUFFER_SIZE];
char name[NAME_SIZE];

int main(int argc,char **argv) {
	if(argc==1)
	{
		printf("Please drag in .uc! file\n");
		system("pause");
		return 0;
	}
	mkdir("out");
	int len,fileCount;
	size_t i,j;
	for(fileCount=1; fileCount<argc; fileCount++) {
		strcpy(name,argv[fileCount]);
		printf("%s --> ",name);
		FILE *in=fopen(name,"rb");
		if(!in) {
			printf("Error: failed to read %s\n",name);
			continue;
		}
		len=strlen(name);
		for(i=2; i<=4&&i<len&&name[len-i]==typeName[4-i]; i++);
		if(i!=5) {
			printf("Error: support .uc! file only\n");
			continue;
		}
		for(i=len-5; i>0&&name[i]!='\\'; i--);
		i+=(i!=0);
		for(j=0; j<len-4-i; j++)
			name[j]=name[j+i];
		name[len-4-i]='\0';
		strcpy(buffer,"out\\");
		strcat(buffer,name);
		FILE *out=fopen(buffer,"wb");
		if(!out) {
			printf("Error: failed to write %s\n",buffer);
			continue;
		}
		while(i=fread(buffer,1,BUFFER_SIZE,in)) {
			for(j=0; j<i; j++)
				buffer[j]^=163;
			fwrite(buffer,i,1,out);
		}
		printf("Success\n");
		fclose(in);
		fclose(out);
	}
	return 0;
}
