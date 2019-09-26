
#include <iostream>
#include <string>
#include <vector>
#include "WordList.h"
#include "MyNgramList.h"

using namespace std;

/*
 * NgramList
 *
 * takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a linked list of 
 * ngrams.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
MyNgramList::MyNgramList(int ngramSz, const WordList & wl)
{
   this->ngramSz = ngramSz;
   WordList::const_iterator p;
   first = NULL;
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
 */
MyNgramList::~MyNgramList()
{
   Ngram_t * nextNgram;
   while (first != NULL)
   {
      nextNgram = first->next;
      //delete first changed from free(first):: Mismatched free, delete, delete[]
      delete first;
      first = nextNgram;
   }
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
std::string MyNgramList::getNextNgram(WordList::const_iterator start, 
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
 * looks for the ngram to be inserted. If it is already in
 * the linked list,  it increments the count. If not, it 
 * inserts it into the linked list.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void MyNgramList::insertNgram(std::string s)
{
    //reference pointer to the first element in the linked list
   Ngram_t * ptr = first;
   //does not need to be created each time there's an insertion place this later in the method
   //Ngram_t * newNode = new Ngram_t();
   //newNode->ngram = s;
   //newNode->count = 1;
   
   //Will either create a new node or increment count if there's already an existing ngram
   if(ptr == NULL || ptr->ngram >= s)
   {
        if(ptr != NULL && ptr->ngram == s)//increments count
        {
            ptr->count++;
            return;
        }
          //creates newNode to add to the linked list
          newNode = new Ngram_t();
          newNode->ngram = s;
          newNode->count = 1;
          newNode->next = first;
          first = newNode;
          
   }
   else
   {
        while(ptr->next != NULL && ptr->next->ngram <= s)//moves the pointer to the next element if no match is found
        {
            ptr = ptr->next;
        }
        if(ptr->ngram == s)//increments count to existing node
        {
            ptr->count++;
            return;
        }
        //creates new node
        newNode = new Ngram_t();
        newNode->ngram = s;
        newNode->count = 1;
        newNode->next = ptr->next;
        ptr->next = newNode;
   }
}


/*
 * Merge
 *
 * Fixing sort by Count from using a bubble sort algorithm to a merge sort algorithm
 *
 * param: initial - the first linked list being merged
 * param: second - the second linked list being merged
 * return: second - last element(s) of the second array (base case)
 * return: initial - last element(s) of the first array (base case)
 * return: result - final result of the merged array
 */
MyNgramList::Ngram_t* MyNgramList::merge(Ngram_t* initial, Ngram_t* second)
{
    //stores end result of the linked list
   Ngram_t * result;
   //base case if the first parameter doesn't exist
   if(initial == NULL)
   {
        return second;
   }
   else if(second == NULL)//base case if the second parameter doesn't exist
   {
        return initial;
   }
   //compares counts of the two lists and sets the first parameter into result
   if(initial->count >= second->count)
   {
        result = initial;
        result->next = merge(initial->next, second);
   }
   else//sets the second parameter into result
   {
        result = second;
        result->next = merge(initial, second->next);
   }

   return result;
}

//takes in a Ngram_t reference to prepare the linked list for merge sort
void MyNgramList::sortByCount()
{
    //
    Ngram_t** ptr = &first;
    //testing loop to see into first
    //Ngram_t* checker = first;
    //while(checker != NULL)
    //{
    //    std::cout<< checker->ngram;
    //    checker = checker->next;
    //}

    //sets up the start of the merge sort
    starter(ptr);
}
/*
 *Starter is what puts the merge sort into motion
 *param: reference- a double pointer to the list that needs to be sorted 
 */
void MyNgramList::starter(Ngram_t** reference)
{
    //creates a pointer to the list
    Ngram_t* ptr = *reference;
    //will be 1/2 of the previous list
    Ngram_t* ptr1;
    //will be other half of the list
    Ngram_t* ptr2;
    
    //base case to method, stops when the list is either empty or will be empty
    if((ptr == NULL) || (ptr->next == NULL))
    {
        return;
    }
    //splits the list into smaller lists
    split(ptr, &ptr1, &ptr2);

    //checks first part of the list
    starter(&ptr1);
    //checks second part of the list
    starter(&ptr2);

    //end result of the lists combined
    *reference = merge(ptr1, ptr2);
}

/*splits the list into back half and front half for merge sort
 *
 *param - source: the original list
 *param front: what will be the front of the list
 *param end: what will be the back end of the list
 */
void MyNgramList::split(Ngram_t* source, Ngram_t** front, Ngram_t** end)
{
    //this pointer will act as the faster pointer
    Ngram_t* last;
    //this pointer will act as the slower pointer
    Ngram_t* first;
    first = source;
    last = source->next;
    
    while (last != NULL)//sets the last pointer ahead of the first pointer
    {
        last = last->next;
        if(last != NULL)//differentiates between the two pointers
        {
            first = first->next;
            last = last->next;
        }
    }

    *front = source;
    *end = first->next;
    first->next = NULL;
}
/*
 * operator<<
 *
 * prints the list of ngrams
 *
 * param: std::ostream & os - output stream to direct the output to
 * param: const NgramList & nglst - ngram list object
 * return: std::ostream & - output stream
 */  
std::ostream& operator<<(std::ostream& os, const MyNgramList & nglst)
{
   cout << "List of " << nglst.ngramSz << " word ngrams and counts\n";
   cout << "--------------------------------\n";
   MyNgramList::Ngram_t * ptr = nglst.first;
   while (ptr != NULL)
   {
      cout << ptr->ngram << ", " << ptr->count << endl;
      ptr = ptr->next;
   } 
   return os;
}
