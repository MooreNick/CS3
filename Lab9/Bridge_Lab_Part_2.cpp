// Nicholas A Moore
// CSIII
// Lab 9 Part II
// 03/17/2023

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
	Fill(char fillChar, char fillCharTwo) : fillChar_(fillChar), fillCharTwo_(fillCharTwo) {}
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;
	virtual ~Fill() {}
protected:
	char fillChar_;
	char fillCharTwo_;
};

// concrete body
class Hollow : public Fill {
public:
	Hollow(char fillChar) :Fill(fillChar, ' ') {} // pass space for second char
	char getBorder() override { return fillChar_; }
	char getInternal() override { return ' '; }
	~Hollow() override {}
};


// another concrete body
class Filled : public Fill {
public:
	Filled(char fillChar, char fillCharTwo) :Fill(fillChar, fillCharTwo) {} // using the same char for both
	char getBorder() override { return fillChar_; }
	char getInternal() override { return fillChar_; }
	~Filled() override {}
};

class FullyFilled : public Filled {
public:
	FullyFilled(char fillChar, char fillCharTwo) : Filled(fillChar, fillCharTwo) {}
	char getBorder() override { return fillChar_; }
	char getInternal() override { return fillCharTwo_; }
	~FullyFilled() override {}
};

class RandomFill : public Fill {
public:
	RandomFill(char fillChar, char fillCharTwo) : Fill(fillChar, fillCharTwo) {}
	char getBorder() override { int get = rand() % 2; if (get == 0) return fillChar_; else return fillCharTwo_; }
	char getInternal() override { int get = rand() % 2; if (get == 0) return fillChar_; else return fillCharTwo_;
	}
	~RandomFill() override {}
};

// abstract handle
class Figure {
public:
	Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
	virtual void draw() = 0;
	virtual ~Figure() {}
protected:
	int size_;
	Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
	Square(int size, Fill* fill) : Figure(size, fill) {}
	void draw() override;

};

void Square::draw() {
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j)
			if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
				cout << fill_->getBorder();
			else
				cout << fill_->getInternal();
		cout << endl;
	}
}

int main() {
	srand(time(nullptr));


	Fill* versions[4]; // holds all the options
	versions[0] = new Hollow('H');
	versions[1] = new Filled('*', '&');
	versions[2] = new FullyFilled('A', 'Z');
	versions[3] = new RandomFill('%', '^');
	
	Figure* shapes[4]; // getting squares for each version
	shapes[0] = new Square(5, versions[0]);
	shapes[1] = new Square(5, versions[1]);
	shapes[2] = new Square(5, versions[2]);
	shapes[3] = new Square(5, versions[3]);

	// Doing all of the drawing
	shapes[0]->draw();
	std::cout << std::endl;
	shapes[1]->draw();
	std::cout << std::endl;
	shapes[2]->draw();
	std::cout << std::endl;
	shapes[3]->draw();
	
	



	/*
	Fill* hollowPaintQ = new Hollow('Q');
	Fill* filledPaintStar = new Filled('*');


	Figure *smallBox = new Square(5, hollowPaintQ);
	Figure *bigBox = new Square(15, filledPaintStar);

	smallBox->draw();
	cout << endl;
	bigBox -> draw();
	*/

	/*
	// ask user for figure parameters
	cout << "Enter fill character: ";
	char fchar; cin >> fchar;
	cout << "Filled or hollow? [f/h] ";
	char ifFilled; cin >> ifFilled;
	cout << "Enter size: "; int size; cin >> size;


	Figure* userBox = new Square(size, ifFilled == 'f' ?
		static_cast<Fill*>(new Filled(fchar)) :
		static_cast<Fill*>(new Hollow(fchar))
	);
	*/

	/*
	Figure *userBox = new Square(size,
			ifFilled == 'f'? new Filled(fchar): new Hollow(fchar)
				);

	*/

	/*
	Figure* userBox = ifFilled == 'f' ?
		new Square(size, new Filled(fchar)) :
		new Square(size, new Hollow(fchar));


	userBox->draw();
	cout << endl;
	*/
}