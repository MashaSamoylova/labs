#include "bool.h"
#include <list>

using namespace BooleanVectorErrors;
using namespace std;

void top(list <Bool> array_of_columns, int n){
	int* result = new int[n];
	int index_of_result = 0;
	int clm = 0;
	list <Bool> :: iterator clm_iterator;
	clm_iterator = array_of_columns.begin();
	while(clm < array_of_columns.size()) { //ищем столбец, который не содержит 1
		int s = 0;
		for(s; s < n; s++){
			if((*clm_iterator).GetValue(s))
				break;
		}
		if(s != n){
			clm++;
			continue;
		} //если нашли 1, то пошли на след столбец
			//иначе выписываем в решение
		result[index_of_result] = clm;
		index_of_result++;
		list <Bool> :: iterator i;
		i = array_of_columns.begin();
		while(i != array_of_columns.end()) { //обнуляем строки
			(*i).SetZero(s);
			i++;
		}
		array_of_columns.erase(clm_iterator);
		clm_iterator = array_of_columns.begin();
		clm = 0; //ничинаем заново
	}
}

int main(){
  try{

    //Bool my_booleanVector;
  //  cout << &my_booleanVector;
   // cin >> &my_booleanVector;
    //cout << &my_booleanVector;
    //Bool second_vector;
 //   cin >> &second_vector;
   // cout << &second_vector;
  //  Bool result_vector;
    //cin >> &result_vector;
	//my_booleanVector.RightCycleShift(3, &second_vector);
  //  my_booleanVector.RightCycleShift(3, &second_vector);
    //cout << &second_vector;

	list <Bool> array_of_columns;
	int n;
	cout << "input n:" << endl;
	cin >> n;
	for(int i=0; i<n; i++){
		Bool vector;
		cin >> &vector;
		array_of_columns.push_back(vector);
	}

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
