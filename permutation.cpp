//permutation.cpp

#include <string.h>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <forward_list>
#include <numeric>
#include "permutation.h"

using namespace std;

/**
 * Returns a vector of the elements in a cycle, in the same order.
 *
 * @param cycle string representation of a cycle, containing string
 *    representations of natural numbers seperated by any number
 *    of ' ' and ',' characters.
 */
static vector<uint> cycle_to_vector (std::string cycle)
{
  // initialize return array
  vector<uint> cyclevector;

  // initialize array to store strings representing uints
  vector<string> cyclevector_str;

  // split the cycle string by commas and spaces
  boost::split(cyclevector_str, cycle, boost::is_any_of(", "));

  // remove empty strings from cyclevector_str
  auto isEmpty = [](string x){return (x == "");};
  cyclevector_str.erase(remove_if(cyclevector_str.begin(),
                                  cyclevector_str.end(),
                                  isEmpty),
                    cyclevector_str.end());

  // map string representations of ints to ints
  auto typeconvert = [](string x) { return stoul (x); };
  transform(cyclevector_str.begin(), cyclevector_str.end(),
            back_inserter(cyclevector), typeconvert);

  return cyclevector;
}

/**
 * Assign the permutation represented by a cycle to a permutation array.
 *
 * @param perm an array representing a permutation of the natural
 *    numbers 1...n, for some n.
 *
 * @param cyclevector a vector of natural numbers where cyclevector[j-1]
 *    represents the element that j is permuted to.
 */
static void assign_cycle_perms (uint *perm, vector<uint> cyclevector)
{
  for (uint i = 0; i < cyclevector.size(); i++)
  {
      perm[cyclevector[i]-1] = cyclevector[(i+1)%(cyclevector.size())];
  }
}

/**
 * Returns a vector representation of a permutation's cycle decomposition.
 */
vector <vector <uint> > Permutation::decomp_list () const
{
  //initialize cycle decomposition vector
  vector <vector <uint> > res;

  uint a;
  uint b;

  // create a list elts containing ints 1...size
  forward_list<uint> elts;
  for (uint i = size; i > 0; i--)
  {
    elts.push_front(i);
  }

  while (!elts.empty())
  {
    // create new cycle
    vector <uint> cycle;

    // a is the first elt of the current cycle
    a = elts.front();
    cycle.push_back(a);

    // remove a from elts
    auto equals_a = [a] (uint x) { return (x == a); };
    elts.remove_if(equals_a);

    // b is the next elt to add to the cycle
    b = this->getval(a);

    while (!(b == a))
    {
      // add b to current cycle
      cycle.push_back(b);

      // remove b from elts
      auto equals_b = [b] (uint x) { return (x == b); };
      elts.remove_if(equals_b);

      // set b to next element in the cycle
      b = this->getval(b);
    }

    // add cycle to res
    res.push_back(cycle);
  }

  // remove all cycles of length 1 from res
  auto has_length_1 = [] (vector <uint> v) { return (v.size() == 1); };
  res.erase(remove_if(res.begin(), res.end(), has_length_1), res.end());

  return res;
}


/**
 * Returns a vector of strings, where each string represents a single cycle.
 *
 * @param str a string representing the cycle decomposition of a permutation.
 */
static vector<string> extract_cycles (string str)
{
 vector<string> tokenvector;
 boost::split(tokenvector, str, boost::is_any_of("()"));
 auto isEmpty = [](string x){ return (x == ""); };
 tokenvector.erase(remove_if(tokenvector.begin(), tokenvector.end(), isEmpty),
                   tokenvector.end());
 return tokenvector;
}

/**
 * A constructor.
 *
 * @param new_permarray an array representing a permutation.
 *
 * @param new_size the number of elements in the permutation.
 */
Permutation::Permutation(uint* new_permarray, uint new_size)
{
  permarray = new_permarray;
  size = new_size;
}

/**
 * A constructor.
 *
 * @param str a string representing a cyclic decomposition of a permutation.
 *
 * @param n the number of elements in the permutation.
 */
Permutation::Permutation(string str, uint n)
{
  size = n;
  // initialize permarray to represent the identity permutation
  permarray = (uint*) malloc(n*sizeof(uint));
  for (int i = 0; i < n; i++)
  {
    permarray[i] = i+1;
  }
  // break str into strings representing cycles and store the cycles
  // in tokenvector
 vector<string> tokenvector;
 tokenvector = extract_cycles(str);
 for (string x : tokenvector)
   {
     assign_cycle_perms(permarray, (cycle_to_vector (x)));
   }
}

/**
 * Returns the value that j is permuted to.
 *
 * @param j the input to the permutation
 */
uint Permutation::getval (uint j) const
{
  return permarray[j-1];
}

/**
 * Returns the string representation of a permutation, for example:
 *
 *    1 -> 2
 *    2 -> 1
 *    3 -> 3
 */
string Permutation::to_string() const
{
  string str = "";
  for (uint i = 1; i <= size; i++)
  {
    str += std::to_string(i) + " -> " + std::to_string(getval(i)) + "\n";
  }
  return str;
}

/**
 * Returns true if the compared Permutations are equal, false otherwise.
 *
 * Permutations p1 and p2 are equal when they have the same size and for each
 * element j, p1.getVal(j) == p2.getVal(j).
 */
bool Permutation::operator == (const Permutation& p) const
{
  return (size == p.size) && (memcmp (permarray, p.permarray, size) == 0);
}

/**
 * Returns false if the compared Permuations are not equal, false otherwise.
 *
 * Permutations p1 and p2 are not equal when they have different sizes or
 * there is some element j such that p1.getVal(j) != p2.getVal(j).
 */
bool Permutation::operator != (const Permutation & p) const
{
  return !(*this == p);
}

/**
 * Returns a Permutation representing the composition of two Permutations.
 */
Permutation Permutation::operator * (const Permutation& p)
{
  if (size != p.size) {throw invalid_argument("different permutation sizes");}
  uint* comparray = (uint*) malloc(size*sizeof(uint));
  for (uint i = 0; i < size; i ++)
  {
    comparray[i] = (*this).getval(p.permarray[i]);
  }
  return Permutation(comparray, size);
}

/**
 * Returns a Permutation representing the inverse of a Permutation.
 */
Permutation Permutation::inverse () const
{
  uint* invarray = (uint*) malloc(size*sizeof(uint));
  for (uint i = 0; i < size; i++)
  {
    invarray[permarray[i]-1] = i+1;
  }
  return Permutation(invarray, size);
}

/**
 * Returns a Permutation representing a Permutation raised to an exponent.
 *
 * @param n the exponent to which to raise the Permutation
 */
Permutation Permutation::operator ^ (int n) const
{
  // initialize accumulator as identity
  Permutation res = Permutation("", size);

  if (n != 0)
  {
    for (uint i = 0; i < abs(n); i++)
    {
      res = res * (*this);
    }
  }

  if (n < 0) { res = res.inverse(); }

  return res;
}

/**
 * Returns the order of a Permutation.
 */
uint Permutation::order () const
{
  // the order of a permutation is the lcm of the lengths of the cycles in its
  // cycle decomposition
  vector <vector <uint> > lst = (*this).decomp_list();

  // initialize return value to 1
  uint res = 1;

  for (vector <uint> cycle : lst)
  {
    res = lcm(res, cycle.size());
  }
  return res;
}

/**
 * Returns a string representing the cyclic decomposition of a Permutation.
 *
 * The cycle decomposition format is described in Dummit and Foote's
 * Abstract Algebra, pg 29. For example, the cycle decomposition of the
 * permutation given by 1 -> 2, 2 -> 1, 3 -> 3 is (1 2).
 */
string Permutation::decomposition () const
{
  vector <vector <uint> > lst = (*this).decomp_list();
  string dstr = "";
  for (vector <uint> cycle : lst)
  {
    dstr += "(";
    for (uint elt : cycle)
    {
      dstr += (std::to_string(elt)) + " ";
    }
    // remove trailing ' '
    dstr.pop_back();
    dstr += ")";
  }
  return dstr;
}
