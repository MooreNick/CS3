#ifndef CS3_LAB3_
#define CS3_LAB3_


// Nicholas A Moore
// CSIII Lab 3 Templated List
// 02/02/2023

#include <iostream>

template <typename T>
class node {
public:
	node() : next_(nullptr) {};

	T getData() const { return data_; };
	void setData(const T& data) { data_ = data; };

	node<T>* getNext() const;
	void setNext(node<T>* const next);


private:
	T data_;
	node<T>* next_;
};

template <typename T>
node<T>* node<T>::getNext() const {
	return next_;
}

template<typename T>
void node<T>::setNext(node<T>* const next) {
	next_ = next;
}

// Forward class and func
// Forwarded class

template <typename T>
class Collection;

// Forwarded function

template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
	Collection() : head_(nullptr), tail_(nullptr) {};

	void add(T item);
	void remove(T item);
	T last() const;
	void print() const;
	friend bool equal<T>(const Collection&, const Collection&);

private:
	node<T>* head_; // Points at first element
	node<T>* tail_; // Points at last element
};

template <typename T>
void Collection<T>::add(T item) {
	if (head_ == nullptr) { // First element to be added
		head_ = new node<T>();
		head_->setData(item);
		tail_ = head_;
	}

	// Adding other elements (not first)
	else {
		tail_->setNext(new node<T>());
		tail_ = tail_->getNext();
		tail_->setData(item);
	}
};

template <typename T>
void Collection<T>::remove(T item) {
	if (head_ == nullptr) return; // empty
	node<T>* temp;
	tail_ = head_; // Will traverse list using tail

	while (tail_ != nullptr) {

		if (tail_->getData() == item) { // First item needs removed
			node<T>* del = tail_;
			tail_ = tail_->getNext();
			head_ = tail_; // Resetting front of list
			delete del;
		}
		else if (tail_->getNext()->getData() == item) {
			node<T>* del = tail_->getNext();
			temp = del->getNext(); // Get position after needed delete
			tail_->setNext(temp); // Setting next to past the deletion
			tail_ = tail_->getNext(); // Increment tail
			delete del;
		}
		else {
			tail_ = tail_->getNext(); // Increment tail
		}
	} 
	temp = head_; // Reset temp
	while (temp->getNext() != nullptr) {
		temp = temp->getNext();
	}
	tail_ = temp; // Make tail point at last element again
};

template <typename T>
T Collection<T>::last() const {
	return tail_->getData();
};

template <typename T>
void Collection<T>::print() const {
	node<T>* temp = head_; // Keeping track of position

	while (temp != nullptr) {	
	std::cout << temp->getData() << std::endl;
	temp = temp->getNext();    
	}
	
};

template <typename T>
bool equal(const Collection<T>& left, const Collection<T>& right) {
	node<T>* tempLeft = left.head_;
	node<T>* tempRight = right.head_;

	while (tempLeft != nullptr && tempRight != nullptr) {
		if (tempLeft->getData() != tempRight->getData()) { // Different data
			return false;
		}
		tempLeft = tempLeft->getNext();
		tempRight = tempRight->getNext();
	}

	if (tempLeft == nullptr && tempRight != nullptr) { // Diff sizes
		return false;
	}

	if (tempLeft != nullptr && tempRight == nullptr) { // Diff sizes
		return false;
	}

	return true;
};



#endif
