#include <map>

class NgramList 
{
   struct Ngram
   {
      std::string ngram;
      int count;
      struct Ngram * next;
   };

   typedef struct Ngram Ngram_t;
 

   private:
      std::map<std::string, int> ngramMap;
      int ngramSz;
      void insertNgram(std::string s);
      std::string getNextNgram(WordList::const_iterator start, 
                               WordList::const_iterator end);
       
   public:
      NgramList(int ngramSz, const WordList & wl);
      ~NgramList();
      friend std::ostream& operator<<(std::ostream& os, const NgramList & nl);
};

