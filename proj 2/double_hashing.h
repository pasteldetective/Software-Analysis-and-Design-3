//Jackie Yee
//Double Hashing
//CSCI 335

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <functional>
#include <algorithm>

namespace {

// Internal method to test if a positive number is prime.
/*
To avoid Redefinition error, changed IsPrime to IsPrimeDouble from quadratic hashing
to double hashing
*/
bool IsPrimeDouble(size_t n) {
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
To avoid Redefinition error, changed NextPrime to NextPrimeDouble from quadratic hashing
to double hashing
*/
int NextPrimeDouble(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeDouble(n)) n += 2;  
  return n;
}

} 


/*
Double Hash Implementation:
Set size to a prime number, I picked 269 to minimize clustering and improve key distribution.
Augmented from Quadratic Probing
*/
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  //from quadratic probing
  explicit HashTableDouble(size_t size = 269) : array_(NextPrimeDouble(size))
  { 
    MakeEmpty(); 
  }
  
  //from quadratic probing
  bool Contains(const HashedObj &x) const 
  {
    return IsActive(FindPos(x));
  }
  
  //from quadratic probing
  void MakeEmpty() 
  {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  //from quadratic probing
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
  
  //from quadratic probing
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

  //from quadratic probing
  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  /*
  from linear probing
  the size of the hash table is returned
  */
  int getSize() 
  {
    return array_.size();
  }

 
  /*
  from linear probing
  the number of elements in the array current size is returned
  */
  int getCurrentSize() 
  {
    return current_size_;
  }


  /*
  from linear probing
  total Collisions is returned
  */
  int getCollisions() 
  {
    return collisions_;
  }

  /*
  from linear probing
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
  
  //initialize variable
  mutable size_t collisions_; 
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  // next available position in array for x is found
  /*
  From quadratic probing and reimplemented to fit double hashing
  Finds next position/index of an element in a hash table
  */
  size_t FindPos(const HashedObj & x) const 
  {

    static std::hash<HashedObj> hashVal; //create a hash object called hashVal
    size_t offset = 151 - (hashVal(x) % 151); //used 151 as the offset since it is a prime

    size_t current_pos = InternalHash(x);

    /*
    remove the changing of the offset by += 2
    */
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) 
    {
      current_pos += offset;
      if (current_pos >= array_.size()){
        current_pos -= array_.size();  
      }
      collisions_++;
    }
    return current_pos;
  }

  //from quadratic probing 
  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeDouble(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  //from quadratic probing, uses hashVal obj instead of hf
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hashVal;
    return hashVal(x) % array_.size( );
  }
};

#endif  // DOUBLE_HASHING_H