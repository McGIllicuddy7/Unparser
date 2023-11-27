# Unparser
this is an attempt at a universal parser(hence the name unparser), it is a header only library so all you have to do is include
 unparser.h in whatever files you plan to use it in. in one(AND ONLY ONE) of those files put "#define UNPARSER_IMPLEMENTATION" above the include of unparser.h and that will put the actual implementation of the code into your program. unparser.c is there too in case you want to link with it for whatever reason. 
# General Information/Instructions for Use
    1: include "unparser.h" in whatever files you want to use unparser in
    2: #define UNPARSER_IMPLEMENTATION above one of the includes of unparser.h in a .c file you plan 
    to compile. DO THIS EXACTLY ONCE
    3: use split_string to get an array of strings where each of the strings was seperated by a space with no spaces
    4: use parse_string to get an array of strings where the seperators between 
    the strings are space seperated tokens passed as the second argument to the function 
    5: all of the string arrays are stack allocated so you should
     not have to worry about allocating or freeing the memory
    6: you can define NUM_SPLIT_STRINGS and/or SPLIT_STR_LEN before
     you include unparser.h to change the length of the strings or how many of them there are in an array