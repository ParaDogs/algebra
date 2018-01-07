#ifndef COMBINATIONS_UTILS_H_INCLUDED
#define COMBINATIONS_UTILS_H_INCLUDED

/* usage guide
 *
 * use constructor to create structure:
 *   it will create an std::vector with N numbers from 0 to N-1 and you can
 *   traverse over the R repetitions of that numbers
 *
 * use "completed" variable to find out is there any combinations left, e. g.:
 * while (!c.completed) c.next(); where c is CombinationsWithRepetitions structure
 *
 */

#include <vector>

struct CombinationsWithRepetitions {

    typedef std::vector<int> COMBINATION_T;

    // initialize status
    CombinationsWithRepetitions(int N, int R);

   // true while there are more solutions
   bool completed;

   // count how many generated
   int generated;

   // get current and compute next combination
   COMBINATION_T next();

private:
   int N, R;
   COMBINATION_T curr;
};

#endif // COMBINATIONS_UTILS_H_INCLUDED
