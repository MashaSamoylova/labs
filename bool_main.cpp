#include "bool.h"
using namespace BooleanVectorErrors;
int main(){
  try{
    Bool my_booleanVector;
  //  cout << &my_booleanVector;
    cin >> &my_booleanVector;
    cout << &my_booleanVector;
    Bool second_vector;
    cin >> &second_vector;
    cout << &second_vector;
  //  Bool result_vector;
    //cin >> &result_vector;
	my_booleanVector.RightCycleShift(3, &second_vector);
  //  my_booleanVector.RightCycleShift(3, &second_vector);
    cout << &second_vector;
    return 0;
  }
  catch(BooleanVectorError my_error){
    switch(my_error){
      case MEMORY_ERROR: {
        cout<<"MEMORY_ERROR"<<endl;
        break;
      }
      case 2:{
        cout<<"INCORRECT_LENGTH"<<endl;
        break;
      }
      case 3:{
        cout<<"INCORRECT_POSITION"<<endl;
        break;
      }
      case 4:{
        cout<<"NULL_OPERAND"<<endl;
        break;
      }
      case 5:{
        cout<<"NON_BOOLEAN_VALUE"<<endl;
        break;
      }
      case 6:{
        cout<<"INCORRECT_SHIFT_VALUE"<<endl;
        break;
      }
    }
  }
}
