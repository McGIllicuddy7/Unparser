#pragma once
#include <stdbool.h>
//define UNPARSER_IMPLEMENTATION to get the thing to work, you don't need to link with anything just make sure you define it once
#ifndef NUM_SPLIT_STRINGS
#define NUM_SPLIT_STRINGS 4096
#endif
#ifndef SPLIT_STR_LEN
#define SPLIT_STR_LEN 128
#endif

typedef struct{
	char strs[NUM_SPLIT_STRINGS][SPLIT_STR_LEN];
	int num_strs;
}split_str_t;
split_str_t split_string(char * string);
split_str_t parse_string(char * string, char * tokens);
long get_time();
#ifdef UNPARSER_IMPLEMENTATION
#include "unparser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


static long get_time(){
	struct timespec res;
    long nano1;
    clock_gettime(CLOCK_REALTIME,&res);
    nano1 = res.tv_nsec;
	return nano1;
}
#define DEBUG_PRNT(sr) \
_t = get_time()-_t;\
printf(" %s took %ld microseconds\n",sr,_t/1000);\
_t = get_time();

split_str_t split_string(char * string){
	split_str_t out;
	out.num_strs = 0;
	char * old = string;
	while(*string){
		if(*string == ' '){
			memcpy(out.strs[out.num_strs], old, string-old);
			out.strs[out.num_strs][string-old+1] = '\0';
			old = string+1;
			out.num_strs++;
		}
		string++;
	}
	memcpy(out.strs[out.num_strs], old, string-old);
	out.num_strs++;
	return out;
}
int matches_str(char * s, split_str_t tokens){
    int max = 0;
    long _t  = get_time();
    for(int i = 0; i<tokens.num_strs; i++){
        int l = 0;
        while ((s[l] == tokens.strs[i][l]) && tokens.strs[i][l]){
            l++;
        }
        if(l>max && l == strlen(tokens.strs[i])){
            max = l;
        }
    }    return max;
}
#define push_back(sz) \
    memcpy(out.strs[out.num_strs], old, string-old);\
    out.num_strs++;\
    if(sz){\
	    memcpy(out.strs[out.num_strs], string, sz);\
	    out.strs[out.num_strs][sz+1] = '\0';\
        out.num_strs++;\
    }\
    string+=sz;\
    old = string;

split_str_t parse_string(char * string, char * tokens){
    split_str_t out;
    out.num_strs = 0;
    long _t = get_time();
    split_str_t tks  = split_string(tokens);
    char * old = string;
    bool last_white_space = false;
    while(*string){
        if(*string != ' ' && *string != '\n'){
            last_white_space = true;
        }
        int m = matches_str(string, tks);
        if(m){
            push_back(m);
        }
        else if(*string == ' ' || *string == '\n'){
            if(!last_white_space){
                push_back(0);
                string++;
                old = string;
                last_white_space = true;
            }
        }
        string++;
    }
    memcpy(out.strs[out.num_strs], old, string-old);
    out.num_strs++;
    return out;
}
#endif