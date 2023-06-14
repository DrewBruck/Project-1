// Drew Bruck  - 24242807
// Few comments describing the class Points2D

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
// ADDING A NEW COMMENT
namespace teaching_project {

// Place comments that provide a brief explanation of the class,
// and its sample usage.
template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    // Zero-parameter constructor.
    //Creates an instance of the class with size zero.
    Points2D(){
        size_=0;
        sequence_=nullptr;
    };    

    // Copy-constructor.
    Points2D(const Points2D &rhs){
        size_= rhs.size();
        sequence_= new std::array<Object, 2>[size_];
        for(size_t i=0; i<size_; i++){
            sequence_[i] = rhs[i];
        }
    };

    // Copy-assignment. 
    Points2D& operator=(const Points2D &rhs){
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move-constructor.
    Points2D(Points2D &&rhs){
        size_=rhs.size();
        sequence_ = new std::array<Object, 2>[size_];
        for(size_t i=0; i,size_; i++){
            sequence_[i]=rhs[i];
        }
    };

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs){
        std::swap(this->size_, rhs.size_);
        std::swap(this->sequence_, rhs.sequence_);
    };

    ~Points2D(){
        size_=0;
        delete *sequence_;
    };

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
        size_= item.size();
        *sequence_ = new std::array<Object, 2>[size_];
    }

    size_t size() const {
        return size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        if(location < this->size_-1){
            return sequence_[location];
        }
        else{
            std::cerr<<"ERROR - invalid input";
            abort();
        }
    }

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        Points2D result;                                                //Creates a new Points 2D object called "result"
        if(c1.size_ == c2.size_){                                       //Checks to see if both sequence are equivalent in size.
            result.size_=c1.size_;                                      //Changes result's size_ to the same value as the sequences.
            result.sequence_= new std::array<Object, 2>[result.size_];  //Creates a new sequence_ with matching size to the result array.
            for(size_t i=0; i<result.size_; i++){                       //This begins the loop to add their matching indices together.
                result.sequence_[i]= (c1[i]+c2[i]);
            }
        }
        else if(c1.size_ > c2.size_){                                   //Checks to see if c1's size_ is bigger than c2's size_.
            result.size_=c1.size_;                                      //Changes result's size_ to the same value as c1, since c1 is larger in this if statement.
            result.sequence_= new std::array<Object, 2>[result.size_];  //Creates a new sequence_ with matching size to the result array.
            for(size_t i=0; i<c2.size_; i++){                           //This begins the loop to add their matching indices together.
                result.sequence_[i]= (c1[i]+c2[i]);
            }
            for(size_t j=c2.size_; j<c1.size_; j++){                    //This loop is to append the unmatched values in the larger c1 to the result array.
                result.sequence_[j]=c1[j];
            }
        }
        else if(c1.size_ < c2.size_){                                   //Checks to see if c2's size_ is bigger than c1's size_.
            result.size_=c2.size_;                                      //Changes result's size_ to the same value as c2, since c2 is larger in this if statement.
            result.sequence_ = new std::array<Object, 2>[result.size];  //Creates a new sequence_ with matching size to the result array.
            for(size_t i=0; i<c1.size_; i++){                           //This begins the loop to add their matching indices together.
                result.sequence_[i] = (c1[i]+c2[i]);
            }
            for(size_t j=c1.size_; j<c2.size_; j++){                    //This loop is to append the unmatched values in the larger c1 to the result array.
                result.sequence_[j] = c2[j];
            }


        }
        return result;                                                  //returns Points2D result.
    }

    // Overloading the << operator.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        // Code missing.
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        // Code missing.
    }

  private:
    // Sequence of points.
    const std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};
}  // namespace teaching_project 
#endif // CSCI_335_HOMEWORK1_Points2D_H_
