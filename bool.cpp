#include "bool.h"
using namespace BooleanVectorErrors;
typedef unsigned int  base;

Bool :: Bool(){
	mass = new base[2];
	length = sizeof(base)*8*2;
	for(int i=0; i<length/(sizeof(base)*8); i++){
		mass[i] = 0;
	}
}

Bool :: Bool(int len){
	length = len;
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	mass = new base[n];
	for(int i=0; i<n; i++){
		mass[i] = 0;
	}
}

Bool :: Bool(const char* string_bit){
	length = strlen(string_bit);
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	mass =  new base[n];
	for(int i=0; i<n; i++){
		mass[i]=0;
	}
	
	for (int i=0, k=(sizeof(base)*8-1), block=0; string_bit[i]; i++){
		if(k<0){
			k=(sizeof(base)*8-1);
			block+=1;
		}
		if(string_bit[i]== '1'){
			mass[block]<<k | 1;
		}
	}
}

Bool :: ~Bool(){
  if(mass)
    delete [] mass;
}

Bool :: Bool(const Bool& old_b){
	cout << "работает конструктор копирования" << endl;
	length = old_b.length;
	int n  = (length/(sizeof(base)*8)) + !!(length%(sizeof(base)*8));
	mass = new base[n];
	for (int i=0; i<n; i++){
		mass[i] = old_b.mass[i];
	}
}

//copy object
void Bool :: copy(const BooleanVector* const source){
	int n = source -> GetLength()/(sizeof(base)*8) + !!(source -> GetLength()%(sizeof(base)*8));
	if(source -> GetLength() > length){
		if(mass){
			delete [] mass;
		}
		mass = new base[n];
	}
	length = source -> GetLength();
	for(int i=0; i<n; i++){
		this -> SetElementValue(i,source -> GetElementValue(i));
	}
}

void Bool :: Resize(const int &newLength){
	int n  = length/(sizeof(base)*8)  + !!(length%(sizeof(base)*8));
	if (newLength > length){
		if (mass){
			delete [] mass;
		}
		mass = new base[n];
	}
	length = newLength;
	for(int i=0; i<n; i++){
		this ->SetElementValue(i, 0);
	}
}

int Bool :: GetLength() const{
	return length;
}

void Bool :: SetOne(const int &position){
	if(position > length) throw INCORRECT_POSITION;
	this -> SetValue(position, 1);
}

void Bool :: SetZero(const int &position){
	if(position > length) throw INCORRECT_POSITION;
	this -> SetValue(position, 0);
}

void  Bool :: SetValue(const int &position, const int &value){
	if(position > length) throw INCORRECT_POSITION;
	if(value != 0 && value != 1) throw  NON_BOOLEAN_VALUE;
	int block = position/(sizeof(base)*8);
//	int i = sizeof(base)*8 - position % (sizeof(base)*8);
	int i = position%(sizeof(base)*8);
	if(value){
		this -> SetElementValue(block, this -> GetElementValue(block) | (1 << i));
	}
	else{
		this -> SetElementValue(block, this -> GetElementValue(block) & ~(1 << i));
	}
}

//set element
void Bool :: SetElementValue(const int &position, const int &value){
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	if (position > n) throw INCORRECT_POSITION;
	mass[position] = value;
}

int Bool :: GetValue(const int &position) const{
	if(position > length) throw INCORRECT_POSITION;
	int block = position/(sizeof(base)*8);
	//int i = sizeof(base)*8 - position % (sizeof(base)*8);
	int i = position%(sizeof(base)*8);
	if(this -> GetElementValue(block) & 1<<i){
		return 1;
	}
	else return 0;
}

//returns block of array
int Bool :: GetElementValue(const int &position) const{
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	if (position > n) throw INCORRECT_POSITION;
	return mass[position];
}

void Bool :: Conjunction(const BooleanVector * const operand, BooleanVector *result) const{
	if (length != operand -> GetLength() || length != result -> GetLength()) throw INCORRECT_LENGTH;
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	for (int i=0; i<n; i++){
		result -> SetElementValue(i, this -> GetElementValue(i) & operand -> GetElementValue(i));
	}
}

void Bool :: Disjunction(const BooleanVector * const operand, BooleanVector *result) const{
	if (length != operand -> GetLength() || length != result -> GetLength()) throw INCORRECT_LENGTH;
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	for (int i=0; i<n; i++){
		result -> SetElementValue(i, this -> GetElementValue(i) | operand -> GetElementValue(i));
	}
}

void Bool :: Xor(const BooleanVector * const operand, BooleanVector *result) const{
	if (length != operand -> GetLength() || length != result -> GetLength()) throw INCORRECT_LENGTH;
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	for (int i=0; i<n; i++){
		result -> SetElementValue(i, this -> GetElementValue(i) ^ operand -> GetElementValue(i));
	}
}

void Bool :: Inversion(BooleanVector *result) const{
	if (length != result -> GetLength()) throw INCORRECT_LENGTH;
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	for (int i=0; i<n; i++){
		result -> SetElementValue(i, ~(this -> GetElementValue(i)));
	}
}

bool Bool :: IsEqual(const BooleanVector * const operand) const{
	if (this -> GetLength() != operand -> GetLength()){
		return false;
	}
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	for(int i=0; i<n ; i++){
		if(this -> GetElementValue(i) != operand -> GetElementValue(i)){
			return false;
      }
	}
	return true;
}

bool Bool :: IsNotEqual(const BooleanVector * const operand) const{
	if (this -> GetLength() != operand -> GetLength()){
		return true;
	}
	int n = length/(sizeof(base)*8) + !!(length%(sizeof(base)*8));
	for(int i = 0; i<n ; i++){
		if(this -> GetElementValue(i) != operand -> GetElementValue(i)){
			return true;
		}
	}
	return false;
}

void Bool :: LeftShift(const int &count, BooleanVector *result) const{
	if(count > this -> GetLength()) throw INCORRECT_SHIFT_VALUE;
	result -> Resize(this -> GetLength());
	int len = this -> GetLength(); 
	for(int i = 0; i < count; i++){
		result -> SetValue(i, 0);
	}
	for(int i= count; i < len; i++){
		result -> SetValue(i, this -> GetValue(i-count)); 
	}
}

void Bool :: RightShift(const int &count, BooleanVector *result) const{
	if(count > this-> GetLength()) throw INCORRECT_SHIFT_VALUE;
	result -> Resize(this -> GetLength());
	int len = this -> GetLength();
	for(int i=len-1; i > len-count; i--){
		result -> SetValue(i,0);
	}
	for(int i=len-count-1; i >=0; i--){
		result -> SetValue(i, this -> GetValue(i+count));
	}
}

void Bool :: LeftCycleShift(const int &count, BooleanVector *result) const{
	result -> Resize(this -> GetLength());
	int new_count_of_shift = count % this -> GetLength();
	int len = this -> GetLength();
	for(int i=0; i < new_count_of_shift; i++){
		result -> SetValue(i, this -> GetValue(i));
	}
	for(int i=new_count_of_shift; i<len; i++){
		result -> SetValue(i, this -> GetValue(i-new_count_of_shift));
	}
}

void Bool :: RightCycleShift(const int &count, BooleanVector *result) const{
	result -> Resize(this -> GetLength());
	int new_count_of_shift = count % this -> GetLength();
	int len  = this -> GetLength();
	for(int i=len-1; i > len - new_count_of_shift; i--){
		result -> SetValue(i, this -> GetValue(i));
	}
	for(int i=len - new_count_of_shift -1; i >= 0; i--){
		result -> SetValue(i,this -> GetValue(i+new_count_of_shift));
	}
}

ostream& operator << (ostream &out, const BooleanVector * const source){
	int n = source -> GetLength();
	cout << "n = " << n << endl;
	for (int i = n-1; i >= 0; i--){
		out << source -> GetValue(i);
	}
	out << endl;
	return out;
}

istream& operator >> (istream &in, BooleanVector *destination) {
	int n;
	char* string_for_vector;
	cout << "Input length:" << endl;
	in >> n;
	if (n > destination -> GetLength()) throw INCORRECT_LENGTH;
	string_for_vector = new char[n];
	cout << "Input vector:" << endl;
	in >> string_for_vector;
	destination -> Resize(n);
	destination -> ReadFromString(string_for_vector, n);
	if(string_for_vector) {
		delete [] string_for_vector;
	}
}

void Bool :: ReadFromString(const char * const source, const int &sourceLength) {
	for(int i = 0, k = 0; source[k] && i < sourceLength; i++,k++){
		switch(source[k]){
			case '1':
				SetValue(sourceLength-i-1, 1);
				continue;
			case '0':
				SetValue(sourceLength-i-1, 0);
				continue;
			default:
				throw NON_BOOLEAN_VALUE;
				return;
      }
	}
}
