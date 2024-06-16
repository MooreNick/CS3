// Nicholas A Moore
// CSIII
// Lab 10
// Part I Adapter
// 03/24/2023

#include <iostream>

using std::cout; using std::endl;

// base interface
class Square {
public:
    virtual void draw() = 0;
    virtual int size() = 0;
    virtual void resize(int) = 0;
    virtual ~Square() {}
};

// implementer/adaptee
class LegacyRectangle {
public:
    LegacyRectangle(int topLeftX, int topLeftY,
        int bottomRightX, int bottomRightY) :
        topLeftX_(topLeftX),
        topLeftY_(topLeftY),
        bottomRightX_(bottomRightX),
        bottomRightY_(bottomRightY) {}

    void oldDraw() const {
        for (int i = 0; i < bottomRightY_; ++i) {
            for (int j = 0; j < bottomRightX_; ++j)
                if (i >= topLeftY_ && j >= topLeftX_)
                    cout << '*';
                else
                    cout << ' ';
            cout << endl;
        }
    }

    void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
        topLeftX_ = topLeftX; // getting all of the new values
        topLeftY_ = topLeftY;
        bottomRightX_ = bottomRightX;
        bottomRightY_ = bottomRightY;
    }

    int getTopLeftX() { return topLeftX_; }
    int getTopLeftY() { return topLeftY_; }
    int getBottomRightX() { return bottomRightX_; }
    int getBottomRightY() { return bottomRightY_; }

private: // defining top/left and bottom/right coordinates 
    int topLeftX_;
    int topLeftY_;
    int bottomRightX_;
    int bottomRightY_;
};

// adapter uses composition to delegate 
// requests to adaptee
class SquareAdapter : public Square {
public:
    SquareAdapter(int size) {
        adaptee_ = new LegacyRectangle(0, 0, size, size);
    }
    void draw() override {
        adaptee_->oldDraw();
    }

    int size() {
        return adaptee_->getBottomRightX() - adaptee_->getTopLeftX();
    }

    void resize(int newSize) {
        adaptee_->move(0, 0, newSize, newSize);
    }

private:
    LegacyRectangle* adaptee_;
};


int main() {

    std::cout << "Enter the size of the desired square: " << std::endl;
    int startSize;
    std::cin >> startSize;

    Square* square = new SquareAdapter(startSize);
    square->draw();

    std::cout << "The size if your square is: " << square->size() << std::endl;

    std::cout << "Enter new size of square: " << std::endl;
    int newSize;
    std::cin >> newSize;
    square->resize(newSize);
    square->draw();

    std::cout << "The new size of your square is: " << square->size() << std::endl;

    return 0;
}
