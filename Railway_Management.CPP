				  /***********************************/
				  /*   PROJECT RAILWAY RESERVATION   */
				  /***********************************/

	/* INCLUDED HEADER FILES */

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>

	/* THIS CLASS CONTAIN ALL THE FUNCTION RELATED TO DATE */

class DATE
{
	public :
			void EXTEND_DATE(int,int,int) ;
			void CURRENT_DATE(void) ;

			int  day, month, year ;
} ;


	/* THIS CLASS CONTAIN ALL THE FUNCTION RELATED TO TRAIN */

class TRAIN
{
	public :
			void DISPLAY_TRAIN(void) ;
			void ADD_TRAIN(char[], char[]) ;
			void ADDITION(void) ;
			void TRAIN_LIST(void) ;
			int  FOUND_TRAIN(char[]) ;

			char train_no[5], train_name[20] ;
} ;


	/* THIS CLASS CONTAIN ALL THE FUNCTION RELATED TO TICKET
	   LIKE RESERVATION, CANCELLATION, ETC. */

class TICKET
{
	public :
			void RESERVATION(void) ;
			void CANCELLATION(void) ;
			void WAITING_LIST(void) ;
			void PASS_INFO(void) ;
	private :
			int  pnr_no, kms ;
			char name[26], sex, tr_no[5] ;
			int  age, fair ;
			int  dd, mm, yy ;
			char from[15], to[15] ;
} t ;


	/* FUNCTION TO GET THE CURRENT SYSTEM DATE */

void DATE :: CURRENT_DATE(void)
{
	struct date d;
	getdate(&d);
	day = d.da_day ;
	month = d.da_mon ;
	year = d.da_year ;
}


	/* FUNCTION TO EXTEN THE CURRENT DATE BY ONE */

void DATE :: EXTEND_DATE(int dday, int dmonth, int dyear)
{
	static int m[] = {31,29,31,30,31,30,31,31,30,31,30,31} ;
	dday++ ;
	if ((dday > m[dmonth-1]) || (dyear%4 != 0 && dmonth == 2 && dday > 28))
	{
		dday = 1 ;
		dmonth++ ;
	}
	if (dmonth > 12)
	{
		dmonth = 1 ;
		dyear++ ;
	}
	day  = dday ;
	month  = dmonth ;
	year = dyear ;
}


	/* FUNCTION TO DISPLAY THE RUNNING TRAIN */

void TRAIN :: DISPLAY_TRAIN(void)
{
	clrscr() ;
	_setcursortype(_NOCURSOR);  // THIS FUNCTION OMMIT THE CURSOR
	int i=1 ;
	while (!kbhit())
	{
	textcolor(i);
	gotoxy(i,5) ;
	cprintf("                       \\             ") ;
	gotoxy(i,6) ;
	cprintf("                      \\ \\ \\          ") ;
	gotoxy(i,7) ;
	cprintf("                       \\ \\ \\        ") ;
	gotoxy(i,8) ;
	cprintf("                         \\ \\        ") ;
	gotoxy(i,9) ;
	cprintf("                            \\_        ") ;
	gotoxy(i,10) ;
	cprintf("           _    _    _    |  |       ") ;
	gotoxy(i,11) ;
	cprintf("    ______³°³°°³°³°°³°³°°°³°°³___    ") ;
	gotoxy(i,12) ;
	cprintf("   ³   __   __   __   __   __    \\   ") ;
	gotoxy(i,13) ;
	cprintf("³__³  ³±±³ ³±±³ ³±±³ ³±±³ ³  ³    ³  ") ;
	gotoxy(i,14) ;
	cprintf(" __³                      |  |    |_ ") ;
	gotoxy(i,15) ;
	cprintf("³__³°°°°°°°°°°°°°°°°°°°°°°³  ³°°°°³_³") ;
	gotoxy(i,16) ;
	cprintf(" __³    NORTHERN RAILWAY  ³__³    ³  ") ;
	gotoxy(i,17) ;
	cprintf("³  ³_____________________________/   ") ;
	gotoxy(i,18) ;
	cprintf("      \\____/ \\____/      \\____/      ") ;
	delay(100) ;
	for (int j=5; j<=18; j++)
	{
		gotoxy(i,j) ;
		cprintf("                                     ") ;


	}
	i++ ;
	if (i == 80)
		i = 1 ;
	}
	_setcursortype(_NORMALCURSOR);  // THIS FUNCTION RESTORE THE CURSOR
}


	/* THIS FUNCTION ADD THE GIVEN DATA TO THE TRAIN FILE */

void TRAIN :: ADD_TRAIN(char tno[5], char tname[20])
{
	fstream file ;
	file.open("TRAIN.DAT", ios::app) ;
	strcpy(train_no,tno) ;
	strcpy(train_name,tname) ;
	file.write((char *) this, sizeof(TRAIN)) ;
	file.close() ;
}


	/* THIS FUNCTION GIVES THE DATA TO ADD RECORDS IN TRAIN FILE */

void TRAIN :: ADDITION(void)
{
	fstream file ;
	file.open("TRAIN.DAT", ios::in) ;
	if (!file.fail())
		return ;
	file.close() ;
	ADD_TRAIN("2021","RAJDHANI EXPRESS") ;
	ADD_TRAIN("2023","TAJ EXPRESS") ;
	ADD_TRAIN("2025","GOMTI EXPRESS") ;
	ADD_TRAIN("2027","KALKA MAIL") ;
	ADD_TRAIN("2029","KALINDI EXPRESS") ;
}


	/* FUNCTION TO DISPLAY THE TRAIN LIST */

void TRAIN :: TRAIN_LIST(void)
{
	clrscr() ;
	fstream file ;
	file.open("TRAIN.DAT", ios::in) ;
	gotoxy(30,1) ;
	cout <<"LIST OF THE TRAINS" ;
	gotoxy(30,2) ;
	cout <<"******************" ;
	gotoxy(2,4) ;
	cout <<" TRAIN NO.        TRAIN NAME" ;
	gotoxy(1,5) ;
	cout <<"*****************************************************" ;
	int row=7 ;
	while (file.read((char *) this, sizeof(TRAIN)))
	{
		gotoxy(4,row) ;
		cout <<train_no ;
		gotoxy(20,row) ;
		cout <<train_name ;
		row++ ;
	}
	file.close() ;
}


	/* THIS FUNCTION RETURNS ONE IF GIVEN TRAIN NO. FOUND */

int TRAIN :: FOUND_TRAIN(char tno[5])
{
	fstream file ;
	file.open("TRAIN.DAT", ios::in) ;
	int found=0 ;
	while (file.read((char *) this, sizeof(TRAIN)))
	{
		if (!strcmp(tno,train_no))
		{
			found = 1 ;
			break ;
		}
	}
	file.close() ;
	return found ;
}


	/* THIS FUNCTION DISPLAY THE PASSENGER INFORMATION */

void TICKET :: PASS_INFO(void)
{
	clrscr() ;
	char tno[5] ;
	TRAIN train ;
	train.TRAIN_LIST() ;
	cout <<"\n\n Enter the train no. " ;
	cin >>tno ;
	if (!train.FOUND_TRAIN(tno))
	{
		cout <<"\7\n\nTrain no. is invalid" ;
		getch() ;
		return ;
	}
	clrscr() ;
	int d1,m1,y1, d2,m2,y2, d3,m3,y3, d4,m4,y4 ;
	int d,m,y ;
	DATE dt ;
	dt.CURRENT_DATE() ;
	d1 = dt.day ;
	m1 = dt.month ;
	y1 = dt.year ;
	cout <<"1: " <<d1 <<"/" <<m1 <<"/" <<y1 ;
	dt.EXTEND_DATE(d1,m1,y1) ;
	d2 = dt.day ;
	m2 = dt.month ;
	y2 = dt.year ;
	cout <<"\t2: " <<d2 <<"/" <<m2 <<"/" <<y2 ;
	dt.EXTEND_DATE(d2,m2,y2) ;
	d3 = dt.day ;
	m3 = dt.month ;
	y3 = dt.year ;
	cout <<"\t3: " <<d3 <<"/" <<m3 <<"/" <<y3 ;
	dt.EXTEND_DATE(d3,m3,y3) ;
	d4 = dt.day ;
	m4 = dt.month ;
	y4 = dt.year ;
	cout <<"\t4: " <<d4 <<"/" <<m4 <<"/" <<y4 ;
	int sno=0 ;
	cout <<"\n\nEnter sno. of the date for Passenger Information - " ;
	cin >>sno ;
	if (sno < 1 || sno > 4)
	{
		cout <<"\7\n\nInvalid data" ;
		getch() ;
		return ;
	}
	switch(sno)
	{
		case 1 :  d = d1 ;
				m = m1 ;
				y = y1 ;
				break ;
		case 2 :  d = d2 ;
				m = m2 ;
				y = y2 ;
				break ;
		case 3 :  d = d3 ;
				m = m3 ;
				y = y3 ;
				break ;
		case 4 :  d = d4 ;
				m = m4 ;
				y = y4 ;
				break ;
		default : break ;
	}
	int pnr=0, found=0 ;
	cout <<"\n\n Enter PNR No. of the Ticket : " ;
	cin >>pnr ;
	fstream file ;
	file.open("TICKET.DAT", ios::in) ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if ((dd == d && mm == m && yy == y) && !strcmp(tr_no,tno) && pnr == pnr_no)
		{
			found = 1 ;
			clrscr() ;
			gotoxy(5,5) ;
			cout <<"************************************************************************" ;
			gotoxy(32,7) ;
			cout <<"NORTHERN RAILWAY" ;
			gotoxy(10,9) ;
			cout <<"PNR NO. " <<pnr_no <<"\t\t\t\tDate : " <<dd <<"/" <<mm <<"/" <<yy ;
			gotoxy(10,10) ;
			cout <<"Train no. : " <<tr_no ;
			gotoxy(35,12) ;
			cout <<"From : " <<from <<"\tTo : " <<to ;
			gotoxy(35,13) ;
			cout <<"Kms. " <<kms ;
			gotoxy(10,15) ;
			cout <<"Passenger name : " <<name ;
			gotoxy(10,16) ;
			cout <<"Passenger age : " <<age <<"\t\tSex : " <<sex ;
			gotoxy(10,18) ;
			cout <<"Total Fair : " <<fair ;
			gotoxy(5,20) ;
			cout <<"************************************************************************" ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue..." ;
			getch() ;
			break ;
		}
	}
	file.close() ;
	if (!found)
	{
		cout <<"\n\n\7 Ticket not found" ;
		getch() ;
	}
}


	/* FUNCTION TO RESERVE TICKET FOR THE PASSENGER */

void TICKET :: RESERVATION(void)
{
	clrscr() ;
	char tno[5] ;
	TRAIN train ;
	train.TRAIN_LIST() ;
	cout <<"\n\n Enter the train no. " ;
	cin >>tno ;
	if (!train.FOUND_TRAIN(tno))
	{
		cout <<"\7\n\nTrain no. is invalid" ;
		getch() ;
		return ;
	}
	clrscr() ;
	int d1,m1,y1, d2,m2,y2, d3,m3,y3, d4,m4,y4 ;
	int d,m,y ;
	DATE dt ;
	cout <<"You can reserve ticket only for 3 days, following the current date.\n\n" ;
	dt.CURRENT_DATE() ;
	d1 = dt.day ;
	m1 = dt.month ;
	y1 = dt.year ;
	cout <<"1: " <<d1 <<"/" <<m1 <<"/" <<y1 ;
	dt.EXTEND_DATE(d1,m1,y1) ;
	d2 = dt.day ;
	m2 = dt.month ;
	y2 = dt.year ;
	cout <<"\t2: " <<d2 <<"/" <<m2 <<"/" <<y2 ;
	dt.EXTEND_DATE(d2,m2,y2) ;
	d3 = dt.day ;
	m3 = dt.month ;
	y3 = dt.year ;
	cout <<"\t3: " <<d3 <<"/" <<m3 <<"/" <<y3 ;
	dt.EXTEND_DATE(d3,m3,y3) ;
	d4 = dt.day ;
	m4 = dt.month ;
	y4 = dt.year ;
	cout <<"\t4: " <<d4 <<"/" <<m4 <<"/" <<y4 ;
	int sno=0 ;
	cout <<"\n\nEnter sno. of the date for Reservation - " ;
	cin >>sno ;
	if (sno < 1 || sno > 4)
	{
		cout <<"\7\n\nInvalid data" ;
		getch() ;
		return ;
	}
	switch(sno)
	{
		case 1 :  d = d1 ;
				m = m1 ;
				y = y1 ;
				break ;
		case 2 :  d = d2 ;
				m = m2 ;
				y = y2 ;
				break ;
		case 3 :  d = d3 ;
				m = m3 ;
				y = y3 ;
				break ;
		case 4 :  d = d4 ;
				m = m4 ;
				y = y4 ;
				break ;
		default : break ;
	}
	int pnr=0 ;
	fstream file ;
	file.open("TICKET.DAT", ios::in) ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if ((dd == d && mm == m && yy == y) && !strcmp(tr_no,tno))
			pnr = pnr_no ;
	}
	file.close() ;
	pnr++ ;
	char pname[26], psex, pfrom[15], pto[15], ch ;
	int  pkms, page, pfair ;
	clrscr() ;
	cout <<"\n\n Enter name of passenger : " ;
	gets(pname) ;
	cout <<"\n Enter age : " ;
	cin >>page ;
	if (page <= 5)
	{
		cout <<"\7\nNo ticket is required upto age of 5" ;
		getch() ;
		return ;
	}
	do
	{
		cout <<"\n Enter sex (M/F) : " ;
		cin >>psex ;
	} while (toupper(psex) != 'M' && toupper(psex) != 'F') ;
	cout <<"\n\n Travelling from : " ;
	cin >>pfrom ;
	cout <<"\t To : " ;
	cin >>pto ;
	cout <<"\n Enter Kms. : " ;
	cin >>pkms ;
	pfair = pkms * 0.75 ;
	clrscr() ;
	gotoxy(5,5) ;
	cout <<"************************************************************************" ;
	gotoxy(32,7) ;
	cout <<"NORTHERN RAILWAY" ;
	gotoxy(10,9) ;
	cout <<"PNR NO. " <<pnr <<"\t\t\t\tDate : " <<d <<"/" <<m <<"/" <<y ;
	gotoxy(10,10) ;
	cout <<"Train no. : " <<tno ;
	gotoxy(35,12) ;
	cout <<"From : " <<pfrom <<"\tTo : " <<pto ;
	gotoxy(35,13) ;
	cout <<"Kms. " <<pkms ;
	gotoxy(10,15) ;
	cout <<"Passenger name : " <<pname ;
	gotoxy(10,16) ;
	cout <<"Passenger age : " <<page <<"\t\tSex : " <<psex ;
	gotoxy(10,18) ;
	cout <<"Total Fair : " <<pfair ;
	gotoxy(5,20) ;
	cout <<"************************************************************************" ;
	cout <<"\n\n\n" ;
	do
	{
		cout <<"Do you want to save ticket (y/n) " ;
		cin >>ch ;
	} while (toupper(ch) != 'Y' && toupper(ch) != 'N') ;
	if (toupper(ch) == 'N')
		return ;
//	TICKET t ;
	file.open("TICKET.DAT", ios::app) ;
	t.pnr_no = pnr ;
	t.kms = pkms ;
	strcpy(t.name,pname) ;
	strcpy(t.tr_no,tno) ;
	strcpy(t.from,pfrom) ;
	strcpy(t.to,pto) ;
	t.sex = psex ;
	t.age = page ;
	t.fair = pfair ;
	t.dd = d ;
	t.mm = m ;
	t.yy = y ;
	file.write((char *) &t, sizeof(TICKET)) ;
	file.close() ;
}


	/* FUNCTION TO CENCEL THE RESERVED TICKET OF THE PASSENGER */

void TICKET :: CANCELLATION(void)
{
	clrscr() ;
	char tno[5] ;
	TRAIN train ;
	train.TRAIN_LIST() ;
	cout <<"\n\n Enter the train no. " ;
	cin >>tno ;
	if (!train.FOUND_TRAIN(tno))
	{
		cout <<"\7\n\nTrain no. is invalid" ;
		getch() ;
		return ;
	}
	clrscr() ;
	int d1,m1,y1, d2,m2,y2, d3,m3,y3, d4,m4,y4 ;
	int d,m,y ;
	DATE dt ;
	dt.CURRENT_DATE() ;
	d1 = dt.day ;
	m1 = dt.month ;
	y1 = dt.year ;
	cout <<"1: " <<d1 <<"/" <<m1 <<"/" <<y1 ;
	dt.EXTEND_DATE(d1,m1,y1) ;
	d2 = dt.day ;
	m2 = dt.month ;
	y2 = dt.year ;
	cout <<"\t2: " <<d2 <<"/" <<m2 <<"/" <<y2 ;
	dt.EXTEND_DATE(d2,m2,y2) ;
	d3 = dt.day ;
	m3 = dt.month ;
	y3 = dt.year ;
	cout <<"\t3: " <<d3 <<"/" <<m3 <<"/" <<y3 ;
	dt.EXTEND_DATE(d3,m3,y3) ;
	d4 = dt.day ;
	m4 = dt.month ;
	y4 = dt.year ;
	cout <<"\t4: " <<d4 <<"/" <<m4 <<"/" <<y4 ;
	int sno=0 ;
	cout <<"\n\nEnter sno. of the date for Ticket Cancellation - " ;
	cin >>sno ;
	if (sno < 1 || sno > 4)
	{
		cout <<"\7\n\nInvalid data" ;
		getch() ;
		return ;
	}
	switch(sno)
	{
		case 1 :  d = d1 ;
				m = m1 ;
				y = y1 ;
				break ;
		case 2 :  d = d2 ;
				m = m2 ;
				y = y2 ;
				break ;
		case 3 :  d = d3 ;
				m = m3 ;
				y = y3 ;
				break ;
		case 4 :  d = d4 ;
				m = m4 ;
				y = y4 ;
				break ;
		default : break ;
	}
	int pnr=0, found=0 ;
	char ch ;
	cout <<"\n\n Enter PNR No. of the Ticket to be Cancelled : " ;
	cin >>pnr ;
	fstream file, temp ;
	file.open("TICKET.DAT", ios::in) ;
	temp.open("TEMP.DAT", ios::out) ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if ((dd == d && mm == m && yy == y) && !strcmp(tr_no,tno) && pnr == pnr_no)
		{
			found = 1 ;
			clrscr() ;
			gotoxy(5,5) ;
			cout <<"************************************************************************" ;
			gotoxy(32,7) ;
			cout <<"NORTHERN RAILWAY" ;
			gotoxy(10,9) ;
			cout <<"PNR NO. " <<pnr_no <<"\t\t\t\tDate : " <<dd <<"/" <<mm <<"/" <<yy ;
			gotoxy(10,10) ;
			cout <<"Train no. : " <<tr_no ;
			gotoxy(35,12) ;
			cout <<"From : " <<from <<"\tTo : " <<to ;
			gotoxy(35,13) ;
			cout <<"Kms. " <<kms ;
			gotoxy(10,15) ;
			cout <<"Passenger name : " <<name ;
			gotoxy(10,16) ;
			cout <<"Passenger age : " <<age <<"\t\tSex : " <<sex ;
			gotoxy(10,18) ;
			cout <<"Total Fair : " <<fair ;
			gotoxy(5,20) ;
			cout <<"************************************************************************" ;
			do
			{
				gotoxy(1,25) ; clreol() ;
				cout <<"Do you want to Cancel ticket (y/n) " ;
				cin >>ch ;
			} while (toupper(ch) != 'Y' && toupper(ch) != 'N') ;
		}
		else
			temp.write((char *) this, sizeof(TICKET)) ;
	}
	file.close() ;
	temp.close() ;
	if (!found)
	{
		cout <<"\n\n\7 Ticket not found" ;
		getch() ;
		return ;
	}
	if (toupper(ch) == 'N')
		return ;
	file.open("TICKET.DAT", ios::out) ;
	temp.open("TEMP.DAT", ios::in) ;
	while (temp.read((char *) this, sizeof(TICKET)))
		file.write((char *) this, sizeof(TICKET)) ;
	file.close() ;
	temp.close() ;
}


	/* FUNCTION TO DISPLAY THE LIST OF THE PASSENGER */

void TICKET :: WAITING_LIST(void)
{
	clrscr() ;
	char tno[5] ;
	TRAIN train ;
	train.TRAIN_LIST() ;
	cout <<"\n\n Enter the train no. for the Waiting List " ;
	cin >>tno ;
	if (!train.FOUND_TRAIN(tno))
	{
		cout <<"\7\n\nTrain no. is invalid" ;
		getch() ;
		return ;
	}
	clrscr() ;
	int d1,m1,y1, d2,m2,y2, d3,m3,y3, d4,m4,y4 ;
	int d,m,y ;
	DATE dt ;
	dt.CURRENT_DATE() ;
	d1 = dt.day ;
	m1 = dt.month ;
	y1 = dt.year ;
	cout <<"1: " <<d1 <<"/" <<m1 <<"/" <<y1 ;
	dt.EXTEND_DATE(d1,m1,y1) ;
	d2 = dt.day ;
	m2 = dt.month ;
	y2 = dt.year ;
	cout <<"\t2: " <<d2 <<"/" <<m2 <<"/" <<y2 ;
	dt.EXTEND_DATE(d2,m2,y2) ;
	d3 = dt.day ;
	m3 = dt.month ;
	y3 = dt.year ;
	cout <<"\t3: " <<d3 <<"/" <<m3 <<"/" <<y3 ;
	dt.EXTEND_DATE(d3,m3,y3) ;
	d4 = dt.day ;
	m4 = dt.month ;
	y4 = dt.year ;
	cout <<"\t4: " <<d4 <<"/" <<m4 <<"/" <<y4 ;
	int sno=0 ;
	cout <<"\n\nEnter sno. of the date for Waiting List - " ;
	cin >>sno ;
	if (sno < 1 || sno > 4)
	{
		cout <<"\7\n\nInvalid data" ;
		getch() ;
		return ;
	}
	switch(sno)
	{
		case 1 :  d = d1 ;
				m = m1 ;
				y = y1 ;
				break ;
		case 2 :  d = d2 ;
				m = m2 ;
				y = y2 ;
				break ;
		case 3 :  d = d3 ;
				m = m3 ;
				y = y3 ;
				break ;
		case 4 :  d = d4 ;
				m = m4 ;
				y = y4 ;
				break ;
		default : break ;
	}
	clrscr() ;
	fstream file ;
	file.open("TICKET.DAT", ios::in) ;
	gotoxy(25,1) ;
	cout <<"WAITING LIST OF THE PASSENGERS" ;
	gotoxy(25,2) ;
	cout <<"******************************" ;
	cout <<"\nTrain no.: " <<tno <<"\t\t\t\tDate: " <<d <<"/" <<m <<"/" <<y ;
	gotoxy(2,5) ;
	cout <<" PNR NO.    PASSENGER NAME             FROM                  TO" ;
	gotoxy(1,6) ;
	cout <<"************************************************************************" ;
	int row=8, found=0 ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if ((dd == d && mm == m && yy == y) && !strcmp(tr_no,tno))
		{
			found = 1 ;
			gotoxy(4,row) ;
			cout <<pnr_no ;
			gotoxy(14,row) ;
			cout <<name ;
			gotoxy(41,row) ;
			cout <<from ;
			gotoxy(63,row) ;
			cout <<to ;
			row++ ;
			if (row == 25)
			{
				getch() ;
				for (int i=8; i<=24; i++)
				{
					gotoxy(1,i) ;
					clreol() ;
				}
				row = 8 ;
			}
		}
	}
	file.close() ;
	if (!found)
	{
		cout <<"\n\n\n\n\n\7 No Reservation." ;
		getch() ;
		return ;
	}
	cout <<"\n\nPress any key to continue..." ;
	getch() ;
}



	/* MAIN FUNCTION WHICH DISPLAY MAIN MENU & CALLS ALL OTHER FUNCTIONS */

void main(void)
{
	TICKET ticket ;
	TRAIN train ;
	train.ADDITION() ;
	train.DISPLAY_TRAIN() ;
	char ch, a=30, a1=31 ;
	while (1)
	{
		clrscr() ;
		gotoxy(29,6) ;
		textcolor(WHITE);
		cout <<"** NORTHERN RAILWAY **" ;
		gotoxy(29,7) ;
		for (int i=1; i<=22; i++)
		{
			if (i%2)
				cout <<a ;
			else
				cout <<a1 ;
		}
		gotoxy(29,10) ;
		cout <<"1 :: TRAIN LIST" ;
		gotoxy(29,11) ;
		cout <<"2 :: RESERVATION" ;
		gotoxy(29,12) ;
		cout <<"3 :: CANCELLATION" ;
		gotoxy(29,13) ;
		cout <<"4 :: WAITING LIST" ;
		gotoxy(29,14) ;
		cout <<"5 :: PASSENGER INFO." ;
		gotoxy(29,15) ;
		cout <<"6 :: QUIT" ;
		gotoxy(29,18) ;
		cout <<"Enter your choice :: " ;
		ch = getche() ;
		if (ch == 27 || ch == '6')
			break ;
		else
		if (ch == 't')
			train.DISPLAY_TRAIN() ;
		else
		if (ch == '1')
		{
			train.TRAIN_LIST() ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue..." ;
			getch() ;
		}
		else
		if (ch == '2')
			ticket.RESERVATION() ;
		else
		if (ch == '3')
			ticket.CANCELLATION() ;
		else
		if (ch == '4')
			ticket.WAITING_LIST() ;
		else
		if (ch == '5')
			ticket.PASS_INFO() ;
	}
}