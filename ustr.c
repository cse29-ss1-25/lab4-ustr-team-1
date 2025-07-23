#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
	//case: all ascii
	if(s.is_ascii == 1)
	{
		s.contents[end] = '\0';
		s = s.contents + start;
		return s;
	}
	//case: invalid range
	if(start < 0 || end > s.codepoints)
	{
		free(s.contents);
		s.contents = malloc(1);
		s.contents[0] = '\0';
		return s;
	}
	int start_byte = 0;
	for(int i = 0; i < s.codepoints; i++)
	{
		//single byte
		if(s.contents[i] > 0 && s.contents[i] < 127)
		{
			start_byte++;
			continue;
		}
		if((s.contents[i] & 0xE0) == 0xC0)
		{
			start_byte +=2;
			continue;
		}
		if((s.contents[i] & 0xF0) == 0xE0)
		{
			start_byte += 3;
			continue;
		}
		if((s.contents[i] & 0xF8) == 0xF0)
		{
			start_byte +=4;
			continue;
		}
	}
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this

}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

