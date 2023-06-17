// Drew Bruck  - 24242807
// A class template for reference, storing and manipulating 2-dimensional 
// coordinates.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <ctype.h>

namespace teaching_project {

// This is a template class for a 2 dimensional points class.  When provided
// with input via stream or user input, it can create an array of points
// that can be added together, stored, moved, and manipulated.  It's
// practicality for mathematics and shipping information would be vast.

template<typename Object>
class Points2D {
  public:
    // Default "big five" -- you have to alter them for your assignment.
    // That means that you will remove the "= default" statement.
    //  and you will provide an implementation.

    // Zero-parameter constructor.
    //Creates an instance of the class with size zero.
    Points2D(){
        this->size_ = 0;
        this->sequence_ = nullptr;
    };    

    // Copy-constructor.
    // Will allow a new class to be created & have values from a different
    // object copied in.
    Points2D(const Points2D &rhs){
        this->size_= rhs.size_;
        this->sequence_= new std::array<Object, 2>[this->size_];
        for(size_t i=0; i<this->size_; i++){
            this->sequence_[i][0] = rhs[i][0];
            this->sequence_[i][1] = rhs[i][1];
        }
    };

    // Copy-assignment. 
    // When given two objects, this will copy the values of the target
    // with the values of the original.
    Points2D& operator=(const Points2D &rhs){
        Points2D copy = rhs;
        std::swap(*this, copy);
        return *this;
    };

    // Move-constructor.
    // This will move the values from one object to the other and will
    // then clear out the values of the original.
    Points2D(Points2D &&rhs){
        this->size_=rhs.size_;
        this->sequence_ = rhs.sequence_;
        rhs.size_ = 0;
        rhs.sequence_ = nullptr;
    };

    // Move-assignment.
    // Just use std::swap() for all variables.
    Points2D& operator=(Points2D &&rhs){
        std::swap(this->size_, rhs.size_);
        std::swap(this->sequence_, rhs.sequence_);
        rhs.size_ = 0;
        rhs.sequence_ = nullptr;
    return *this;
    };

    //Destructor
    //This will enable the dynamic memory of the objects to be cleared
    //responsibly.
    ~Points2D(){
        if(this->size_>0){
            this->size_=0;
            delete this->sequence_;
        }
    };

    // End of big-five.

    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item){
        this->size_= 1;
        this->sequence_ = new std::array<Object,2>[1];
        this->sequence_[0][0] = item[0];
        this->sequence_[0][1] = item[1];
    };

    size_t size() const {
        return this->size_;
    }

    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // abort() if out-of-range.
    std::array<Object, 2>& operator[](size_t location) const {
        if(location > this->size_){        //check if the location is valid
            std::cerr<<"ERROR - invalid input";
            abort();
        }
        return this->sequence_[location]; //if location is valid, return value.
    };

    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //  result with the remaining part of the larger sequence.
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        if(c1.size_ == c2.size_){                             //Checks to see if both sequence are equivalent in size.
            Points2D result;                                  //Creates a new Points 2D object called "result"
            result.size_=c1.size_;                            //Changes result's size_ to the same value as the sequences.
            result.sequence_= new std::array<Object, 2>[result.size_];  //Creates a new sequence_ with matching size to the result array.
            for(size_t i=0; i<result.size_; i++){             //This begins the loop to add their matching indices together.
                result[i][0]= c1[i][0]+c2[i][0];
                result[i][1]= c1[i][1]+c2[i][1];
            }
            return result;
        }
        else if(c1.size_ > c2.size_){                         //Checks to see if c1's size_ is bigger than c2's size_.
            Points2D result;                                  //Creates a new Points 2D object called "result"
            result.size_=c1.size_;                            //Changes result's size_ to the same value as c1, since c1 is larger in this if statement.
            result.sequence_= new std::array<Object, 2>[result.size_];  //Creates a new sequence_ with matching size to the result array.
            for(size_t i=0; i<c2.size_; i++){                 //This begins the loop to add their matching indices together.
                result[i][0]= (c1[i][0]+c2[i][0]);
                result[i][1]= (c1[i][1]+c2[i][1]);
            }
            for(size_t j=c2.size_; j<c1.size_; j++){          //This loop is to append the unmatched values in the larger c1 to the result array.
                result[j][0]=c1[j][0];
                result[j][1]=c1[j][1];
            }
            return result;
        }
        else if(c1.size_ < c2.size_){                         //Checks to see if c2's size_ is bigger than c1's size_.
            Points2D result;                                  //Creates a new Points 2D object called "result"
            result.size_=c2.size_;                            //Changes result's size_ to the same value as c2, since c2 is larger in this if statement.
            result.sequence_ = new std::array<Object, 2>[result.size_];  //Creates a new sequence_ with matching size to the result array.
            for(size_t i=0; i<c1.size_; i++){                 //This begins the loop to add their matching indices together.
                result.sequence_[i][0] = (c1[i][0]+c2[i][0]);
                result.sequence_[i][1] = (c1[i][1]+c2[i][1]);
            }
            for(size_t j=c1.size_; j<c2.size_; j++){          //This loop is to append the unmatched values in the larger c1 to the result array.
                result.sequence_[j][0] = c2[j][0];
                result.sequence_[j][1] = c2[j][1];
            }
        return result;
        }       
        std::cerr<<"ERROR - invalid input"<< std::endl;;
        abort();                                          
    }

    // Overloading the << operator.
    // In order to input and output data, this function will overload the <<
    // operator to allow a larger functionality within the program.
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        if (some_points.size_ <=0){
            out << "()" << std::endl;
            return out;
        }
        for (size_t i=0; i<some_points.size_; i++){
            out << "(";
            out << some_points[i][0];
            out << ",";
            out << some_points[i][1];
            out << ")";
        }
        out << std::endl;
        return out;
    }

    // Overloading the >> operator.
    // Read a chain from an input stream (e.g., standard input).
    // In order to input data as needed, this function will overload the >>
    // operator to allow a larger functionality within the program.
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        int sum_size;
        in >> sum_size;
        if(isalpha(sum_size) == 0){
            std::cerr<<"ERROR - invalid input" << std::endl;
            abort();                       
        }
        some_points.size_ = sum_size;
        some_points.sequence_ = new std::array<Object, 2>[sum_size];
        for(int i = 0; i < sum_size; i++){
            Object a, b;
            in >> a >> b;
            if(isalpha(a) == 0 || isalpha(b) == 0){
                std::cerr<<"ERROR - invalid input" << std::endl;
                abort(); 
            }
            some_points[i][0] = a;
            some_points[i][1] = b;
        }
        return in;
    }

  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};
}  // namespace teaching_project 
#endif // CSCI_335_HOMEWORK1_Points2D_H_
