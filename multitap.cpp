#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cstdlib>

#include "multitap.h"

using namespace std;

int encode_character(char ch, char stri[]){

  stri[0] = '\0';
  ifstream in_stream;
  char character;
  int count = 0;

  if(isalpha(ch) || ch == '.' || ch == ',' || ch == '!' || ch == '?'){
    ch = tolower(ch);
    in_stream.open("lookup.txt"); 
    
    if(in_stream.fail()){
      cout << "Failed to open file";
      exit(1);
    }

    in_stream.get(character);    
    while(!in_stream.eof()){
      
      if(character == ch){
	in_stream.get(character);
	while(character != '\n'){
	  *stri = character;
	  stri++;
	  count++;
	  in_stream.get(character);
	 }
	*(stri++) = '\0';
	break;
      }
      in_stream.get(character);
    }
    in_stream.close();
    return count;
  }

  if(isdigit(ch)){
    stri[0] = '*';
    stri[1] = ch;
    stri[2] = '\0';
    return 2;
  }

  return 0;

}

void encode(const char plaintext[], char multitap[]){

  //char* multitap_org = multitap;
  char* current_char;
  char* previous_char;
  //*current_char = ' ';

  while(*plaintext != '\0'){
    if(isalpha(*plaintext) && !islower(*plaintext)){
      *multitap = '#';
      multitap++;
    }
    encode_character(*plaintext,current_char);
    if(current_char == previous_char){
      *multitap = '|';
      multitap++;
    }
    multitap = current_char;
    cout << multitap;
    plaintext++;
    *previous_char = *current_char;
  }
  //multitap = multitap_org;
}
