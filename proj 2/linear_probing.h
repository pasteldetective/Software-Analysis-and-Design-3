// Jackie Yee
// Linear probing
// CSCI 335

#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace {

// Internal method to test if a positive number is prime.
/*
To avoid Redefinition error, changed IsPrime to IsPrimeLinear
*/
bool IsPrimeLinear(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}


// Internal method to return a prime number at least as large as n.
/*
To avoid Redefinition error, changed NextPrime to NextPrimeLinear
*/
int NextPrimeLinear(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeLinear(n)) n += 2;  
  return n;
}

}  // namespace


/*
Linear Probing Implementation:
Set size to a prime number, I picked 269 to minimize clustering and improve key distribution.
Augmented from Quadratic Probing
*/
template <typename HashedObj>
class HashTableLinear {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 269) : array_(NextPrimeLinear(size))
  { 
    MakeEmpty(); 
  }
  
  bool Contains(const HashedObj & x) const 
  {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  /*
  the size of the hash table is returned
  */
  int getSize() 
  {
    return array_.size();
  }

  /*
  the number of elements in the array current size is returned
  */
  int getCurrentSize() 
  {
    return current_size_;
  }

  /*
  total Collisions is returned
  */
  int getCollisions() 
  {
    return collisions_;
  }

  /*
  total Collisions is set to 0
  */
  void resetCollisions() 
  {
    collisions_ = 0;
  }	

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  /*
  mutable lets collisions_ change even if funct is const
  */
  mutable size_t collisions_;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    /*
    to implement a linear approach, collisions_ is incremented by 1
    there is no change to offset like in quadratic probing
    */
    while (array_[current_pos].info_ != EMPTY 
    && array_[current_pos].element_ != x) 
    {
        current_pos += offset; 
        if (current_pos >= array_.size())
        {
            current_pos -= array_.size();
        }
        collisions_++; 
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeLinear(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
};

#endif  // LINEAR_PROBING_H
