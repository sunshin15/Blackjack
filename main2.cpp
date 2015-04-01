#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
using namespace std;

int cards[4][13]={0};			//0:in the group,	1:owed by the Player,	2:computer
float score1=0,score2=0;
int result=0;					//result=1:win,		2:lost
string record="";				//eg:record="Club 10 Diamond 8 Spade Q Heart 7"
const string HuaSe[4]={"Spade","Heart","Club","Diamond"};
const string DianShu[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};



char GetInput();				//Judge if the input string is legal.
void XiPai();					//rt
void FaPai(int person);			//rt
string PaiHao(int a,int b);		//a:suit,	b:number
float score(int x,int y);		//card--->the score of the card.
float JiSuan(int person);		//calculate the total score of the person(1:Player,2:Computer)
void WanJiaJieDuan();			//rt
void DianNaoJieDuan();			//rt


int main()
{
	char JiXu='y';
	srand((int)time(0));

	while (JiXu=='y')
	{
		XiPai();
		WanJiaJieDuan();
		//cout<<"result="<<result<<endl;
		if (result!=2)
			DianNaoJieDuan();

		if (result==2)
			cout<<"\n  Defeat!\n\n";
		else
			cout<<"\n  Victory!\n\n";

		cout<<"Continue?(y/n)：";

		JiXu=GetInput();
		cout<<"\n\n";
	}
	return(0);

}

void XiPai()
{
	int i,j;
	for (i=0;i<4;i++)
		for (j=0;j<13;j++)
			cards[i][j]=0;
	record="";
	score1=0;
	score2=0;
	result=0;
}

string PaiHao(int a,int b)
{
	return(HuaSe[a]+" "+DianShu[b]);
}

void FaPai(int person)
{
	int x,y;

	x=rand()%4;
	y=rand()%13;

	while (cards[x][y]!=0)
	{
		x=rand()%4;
		y=rand()%13;
	}
	
	cards[x][y]=person;
	record=record+PaiHao(x,y)+" ";
}

float score(int x,int y)
{
	if (y<=9)
		return(y+1);
	else 
		return(0.5);
}

float JiSuan(int person)
{
	int i,j;
	float sum;
	sum=0;
	for(i=0;i<4;i++)
		for (j=0;j<13;j++)
		{
			if (cards[i][j]==person)
				sum=sum+score(i,j);
		}
	return(sum);
}

void WanJiaJieDuan()
{
	char JiXu='0';
	int x,y,i;
	
	
	cout<<"Player Stage\n\n";
	while (JiXu=='y'||JiXu=='0')
	{
		if (JiXu=='0')
		{
			cout<<"The Player get 2 cards: ";
			FaPai(1);
			FaPai(1);
		}
		else if(JiXu=='y')
		{
			cout<<"Get another card: ";
			FaPai(1);
		}
		cout<<record+"\n";

		score1=JiSuan(1);
		//cout<<"score1:"<<score1<<"\n";
		if (score1>21)
		{
			result=2;
			cout<<"\n";
			return;
		}

		cout<<"Do you want another card?(y/n):";
		JiXu=GetInput();

	}
	cout<<"\n";
}


void DianNaoJieDuan()
{
	char JiXu='0';

	record="";

	//cout<<"  Defeat!\n\n";
	while (JiXu=='y'||JiXu=='0')
	{
		if (JiXu=='0')
		{
			cout<<"The computer get 2 cards: ";
			FaPai(2);
			FaPai(2);
		}
		else if(JiXu=='y')
		{
			cout<<"Get another card: ";
			FaPai(2);
		}
		cout<<record+"\n";
		score2=JiSuan(2);
		//cout<<"score2:"<<score2<<"\n";

		if (score2>21)
		{
			result=1;
			return;
		}
		else if (score2>score1)
		{
			result=2;
			return;
		}
		else 
		{
			JiXu='y';
		}
	}
}


char GetInput()
{
	string input;

	while(1)
	{

		getline(cin,input);
		if (input.length()!=1)
		{
			cout<<"error:please input y/n."<<endl;
			continue;
		}
		if (input=="y"||input=="Y")
			return('y');
		else if (input=="n"||input=="N")
			return('n');
		
		cout<<"error:please input y/n."<<endl;
	}
}

