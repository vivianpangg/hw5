#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findWords();


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    findWords(string& in, string& floating, set<string>& dict,
     string& currBuiltWord, int pos, set<string>& resultWords);

}

// Define any helper functions here

//use std::set<std<<string> dict for all possible true english language words
// function does not play the game, just gives all possible words that can fit
//floating is yellow letters
// fixed is green letters
// -i-: 3 letter word with i in the middle (stirng& in)
void findWords(
  string& in, string& floating, set<string>& dict, 
  string& currBuiltWord, int pos, set<string>& resultWords){

  //base case
  if(pos == in.length()){
    if(dict.find(currBuiltWord) != dict.end()){
      resultWords.insert(currBuiltWord);
    }
    return;
  }

  if(pos[in]!='-'){ //on a green letter
    findWords(in, floating, dict, currBuiltWord, pos+1, resultWords);
    return;
  }

  //try yellow letters at the pos
  for(int i =0; i<floating.length();i++){
    currBuiltWord[pos] = floating[i];
    string newFloating=floating;
    newFloating.erase(i,1);//removes the letter at this pos in floating string

    findWords(in, newFloating, dict, currBuiltWord, pos+1, resultWords);
  }

  for(char i = 'a';i<='z';i++){
    if(floating.find(i)==string::npos){
      currBuiltWord[pos] = i;
      return findWords(in, floating, dict, currBuiltWord, pos+1, resultWords);
    }
  }

}
