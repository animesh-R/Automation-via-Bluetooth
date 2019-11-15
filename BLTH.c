#include<lpc21xx.h>

#define rs 8
#define rw 9
#define e 10

void delay(int t)
{
int i,j;
for(i=0;i<t;i++)
for(j=0;j<1250;j++);
}

void cmd(char a)
{
IOSET0=a<<16;
IOCLR0=(1<<rs);
IOCLR0=(1<<rw);
IOSET0=(1<<e);
delay(100);
IOCLR0=(1<<e);
IOCLR0=a<<16;
}

void data(char a)
{
IOSET0=a<<16;
IOSET0=(1<<rs);
IOCLR0=(1<<rw);
IOSET0=(1<<e);
delay(100);
IOCLR0=(1<<e);
IOCLR0=a<<16;
}
 							
void string(char *s)
{
	int i;
	for(i=0;s[i]!='\0';i++)
	{
		data(s[i]);
	}
}

void pll_clk()
{
	PLLCON=0x01;
	PLLCFG=0x25;
	PLLFEED=0xAA;
	PLLFEED=0x55;
while(!(PLLSTAT&(1<<10)));
	PLLCON=0x03;
	PLLFEED=0xAA;
	PLLFEED=0x55;
	VPBDIV=0x00;
}


void tx(char a)
{
	U0THR=a;
	while(!(U0LSR&(1<<6)));
}

	char rx()
	{
		
		while(!(U0LSR&(1<<0)));
		return U0RBR;

	}

void skip1()
{
cmd(0x80);
string("                            ");
cmd(0x80);
}	

void skip2()
{
cmd(0xc0);
string("                              ");
cmd(0xc0);
}	

void main()
{
	int y,i,j,d,c,k=0xc0,r[5]={0x01,0x02,0x04,0x08,0x0F},m;
	char a[4],b[2];
	
	PINSEL0=0x05;
	PINSEL1=0;
	PINSEL2=0;
	IODIR0=0xffffffff;
	IODIR1=0xffffffff;
	
pll_clk();
	U0LCR=0X83;
	U0DLL=0X61;
	U0DLM=0X00;
	U0LCR=0X03;

while(1)
{
	
 cmd(0x38);
 cmd(0x0e);
 cmd(0x80);
x:	
string("EMBEDDED SYSTEM");
cmd(0xc0);
string("BLUETOOTH CONTROLLED AUTOMATION");
cmd(0x01);
cmd(0x80);
string("ENtEr PaAswoRd");


for(i=0;i<4;i++)
{
	a[i]=rx();
tx(a[i]);
	cmd(k);
	string("*");
	k++;
}	
	if(a[0]=='0'&&a[1]=='0'&&a[2]=='0'&&a[3]=='0')
	{
		{
		cmd(0x01);
		cmd(0x80);
		string("aCCeSS gRAntEd");
		cmd(0x01);
		}
	cmd(0x80);
	string("enter required passcode for :-");
	cmd(0x01);
	cmd(0x80);		
	string("Press 01 for led lightning");
	cmd(0x01);
	string("Press 02 for fAn");
	cmd(0x01);
	string("Press 03 for 7_segmnt");
	cmd(0x01);
		
	
for(j=0;j<2;j++)
{
b[j]=rx();
tx(b[j]);
	cmd(k);
	string("*");
	k++;
	cmd(0x01);
}	

if(b[0]=='0'&&b[1]=='1')
{
	for(c=0;c<5;c++)
	{
		for(m=0;m<5;m++)
		{
			IOSET0=r[m]<<25;
			delay(500);
			IOCLR0=r[m]<<25;
		}
	}

}
	
else if(b[0]=='0'&&b[1]=='2')
{
	for(c=0;c<2;c++)
	{
	IOSET1=0x05<<16;
	delay(10000);
	IOCLR1=0x05<<16;
	IOSET1=0x0a<<16;
	delay(10000);
	IOCLR1=0x0a<<16;
	}

}

 else if(b[0]=='0'&&b[1]=='3')
{
	for(c=0x01;c<9;c++)
	{
	IOSET1=c<<28;
	delay(500);
	IOCLR1=c<<28;
	}
		for(d=0x09;d>0;d--)
	{
	IOSET1=d<<28;
	delay(500);
	IOCLR1=d<<28;
	}

}

		}
else
	{
		cmd(0x01);
		cmd(0x80);
		string("WroNG pasSword");
		cmd(0x01);
		goto x;

	}



} 
}

