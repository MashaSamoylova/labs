#include "boolean_vector.h"
#include <cstring>
#include <iostream>
typedef unsigned int  base;
using namespace std;

class Bool: public BooleanVector{
  private:
    base* mass;
    int length;

  public:
      Bool();
      Bool(int);
      Bool(const char*);
      ~Bool();
      Bool(const Bool&);

      virtual void copy(const BooleanVector * const source);
      virtual void Resize(const int &newLength);
      virtual int GetLength() const;
      virtual void SetOne(const int &position);
      virtual void SetZero(const int &position);
      virtual void SetValue(const int &position, const int &value);
      virtual void SetElementValue(const int &position, const int &value);
      virtual int GetValue(const int &position) const;
      virtual int GetElementValue(const int &position) const;
      virtual void Conjunction(const BooleanVector * const operand, BooleanVector *result) const;
      virtual void Disjunction(const BooleanVector * const operand, BooleanVector *result) const;
      virtual void Xor(const BooleanVector * const operand, BooleanVector *result) const;
      virtual void Inversion(BooleanVector *result) const;
      virtual bool IsEqual(const BooleanVector * const operand) const;
      virtual bool IsNotEqual(const BooleanVector * const operand) const;
      virtual void LeftShift(const int &count, BooleanVector *result) const;
      virtual void RightShift(const int &count, BooleanVector *result) const;
      virtual void LeftCycleShift(const int &count, BooleanVector *result) const;
      virtual void RightCycleShift(const int &count, BooleanVector *result) const;
      friend ostream& operator << (ostream &out, const BooleanVector * const source);
      friend istream& operator >> (istream &in, BooleanVector *destination);
      virtual void ReadFromString(const char * const source, const int &sourceLength);
	  virtual void DeleteBit(const int &position, BooleanVector * cup);
    };
