/* ReadingAndWriting.cpp
This program reads the file created by the previous program, displays the
entered data on the menu and lets the user type in the price
of the food and total. It will them calculate the bill and
display a time and date when created
16/04/2015
*/

#include<string>
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
using std::right;

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <sstream>
using std::stringstream;

#include <ctime>

class List {
    private:
    string _identification;
    string _category;
    string _itemDescription;
    string _price;
    string _quantity;
    string _total;
    string _newprice;
    string _VAT;
    public:
    List();
    List(string id, string category, string itemDescription, string price);
    List(string id, string quantity, string price, string total, string VAT );
    string toString();
	void display();
    void Bill();
};
class ListItem {
    private:
    int _identification;
    string _price;
    vector<List> _items;
    vector<List> _itemSlot;
    public:
    void displayAll();
    void ListBill();
    void getFile();
    void showMenu();
    void StopProgram();
};
class Menu {
    private:
    ListItem _Li;
    string _file;
    public:
    Menu();
    bool select();
};

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}


//***************************************************************
// Displaying and string data to the document
//****************************************************************
List::List(string id, string itemDescription, string category, string price)
:_identification(id), _itemDescription(itemDescription), _category(category), _price(price){      }
List::List(string id, string quantity, string price, string total, string VAT)
:_identification(id), _quantity(quantity), _price(price), _total(total), _VAT(VAT) { }
string List::toString(){
    return string(_identification + ":" + _quantity +  ":" + _price + ":" + _total + ":" +  _VAT);
}
void List::display(){
    cout << _identification << " " << left << _category << " " << left << _itemDescription << " " << left << _price <<setw(2) << left << endl;
}
void List::Bill(){
    cout << _identification << " " << _quantity << " " << _price << " " <<  _total << " " << _VAT;
}
void ListItem::displayAll(){
    for(size_t i = 0; i < _items.size(); ++i){
        _items[i].display();
    }
    cout << endl;
}
//***************************************************************
// Read file
//****************************************************************
void ListItem::getFile(){
    //Opens the file and reads the file
    char ch;
    while(ch = 'y')
    {
        cout << "Enter File name: ";
        system("color 1f");
        string name = "menu";
        cin >> name;
        name += ".txt";
        ifstream fin(name.c_str());
        if(fin){
            ch = 'n';
            while(!fin.eof()){
                string IdNo;
                getline(fin,  IdNo, ':'); // Finds "IDNO://
                string category;
                getline(fin, category, ':');
                string itemDescription;
                getline(fin, itemDescription, ';');
                string price;
                getline(fin, price);
                if(!fin.eof()){
                    _items.push_back(List(IdNo, category, itemDescription, price));
                }
            }
        }
        if (ch = 'n')
        {
            break;
        }
    }
}
//***************************************************************
// Allows other functions to link up with each other!!
//****************************************************************
Menu::Menu(){
    select();
}
//***************************************************************
// Entering the details
//****************************************************************
void ListItem::showMenu(){

    
	system ("cls");
    int ch, quantity;
    double price,total, VAT;
    char choice;
	char buffer[80];
	
	string _quantity, _total, _VAT, _ch;
  

    // User enters data
	
	cout<<"\nn============================";
    cout<<"\n PLACE YOUR ORDER";
    cout<<"\n============================";
    cout << "\nEnter the ID, Quantiy and Price" <<endl;
    while((choice = 'y') || (choice = 'Y'))
    {
        cout << "\nItem ID: ";
	   	cin >> ch;
        cout << "\nQuantity; ";
        cin >> quantity; 
        cout << "\nprice: ";
        cin >> price;
        
		total = price * quantity;
        VAT = total * 1.2;
        
		cout << "\ntotal: " << total << endl;
        cout << "\nVAT: " <<VAT << endl;
      
       
	    stringstream  stream;
  	    stream << quantity;   //String Streams, passes data into the attribute in the class which then gets stored in a vector
  	    stream >> _quantity;
  	    stringstream stream2;
  	    stream2 << price;
  	    stream2 >> _price;
  	    stringstream  stream3;
  	    stream3 << total;
  	    stream3 >> _total;
 	    stringstream  stream4;
    	stream4 << VAT;
    	stream4 >> _VAT;
    	stringstream  stream5;
    	stream5 << ch;
    	stream5 >> _ch;
       
	    cout << "\nCurrent time: ";
    	cout << currentDateTime() << std::endl;
    	getchar();
        _itemSlot.push_back(List(_ch, _quantity, _price, _total, _VAT) );
	   cout << "\n To continue press Y, else to quit press N " << endl;
        cin >> choice;
		cin.ignore();
	    
        if(choice == 'n' || choice == 'N')
        {
            system("cls");
			break;
        }
    }
}
//********************************************************************************************************
// Gets the information he user enters which is then sent to endMenu when the close it and it saves the file
//**********************************************************************************************************
void ListItem::ListBill(){
    cout << "ItemID" << " Quantity" << " Price" << " total" << "VAT" << endl;
    for(size_t i = 0; i < _itemSlot.size(); ++i){
        _itemSlot[i].Bill();
    }
    cout <<endl;
}
void ListItem::StopProgram(){
	system("color 2f");
    string _bill = "Transaction";  // For some unknown strange reason, it saves the file as 5.txt
    cout << right <<  "Bill has been saved " <<endl;
    _bill += ".txt";
    ofstream fout(_bill.c_str());
    for(size_t i = 0; i < _itemSlot.size(); ++i) {
        fout << i+1 << " : " << _itemSlot[i].toString() << endl;
    }
    fout.close();
    cout << endl;
}
bool Menu::select(){
    system("color 1f");
	cout << "Menu====\n" << endl;
    cout << "(1) Read a file \n(2) Add a "
    "bill \n(3)  Display Bill\n(4) Display all data\n(5) Save file and leave  the Program\n" << endl;
  
	cout << "Select: ";
    char ch;
    cin >> ch;
    cin.ignore(256, '\n');
    cout << endl;
	    switch(ch)
		do
		{
        case '1' : _Li.getFile();
        return true;
        case '2' : _Li.showMenu();
        return true;
        case '3' : _Li.ListBill();
        return true;
        case '4': _Li.displayAll();
        return true;
        case '5': _Li.StopProgram();
        return false;
		default : cout << "Enter an '1', '2' ,'3', '4' or '5' without"
        " the qoutes.n";
        return true;
		}while(ch!=1 || ch !=2 || ch != 3 || ch !=4 || ch!=5);
    
}
int main(){
    //all of the functions are run through menu4
    Menu menu;
    while(menu.select()) {
        // empty body
    }
    return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
