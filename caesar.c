#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 1024

void encrypt(char*, int);
void decrypt(char*, int);

int menu();

int
main(void)
{

char c,
     choice[2],
     s[MAXSIZE];
int shift;

 while(1)
 {
 menu();

 gets(choice);

 if((choice[0]=='e')||(choice[0]=='E'))
 {
  puts("Input text to encrypt->");
  gets(s);
  puts("Enter shift amount (1-25)->");
  scanf("%d", &shift);
  getchar(); // consume newline
  encrypt(s, shift);
 }
 else if((choice[0]=='d')||(choice[0]=='D'))
 {
  puts("Input text to decrypt->");
  gets(s);
  puts("Enter shift amount (1-25)->");
  scanf("%d", &shift);
  getchar(); // consume newline
  decrypt(s, shift);
 }
 else
    break;
 }

 return 0;
}

void encrypt(char*str, int shift)
{
	int n=0;
	char *p=str,
		 q[MAXSIZE];

	while(*p)
	{
	 if(islower(*p))
	 {
		 q[n] = toupper((*p - 'a' + shift) % 26 + 'A');
	 }
	 else
	 {
		 q[n]=*p;
	 }
	 n++; p++;
	}
	q[n++]='\0';
	puts(q);
}

void decrypt(char*str, int shift)
{
	int   n=0;
	char *p=str,
		 q[MAXSIZE];

	while(*p)
	{
	 if(isupper(*p))
	 {
		 q[n] = tolower((*p - 'A' - shift + 26) % 26 + 'a');
	 }
	 else
	 {
		 q[n]=*p;
	 }
	 n++; p++;
	}
	q[n++]='\0';
	puts(q);
}

int menu()
{
 puts("To encrypt, input e or E\n");
 puts("To decrypt, input d or D\n");
 puts("To exit, input any other letter\n");
 puts("Your choice:->\n");
 return 0;
}