
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <set>
#include <algorithm>
#include "WordList.h"
#include "NgramList.h"

using namespace std;

/*
 * NgramList
 *
 * takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a map of 
 * ngrams.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
NgramList::NgramList(int ngramSz, const WordList & wl)
{
   this->ngramSz = ngramSz;
   WordList::const_iterator p;
   p = wl.begin();
   while (p != wl.end())
   {
      std::string ngram = getNextNgram(p, wl.end());
      p++;
      if (!ngram.empty()) insertNgram(ngram);
   }
}

/*
 * NgramList destructor
 *
 * automatically called when NgramList object goes out of scope
 * deletes the linked list
 **/
NgramList::~NgramList()
{
  /**Ngram_t * nextNgram;
   while (first != NULL)
   {
      nextNgram = first->next;
      //delete first changed from free(first):: Mismatched free, delete, delete[]
      delete first;
      first = nextNgram;
   }**/
}

/*
 * getNextNgram
 *
 * takes as input an iterator that points to the word to start the
 * ngram and an iterator that points to the end of the word list
 * and builds and returns the ngram. returns empty string if no
 * ngram can be built, for example, if there are insufficient words
 * to build one.
 *
 * param: WordList::const_iterator start - points to first word in ngram
 * param: WordList::const_iterator end - points to end of word list
 * return: std::string - returns ngram or empty string
 */
std::string NgramList::getNextNgram(WordList::const_iterator start, 
                                    WordList::const_iterator end)
{
   int i, len;
   string ngram = "";
   for (i = 0; i < ngramSz && start != end; i++)
   {
      std::string word = (*start);
      //see if the string ends with punctuation
      //don't create ngrams that continue after punctuation
      if (!isalpha(word[word.length()-1]) && i < ngramSz - 1) return "";

      //take off all ending punctuation
      len = word.length() - 1;
      while (len >= 0 && !isalpha(word[len])) 
      {
         //remove last character
         word = word.substr(0, word.length() - 1);
         len--;
      }
      if (len < 0) return "";  //give up

      //is the first word in the ngram?
      if (ngram == "") ngram = word;
      else ngram = ngram + " " + word;

      start++;
   }

   //could we build a long enough ngram?
   if (i < ngramSz) return "";

   //take off beginning punctuation
   while (ngram.length() > 0 && !isalpha(ngram[0])) 
      ngram = ngram.substr(1, ngram.length());
   return ngram;
}

/*
 * insertNgram
 *
 * Looks for the ngram to be inserted. If it is already in
 * the map then the count is incremented
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void NgramList::insertNgram(std::string s)
{
   /**Ngram_t * ptr = first; 

   while (ptr != NULL)
   {
      //s already in list
      if (ptr->ngram == s) 
      {
         ptr->count++;
         return;
      }
      ptr = ptr->next;
   }
   //moved this code chunk under the while loop.
   //It doesnt need to be created if the return will be taken
   Ngram_t * newNode = new Ngram_t();
   newNode->ngram = s;
   newNode->count = 1;
   //insert in front of list
   newNode->next = first;
   first = newNode;*/

   if (ngramMap.find(s) != ngramMap.end())
   {
        ngramMap.at(s)++;
   }
   else
   {
        ngramMap[s] = 1;
   }

}

/*
 * operator<<
 *
 * sorts then prints the list of ngrams
 * after loading the map into a multiset
 *
 * param: std::ostream & os - output stream to direct the output to
 * param: const NgramList & nglst - ngram list object
 * return: std::ostream & - output stream
 */  
std::ostream& operator<<(std::ostream& os, const NgramList & nglst)
{
   cout << "List of " << nglst.ngramSz << " word ngrams and counts\n";
   cout << "--------------------------------\n";
   

   typedef std::function<bool(std::pair<std::string, int>,
        std::pair<std::string, int>)> Comparator;

   Comparator cmp = 
   [](std::pair<std::string, int> e1, std::pair<std::string, int> e2)
   {
        return e1.second > e2.second;
   };

   std::multiset<std::pair<std::string, int>, Comparator> ngramSet(nglst.ngramMap.begin(),
        nglst.ngramMap.end(), cmp);

   for (std::pair<std::string, int> num : ngramSet)
   {
        cout << num.first << ", " << num.second << endl;
   }
    
   return os;
}
