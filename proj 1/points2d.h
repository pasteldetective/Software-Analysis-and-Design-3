// --> Jackie Yee 
// The class Points2D can create a coordinate of points in the cartesian plane
// from user input. It is able to add the total from coordinate points in the 
// x axis and y axis. This is a template class.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

/*
This class creates a set of coordinate points from the cartesian plane.
The points (x,y) can either be int or double.
*/
template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.
    /*
    Zero-parameter constructor.
    Set size to 0.
    */ 
    Points2D() : size_(0)
     //mX(0), mY(0) //default constructor set mX, mY to size 0
    {
        //size_ = 0;
        //myVec(0);
        //mX = 0;
        //mY = 0;
    }
    /* Parameterized Constructor
    Points2D() : size_(0), sequence_(0) //parameterized constructor for input 
    {
    }
    */
    // Copy-constructor.
    Points2D(const Points2D &rhs) //rhs is ref to Points2D object to copy
    {
        //std::cout<<"copy constructor called"<<std::endl;

        //memory is allocated to a new array to sequence_
        sequence_ = new std::array<Object, 2>[rhs.size_];
        //size of sequence is copied to size_
        size_ = rhs.size(); 
        
        /*
        elements from source(rhs) sequence is copied onto sequence_
        */
        for (size_t i = 0; i < rhs.size(); i++)
        {
            sequence_[i]= rhs.sequence_[i];
            //sequence_[i][0] = rhs.sequence_[i][0]; 
            //sequence_[i][1] = rhs.sequence_[i][1]; 
        }

        
        //size_ = rhs.size_; //member variable is assigned to the length of rhs Points2D object
        //sequence_ = new std::array<Object, 2>[size_];
    
        //std::cout<<"copy constructor called"<<std::endl;
        //mX = rhs.mX;
        //mY = rhs.mY;
    }

    // Copy-assignment. If you have already written
    // the copy-constructor and the move-constructor
    // you can just use:
    // {
    // Points2D copy = rhs;
    // std::swap(*this, copy);
    // return *this;
    // }
    Points2D& operator=(const Points2D &rhs)
    {
        //std::cout<<"copy-assignment constructor called"<<std::endl;
        //Points object is created and is initialized with rhs
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;

        /* if (this == &rhs)
        {
            return *this;
        }
        delete[] sequence_;

        size_ = rhs.size_;
        sequence_ = new std::array<Object, 2>[size_];
        for (size_t i = 0; i < size_; i++)
        {
            sequence_[i] = rhs.sequence_[i];
        }
        return *this; */
        
    }

    // Move-constructor.
    Points2D(Points2D &&rhs)
    {
        //std::cout<<"move constructor called"<<std::endl;
        //sequence ownership from rhs to sequence_
        sequence_ = rhs.sequence_;
        //size ownership from rhs.size_ to size_
        size_ = rhs.size_;

        //rhs members are set to 0 and nullptr
        // source object does not have any elements
        // sequence does not deallocate memory
        rhs.size_ = 0;
        rhs.sequence_ = nullptr;
        

        //size_ = rhs.size_;
        //sequence_ = rhs.sequence_;

        //rhs.size_ = 0;
        //rhs.sequence_ = nullptr;
        //mX = rhs.mX;
        //mY = rhs.mY;
        //rhs.mX = 0;
        //rhs.mY = 0;
    }

    // Move-assignment.
    // Just use std::swap() for all variables.
    // r value so temporary ownership
    Points2D& operator=(Points2D &&rhs)
    {
        //std::cout<<"move-assignment constructor called"<<std::endl;
        //exchange ownership using swap
        std::swap(this->size_, rhs.size_);
        std::swap(this->sequence_, rhs.sequence_);
        //returns reference this
        return *this;

    }

    ~Points2D()
    {
        delete[] this->sequence_;
    }

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) : size_(1), sequence_(new std::array<Object,2>[1]) {
        //size_ = 1;
        //sequence_ = new std::array<Object,2>[size_];
        sequence_[0][0] = item[0];
        sequence_[0][1] = item[1];
    }

    size_t size() const {
        return size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        if (location >= size_ || location < 0)
            {
                abort();
            }
            else
            {
                return sequence_[location];
            }
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        if (c1.size() >= c2.size())
            {
                Points2D<Object> total{c1};
                for (size_t i = 0; i < c2.size(); i++)
                {
                    //appends total by c1 + c2
                    total.sequence_[i][0] += c2.sequence_[i][0];
                    total.sequence_[i][1] += c2.sequence_[i][1];
                }
                return total;
            }
            else
            {
                Points2D<Object> total{c2};
                for (size_t i = 0; i < c1.size(); i++)
                {
                    //appends total by c1 + c2
                    total.sequence_[i][0] += c2.sequence_[i][0];
                    total.sequence_[i][1] += c2.sequence_[i][1];
                }
                return total;
            }
    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
       if (some_points.size() == 0)
            {
                //no points left or provided
                out << "()" << std::endl; 
                return out;
            }
            for (size_t i = 0; i < some_points.size(); i++)
            {
                out << "(" << some_points.sequence_[i][0] << "," << some_points.sequence_[i][1] << ") ";
            }
            out << std::endl;
            return out; 
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        //local variables declared to store coordinate points
        Object xCord, yCord;
        size_t numPoints;
        
        // input reads the number of points to determine size and sequence of some_points
        in >> numPoints;
        some_points.size_ = numPoints;
        some_points.sequence_ = new std::array<Object, 2>[numPoints];
        
        for (size_t i = 0; i < numPoints; i++)
        {
            //if xCord is successfully stored in some_points
            if (in >> xCord)
            {
            }
            else
            {
                std::cerr << "ERROR";
                abort();
            }
            //if yCord is successfully stored in some_points
            if (in >> yCord)
            {
            }
            else
            {
                std::cerr << "ERROR";
                abort();
            }
            //asigned to position of x or y in the sequence
            some_points.sequence_[i][0] = xCord;
            some_points.sequence_[i][1] = yCord;
        }
        std::cout << std::endl;
        return in;
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;

    //Object mX,mY;
    //vector<int> myVec;
    //int mX, mY;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
