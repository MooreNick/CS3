// Nicholas A Moore
// CSIII
// Lab 12 Part II
// 04/20/2023

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

    Document(const vector <string>& lines = {}) : lines_(lines) {}

    // actions
    void insert(int line, const string& str) {
        const int index = line - 1;
        if (index <= lines_.size())
            lines_.insert(lines_.begin() + index, str);
        else
            cout << "line out of range" << endl;
    }

    const string remove(int line) {
        const int index = line - 1;
        string deletedLine = "";
        if (index < lines_.size()) {
            deletedLine = lines_[index];
            lines_.erase(lines_.begin() + index);
        }
        else
            cout << "line out of range" << endl;
        return deletedLine;
    }

    void show() {
        for (int i = 0; i < lines_.size(); ++i)
            cout << i + 1 << ". " << lines_[i] << endl;
    }

    class Memento* createMemento() const;
    void rollBack(class Memento*);

private:
    vector<string> lines_;
};

// abstract command
class Command {
public:
    Command(Document* doc) : doc_(doc) {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual ~Command() {}
    virtual void history() = 0;
    virtual std::string getCommand() = 0;
    virtual int getLine() = 0;
protected:
    Document* doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
    InsertCommand(Document* doc, int line, const string& str) :
        Command(doc), line_(line), str_(str) {}
    void execute() override { doc_->insert(line_, str_); }
    void unexecute() override { doc_->remove(line_); }
    void history() override { std::cout << "insert " << str_ << " at line " << line_ << std::endl; }

    std::string getCommand() override { return str_; }
    int getLine() override { return line_; }

private:
    int line_;
    string str_;
};


class EraseCommand : public Command {
public:
    EraseCommand(Document* doc, int line) :
        Command(doc), line_(line), str_("") {}
    void execute() override { str_ = doc_->remove(line_); }
    void unexecute() override { doc_->insert(line_, str_); }
    void history() override { std::cout << "erase " << "line " << line_ << std::endl; }

    std::string getCommand() override { return str_; }
    int getLine() override { return line_; }
private:
    int line_;
    string str_;
};

// client
class DocumentWithHistory {
public:
    DocumentWithHistory(const vector<string>& text = {}) : doc_(text) {}

    void insert(int line, string str) {
        Command* com = new InsertCommand(&doc_, line, str);
        com->execute();
        doneCommands_.push(com);
    }

    void erase(int line) {
        Command* com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
    }

    void undo() {
        if (doneCommands_.size() != 0) {
            Command* com = doneCommands_.top();
            doneCommands_.pop();
            com->unexecute();
            delete com; // don't forget to delete command
        }
        else
            cout << "no commands to undo" << endl;
    }

    void showHistory() {
        int i = 1;
        std::stack<Command*> temp = doneCommands_; // hold commands

        while (!temp.empty()) {
            Command* com = temp.top();
            std::cout << i << ". ";
            com->history();
            temp.pop();
            ++i;
        }

    }

    void redoCommand(int redo) {
        int pops = redo - 1;
        std::stack<Command*> temp = doneCommands_; // hold commands
        while (pops != 0) {
            temp.pop();
            --pops;
        }
        auto repeat = temp.top();
        repeat->execute();
        doneCommands_.push(repeat);
    }

    void show() { doc_.show(); }

    Document getDocument() { return doc_; }

    void setDocument(Document d) { doc_ = d; }

    void eraseHistory() { while (!doneCommands_.empty()) doneCommands_.pop(); }



private:
    Document doc_;
    std::stack<Command*> doneCommands_;
};

class Memento {
public:
    Memento(const Document& doc) : doc_(doc) {}
    const Document& getState() const { return doc_; }
private:
    const Document doc_;
};

Memento* Document::createMemento() const {
    return new Memento(*this); // copying the Document itself
}

void Document::rollBack(Memento* mem) {
    *this = mem->getState();  // copying back
}



int main() {
    DocumentWithHistory doc({
        "Lorem Ipsum is simply dummy text of the printing and typesetting",
        "industry. Lorem Ipsum has been the industry's standard dummy text",
        "ever since the 1500s, when an unknown printer took a galley of",
        "type and scrambled it to make a type specimen book. It has",
        "survived five centuries." });

    char option;
    int redo, numOfPops;

    do {
        static Memento* checkpoint = nullptr;
        Document temp;

        doc.show();
        cout << endl;

        cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command, (c)heckpoint, roll(b)ack, (h)istory, (r)edo: ";
        cin >> option;

        int line; string str;
        switch (option) {
        case 'i':
            cout << "line number to insert: ";
            cin >> line;
            cout << "line to insert: ";
            cin.get(); // removes end-of-line character so getline() works correctly
            getline(cin, str);
            doc.insert(line, str);
            break;

        case 'e':
            cout << "line number to remove: ";
            cin >> line;
            doc.erase(line);
            break;

        case 'u':
            doc.undo();
            break;

        case 'c':
            temp = doc.getDocument();
            checkpoint = temp.createMemento();
            doc.eraseHistory();
            break;
        case 'b':
            if (checkpoint != nullptr) {
                temp = checkpoint->getState();
                doc.setDocument(temp);
                // doc.rollBack(checkpoint);
                delete checkpoint;
                checkpoint = nullptr;
            }

        case 'h':
            doc.showHistory();
            break;

        case 'r':
            doc.showHistory();
            std::cout << "Which command would you like to redo?" << std::endl;
            std::cin >> redo;
            doc.redoCommand(redo);
        }


    } while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}


