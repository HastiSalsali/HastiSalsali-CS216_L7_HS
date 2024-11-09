#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

enum MenuOptions { CREATE_TABLE = 1, QUIT = 2 };
const int COLLUMN_SIZE = 7;
class Fraction {
private:
  int numerator = DEFAULT_NUMERATOR;
  int denominator = DEFAULT_DENOMINATOR;

  static int numFractions;

  static const int DEFAULT_NUMERATOR = 1;
  static const int DEFAULT_DENOMINATOR = 1;

public:
  Fraction();
  Fraction(int);
  Fraction(int, int);
  Fraction(int, int, int);
  Fraction(const Fraction &);

  ~Fraction();

  void setNumerator(int);
  void setDenominator(int);
  void setFraction(int);
  void setFraction(int, int);
  void setFraction(int, int, int);
  void setFraction(const Fraction &);

  string toString() const;
  void print() const;

  static int getNumFractions();
};

class FractionException {
private:
  string message;

public:
  FractionException(string = "Unkown error");
  void PrintMessage() const;
  ~FractionException();
};

void FixCinStream(string);
void CreateTable();
void CreateTable(int, Fraction**&);
void SetTable (int, Fraction**&);
void PrintTable(int, Fraction**);
void DeleteTable (int denominator, Fraction** &ppTable);
int GetDenominator();
/*******************************************************/
int main() {
  int menuInput;
  MenuOptions choice;
  cout << "Welcome to the Multiplication table Program" << endl;
  do {
    cout << "Please choose an option:\n"
            "1- Create a multiplication table\n"
            "2- Quit\n";
    cin >> menuInput;
    choice = static_cast<MenuOptions>(menuInput);
    switch (choice) {
    case CREATE_TABLE:
      CreateTable();
      break;
    case QUIT:
      cout << "Thank you for using the Fraction Program!\n";
      break;
    default:
      FixCinStream("Invalid input, please try again.\n");
    }
  } while (choice != QUIT);
}
/*******************************************************/
int Fraction::numFractions = 0;
Fraction::Fraction() { numFractions++; }
Fraction::Fraction(int wholeNumber) {
  setFraction(0, wholeNumber, DEFAULT_DENOMINATOR);
  numFractions++;
}
Fraction::Fraction(int newNumerator, int newDenominator) {
  setFraction(0, newNumerator, newDenominator);
  numFractions++;
}
Fraction::Fraction(int wholeNumber, int newNumerator, int newDenominator) {
  setFraction(wholeNumber, newNumerator, newDenominator);
  numFractions++;
}
Fraction::Fraction(const Fraction &other) {
  setFraction(0, other.numerator, other.denominator);
  numFractions++;
}
Fraction::~Fraction() {
  numerator = 0;
  denominator = 1;
  numFractions--;
}
void Fraction::setNumerator(int newNumerator) {
  setFraction(0, newNumerator, denominator);
}
void Fraction::setDenominator(int newDenominator) {
  setFraction(0, numerator, newDenominator);
}
void Fraction::setFraction(int wholeNumber) {
  setFraction(0, wholeNumber, DEFAULT_DENOMINATOR);
}
void Fraction::setFraction(int newNumerator, int newDenominator) {
  setFraction(0, newNumerator, newDenominator);
}
void Fraction::setFraction(const Fraction &copyFraction) {
  setFraction(copyFraction.numerator, copyFraction.denominator);
}
void Fraction::setFraction(int wholeNumber, int newNumerator,
                           int newDenominator) {
  try {
    if (newDenominator == 0) {
      throw FractionException("Denominator cannot be zero");
    }
    if (newNumerator == 0) {
      throw FractionException("Numerator cannot be zero");
    }
    if (wholeNumber < 0 || newNumerator < 0 || newDenominator < 0) {
      throw FractionException("Negative values not allowed");
    }
    if (wholeNumber > 0 && newNumerator > newDenominator) {
      throw FractionException("Invalid mixed number, numerator cannot be "
                              "greater than denominator in mixed numbers");
    }
    numerator = wholeNumber * newDenominator + newNumerator;
    denominator = newDenominator;
  } catch (FractionException &e) {
    e.PrintMessage();
  } catch (...) {
    cout << "Unknown exception occured." << endl;
  }
}
string Fraction::toString() const {
  stringstream ss;
  if (numerator > denominator) {
    ss << numerator / denominator << " ";
    ;
  }
  ss << numerator % denominator << "/" << denominator;
  return ss.str();
}
void Fraction::print() const { cout << toString(); }
int Fraction::getNumFractions() { return numFractions; }

FractionException::FractionException(string newMessage) {
  message = newMessage;
}
void FractionException::PrintMessage() const {
  cout << message << "\n"
       << "Values are restet to original or default" << endl;
}
FractionException::~FractionException() { message = ""; }

void FixCinStream(string errorMsg) {
  cout << errorMsg << endl;
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void CreateTable() {
  int denominator = GetDenominator();
  Fraction product, **ppTable = nullptr;

  try {
    CreateTable(denominator, ppTable);
    SetTable(denominator, ppTable);
    PrintTable(denominator, ppTable);
  } catch (bad_alloc &e) {
    cout << "Memory allocation failed" << endl;
  } catch (...) {
    cout << "Unknown exception occured." << endl;
  }

  DeleteTable(denominator, ppTable);
}

void CreateTable(int denominator, Fraction** &ppTable){
  if (denominator < 0) {
    
  }
  ppTable = new Fraction *[denominator] { nullptr };
  for (int i = 0; i < denominator; i++) {
    ppTable[i] = new Fraction[denominator];
  }
}

void SetTable (int denominator, Fraction** &ppTable){
  for (int i = 1; i < denominator; i++) {
    ppTable[0][i].setFraction(i, denominator);
    ppTable[i][0].setFraction(i, denominator);
    for (int j = 1; j < denominator; j++) {
      ppTable[i][j].setFraction(i * j, denominator * denominator);
    }
  }
}

void PrintTable(int denominator, Fraction** ppTable){
  cout << right << setw(COLLUMN_SIZE) << " ";
     for (int j = 1; j < denominator; j++){
        cout << setw(COLLUMN_SIZE) << ppTable [0][j].toString();
      }
      cout << endl;
  for (int i = 1; i < denominator; i++) {
    for (int j = 0; j < denominator; j++) {
      cout << setw(COLLUMN_SIZE) << ppTable[i][j].toString();
    }
    cout << endl;
  }
  cout << endl;
}

void DeleteTable (int denominator, Fraction** &ppTable){
  if (ppTable != nullptr) {
    for (int i = 0; i < denominator; i++){
      {
        if(ppTable[i]!=nullptr){
            delete[] ppTable[i];
          }
      }
    delete[] ppTable;
    ppTable = nullptr;
    }
  }
}

int GetDenominator() {
  int denominator;
  bool validInput = false;
  do {
    cout << "Please type what you would like the denominator to be: ";
    cin >> denominator;
    if (!cin) {
      FixCinStream("Invalid input, please try again.");
    } else if (denominator == 0) {
      cout << "Denominator cannot be zero" << endl;
    } else {
      validInput = true;
    }
  } while (!validInput);
  return denominator;
}

/*************************************************************************
//TEST:
Welcome to the Multiplication table Program
Please choose an option:
1- Create a multiplication table
2- Quit
1
Please type what you would like the denominator to be: 5
           1/5    2/5    3/5    4/5
    1/5   1/25   2/25   3/25   4/25
    2/5   2/25   4/25   6/25   8/25
    3/5   3/25   6/25   9/25  12/25
    4/5   4/25   8/25  12/25  16/25

Please choose an option:
1- Create a multiplication table
2- Quit
1
Please type what you would like the denominator to be: 8
           1/8    2/8    3/8    4/8    5/8    6/8    7/8
    1/8   1/64   2/64   3/64   4/64   5/64   6/64   7/64
    2/8   2/64   4/64   6/64   8/64  10/64  12/64  14/64
    3/8   3/64   6/64   9/64  12/64  15/64  18/64  21/64
    4/8   4/64   8/64  12/64  16/64  20/64  24/64  28/64
    5/8   5/64  10/64  15/64  20/64  25/64  30/64  35/64
    6/8   6/64  12/64  18/64  24/64  30/64  36/64  42/64
    7/8   7/64  14/64  21/64  28/64  35/64  42/64  49/64

Please choose an option:
1- Create a multiplication table
2- Quit
5
Invalid input, please try again.

Please choose an option:
1- Create a multiplication table
2- Quit
fwws
Invalid input, please try again.

Please choose an option:
1- Create a multiplication table
2- Quit
1
Please type what you would like the denominator to be: 6
           1/6    2/6    3/6    4/6    5/6
    1/6   1/36   2/36   3/36   4/36   5/36
    2/6   2/36   4/36   6/36   8/36  10/36
    3/6   3/36   6/36   9/36  12/36  15/36
    4/6   4/36   8/36  12/36  16/36  20/36
    5/6   5/36  10/36  15/36  20/36  25/36

Please choose an option:
1- Create a multiplication table
2- Quit
2
Thank you for using the Fraction Program!

*/