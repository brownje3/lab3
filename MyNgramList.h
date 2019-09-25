
class MyNgramList 
{
   struct Ngram
   {
      std::string ngram;
      int count;
      struct Ngram * next;
   };

   typedef struct Ngram Ngram_t;

   private:
      Ngram_t * first;
      Ngram_t * newNode;
      int ngramSz;
      void insertNgram(std::string s);
      void starter(Ngram_t** reference);
      void split(Ngram_t* source, Ngram_t** front, Ngram_t** end);
      Ngram_t* merge(Ngram_t* initial, Ngram_t* second);
      std::string getNextNgram(WordList::const_iterator start, 
                               WordList::const_iterator end);
       
   public:
      MyNgramList(int ngramSz, const WordList & wl);
      ~MyNgramList();
      void sortByCount();
      friend std::ostream& operator<<(std::ostream& os, const MyNgramList & nl);
};

