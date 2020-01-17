// permutation.h

#pragma once

/**
 * A representation of a permutation of natural numbers 1...n, for some n.
 */
class Permutation
{
 public:

  /// The number of elements in the permutation.
  uint size;

  Permutation (uint* new_permarray, uint new_size);

  Permutation (std::string str, uint n);

  uint getval (uint j) const;

  std::string to_string () const;

  bool operator == (const Permutation& p) const;

  bool operator != (const Permutation & p) const;

  Permutation operator * (const Permutation& p);

  Permutation inverse () const;

  Permutation operator ^ (int n) const;

  uint order () const;

  std::string decomposition () const;

 private:

  /// Pointer to the start of the permutation array.
  /// permarray[j-1] is the element that j is permuted to.
  uint* permarray;

  std::vector <std::vector <uint> > decomp_list () const;

};

