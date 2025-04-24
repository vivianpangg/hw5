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
void findWords(string& in, string floating, const set<string>& dict, 
  int pos, set<string>& resultWords);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    // set<string> filteredDict; //for words with correct length
    // for(set<string>::iterator it = dict.begin();it!= dict.end();++it){
    //   bool matchesLength = true;
    //   for(int i =0;i<in.length();i++){
    //     if(in[i] != '-' && in[i] !=((*it)[i])){
    //       matchesLength = false;
    //       break;

    //     }

    //     if(matchesLength){
    //       filteredDict.insert(*it);

    //     }

    //   }

    // }

    
    set<string> resultWords;
    string currBuiltWord = in;
    int dashes =0;
    for(char i:currBuiltWord){
      if(i =='-'){
        dashes++;

      }

    }

    if(dashes<floating.size()){
      return resultWords;

    }

    findWords(currBuiltWord, floating,dict,0,resultWords);

    return resultWords;

}

// Define any helper functions here

//use std::set<std<<string> dict for all possible true english language words
// function does not play the game, just gives all possible words that can fit
//floating is yellow letters
// fixed is green letters
// -i-: 3 letter word with i in the middle (stirng& in)
void findWords(
  string& in, string floating, const set<string>& dict, 
  int pos, set<string>& resultWords){

  set<char> usedLetters;


  if(pos == in.size()){
    if(dict.find(in) != dict.end() && floating.empty()){
      resultWords.insert(in);
    }
    return;
  }


  if(in[pos]!= '-'){ //on a green letter
    findWords(in, floating, dict, pos+1, resultWords);
    return;
  }

  int remainingSlots = 0;
  for(size_t i = pos; i <in.size();i++){
    if(in[i]=='-'){
      remainingSlots++;
    }

  }

  for(size_t i=0;i<floating.size();i++){
    if(usedLetters.find(floating[i]) != usedLetters.end()){
      continue;

    }

    in[pos] = floating[i];
    usedLetters.insert(floating[i]);

    
    string newFloating = floating;
    newFloating.erase(i,1);

    findWords(in, newFloating, dict, pos+1, resultWords);

    in[pos] = '-';

  }

  if(!(remainingSlots<=floating.size())){
    for(char c = 'a';c<='z';c++){
      if(usedLetters.find(floating[c]) != usedLetters.end()){
        continue;
      }
      in[pos]=c;
      findWords(in, floating, dict, pos+1, resultWords);
      in[pos]='-';

    }

  }

  // //try yellow letters at the pos
  // for(int i =0; i<floating.length();i++){
  //   currBuiltWord[pos] = floating[i];
  //   string newFloating=floating.substr(0,i)+floating.substr(i+1); //removes the letter at this pos in floating string

  //   bool valid = false;
  //   for(set<string>::iterator it = dict.begin(); it!= dict.end();++it){
  //     if(it->substr(0,pos+1)==currBuiltWord.substr(0,pos+1)){
  //       valid = true;
  //       break;

  //     }

  //   }

  //   if(valid){
  //     findWords(in, newFloating, dict, currBuiltWord, pos+1, resultWords);
  //   }
  // }

  // int remainingSlots = 0;
  // for(int i = 0;i <in.length();i++){
  //   if(in[i]=='-'){
  //     remainingSlots++;

  //   }

  // }

  // if(remainingSlots>(int)floating.length()){


  //   // for(int i =0; i<floating.length();i++){
  //   //   currBuiltWord[pos] = floating[i];
  //   //   string newFloating=floating;
  //   //   newFloating.erase(i,1);//removes the letter at this pos in floating string

  //   //   findWords(in, newFloating, dict, currBuiltWord, pos+1, resultWords);
  //   // }



  //     for(char i = 'a';i<='z';i++){
  //       bool inYellow = false;
  //       for(int j = 0; j<floating.length();j++){
  //         if(floating[j]==i){
  //           inYellow=true;
  //           break;

  //         }

  //       }
  //       if(inYellow==false){
  //         currBuiltWord[pos] = i;

  //         bool valid = false;
  //         for(set<string>::iterator it = dict.begin(); it!= dict.end();++it){
  //           if(it->substr(0,pos+1)==currBuiltWord.substr(0,pos+1)){
  //             valid = true;
  //             break;

  //           }

  //         }

  //         if(valid){
  //           findWords(in, newFloating, dict, currBuiltWord, pos+1, resultWords);
  //         }
  //         // findWords(in, floating, dict, currBuiltWord, pos+1, resultWords);
  //       }
  //     }
  //     return;

  // }

}
