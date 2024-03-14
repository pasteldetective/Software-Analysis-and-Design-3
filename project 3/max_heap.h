// Jackie Yee
// Project 3
// Max Heap

#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>

/*
Part Two
Create a Customer Class
*/
class Customer
{
    public:
    Customer():name_(""),priority_level_(0)
    {
        void SetPriorityLevel();
    }
    
    void SetPriorityLevel()
    {
        // set from 0 - 100
        priority_level_ = rand() % 101;
    }

    void SetServiceTime()
    {
        // set from 0 - 60
        service_time_ = rand() % 61;
    }

    int GetPriorityLevel() const
    {
        return priority_level_;
    }

    private:
    string name_;
    int service_time_, priority_level_;
};

/*
Part 1 and 3, adjust to create a maxHeap and modify to store customer objects
*/
template <class Comparable = Customer>
class maxHeap 
{
    public: // Constructor
    maxHeap() : current_size(0) {}

    // Insert an element into the heap
    // From priority queue notes, adjusted for maxHeap
    template < class Comparable >
    void maxHeap < Comparable >:: insert ( const Comparable & new_item )
    {
        if ( isFull() > 10000 )
        throw Overflow ( ) ;
        // Percolate up
        int hole = ++ current_size ;
        /*
        condition is changed to new_item > array [ hole /2] 
        to perculate up every node bigger than the two children 
        */
        //updated to check for priority level (part 3)
        while ( hole > 1 && new_item.GetPriorityLevel() > array [ hole /2].GetPriorityLevel() ) 
        {
            array [ hole ] = array [ hole / 2 ];
            hole = hole /2;
        }
        array [ hole ] = new_item ;
    }

    // hole is the position containing an element that might need to be percolated down
    // from priority queue notes
    /*
    adjusted from notes to fit a maxHeap implementation, perculateDown now perculatesUp
    swaps parent down and moving up hole index, temp moves up to position of maxheap
    */
    template < class Comparable >
    void maxHeap < Comparable >:: percolateUp (int hole)
    {
        Comparable temp = array[hole]; // Copy the element for later
        //updated to check for priority level (part 3)
        while (hole > 1 && temp.GetPriorityLevel() > array[hole/2].GetPriorityLevel()) //updated to include
        {
            array[hole] = array[hole/2]; // Move parent down to hole
            hole = hole/2; // Move up to parent
        }

        array[hole] = temp; // Insert element into final position

        // int child ;
        // Comparable temp = array [ hole ]; // copy the element for later
        // insertion
        // while ( 2* hole <= current_size ) 
        // {
        //     child = hole * 2; // left child of hole
        //     if ( child != current_size && array [ child + 1] < array [ child ] )
        //     // right child exists and is smaller than left , so make child
        //     its index
        //     child ++;
        //     if ( array [ child ] < temp )
        //     // copy smaller child into hole
        //     array [ hole ] = array [ child ];
        //     else
        //     break ; // both children are bigger than hole
        //     // repeat with hold being child that was copied up
        //     hole = child ;
        // }
        // array [ hole ] = temp ;
    }

    //from priority queue notes
    /*
    adjusted to fit maxHeap implementation, 
    deletes the max instead and percolateUp
    */
    Comparable deleteMax( )
    // or you can make it
    // void heap < Comparable >:: deleteMin ( Comparable & min_item )
    // and set min_item = array [1]
    {
        if (isEmpty() < 0)
        throw Underflow ( );
        
        Comparable maxItem = array[1]; // Save the top element (part 3)

        array [1] = array [ current_size ];
        current_size --;
        percolateUp(1);

\       // Set service time of deleted customer (part 3)
        maxItem.SetServiceTime(); 

        // Store deleted customer in history vector (part 3)
        history.push_back(maxItem); 
        // Sort history vector based on service time (part 3)
        /*
        compares between the beginning of history and the end of history
        compares the service time of reference of a and b, returns true if a < b
        if a < b, then the the customers obj in history vector is sort from 
        least to greatest service time
        */
        std::sort(history.begin(), history.end(), [](const Comparable& a, const Comparable& b) 
        {
            return a.GetServiceTime() < b.GetServiceTime();
        }); 

        return maxItem; // Return the saved top element (part 3)
    }

    //from priority queue notes
    /*
    adjusted to fit a maxHeap implementation
    i is set to current size/2 and goes down the heap through the last 
    parent node, then each element is perculated up 
    */
    template < class Comparable >
    void maxHeap < Comparable >:: heapify ()
    {
        for ( int i = current_size/2; i > 0; i--)
        {
            percolateUp(i);
        }
    }

    // Check if heap is empty
    bool isEmpty() const 
    {
        return current_size == 0;
    }

    // Check if heap is full
    bool isFull() const 
    {
        return current_size == MAX_SIZE;
    }

    private:
    static const int MAX_SIZE = 10000; // Maximum size of the heap
    Comparable array[10000]; // Array to store the heap elements
    int current_size; // Current size of heap

    vector<Comparable> history; // (part 3) stores deleted customer
};

