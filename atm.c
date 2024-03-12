/*ATM-Any Time Money*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
// Preface to Code
/*File Details:
Name Of File: acc.no
     balance-first line and first word of File
     from second line :  Transaction Deatils
     
     
Procedure:
     -> Enter Acc.No
     -> If Account present proceed to Pay or accept cash or transaction history
     -> else create a new account
     
Total Files:
     1. per account-1 file (1- personal details 1- Financial Details)
     2. A file which contains all the account numbers(accounts.txt)

*/

struct bank_acc
{
     int password;  //Password for each account
     int balance;   //balance amt
     long int pno;  //phone number
     char name[15];      //Name
     char aadhar[12];    //Aadhar Number
     int acc_no;    //Account Number (8 digits only)
     struct bank_acc *next;
};
typedef struct bank_acc Node;
Node *head;
int *accounts;
int no_acc;
void initialize_Head();
void atm();
void myStartup();
int isAccountThere(int);
void createAccount();
void modifyAccounts(int);
Node* getNode();
char* add(char*,char*);
int displayOptions();
void delay(int);
void myCleanUp();
void transaction(int);
void modify_Balance(int,int,char*,int);
int displayOptions1();
int checkBalance(char*);
void displayHistory(char*);
int charToInt(char);
void displayPersonalDetails(char*);
void myStartup() __attribute__ ((constructor));
void myCleanUp() __attribute__ ((destructor));
int main()
{
     atm();
     return 0;
}
void delay(int time)
{
	int i;
	for(i=0;i<2000000000;i++);
}
void atm()
{
	time_t t;
	time(&t);
     while(1)
     {
     	int ch;
//     	system("clear");
     	printf("\t\t\t\tTime : %s\n",ctime(&t));
     	ch=displayOptions();
     	if(ch==1)
     	{
     	     createAccount();
//     	     system("clear");
    	     }
     	else if(ch==2)
     	{
     		int accno;
	          printf("Account Number : ");
     	     scanf("%d",&accno);
     	     if(!isAccountThere(accno))    //If account is not present
	          {
	          	
		          printf("Account Not Found.\n");
	              	printf("Create A New Account Instead...?(1/0) \t");
	              	scanf("%d",&ch);
	              	if(ch==1)
	              		createAccount();
	          }
	          else
	          	transaction(accno);
//	          system("clear");
		}
          else
          	break;
     }
}
int checkBalance(char *file_name)	//Complete
{
	//printf("%s",file_name);
     FILE *fp;
     fp=fopen(file_name,"r");
     char ch;
     char amt[15];
     int c=0,balance=0;
     while(!feof(fp))
     {
     	ch=fgetc(fp);
     	if(ch=='\n')
     		break;
     	//printf("%c",ch);
     	amt[c++]=ch;
     }
     amt[c]='\0';
     fclose(fp);
	balance=atoi(amt);
	
     return balance;
}
int charToInt(char ch)
{
     return ch-'0';
}
void transaction(int accno)
{
     /*Account Number*/
     //printf("%d\n",accno);
     int password;
     printf("Enter Password : ");
     scanf("%d",&password);
     //Read the password from filename
     fflush(stdin);
     int flag=0,size=0;
     char *file_name1,ano[8];
     char *file_name2;
     file_name1=(char*)malloc(12);
     sprintf(ano,"%d",accno);
     file_name1=add(ano,".txt");
     file_name2=add(ano,"personal.txt");
     //Lets read the first line which contains password
     FILE *fp;
     fp=fopen(file_name2,"r");
     char ch;
     ch=fgetc(fp);
     int pwde=0;
     while(ch!='\n')
     {
          pwde=(pwde*10)+(charToInt(ch));
          ch=fgetc(fp);
     }
     fclose(fp);
     if(pwde==password)
          flag=0;
     else
          flag=1;
     if(flag==1)
          printf("Wrong Password.....\n");
     else
     {
          //printf("Account Name :%s\n",file_name1);
          int ch;
          //printf("Choice : %d\n",ch);
          int amt=0;
          amt=checkBalance(file_name1);
          printf("Your Balance : %d\n\n\n",amt);
          ch=displayOptions1();
          if(ch==1)
               printf("Balance Amount In Your Account : %d\n",amt);
          else if(ch==2)
          {
               int withdraw;
               printf("Amount to Withdraw : ");
               scanf("%d",&withdraw);
               if(withdraw<amt)
               	modify_Balance(amt,withdraw,file_name1,0);
               else
               	printf("No sufficient Funds....\n");
          }
          else if(ch==3)
          {
               int deposit;
               printf("Enter Amount To Deposit : ");
               scanf("%d",&deposit);
               modify_Balance(amt,deposit,file_name1,1);
          }
          else if(ch==4)
               displayHistory(file_name1);
          //delay(5);
          else if(ch==5)
               displayPersonalDetails(file_name2);
          printf("\n\nSession Closed.....\n");
     }
}
void displayPersonalDetails(char *file_name)
{
     FILE *fp;
     fp=fopen(file_name,"r");
     char ch;
     while((ch=fgetc(fp))!='\n');  //Skip first line
     printf("Details : \n");
     printf(" Name : ");
     while((ch=fgetc(fp))!='\n')
          fputc(ch,stdout);
     printf("\n Account Number : ");
     while((ch=fgetc(fp))!='\n')
          fputc(ch,stdout);
     printf("\n Aadhar Card Number : ");
     while((ch=fgetc(fp))!='\n')
          fputc(ch,stdout);
     printf("\n Phone Number : ");
     while((ch=fgetc(fp))!='\n')
          fputc(ch,stdout);
}
void modify_Balance(int amt,int newamt,char *file_name,int type)
{
	time_t t;
	time(&t);
	FILE *fp,*temp;
	fp=fopen(file_name,"r");
	temp=fopen("temp.txt","w");
	//Skip the Balance and copy the rest to temp.txt
	char ch;
	/*while(!feof(fp))
     {
     	ch=fgetc(fp);
     	if(ch=='\n')
     		break;
     }*/
     while((ch=fgetc(fp))!='\n');
	//Skipped
	while(!feof(fp))
	{
		ch=fgetc(fp);
		fputc(ch,temp);
	}
	fclose(fp);
	fclose(temp);
	fflush(stdin);
	fp=fopen(file_name,"w");
	temp=fopen("temp.txt","r");
	if(type==1)	//Deposit Amount
	{
		amt=amt+newamt;
		fprintf(fp,"%d\n",amt);	//Printed Balance to Orginal File
	}
	else
	{
		amt=amt-newamt;
		fprintf(fp,"%d\n",amt);	//Printed Balance to Orginal File
	}
	//Copy temp.txt to file_name
	while(!feof(temp))
	{
		ch=fgetc(temp);
		fputc(ch,fp);
	}
	if(type==1)
		fprintf(fp,"Deposited Amount : %d\t Total Balance : %d at %s\n",newamt,amt,ctime(&t));
	else
		fprintf(fp,"Withdrawn Amount : %d\t Total Balance : %d at %s\n",newamt,amt,ctime(&t));
	fclose(fp);
	fclose(temp);
	printf("\nTransction Successfull\n");
}
void displayHistory(char *file_name)
{
     FILE *fp;
     char ch;
     fp=fopen(file_name,"r");
     while((ch=fgetc(fp))!='\n');
     while(!feof(fp))
          printf("%c",fgetc(fp));
}
int displayOptions1()
{
     int ch;
     printf(" 1- Check Balance\n 2- Withdraw Cash\n 3- Deposit Money\n 4- Transaction History\n 5- Display Personal Details\n Press Any Other To Exit\n");
     printf("Choice : ");
     scanf("%d",&ch);
     return ch;
}
void myCleanUp()
{
	Node *node=head,*prev;
	while(node!=NULL)
	{
		prev=node;
		node=node->next;
		free(prev);
	}
	printf("All Done....\n");
	printf("Exited .....\n");
}
int displayOptions()
{
	int ch;
	printf(" New Account(Press 1)\n Transactions(Press 2)\n Press Any Other To Exit.....\t");
	scanf("%d",&ch);
	return ch;
}
void initialize_Head()
{
     head=(Node*)malloc(sizeof(Node));
     head->next=NULL;
}
void myStartup() 
{
     /*Here we will read all the data in accounts file and get all the account numbers*/
     int no_acc=0;
     FILE *fp;
     fp=fopen("accounts.txt","r");
     if(fp==NULL)
     {
     	printf("Unable to Open File....\n");
     	exit(0);
     }
     else
     {
          //Read All Numbers from the File
          char acc[8],ch;
          int c=0,num;
          while(!feof(fp))
          {
               ch=fgetc(fp);
               acc[c%8]=ch;
               if(c==7)
               {
               	num=atoi(acc);
               	modifyAccounts(num);
               	printf("%d\n",num);
               	ch=fgetc(fp);
				no_acc++;
				c=-1;
               }
               c++;
          }
     }
     //We got all the account numbers....
     initialize_Head();
     printf("All Ready ....\n");
}
int isAccountThere(int accno)
{
     int i;
     for(i=0;i<no_acc;i++)
          if(accno==accounts[i])
               return 1; //Account present
     return 0;//Not present
}
void createAccount()
{
     // Here we will create a new account to the person by taking details
     Node *new,*node=head;
     new=getNode();
     while(node->next!=NULL)
          node=node->next;
     node->next=new;
     modifyAccounts(new->acc_no);
     // Modify the accounts file to add new accounts
	int i;
	FILE *fp;
	fp=fopen("accounts.txt","w");
	for(i=0;i<no_acc;i++)
		fprintf(fp,"%d\n",accounts[i]);
	fclose(fp);
}
void modifyAccounts(int number)
{
     accounts=(int*)realloc(accounts,(no_acc+1)*sizeof(int));
     accounts[no_acc]=number;
     no_acc++;
}
Node* getNode()
{
     Node *newnode=(Node*)malloc(sizeof(Node));
     printf("Enter Name : ");
     scanf("%s",newnode->name);
     printf("Enter Aadhar Number : ");
     scanf("%s",newnode->aadhar);
     printf("Enter Phone Number : ");
     scanf("%ld",&newnode->pno);
     int password1,password;
     while(1)
     {
          printf("Create A Strong Numeric Password : ");
          scanf("%d",&password1);
          printf("Enter The Same Password : ");
          scanf("%d",&password);
          if(password1==password)
               break;
          else
               printf("Password Mismatch\n");
     }
     newnode->password=password1;
     //Account NUmber is given by adding number of previous accounts to base number ...
     newnode->acc_no=11162600+(no_acc*5)+6;
     newnode->balance=1; //Initial Balance is 1 Rupee ;)
     fprintf(stdout,"\n\n\n");
     printf("Details : \n\n");
     printf("Account Number : %d\n",newnode->acc_no);
     printf("Name : %s\n",newnode->name);
     printf("Aadhar Number : %s\n",newnode->aadhar);
     printf("Phone Number : %ld\n",newnode->pno);
     printf("Password : %d\n",password);
     printf("Account Created Successfully......\n");
     //Now creating a file and adding the Details
     //Here 2 Accounts will be created
     //1. acc_no.txt       2. acc_nopersonal.txt (for storing personal details)
     char snum[8];
     sprintf(snum,"%d",newnode->acc_no);   //Convert integer to char type
     
     char *file_name1=add(snum,".txt"),*file_name2=add(snum,"personal.txt");
     FILE *fp1,*fp2;
     fp1=fopen(file_name2,"w");
     fprintf(fp1,"%d\n%s\n%d\n%s\n%ld\n",newnode->password,newnode->name,newnode->acc_no,newnode->aadhar,newnode->pno);
     fclose(fp1);
     
     time_t t;
     time(&t);
     fp2=fopen(file_name1,"w");
     fprintf(fp2,"1");
     fprintf(fp2,"\n");
     fprintf(fp2,"Account Opened On %s\n",ctime(&t));
     fclose(fp2);
     newnode->next=NULL;
     return newnode;
}
char* add(char *n1,char *n2)
{
     int l,l1,i;
     for(l=0;*(n1+l)!='\0';l++);
     for(l1=0;*(n2+l1)!='\0';l1++);
     int size=l+l1;
     char *ans=(char*)malloc((l+l1)*sizeof(char));
     for(i=0;i<l;i++)
          *(ans+i)=*(n1+i);
     for(i=0;i<l1;i++)
          *(ans+i+l)=*(n2+i);
     *(ans+i+l)='\0';
     return ans;
}