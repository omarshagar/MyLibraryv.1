#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <regex>
#include <windows.h>
#include <string.h>
#include <iterator>
#include <set>
#include <sstream>
#include<cmath>
using namespace std;
struct Date
{
	string  day;
	string  month;
	string  year;
};
//the struct that contains all book props
struct bookpropertis
{
	string name;
	string author;
	string nopage;
	string URL;
	string numberofsection;
	string puplisher;
	string category;
	Date date;
};
map<string, vector<string>>programpath;//contains all logic pathes witches in mapping();
map<string, bookpropertis>books;//contains all book props
//vector<string>categoryName;//this vector  will be used if we need store our category to add a new one
vector<string>element;//contains the elements inside each map in programpath map
string path = "/main";//the search key in programpath map
string command;//the input that user will inter
map<string, vector<int>>wordToBook;
map<string, set<string>> my_categ_map;
//
vector<string>searsh_word;
vector<string>searsh_book;
vector<pair<string, int>> sort1;
pair<string, int>pr;
//
map<string, map<string, vector<int>>> wordList;
map < string, bool>filter_book;
map < int, bool>filter_line;
map<string, set<string>>fvrt;
//
map<string, map<string, vector<int>>>::iterator found;
map<string, vector<int>> ::iterator found2;
vector<int > ::iterator found3;
vector<pair<string, int>>::iterator found4;
map < int, bool>::iterator itr;
map<string, set<string>>::iterator favptr;
//
//a function to change the cursor  x,y position
void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
//a function to compare two strings
int compareString(string s1, string s2)
{
	// returns a 2 (s2 is bigger )
	if ((s1.compare(s2)) < 0)
		return 2;

	// returns 3(they are equal)
	if ((s1.compare(s1)) == 0)
		return 3;
	//returns 1 s1 is bigger
	else
		return 1;

}
void pathelementsearch(string);//display all elements in the map of key of the path
bool pathelementsearch(string, string);//checks if the map of the map with the key of first string contains second string
void drawmain();//draws the console draw of my library
void mapping();//fill the map of programpath
void mainOfAddBook();//contains the options of addBook function
void printBookMenu();//contains the draw  of addBook function
void addBookContact(); //add new book prop and fill the books map
void listBookContact();//lists book props
void addDataToBookMap();//fills the books map from book.txt file
//bool check_category(string category);//checks if new category presents in the category.txt file
//void re_file();//clears category.txt and fill it again with the categoryName vector
bool read_category_from_file(string);
void write_category(void);
void read_category_book(string category, string name_book);
//void write_category_book(void);
void addWord(string, string);
void getDataToWordMap();//fills the word list map from word.txt
void mainofsearch();
void printmenuofsearch();
void nameofbook();
void authorofbook();
void nopageofbook();
void URL();
void numberofsection();
void puplisherofbook();
void wordSearch();
void word(string searsh);
void filter_one(void);
void filter_two(void);
void filter_one2(string one, string two);
void filter_two2(void);
void save(string book, int rerpitation);
bool isNumber(string);
void favbook(void);
void addfvrtbook(void);
void fvrtsearch(void);
void category(void);
int main() {
	mapping();
	/*map<string, map<string, vector<int>>>::iterator it;
	 map<string, vector<int>>::iterator itt;
	 vector<int>::iterator ittt;
	 for(it=wordList.begin();it!=wordList.end();it++)
	 {
		 cout<<it->first<<endl;
		 for(itt=it->second.begin();itt!=it->second.end();itt++)
		 {
			 cout<<itt->first<<endl;
			 for(ittt=itt->second.begin();ittt!=itt->second.end();ittt++)
			 {
				 cout<<*ittt<<" ";
			 }
			 cout<<endl;

		 }


	 }

	system("pause");*/
	//changing the color of consol
	system("color F8");
	addDataToBookMap();
	while (true)
	{
		//the key of searching is my map
		pathelementsearch(path);
		drawmain();
		gotoxy(2, 17);
		cout << path << ":#";
		cin >> command;//giiting the coomand from user
		system("cls");
		//exit program if user writes quit
		if (command == "quit")
			break;

		else if (command == "help")
		{
			gotoxy(6, 11);
			cout << "You are in this path :-" << path << endl;
			cout << "      If you want to return the previous page write return " << endl;
			cout << "      Very important note \" You should write words in the shown case \"" << endl;
		}
		else if (command == "return")
		{
			//cant return any more!!
			if (path == "/main")
			{
				gotoxy(6, 11);
				cout << "you are in the main window!!" << endl;
			}
			else
			{
				//by removing last /optionName it will changes the key of searching by the last window
				int locofend = path.rfind("/");
				string newpath = path.substr(0, locofend);
				path = newpath;
				pathelementsearch(path);
			}
		}
		else if (path == "/main/add"&&command == "addBook")
		{
			mainOfAddBook();
			drawmain();
			system("cls");
		}
		else if (path == "/main/add"&&command == "addCategory")
		{
			string category_name;
			bool exist;
			drawmain();
			gotoxy(2, 17);
			cout << "Please Enter your category name :)";
			cin >> category_name;
			exist = read_category_from_file(category_name);
			if (exist)
			{
				gotoxy(2, 15);
				cout << "this categry exist before!" << endl;;
			}
			system("pause");
			system("cls");
		}
		else  if (path == "/main"&&command == "search")
		{
			mainofsearch();

			system("CLS");
		}
		else if (path == "/main"&&command == "favourite") {
			favbook();
			system("cls");
		}
		//by printing any another command it may be any anathor option or path
		else if (path == "/main"&&command == "categories")
		{
			category();
			system("pause");
			system("cls");
		}
		else
		{
			if (pathelementsearch(path, command))
				path.append("/" + command);

			pathelementsearch(path);
		}
	}


	return 0;
}
void mapping() {
	getDataToWordMap();
	//read_category_from_file();
	programpath["/main"] = { "search","categories","favourite","add" };
	programpath["/main/search"] = { "bySentence","byAuthor","byName","byDate" };
	programpath["/main/categories"];
	programpath["/main/favorites"];
	programpath["/main/add"] = { "addBook","addCategory" };
}
void pathelementsearch(string keypath) {
	map<string, vector<string>>::iterator it;
	it = programpath.find(keypath);
	//if i found the keypath
	if (it != programpath.end())
	{
		//coping the location of the elements of that key
		element = programpath.find(keypath)->second;
		gotoxy(6, 10);

		cout << "options in this window:" << endl;
		//printing the elements
		for (int i = 0; i < element.size(); i++)
		{
			gotoxy(6, 11 + i);

			cout << "     " << i + 1 << "-" << element[i] << endl;

		}
	}
}
//to make overload
bool pathelementsearch(string keypath, string myelement) {
	map<string, vector<string>>::iterator it;
	it = programpath.find(keypath);
	bool check = false;
	if (it != programpath.end())
	{
		element = programpath.find(keypath)->second;

		for (int i = 0; i < element.size(); i++)
		{
			if (element[i] == myelement)
				check = true;
		}
	}
	return check;
}
void drawmain() {
	//printing all borders and the mylibrary word
	gotoxy(0, 0);
	for (int i = 0; i < 100; i++)
		cout << "~";
	gotoxy(0, 35);
	for (int i = 0; i < 100; i++)
		cout << "~";
	gotoxy(5, 1);
	cout << "          _  _        _      _  _                        " << endl;
	cout << "               |  \\/  |       | |    (_)| |                              " << endl;
	cout << "               | .  . | _   _ | |     _ | |__   _ _   _ _  _ __  _   _ " << endl;
	cout << "               | |\\/| || | | || |    | || '_ \\ | '__| / _` || '__|| | | |" << endl;
	cout << "               | |  | || |_| || |____| || |_) || |   | (_| || |   | |_| |" << endl;
	cout << "               \\_|  |_/ \\__, |\\_____/|_||_.__/ |_|    \\__,_||_|    \\__, |" << endl;
	cout << "                         __/ |                                      __/ |" << endl;
	cout << "                        |___/                                      |___/ " << endl;
	gotoxy(0, 16);
	for (int i = 0; i < 100; i++)
		cout << "_";
	gotoxy(0, 18);
	for (int i = 0; i < 100; i++)
		cout << "_";

	for (int i = 0; i < 36; i++)
	{
		gotoxy(0, i);
		cout << "|";
		gotoxy(100, i);
		cout << "|";
	}

}
void mainOfAddBook() {
	system("cls");
	bool goodchoice = true;
	char choice;


	while (goodchoice != false)
	{

		printBookMenu();
		cin >> choice;
		switch (choice)
		{
			//add book
		case 'a':
		case 'A':
			addBookContact();
			break;
			//list book
		case 'l':
		case 'L':
			listBookContact();
			break;
			//quit addbook function
		case 'q':
		case 'Q':
			return;
			break;
		default:
			break;
		}
	}
	system("PAUSE");


}
void printBookMenu() {
	//printing and entering the options
	system("CLS");
	cout << "                              options                              " << endl << endl;
	cout << "|-----------------------------main menu---------------------------|" << "\n";
	cout << "|                             (a)dd content                       |" << "\n";
	cout << "|                             (l)ist content                      |" << "\n";
	cout << "|                             (q)uit                              |" << "\n";
	cout << "|-----------------------------------------------------------------|" << "\n";
	cout << endl << endl << "your choice #";

}
void addBookContact() {
	char save = '/0';
	bookpropertis prop;
	system("CLS");
	cin.ignore();
	string text;//2,17
	//drawing the borders and my library
	drawmain();
	for (int i = 2; i < 12; i += 2)
	{
		gotoxy(1, 18 + i);
		for (int ii = 0; ii < 99; ii++)
			cout << "_";
	}
	/*
	  !name;
	  @author;
	  category
	  $nopage;
	  %URL;
	  ^numberofsection;
	  #puplisher;
	 / date;*/
	 //taking the props of new book
	//bool checkNotRepeated = true;
	map<string, bookpropertis>::iterator it;
	gotoxy(2, 17);
	cout << "Enter the book name:";
	getline(cin, text);
	prop.name =/*'!'+*/text;
	it = books.find(prop.name);
	bool cont = true;
	//checking if book exist before and searching in books map
	if (it != books.end())///if  the book found
	{
		gotoxy(3, 15);
		cout << "this book is exist before !!";
		cont = false;
		system("pause");
	}
	//if i didnt found the book complete taking book props
	if (cont)
	{
		gotoxy(2, 19);
		cout << "enter the author :";
		getline(cin, text);
		prop.author = text;
		gotoxy(2, 21);
		cout << "enter the category :";
		getline(cin, text);
		prop.category = text;
		gotoxy(2, 23);
		cout << "enter the puplisher :";
		getline(cin, text);
		prop.puplisher = text;
		do {
			gotoxy(2, 25);
			cout << "enter the number of pages :";
			getline(cin, text);
			gotoxy(2, 25);
			if (!isNumber(text))cout << "                                                                                                ";
		} while (!isNumber(text));
		prop.nopage = text;
		gotoxy(2, 27);
		cout << "enter the URL of book :";
		getline(cin, text);
		prop.URL = text;
		do {
			gotoxy(2, 29);
			cout << "enter the number of chapters :";
			getline(cin, text);
			gotoxy(2, 29);
			if (!isNumber(text))cout << "                                                                                                    ";
		} while (!isNumber(text));
		prop.numberofsection = text;
		do {
			gotoxy(2, 31);
			cout << "Enter the date of puplishing (year-month-day):";
			cin >> text;
			if (!isNumber(text))
			{
				gotoxy(2, 31);

				cout << "                                                                                                                                                                        ";
				continue;
			}
			prop.date.year = text;
			cin >> text;
			if (!isNumber(text))
			{
				gotoxy(2, 31);
				cout << "                                                                                                                                                      ";
				continue;
			}
			prop.date.month = text;
			cin >> text;
			if (!isNumber(text))
			{
				gotoxy(2, 31);
				cout << "                                                                                                                                                         ";
				continue;
			}
			prop.date.day = text;
		} while (!isNumber(text));
		gotoxy(2, 33);
		cout << "save content(y - yes)?";
		cin >> save;
		//check if i want to save content or not
		if (save == 'y' || save == 'Y')
		{
			read_category_book(prop.category, prop.name);
			try
			{
				string c = "books\\"; //coping the book to books  directory
				c.append(prop.name);
				c.append(".txt");
				ifstream source(prop.URL, ios::binary);
				ofstream dest(c, ios::binary);
				dest << source.rdbuf();
				source.close();//puts the file binary to the distenation
				dest.close();//coping the book to books directory
				//inserting all data in books map
				books[prop.name] = prop;
				//clearing book file then inserting all map in it again
				map<string, bookpropertis>::iterator it;
				it = books.begin();
				ofstream datafile;
				datafile.open(("book.txt"), ios::out | ios::trunc);
				datafile.close();
				datafile.open(("book.txt"), ios::out);
				while (it != books.end())
				{
					datafile << it->second.name << "\n";
					datafile << it->second.author << "\n";
					datafile << it->second.puplisher << "\n";
					datafile << it->second.nopage << "\n";
					datafile << it->second.URL << "\n";
					datafile << it->second.numberofsection << "\n";
					datafile << it->second.date.day << "\n";
					datafile << it->second.date.month << "\n";
					datafile << it->second.date.year << "\n";
					it++;
				}
				datafile.close();
				addWord(c, prop.name);
				cout << endl << "content saved" << endl << endl;
				system("pause");
			}
			catch (exception ex)
			{
				cout << endl << "error save data to the file" << endl;
				system("PAUSE");

			}
		}
		else
		{
			system("cls");
		}
	}

}
void listBookContact() {
	system("CLS");

	map<string, bookpropertis>::iterator it;
	it = books.begin();
	while (it != books.end())
	{
		cout << it->first << endl;
		cout << it->second.author << " ";
		cout << it->second.puplisher << " ";
		cout << it->second.nopage << " ";
		cout << it->second.URL << " ";
		cout << it->second.numberofsection << " ";
		cout << it->second.date.day;
		cout << it->second.date.month;
		cout << it->second.date.year << endl;
		cout << endl;
		it++;
	}
	cout << endl;
	system("pause");
}
void addDataToBookMap() {
	ifstream file;
	file.open("book.txt");
	string txt[9];

	for (int i = 0; !file.eof(); i++)
	{
		getline(file, txt[i % 9]);
		if (i % 9 == 8)
		{

			books[txt[0]].name = txt[0];
			books[txt[0]].author = txt[1];
			books[txt[0]].puplisher = txt[2];
			books[txt[0]].nopage = txt[3];
			books[txt[0]].URL = txt[4];
			books[txt[0]].numberofsection = txt[5];
			books[txt[0]].date.day = txt[6];
			books[txt[0]].date.month = txt[7];
			books[txt[0]].date.year = txt[8];
		}
	}
	file.close();
}
//here we will check if the category exist or not
/*bool check_category(string category) {
	vector<string>store_vector2;
	string line;
	int found, mid, tamp = 0;
	bool b = 0;
	ifstream my_category;
	my_category.open("category.txt");
	while (getline(my_category, line))
	{
		store_vector2.push_back(line);
	}
	my_category.close();
	//here we search for the category
	int i = 0;

	while (i < store_vector2.size())
	{
		// if we found the category we will return to the main function which decleared in calltion
		line = store_vector2[i];
		if ((found = line.find(category)) != string::npos)
		{
			cout << "This category Already exists " << endl;
			system("pause");
			b = 1;
		}
		i++;
	}


	// but if didn't find it  we will put all category we have in the store vector
	if (b == 0)
	{
		int counter = 0;
		bool check = false;
		i = 0;
		categoryName.clear();
		while (i < store_vector2.size())
		{
			line = store_vector2[i];
			i++;
			categoryName.push_back(line);

			if (counter == 0 && (compareString(categoryName[0], category) == 3 || compareString(categoryName[0], category) == 1))
			{
				categoryName.push_back(category);
				counter++;
				swap(categoryName[0], categoryName[1]);
				check = 1;
			}
			else if (counter > 0)
			{
				if ((compareString(categoryName[counter], category) == 2 && compareString(categoryName[counter], category) == 1) || compareString(categoryName[counter], category) == 3)
				{
					categoryName.push_back(category);
					swap(categoryName[counter], categoryName[counter + 1]);
					counter++;
					check = 1;
				}
			}


			counter++;
		}
		if (check == 0)
			categoryName.push_back(category);


		// this function return all category inthe file
		re_file();
	}
	my_category.close();



	return b;
}
// this is the return function
void re_file() {
	ofstream my_category;
	my_category.open("category.txt");
	my_category.clear();
	for (int i = 0; i < categoryName.size(); i++)
	{

		my_category << categoryName[i] << endl;
	}
	my_category.close();
}*/
void addWord(string bookloc, string bookName) {

	vector<int>::iterator it;
	map<string, vector<int>> ::iterator itt;
	map<string, map<string, vector<int>>> ::iterator ittt;

	ifstream file;
	file.open(bookloc);
	int line = 0;
	string linee;
	string x;
	while (getline(file, linee)) {
		string subject = linee;
		std::regex re("\\w+");
		std::sregex_iterator next(subject.begin(), subject.end(), re);
		std::sregex_iterator ende;
		while (next != ende) {
			std::smatch match = *next;
			x = match.str();
			ittt = wordList.find(x);
			if (ittt != wordList.end())
			{
				itt = ittt->second.find(bookName);
				if (itt != ittt->second.end())
				{
					itt->second.push_back(line);
				}
				else
				{
					vector<int> a;
					a.push_back(line);
					ittt->second.insert(pair<string, vector<int>>(bookName, a));
				}
			}
			else
			{
				vector<int> a;
				a.push_back(line);
				map<string, vector<int>> aa;
				aa.insert(pair<string, vector<int>>(bookName, a));
				wordList.insert(pair<string, map<string, vector<int>>>(x, aa));
			}
			next++;
		}
		line++;
	}
	////////////////
	file.close();
	ofstream file2;
	file2.open("word.txt", ios::out | ios::trunc);
	file2.close();
	file2.open("word.txt");
	ittt = wordList.begin();
	while (ittt != wordList.end())
	{
		file2 << "---" << endl;
		file2 << ittt->first << endl;
		itt = ittt->second.begin();
		while (itt != ittt->second.end())
		{
			file2 << "----" << endl;
			file2 << itt->first << endl;
			it = itt->second.begin();
			while (it != itt->second.end())
			{
				file2 << *it << endl;
				it++;
			}
			itt++;
		}
		ittt++;
	}
	file2.close();
}
void getDataToWordMap() {
	string sign;
	string line;
	string book;
	string word;
	bool enter = false;
	map<string, vector<int>>book_line;
	vector<int>linev;
	ifstream file;
	file.open("word.txt");
	int i = 0;
	while (file >> sign)
	{
		i++;
	}
	int sizee = i;
	string * arr = new string[i + 1];
	file.close();
	file.open("word.txt");
	i = 0;
	while (getline(file, arr[i]))
	{
		//cout<<arr[i]<<endl;
		i++;

	}
	file.close();
	for (i = 0; i < sizee; i++)
	{
		if (arr[i] == "---")
		{
			i++;
			word = arr[i];
		}
		else if (arr[i] == "----")
		{
			i++;
			book = arr[i];
			i++;
			while (arr[i] != " "&&arr[i] != "---"&&arr[i] != "----")
			{
				// cout<<"g"<<endl;
				linev.push_back(std::stoi(arr[i]));
				i++;
				if (i == sizee)
				{
					book_line.insert(pair<string, vector<int>>(book, linev));
					wordList.insert(pair<string, map<string, vector<int>>>(word, book_line));
					break;

				}
			}
			if (arr[i] == "---")
			{
				book_line.insert(pair<string, vector<int>>(book, linev));
				wordList.insert(pair<string, map<string, vector<int>>>(word, book_line));
				book_line.clear();
				linev.clear();
				i--;
			}
			else if (arr[i] == "----")
			{
				book_line.insert(pair<string, vector<int>>(book, linev));
				linev.clear();
				i--;
			}
		}
	}

	delete[]arr;
	arr = NULL;
}
void mainofsearch() {
	bool check = true;
	char select;


	bookpropertis prop;


	while (check != false)
	{
		printmenuofsearch();
		cin >> select;
		switch (select)
		{
		case 'A':
		case 'a':
			nameofbook();
			break;
		case 'B':
		case 'b':
			authorofbook();
			break;
		case 'C':
		case 'c':
			nopageofbook();
			break;
		case 'D':
		case 'd':
			URL();
			break;
		case 'E':
		case 'e':
			numberofsection();
			break;
		case 'F':
		case 'f':
			puplisherofbook();
			break;
		case 'g':
		case 'G':
			wordSearch();
			break;
		case'r':
		case'R':
			check = false;
			break;
		default:
			printmenuofsearch();
			break;
		}
	}
	system("pause");
	system("CLS");
}
void printmenuofsearch() {
	system("CLS");
	cout << "                                 # ENTER THE METHOD OF SEARCH #                                      " << "\n" << "\n";
	cout << "*****************************************************************************************************" << "\n";
	cout << "|                                   (A)BY NAME OF BOOK                                              |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (B)BY AUTHOR                                                    |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (C)BY NUMBER OF PAGE                                            |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (D)BY URL OF BOOK                                               |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (E)BY NUMBER OF SECTION                                         |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (F)BY PUPLISHER OF BOOK                                         |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (G)BY WORD                                                      |" << "\n";
	cout << "|                                                                                                   |" << "\n";
	cout << "|                                   (R)RETURN                                                       |" << "\n";
	cout << "*****************************************************************************************************" << "\n";
	cout << "\n" << "\n";
	cout << "enter your select (A/B/C/D/E/F/G/R):";
}
void nameofbook() {

	system("CLS");
	drawmain();
	gotoxy(2, 17);
	cout << "enter name of book :";
	int z = 0;
	string x;
	bookpropertis prop;
	map<string, bookpropertis>::iterator it;
	cin.ignore();
	getline(std::cin, x);
	it = books.find(x);
	//cout << "name of book:";
	if (it != books.end())
	{
		cout << "found!!" << endl;
	}
	else
	{
		cout << "not found!!" << "\n";
	}

	system("pause");
}
void authorofbook() {
	system("CLS");
	cout << "enter the auhtor of book " << "\n";
	int z = 0;
	string x;
	bookpropertis prop;
	map<string, bookpropertis>::iterator it;
	it = books.begin();
	cin.ignore();
	getline(std::cin, x);
	cout << "name of book:";
	while (it != books.end())
	{
		prop = it->second;
		if ((prop.author == x))
		{
			cout << prop.name << "\n";
			z = 1;
		}
	}
	if (z == 0)
	{
		cout << "not found" << "\n";
	}
	system("pause");
}
void nopageofbook() {
	system("CLS");
	cout << "enter the number of page of book" << "\n";
	int z = 0;
	string x;
	bookpropertis prop;
	map<string, bookpropertis>::iterator it;
	it = books.begin();
	cin.ignore();
	getline(std::cin, x);
	cout << "name of book:";
	while (it != books.end())
	{
		prop = it->second;
		if ((prop.nopage == x))
		{
			cout << prop.name << "\n";
			z = 1;
		}
	}
	if (z == 0)
	{
		cout << "not found" << "\n";
	}
	system("pause");
}
void URL() {
	system("CLS");
	cout << "enter the URL of the book " << "\n";
	int z = 0;
	string x;
	bookpropertis prop;
	map<string, bookpropertis>::iterator it;
	it = books.begin();
	cin.ignore();
	getline(std::cin, x);
	cout << "name of book:";
	while (it != books.end())
	{
		prop = it->second;
		if ((prop.URL == x))
		{
			cout << prop.name << "\n";
			z = 1;
		}
	}
	if (z == 0)
	{
		cout << "not found" << "\n";
	}
	system("pause");
}
void numberofsection() {
	system("CLS");
	cout << "enter the number of section of book" << "\n";
	int z = 0;
	string x;
	bookpropertis prop;
	map<string, bookpropertis>::iterator it;
	it = books.begin();
	cin.ignore();
	getline(std::cin, x);
	cout << "name of book:";
	while (it != books.end())
	{
		prop = it->second;
		if ((prop.numberofsection == x))
		{
			cout << prop.name << "\n";
			z = 1;
		}
	}
	if (z == 0)
	{
		cout << "not found" << "\n";
	}
	system("pause");
}
void wordSearch() {
	system("cls");
	drawmain();
	try {
		found = wordList.begin();
		for (found; found != wordList.end(); found++) {
			found->first;
		}
		string phrase;
		cin.ignore();
		cin.clear();
		gotoxy(2, 17);
		cout << "please enter your phrase:";
		getline(cin, phrase);

		word(phrase);

		for (int i = 0; i < sort1.size(); i++) {
			gotoxy(2, 19 + i * 2);
			cout << sort1[i].first << "    " << sort1[i].second << endl;
			for (int ii = 0; ii < 100; ii++)
			{
				cout << "_";
			}
		}
		system("pause");
	}
	catch (exception e)
	{
		cout << "1" << e.what();
	}
}
void puplisherofbook() {
	system("CLS");
	cout << "enter the puplisher of book" << "\n";
	int z = 0;
	string x;
	bookpropertis prop;
	map<string, bookpropertis>::iterator it;
	it = books.begin();
	cin.ignore();
	getline(std::cin, x);
	cout << "name of book:";
	while (it != books.end())
	{
		prop = it->second;
		if ((prop.puplisher == x))
		{
			cout << prop.name << "\n";
			z = 1;

		}


	}
	if (z == 0)
	{
		cout << "not found" << "\n";
	}

	system("pause");
}
//here we will check if the category exist or not
bool read_category_from_file(string category) {

	my_categ_map.clear();
	bool b = 0;
	string line, key, word;
	ifstream my_category;
	my_category.open("category.txt");
	if (my_category.is_open()) {
		int i = 0;
		while (getline(my_category, line)) {

			if (i % 2 == 0) {
				if (line == category) {
					b = 1;
					break;
				}
				key = line;
				my_categ_map[key];
			}
			else {
				favptr = my_categ_map.find(key);


				stringstream ssm;
				ssm << line;
				while (ssm >> word) {

					favptr->second.insert(word);
				}
			}
			i++;
		}
	}
	else {
		cout << "there is erorr in openining file " << endl;
	}
	my_category.close();
	if (!b) {
		my_categ_map[category];
		write_category();
	}
	return b;
	/*set<string> books;
	string cate;
	string line;
	ifstream my_category;
	my_category.open("category.txt");
	if (my_category.is_open()) {
		while (getline(my_category, cate))
		{
			getline(my_category, line);
			string subject = line;
			std::regex re("\\w+");
			std::sregex_iterator next(subject.begin(), subject.end(), re);
			std::sregex_iterator ende;
			while (next != ende) {
				std::smatch match = *next;
				//std::cout << match.str() << "\n";
				books.insert(match.str());
				next++;
			}
			my_categ_map.insert(pair<string, set<string>>(cate, books));
		}
	}*/
}
void read_category_book(string category, string name_book) {
	my_categ_map.clear();
	string line, key, word;
	ifstream my_category;
	my_category.open("category.txt");
	if (my_category.is_open()) {
		int i = 0;
		while (getline(my_category, line)) {

			if (i % 2 == 0) {
				key = line;
				my_categ_map[key];

			}
			else {
				favptr = my_categ_map.find(key);
				stringstream ssm;
				ssm << line;
				while (ssm >> word) {
					favptr->second.insert(word);
				}
			}
			i++;
		}
	}
	else {
		cout << "there is erorr in openining file " << endl;
	}
	my_category.close();
	my_categ_map[category];
	favptr = my_categ_map.find(category);
	favptr->second.insert(name_book);
	write_category();
	/*map<string, set<string>>::iterator itm;
	set<string>::iterator its;
	itm = my_categ_map.find(category);
	if (itm != my_categ_map.end())
	{
		itm->second.insert(name_book);
	}
	else {
		my_categ_map.insert(pair<string, set<string>>(category, { name_book }));
	}
	write_category();*/
}
void write_category(void) {
	ofstream my_category;
	my_category.open("category.txt");
	my_category.clear();
	for (auto i : my_categ_map) {
		my_category << i.first << endl;
		for (auto is : i.second) {
			my_category << is << " ";
		}
		my_category << "\n";
	}
	my_category.close();
}
void word(string searsh) {

	try {
		searsh_word.clear();
		searsh_book.clear();
		filter_book.clear();
		filter_line.clear();
		sort1.clear();

		stringstream ssm;
		string word;
		ssm << searsh;
		while (ssm >> word) {
			searsh_word.push_back(word);
		}

		if (searsh_word.size() > 1) {
			filter_one();
		}
		else {
			found = wordList.find(searsh_word[0]);
			if (found != wordList.end()) {
				for (auto x : found->second) {
					save(x.first, x.second.size());
				}
			}
		}
	}
	catch (exception e)
	{
		cout << 2 << e.what();
	}
}
void filter_one(void) {
	try {

		found = wordList.find(searsh_word[0]);
		if (found != wordList.end()) {
			for (found2 = (found->second).begin(); found2 != (found->second).end(); found2++) {
				filter_book[found2->first] = true;
			}
			filter_two();
		}
		else {
			cout << "please be sure that your words is already exist :)" << endl;
			system("pause");
		}


	}
	catch (exception e)
	{
		cout << 3 << e.what();

	}
}
void filter_two(void) {
	try {
		map<string, bool>::iterator it;
		vector<string>ss;
		for (long long i = 1; i < searsh_word.size(); i++) {
			found = wordList.find(searsh_word[i]);
			if (found != wordList.end()) {
				for (found2 = (found->second).begin(); found2 != (found->second).end(); found2++) {
					it = filter_book.find(found2->first);
					if (it != filter_book.end()) {
						filter_book[found2->first] = false;

					}

				}
			}
			for (it = filter_book.begin(); it != filter_book.end(); it++) {

				if (!it->second) {
					ss.push_back(it->first);

				}
			}
			filter_book.clear();
			for (int z = 0; z < ss.size(); z++) {
				filter_book[ss[z]] = true;
			}
			ss.clear();
		}
		for (it = filter_book.begin(); it != filter_book.end(); it++) {
			searsh_book.push_back(it->first);
		}
		filter_book.clear();
		filter_two2();
	}
	catch (exception e)
	{
		cout << 4 << e.what();
	}
}
void filter_one2(string one, string two) {
	try {
		found = wordList.find(one);
		if (found != wordList.end()) {
			found2 = (found->second).find(two);
			if (found2 != (found->second).end()) {
				found3 = (found2->second).begin();
				for (found3; found3 != (found2->second).end(); found3++) {
					filter_line[*found3] = true;
				}
			}
		}
	}
	catch (exception e)
	{
		cout << 5 << e.what();
	}
}
void filter_two2(void) {
	try {
		vector<int>ss;
		for (long long i = 0; i < searsh_book.size(); i++) {
			filter_line.clear();
			filter_one2(searsh_word[0], searsh_book[i]);
			for (long long j = 1; j < searsh_word.size(); j++) {

				found = wordList.find(searsh_word[j]);
				if (found != wordList.end()) {
					found2 = (found->second).find(searsh_book[i]);
					if (found2 != (found->second).end()) {
						found3 = (found2->second).begin();
						for (found3; found3 != (found2->second).end(); found3++) {

							itr = filter_line.find(*found3);
							if (itr != filter_line.end()) {
								filter_line[*found3] = false;

							}


						}
					}
				}
				for (itr = filter_line.begin(); itr != filter_line.end(); itr++) {

					if (!itr->second) {
						ss.push_back(itr->first);

					}
				}
				filter_line.clear();
				for (int z = 0; z < ss.size(); z++) {
					filter_line[ss[z]] = true;
				}
				ss.clear();
			}
			save(searsh_book[i], filter_line.size());
		}
	}
	catch (exception e)
	{
		cout << 7 << e.what();
	}
}
void save(string book, int repitation) {
	try {
		pr.first = book;
		pr.second = repitation;
		int strt = 0, end = sort1.size() - 1, mid = 0;
		while (end >= strt) {
			mid = (strt + end) / 2;
			if (sort1[mid].second <= pr.second) {
				end = mid - 1;
			}
			else if (sort1[mid].second > pr.second) {
				strt = mid + 1;
			}
		}
		sort1.insert(sort1.begin() + mid, pr);
	}
	catch (exception& e)
	{

		cout << 9 << e.what();
	}
}
bool isNumber(string s) {

	for (int i = 0; i < s.length(); i++)
		if (isdigit(s.at(i)) == false)
			return false;

	return true;
}
void favbook(void) {
	drawmain();
	char chioce;
	if (fvrt.empty()) {
		string line, key, word;
		ifstream my_favourit;
		my_favourit.open("favourite.txt");
		if (my_favourit.is_open()) {
			int i = 0;
			while (getline(my_favourit, line)) {

				if (i % 2 == 0) {
					key = line;
					fvrt[key];
				}
				else {
					favptr = fvrt.find(key);
					stringstream ssm;
					ssm << line;
					while (ssm >> word) {
						favptr->second.insert(word);
					}
				}
				i++;
			}

		}
		else {
			cout << "there is erorr in openining file " << endl;
		}
		my_favourit.close();
	}
	gotoxy(20, 11);
	cout << "      (a)ddbook         " << endl;
	gotoxy(20, 12);
	cout << "      (s)howbook        " << endl;
	gotoxy(1, 17);
	cout << "enter \(a\/s\/r\)   :";
	cin >> chioce;

	if (chioce == 'a') {
		addfvrtbook();
	}
	else if (chioce == 's') {
		fvrtsearch();
	}
	else if (chioce == 'r') {
	}
}
void addfvrtbook(void) {
	map<string, bookpropertis>::iterator bookptr;
	string user;
	int num;
	int b = 0;
	cout << "please Enter your  username" << endl;
	cin.ignore();
	getline(cin, user);
	favptr = fvrt.find(user);
	if (favptr != fvrt.end()) {
		fvrt[user] = {};
	}
	cout << "please Enter number of book you  want to be added :)" << endl;
	cout << "note : be sure that your book is already added in the liberary " << endl;
	cin >> num;
	for (int i = 0; i < num; i++) {
		cout << "enter your book " << endl;
		string str;
		cin.ignore();
		getline(cin, str);
		bookptr = books.find(str);
		if (bookptr != books.end()) {
			(favptr->second).insert(str);
		}
		else {
			cout << "you should be sure that your book is already added in the liberary " << endl;
			i--;
			cout << "if you want to escape enter 1  else press any key " << endl;
			cin >> b;
		}
		if (b == 1) {
			break;
		}
	}
	ofstream my_favourit;
	my_favourit.open("favourite.txt");
	my_favourit.clear();
	for (auto i : fvrt) {
		my_favourit << i.first << endl;
		for (auto is : i.second) {
			my_favourit << is << " ";
		}
		my_favourit << "\n";
	}
	my_favourit.close();
}
void fvrtsearch(void) {
	string user, openb;
	cout << "please Enter your  username" << endl;
	cin.ignore();
	getline(cin, user);
	favptr = fvrt.find(user);
	if (favptr != fvrt.end()) {
		for (auto x : favptr->second) {
			cout << x << endl;
		}
	}
	else {
		cout << "you have not any book " << endl;
	}
	system("pause");
}
void category(void) {

	string line, word;
	ifstream my_category;
	my_category.open("category.txt");
	if (my_category.is_open()) {
		int i = 0, j = 0;
		while (getline(my_category, line)) {

			if (i % 2 == 0) {
            //   gotoxy(2,2+i);
				cout << line << endl;
			}
			else {

				stringstream ssm;
				ssm << line;
				j = 0;
				//gotoxy(2,4+i);
				while (ssm >> word) {
					cout << word << "       ";
					j++;
					if (j % 2 == 0) {
						cout << endl;
					}
				}
				//gotoxy(1,6+i);
				//for(int ii=0;ii<99;ii++)cout<<"_";
			}
			i++;
			cout << endl;
		}
	}
	else {
		cout << "there is erorr in openining file " << endl;
	}
	my_category.close();

}
