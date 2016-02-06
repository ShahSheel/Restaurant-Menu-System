
// WriteToFile.cpp 
// creating a menu for headoffice
// 27/03/2015
// Sheel SHah

#include <string>
using std::string;
using std::getline;

#include <vector>
using std::vector;


#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <iomanip>
using std::setw;
using std::left;

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <sstream>
using std::stringstream;



////////////////////////////////////////////////////////
class category{
	private:
	string _starter;
	string _maincourse;
	string _pudding;
	string _drink;
	string _itemDescription;
	string _price;
	public:
	category ();
		 const string * starter
        ,const string * maincourse
       , const string * pudding
       , const string * drink
       , const string * itemDescription
       , const string * price
       )
       : _starter(starter)
       , _maincourse(maincourse)
       , _pudding(pudding)
       , _drink(drink)
       , _itemDescription(itemDescription)
       , _price(price)
	category(string starter, string maincourse, string pudding, string drinks);
	void display();
	string tostring();
	

	
};

////////////////////////////////////////////////////////
class orderList{
	
	private:
	vector<category> _ca;
	//string _itemDescription;
	float _item_price;
	public:
	orderList();
	void addCategory();
	void displayall();
	void stopProgram();
//	  void writeFile();

};
////////////////////////////////////////////////////////
class Menu{
	
    private:
	orderList _ol;
	public:
	Menu();
	bool select();
};


////////////////////////////////////////////////////////

// Constructors
 
 category::category(){
 
 
 
  
 


 cout << "Menu\n====\n" << endl;
 cout << "(1) Starter\n(2) Main Course "
 "items\n(3) Pudding.\n(4)Drink\n(5) End program\n" << endl;
 cout << "Select: ";
 char ch;
 cin >> ch;
 cin.ignore(100, '\n');
 cout << endl;

switch(ch) {
case '1': 
			cout << "Starter";
			cout << "\nItem Description: ";
			getline(cin,_itemDescription);
			cout << "\nPrice: ";
			getline(cin,_price);
			
break; 
case '2': 
		 	cout << "Main Course";;
			cout << "\nItem Description: ";
			getline(cin,_itemDescription);
			cout << "\nPrice: ";
			getline(cin,_price);
break; 
case '3': 	
			cout << "Pudding";
			cout << "\nItem Description: ";
			getline(cin,_itemDescription);
			cout << "Price: ";
			getline(cin,_price);

break;
case '4': 
			cout << "Drink";
			cout << "\nItem Description: ";
			getline(cin,_itemDescription);
			cout << "\nPrice: ";
			getline(cin,_price);
}
	 

 }
  category::category(string starter, string maincourse, string pudding, string drink)
  : _starter(starter),_maincourse(maincourse),_pudding(pudding),_drink(drink){  }
  
 
  void category::display(){
  	
  	cout << setw(15) << left << _starter << _maincourse << _pudding << _drink << endl;

  }
  
  string category::tostring() {
	string record = _starter + ":" +  _maincourse + ":" + _pudding + ":" + _drink + ":"  + _itemDescription + ":"+ _price;

	return string (record);
}

  orderList::orderList(){
  	
  	// No action required
  }

  void orderList::addCategory(){
  	
  	_ca.push_back(category());
  	cout << endl;
  }

  void orderList::displayall(){

	for(size_t i = 0; i < _ca.size(); ++i){
  		_ca[i].display();
  	}
  }

 void orderList::stopProgram(){
 	ofstream fout("testy.txt");
 	for(size_t i=0; i< _ca.size(); ++i){
 		fout << _ca[i].tostring() << endl;
 	}

 	fout.close();
 	cout << endl;
 }
 
// orderList::writeFile(){
 	
 	// Not needed yet?
// }

Menu::Menu(){

// no action requred yet
}

bool Menu::select(){
	
 cout << "Menu\n====\n" << endl;
 cout << "(1) Add an item\n(2) Display all stored "
 "items\n(3) stop the program.\n" << endl;
 cout << "Select: ";
 char ch;
 cin >> ch;
 cin.ignore(100, '\n');
 cout << endl;
 switch(ch) {
 case '1' : _ol.addCategory();
 return true;
 case '2' : _ol.displayall();
 return true;
 case '3' : _ol.stopProgram();
 return false;
 default : cout << "Enter an '1', '2' or '3' without"
 " the qoutes.\n";
 return true;
 }
}
////////////////////////////////////////////////////////////
int main() {
 Menu Menu;
 while(Menu.select()) {
 // empty body
 }
 return 0;
}

