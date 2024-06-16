#ifndef CS3_LAB2_WORDCOUNT_
#define CS3_LAB2_WORDCOUNT_

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word = "", int num = 0) : word_(word), num_(num) {};
    bool matchWord(const std::string&); // returns true if word matches stored
    void increment() { ++num_;  }; // increments number of occurrences
    std::string getWord() const { return word_;  };
    int getNum() const { return num_;  };

private:
    std::string word_;
    int num_;
};

class WordList {
public:
    // add copy constructor, destructor, overloaded assignment
    WordList(int size = 0) : wordArray_(nullptr), size_(size) {};
    ~WordList() { delete[] wordArray_; size_ = 0; }
    WordList(const WordList& other);

    void swap(WordList& other);

    WordList& operator=(WordList other) { swap(other); return *this; };


    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const std::string&);
    void print();
private:
    WordOccurrence* wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};


bool WordOccurrence::matchWord(const std::string& word) {
    return word_ == word;
};

WordList::WordList(const WordList& other) {


    size_ = other.size_;
    size_ > 0 ? wordArray_ = new WordOccurrence[size_] : nullptr;

    for (int i = 0; i < size_; ++i) {
        wordArray_[i] = other.wordArray_[i];
    }
}

void WordList::swap(WordList& other) {
    WordOccurrence* temp = other.wordArray_;
    other.wordArray_ = wordArray_;
    wordArray_ = temp;
    int tempSize = other.size_;
    other.size_ = size_;
    size_ = tempSize;
};

bool equal(const WordList& lhs, const WordList& rhs) {
    if (lhs.size_ != rhs.size_) return false;
    for (int i = 0; i < lhs.size_; ++i) {
        if (lhs.wordArray_[i].getWord() != rhs.wordArray_[i].getWord()) { // Check all words
            return false;
        }
        if (lhs.wordArray_[i].getNum() != rhs.wordArray_[i].getNum()) { // Check all frequencies
            return false;
        }
        return true;
    }
    return true;
};

void WordList::addWord(const std::string& word) {

    bool newWord = true;
     if (size_ == 0) { // First word to be added
         size_ = 1; // Set size
         wordArray_ = new WordOccurrence[size_]; // Create array
         wordArray_[0] = word; // First index is word
       //  wordArray_[0].increment();
     }

     

     for (int i = 0; i < size_; ++i) {
         if (word == wordArray_[i].getWord()) { // Word is already in the list
             wordArray_[i].increment(); // Increment occurrence
             newWord = false;
             break;
         }
     }

     if (newWord == true) {

         WordList larger; // Will be used to "grow" array
         int originalSize = size_; // Used in loop to avoid out of range error
         ++size_; // The new size needed
         larger.size_ = size_;
         larger.wordArray_ = new WordOccurrence[larger.size_];

         for (int j = 0; j < originalSize; ++j) { // Copy old contents to new, larger, array
             larger.wordArray_[j] = wordArray_[j];
         }

         larger.wordArray_[size_ - 1] = word; // Add the desired word
         larger.wordArray_[size_ - 1].increment();
         delete[] wordArray_; // Deollacate old array
         wordArray_ = larger.wordArray_; // Reassign this pointer to array
         larger.wordArray_ = nullptr; // Avoid accidental deollacation


     }
       
        
     


   /* if (size_ == 0) { // First word to be added
        size_ = 1; // Set size
        wordArray_ = new WordOccurrence[size_]; // Create array
        wordArray_[0] = word; // First index is word
        wordArray_[0].increment();
    }

    else {

        for (int i = 0; i < size_; ++i) {
            if (word == wordArray_[i].getWord()) { // Word is already in the list
                wordArray_[i].increment(); // Increment occurrence
            }
            else { // Word was not already in list
                WordList larger; // Will be used to "grow" array
                int originalSize = size_; // Used in loop to avoid out of range error
                ++size_; // The new size needed
                larger.size_ = size_; 
                larger.wordArray_ = new WordOccurrence[larger.size_];

                for (int j = 0; j < originalSize; ++j) { // Copy old contents to new, larger, array
                    larger.wordArray_[j] = wordArray_[j];
                }

                larger.wordArray_[size_ - 1] = word; // Add the desired word
                larger.wordArray_[size_ - 1].increment();
                delete[] wordArray_; // Deollacate old array
                wordArray_ = larger.wordArray_; // Reassign this pointer to array
                larger.wordArray_ = nullptr; // Avoid accidental deollacation
                

            }
            break; // Cannot go back to for-loop because word is now present
        }
    }*/

};

void WordList::print() {
    
    WordOccurrence temp; // Used for sorting

    for (int i = size_ - 1; i > 0; --i) { // Set i to max val and decrement
        for (int j = 0; j < i; ++j) { // Check index through j
            if (wordArray_[j].getNum() > wordArray_[j+1].getNum()) { // Move lesser values to the left
                temp = wordArray_[j + 1];
                wordArray_[j + 1] = wordArray_[j];
                wordArray_[j] = temp;
            }
        }
    }
    
    for (int k = 0; k < size_; ++k) {
        std::cout << "Word: " << wordArray_[k].getWord() << "     Frequency: " << wordArray_[k].getNum() << std::endl;
    }
};






#endif