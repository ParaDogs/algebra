#include "combinations_utils.h"

CombinationsWithRepetitions::CombinationsWithRepetitions(int N, int R) {

   completed = N < 1 || R > N;
   generated = 0;
   this->N = N;
   this->R = R;

   for (int c = 0; c < R; ++c)
       curr.push_back(c);
}


CombinationsWithRepetitions::COMBINATION_T CombinationsWithRepetitions::next() {

   COMBINATION_T ret = curr;

   // find what to increment
   completed = true;
   for (int i = R - 1; i >= 0; --i) {

       if (curr[i] < N - R + i + 1) {

           int j = curr[i] + 1;

           while (i <= R-1)
               curr[i++] = j++;

           completed = false;
           ++generated;
           break;
       }
   }

   return ret;
}
