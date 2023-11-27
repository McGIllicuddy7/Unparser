#include <stdio.h>
#include <string.h>
//#define UNPARSER_IMPLEMENTATION
#include "unparser.h"
#include <unistd.h>
#include <time.h>
long test(int argc, const char ** argv){
	char buff[10000];
	if(argc>1){
		FILE * f = fopen(argv[1], "r");
		int counter = 0;
		while(true){
			char c = fgetc(f);
			buff[counter] = c;
			counter++;
			if(feof(f)){
			break;}
		}
	}
	else{
		printf("enter expression: ");
		fgets(buff, 10000, stdin);
		buff[strlen(buff)-1] = '\0';
	}
	long t = get_time();
	split_str_t f = parse_string(buff, "-> + - / * ( ) } , .");
	long dt = get_time()-t;
	return dt;
}
int main(int argc, const char ** argv){
	char buff[10000];
	if(argc>1){
		FILE * f = fopen(argv[1], "r");
		int counter = 0;
		while(true){
			if(feof(f)){
			break;}
			char c = fgetc(f);
			buff[counter] = c;
			counter++;
		}
	}
	else{
		printf("enter expression: ");
		fgets(buff, 10000, stdin);
		buff[strlen(buff)-1] = '\0';
	}
	long t = get_time();
	split_str_t f = parse_string(buff, "<secret>");
	long dt = get_time()-t;
	dt = dt/1000;
	for(int i = 0; i<f.num_strs; i++){
		printf("<%s>\n", f.strs[i]);
	}
	printf("took %ld microseconds\n", dt);
	return 0;
}
