#include <iostream>
#include<fstream>
#include<sstream> 
#include<string.h>
#include<string>
#include<math.h>
using namespace std;

////////////////////////////////// defining file
class file{
public:						//public class initialisations
char name[64];
long int len;
int startpos;
char* get_file_name();
long int get_file_length();
int get_startpos();
};
						

//////////////////////////////  defining filesys
#define MAX_FILE_LEN 1000
#define MAX_FILES 15

class filesys					//public class initialisations
{
public:
file files[MAX_FILES];
void initialize();				//initialisations of all functions required to implement
void read_from_file();
void write_to_file();
void set_file_system_name();
filesys(char f_name[]);
char file_system_name[20];
void list_files();
char* show_file_content(char* f_name);
char* search_file(char* f_name);
void search_keyword(char* f_name, char* keyword);
void delete_file(char* f_name);
void create_file(char* f_name, char* file_contents);
};

////////////////////////////////  cpp for file
char* file::get_file_name()
{
return name;
}
long int file::get_file_length()			//constructor concept to inherit file length
{
return len;
}
int file::get_startpos()					//constructor concept to inherit start position
{
return startpos;
}

///////////////////////////////////////// cpp for filesys
void filesys::set_file_system_name()
{
cout << "Enter file system name\n";		//naming file system initially
char temp[80];
cin >> temp;
strcpy(file_system_name, temp);			//comparing if the same name is present before
initialize();
}
filesys::filesys(char f_name[])
{
if(f_name == NULL)						//if it isnt used before set the file system name as given input
set_file_system_name();
else{
cout << "Existing File System\n";		//if the filesystem name is already present, give output
strcpy(file_system_name, f_name);
read_from_file();
}
}
//////////////////////////////////////////////////////////

void filesys::initialize()           		//initialisation of all the variables and functions of file in the file system
{
fstream myfile(file_system_name, ios::out);		//fstream to open file
int i;
myfile.seekp(0, ios::beg);
for(i = 0; i < MAX_FILES; i++){
strcpy(files[i].name, "\0");
files[i].len = 0;
files[i].startpos = 0;
}
myfile.close();
write_to_file();
}

////////////////////////////////////////////////////////////////

void filesys::list_files()
{
for(int i = 0; i < MAX_FILES; i++){				//in the loop of all the file
if(!strcmp(files[i].get_file_name(), "\0"))		//comapring the input name with files presnt
break;
cout << files[i].get_file_name() << endl;		//giving output of all matched strings
}
}

/////////////////////////////////////////////////////////

char* filesys::show_file_content(char* f_name){		//to display the data in stored in file
fstream myfile(file_system_name, ios::in);
int i;
char* file_contents = new char[MAX_FILE_LEN];
cout << f_name << "\n";
for(i = 0; i < MAX_FILES; i++){
if(!strcmp(files[i].get_file_name(), f_name))		//comparing filename with input file name to match
{
myfile.seekg(files[i].get_startpos(), ios::beg);		//reading all data in file and printing it
myfile.read(file_contents, files[i].get_file_length());
*(file_contents + files[i].get_file_length()) = '\0';
myfile.close();
return file_contents;
}
}
cout<<"File not found!";						//if given input file name is not present
myfile.close();									
return NULL;
}

//////////////////////////////////////////////////

char* filesys::search_file(char* f_name){			//to search for file if present in filesystem
int i;
for(i = 0; i < MAX_FILES; i++){						//in the loop of all files
if(!strcmp(files[i].get_file_name(), f_name)){    	//if input string matched
cout<<"File found\nFile name:";
return files[i].get_file_name();					
}
}
cout<<"File not found!";
return NULL;										//if file not present
}

//////////////////////////////////////////////////////////////

void filesys :: search_keyword(char* f_name, char* keyword){   //searching particular keyword on whole file system
fstream myfile(file_system_name, ios::in);						
for(int i = 0; i < MAX_FILES; i++){
if(!strcmp(f_name, files[i].get_file_name())){				//under loop of all files,checking if the keyword is matched with any file contents(data)
char* file_content = new char[MAX_FILE_LEN];
myfile.seekg(files[i].get_startpos());
myfile.read(file_content, files[i].get_file_length());
char* p = strstr(file_content, keyword);
if(p == NULL){
cout<<"\nKeyword not Found!\n";
myfile.close();
return;
}
int pos = p - file_content + 1; // The difference between the address of substring in the string 
cout<<"\nKeyword Found!\nPosition of keyword:\t"<<pos;
myfile.close();
return;
}
}
cout<<"\nFile not found!\n";
myfile.close();
return;
}

////////////////////////////////////////////////////

void filesys::delete_file(char* f_name)		//to delete a file in filesystem
{int i,j;
char* file_content = new char[MAX_FILE_LEN];
for(i = 0; i < MAX_FILES; i++){
if(!strcmp(files[i].get_file_name(), f_name)){		//checking the file name under the loop of file system if matching
int del_len;
strcpy(files[i].name, "\0");
del_len = files[i].get_file_length() ;				//make the data of file null if matched
files[i].len = 0;
files[i].startpos = 0;
write_to_file(); 								//Will skip the content of the file to be deleted
for(j = i + 1; j < MAX_FILES ; j++){
strcpy(files[j - 1].name, files[j].get_file_name());
files[j - 1].len = files[j].get_file_length();
files[j - 1].startpos = files[j].get_startpos() - del_len;
}
write_to_file();
cout << "\nFile deleted!\n";
return;
}
}
cout<<"File not found!";
}

///////////////////////////////////////////////////////////////

void filesys::create_file(char* f_name, char* file_contents){ //creating a file in system
int i;
for(i = 0; i < MAX_FILES; i++){
if(!strcmp(files[i].get_file_name(), "\0"))			//checking if file name already present
break;
}
if(i == MAX_FILES)							//if memory not present
cout<<"No space";
else{
fstream myfile(file_system_name, ios::out | ios::app);
strcpy(files[i].name, f_name);
files[i].len = strlen(file_contents);
myfile.seekp(0, ios::end);
files[i].startpos = myfile.tellp();
myfile.write(file_contents,sizeof(char) * strlen(file_contents));
myfile.close();
write_to_file();
}
}

//////////////////////////////////////////////////////////

void filesys::read_from_file()				//read_from_file and write_to_file are functions used in between the main working functions
{
fstream myfile(file_system_name, ios::in);
int i;
myfile.seekg(0 , ios::beg);
for(i = 0; i < MAX_FILES; i++) //read already created files till null string is encountered or max limit
{myfile.read((char*)&(files[i].name) , sizeof(files[i].name));
if(!strcmp(files[i].name,"\0"))
break;
myfile.read((char*)&files[i].len , sizeof(long int));
myfile.read((char*)&files[i].startpos , sizeof(int));
}
while(i < MAX_FILES){
strcpy(files[i].name,"\0");
files[i].len = 0;
files[i].startpos = 0;
i++;
}
myfile.close();
}

void filesys::write_to_file(){
fstream myfile(file_system_name, ios::in);
fstream newfile("temp.txt", ios::out);
int i;
char file_content[MAX_FILE_LEN];
newfile.seekp(0 , ios::beg);
for(i = 0; i < MAX_FILES; i++){
newfile.write((char*)&files[i].name , sizeof(files[i].name));
newfile.write((char*)&files[i].len , sizeof(long int));
newfile.write((char*)&files[i].startpos , sizeof(int));
}
for(i = 0; i < MAX_FILES; i++){
if(files[i].get_file_length()){
myfile.seekg(files[i].get_startpos(), ios::beg);
myfile.read((char*)&file_content, sizeof(char) * files[i].len);
newfile.seekp(0 , ios::end);
newfile.write((char*)&file_content, sizeof(char) * files[i].len);
}
}
newfile.close();
myfile.close();
remove(file_system_name);
rename("temp.txt", file_system_name);
}

////////////////////////////////////////////////////////

int main(int argc, char* argv[]) 

{


char name[80], content[200], name1[80], keyword[60], *c = NULL;		//initialisations

cout<< "-----------------------------------------------------------------------------\n";
cout<< "************************** Virtual File System ******************************\n";
cout<< "-----------------------------------------------------------------------------\n";
int choice;
filesys f1(argv[1]);		//for a file system f1
while(1){
cout << "\n\nEnter your choice:\n";
cout << "1. List files in the file system\n";
cout << "2. Show file content\n";
cout << "3. Search a file\n";
cout << "4. Search for a keyword in a file\n";
cout << "5. Create new file\n";
cout << "6. Delete a file\n";
cin >> choice;
switch(choice){						//switch case
case 1:
	f1.list_files();				//lisiting all the files in file system f1
	break;
case 2:								//to show file content
	cout << "Enter file name\n";	
	cin >> name;					//read file name input
	c = f1.show_file_content(name);	//show file content function for f1 filesystem with input file name
	if(c != NULL)					//checking that the output is not =0
	cout << c;
	break;
case 3:								//to search for a file in file system if present
	cout << "Enter file name\n";	
	cin >> name;					//read file name input
	c = f1.search_file(name);		//search file function for f1 filesystem with input file name
	if(c != NULL) 					//checking that output is not =0
	cout << c;
	break;
case 4:
	cout << "Enter the file name\n";	//to search for a keyword inside file in file system if present
	cin >> name;						
	cout << "Enter the keyword to be searched\n"; //read input of keyword
	cin >> keyword;
	f1.search_keyword(name, keyword);	//search keyword function to check if input keyword is present in input file
	break;
case 5:									//to insert new file into filesystem
	cout << "Enter the name of new file\n";
	cin >> name;
	cout << "Enter the content of the file\n";	//read input
	cin.clear();
	fflush(stdin);							//to clear the buffer output and move it to disk
	cin.getline(content, sizeof(content));
	f1.create_file(name, content);			//create file function
	break;
case 6:
	cout << "Enter the name of the file to be deleted\n";			//to delete file
	cin >> name;
	f1.delete_file(name);				//to del file with given name in f1 filesystem
	break;
	
	default:							//default case
	cout << "Enter a valid option!\n";
}
}
}

