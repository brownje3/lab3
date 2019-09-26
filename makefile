CC = g++ 
CFLAGS = -g -pg -c -std=c++0x
OBJS = NgramList.o WordList.o main.o
OBJ = MyNgramList.o WordList.o main.o
LFLAGS = -pg
MFLAGS = -g -pg -O3

.C.o:
	$(CC) $(CFLAGS) $< -o $@

ngram: NgramList.o WordList.o main.o
	$(CC) $(MFLAGS) $(OBJS) -o ngram

my-ngram: MyNgramList.o WordList.o main.o
	$(CC) $(MFLAGS) $(OBJS) -o my-ngram

main.o: WordList.h NgramList.h

WordList.o: WordList.h

NgramList.o: NgramList.h WordList.h

MyNgramList.o: MyNgramList.h WordList.h

clean:
	rm *.o *ngram gmon.out 

submit:
	submit efb 3482-lab3 NgramList.h MyNgramList.h MyNgramList.C NgramList.C WordList.h WordList.C main.C report.txt makefile
