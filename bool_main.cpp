#include "bool.h"
#include <vector>

using namespace BooleanVectorErrors;
using namespace std;

void top(Bool* array_of_strings, int n, vector <int> result) {
	int clm = 0; 
	int str = 0;
	vector <int> cup;
	while(result.size() < n){
		cout << "cup: " << cup.size() << endl;
		for(clm = 0; clm < n; clm++) {
			for(str = 0; str < n; str++){
				if(array_of_strings[str].GetValue(clm)){ //если в столбце, его бросаем и идем ДАЛЬШЕ
					cout << "daaaaa" << endl;
					break;
				}
			
				if(str = n){//found zero-column
					cout << "n= " << n << endl << "clm = " << clm  << endl;
					cup.push_back(clm); //иначе записываем в промеж вектор, чтобы потом удалить стороки
				}
			} 
		}
		vector <int> :: iterator ld;
		cout << "cup.size= " << cup.size() << endl;
		ld = cup.begin();
		while(ld != cup.end()){ //обнуляем строки(шаг2)
			cout << "raz " << endl;
			for(int i = 0; i < n; i++) {
				array_of_strings[(*ld)].SetZero(i);
			}
			for(int i = 0; i < n; i++){ //удаляем столбец
				array_of_strings[i].SetOne(*ld);
			}
			result.push_back(*ld); // записываем в решение
			ld++;
		}
		cup.clear();
		for(int i = 0; i < n; i++) {
			cout << &array_of_strings[i];
		}
	}
	
	vector <int> :: iterator for_show;
	for_show = result.begin();
	cout << result.size() << endl;
	while(for_show != result.end()){
		cout << (*for_show) << " ";
		for_show++;
	}
	cout << endl;
}
int main(){
  try{

	Bool* array_of_strings;
	int n;
	cout << "input n:" << endl;
	cin >> n;
	array_of_strings = new Bool[n];
	for(int i=0; i<n; i++){
		cin >> &array_of_strings[i];
	}

/*	for(int i=0; i<n; i++){
		cout << &(array_of_strings[i]);
	}*/

	vector <int> result;
	top(array_of_strings, n, result); 

/*	Bool example;
	Bool cup;
	cin >> &example;
	example.DeleteBit(3, &cup);
	cout << &example;*/
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
