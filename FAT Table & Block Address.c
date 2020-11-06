#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *buffer[500]; //Memory created-500 bytes
int s_b[10][2],empty[10]; //Stores size and number of blocks
int mem=500; //keeps track of free memory
char *block[10]; //store address of the blocks
int *address[10]; //stores address of files
char name[10][30]; //stores name of the file

//////////////////////////////////////////////////////////////////
void open_createdfile() //to open the file
{
char fname[30],c;
int size=1,i;
printf("Enter txt file name\n");
scanf("%s",fname);
FILE *inputf;   //FILE is a kind of structure that holds information about the file.
inputf = fopen(fname,"r");  //--filehandling, opens name specified in parameter, r-read
if (inputf == NULL)
{
printf("\nFile unable to open ");
exit(0);
}
rewind(inputf);   //rewind-sets the file position to the beginning
c=fgetc(inputf);  //get syntax in file handling
while(c!=EOF)		//EOF-end of file
{
c=fgetc(inputf);
size=size+1;
}
printf("The size of given file is : %d\n", size);

if(mem>=size)		//checking if the file can be saved 
{
int n=1,parts=0,m=1;
while(address[n]!=0)
n++;
strcpy(name[n],fname);   //string copy
s_b[n][1]=size;
int bnum=size/50;
if(size%50!=0)
bnum=bnum+1;
s_b[n][2]=bnum;
mem=mem-(bnum*50);
int *bfile=(int*)malloc(bnum*(sizeof(int)));   //allocation
address[n]=bfile;
printf("Number of blocks required: %d\n",bnum);
rewind(inputf);		//rewind-sets the file position to the beginning
c = fgetc(inputf);
while(parts!=bnum && c!=EOF)
{
int k=0;
if(empty[m]==0)
{
char *temp=block[m];
while(k!=50)		//taking max size of file to be 50
{
*temp=c;
c=fgetc(inputf);
temp++;
k=k+1;
}
*(bfile+parts)=m;
parts=parts+1;
empty[m]=1;
}
else
m=m+1;
}
printf("File info displayed\n");
printf("\n");
fclose(inputf);					//close file
}
else
printf("Not enough memory\n");		//memory full case
}

int filenum(char fname[30])       ////////filenum
{
int i=1,fnum=0;
while(name[i])
{
if(strcmp(name[i], fname) == 0)		//comparing string
{
fnum=i;
break;
}
i++;
}
return fnum;
}
//////////////////////////////////////////////////
void remove1()
{
char fname[30];
int i=1,j,k,fnum=0;
printf("Enter the file name: ");
scanf("%s",fname);		
fnum=filenum(fname);
if(fnum==0)
printf("File not available:\n");
else
{
int *temp=address[fnum];   		//searching file named given as input
int b=(s_b[fnum][2]);
mem=mem+b*50;
for(j=0;j<b;j++)
{
int s=*(temp+j);			//making it empty
empty[s]=0;
}
address[fnum]=0;		  //address 0
}
printf("\n");
}
/////////////////////////////////////////////////
void fat_file()
{
int i=1;
printf("File name size address\n");
for(i=1;i<=10;i++)
{
if(address[i]!=0)
printf("%s   %d   %d\n",name[i],s_b[i][1],address[i]); //name,size,address
}
printf("\n");
}
/////////////////////////////////////////////////
void print()
{
char fname[30];
int i=1,j,k,fnum=0; 	//initialiazations
printf("Enter the file name: ");
scanf("%s",fname);		//read input
fnum=filenum(fname);    // predefined func which checks if string is 0 or not
if(fnum!=0&& address[fnum]!=0)
{
int *temp;
temp=address[fnum];
printf("Content of the file %s is:\n",name[fnum]); //file handling fns ie name[]
int b=(s_b[fnum][2]);
for(j=0;j<b;j++)
{
int s=*(temp+j);    //content of the file in next position
char *prt=block[s];
for(k=0;k<50;k++)
{
printf("%c",*prt);
prt++;
}
}
printf("\n");
printf("\n");
}
else
printf("File not available:\n");
}

////////////////////////////////////////////////
void blocks()
{
int i;
printf(" Block address empty/free\n");
for(i=1;i<=10;i++)
printf("%d. %d - %d\n",i,block[i],empty[i]);    //number,block address,empty or not
printf("\n");
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

int main()
{
printf("\n\t\t ____________________________");
printf("\n\t\t|\t\t\t     |");
printf("\n\t\t|\tFAT TABLE AND\t     |\t\t");
printf("\n\t\t|    BLOCK ADDRESS VIEWER    |\t\t");
printf("\n\t\t|____________________________|\t\t\n");
int choice,i;
char *temp;
if (buffer == NULL)
{
fputs ("Memory error",stderr);  //checking buffer is empty or anything present
exit(2);
}
temp=buffer;
block[1]=temp;
empty[1]=0;
for(i=2;i<=10;i++)
{
block[i]=block[i-1]+50;
empty[i]=0;
}
menu:while(1)
{
printf("\n1.Open existing file\n");
printf("2.Delete a file\n");
printf("3.Print a file \n");
printf("4.Display FAT table\n");
printf("5.Display Block Details\n");
printf("6.Exit the program\n");
printf("Enter your choice: ");
scanf("%d",&choice);
switch(choice)
{
case 1:
	open_createdfile();
	break;
case 2:
	remove1();
	break;
case 3:
	print();
	break;
case 4:
	fat_file();
	break;
case 5:
	blocks();
	break;
case 6:
	exit(1);
default:printf("Invalid option entered. Try again!\n\n");
goto menu;
}
}
return 0;
}
