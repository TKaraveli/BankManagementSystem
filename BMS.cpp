#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<locale.h>
using namespace std;
class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
    public:
    void create_account();	//Kullan�c�dan veri alan fonksiyon.
	void show_account() const;	//Kullan�c�ya veri g�steren fonksiyon.
	void modify();	//Veriyi d�zenlemeye yarayan fonksiyon.
	void dep(int);	//Para yat�rmak i�in kulland���m�z fonksiyon.
	void draw(int);	//Para �ekmek i�in kulland���m�z fonksiyon.
	void report() const;	//Veriyi �izelge halinde g�steren fonksiyon.
	int retacno() const;	//Hesap numaras�na d�nmek i�in kulland���m�z fonksiyon.
	int retdeposit() const;	//Hesap bakiyesini g�rmek i�in kulland���m�z fonksiyon.
	char rettype() const;	//Hesap t�r�n� ayarlamak i�in kulland���m�z fonksiyon
};         

void account::create_account()
{
	account(); setlocale(LC_ALL, "Turkish");
	cout<<"\nHesap numaras�n� giriniz. :";
	cin>>acno;
	cout<<"\n\nHesap sahibinin ad�n� giriniz. : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nHesap t�r�n� giriniz.Vadeli veya C�ri hesap (V/C) : "; //C harfi C�ri hesap a�mak i�in , V harfi ise Vadeli hesap a�mak i�in kullan�l�r.
	cin>>type;
	type=toupper(type);
	cout<<"\nBa�lang�� tutar�n� giriniz.(Vadeli hesap i�in >=500 ve C�ri hesap i�in >=1000 ) : ";
	cin>>deposit;
	cout<<"\n\n\nHesab�n�z olu�turuldu..";
}

void account::show_account() const
{
	cout<<"\nHesap numaras� : "<<acno;
	cout<<"\nHesap sahibi : ";
	cout<<name;
	cout<<"\nHesap t�r� : "<<type;
	cout<<"\nHesap bakiyesi : "<<deposit;
}


void account::modify()
{
	cout<<"\nHesap numaras� : "<<acno;
	cout<<"\nHesap sahibinin ad�n� d�zenle : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nHesap bakiyesini d�zenle : ";
	cin>>deposit;
	type=toupper(type);
	cout<<"\nHesap t�r�n� d�zenle : ";
	cin>>type;
}
void account::dep(int x)
{
	deposit+=x;
}
void account::draw(int x)
{
	deposit-=x;
}
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}
int account::retacno() const
{
return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


void write_account();	//�kili say� sisteminde kay�t tutan fonksiyon.
void display_sp(int);	//Kullan�c�n�n girdi�i hesap detaylar�n� g�steren fonksiyon.
void modify_account(int);	//Hesab� d�zenleyen fonksiyon.
void delete_account(int);	//Hesap numaras�n� silen fonksiyon
void display_all();		//B�t�n hesaplar�n detaylar�n� g�steren fonksiyon.
void deposit_withdraw(int, int); //Para �ekmek veya yat�rmak i�in kullanaca��m�z fonksiyon.
void intro();	//Tan�t�m ekran�m�z.

//PROGRAMIMIZIN ANA FONKS�YONU

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		account(); setlocale(LC_ALL, "Turkish");
		system("cls");
		cout<<"\n\n\n\tANA MEN�";
		cout<<"\n\n\t01. YEN� HESAP";
		cout<<"\n\n\t02. PARA YATIR";
		cout<<"\n\n\t03. PARA �EK";
		cout<<"\n\n\t04. BAK�YE SORGULAMA";
		cout<<"\n\n\t05. B�T�N HESAP SAH�PLER�";
		cout<<"\n\n\t06. B�R HESABI KAPAT";
		cout<<"\n\n\t07. B�R HESABI D�ZENLE";
		cout<<"\n\n\t08. �IKI�";
		cout<<"\n\n\tSe�ene�inizi belirtin. (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tHesap numaras�n� girin. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tHesap numaras�n� girin. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tHesap numaras�n� girin. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tHesap numaras�n� girin. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tHesap numaras�n� girin. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tBanka y�netim sistemimizi kulland���n�z i�in te�ekk�r ederiz.";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

//Kay�t tutma fonksiyonu
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//Ki�isel kay�tlar� okuyan fonksiyon
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Dosya a��lamad� !! Bir tu�a bas�n...";
		return;
	}
	cout<<"\nHESAP DETAYLARI\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nHesap numaras� mevcut de�il.";
}


//Hesap kayd�n� d�zenleyen fonksiyon

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Dosya a��lamad� !! Bir tu�a bas�n...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nYeni hesap detaylar�n� girin."<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Kay�t g�ncellendi.";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Kay�t bulunamad�. ";
}

//Hesap kayd�n� silen fonksiyon


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Dosya a��lamad� !! Bir tu�a bas�n...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tKay�t silindi ..";
}

//B�t�n hesaplar�n detaylar�n� g�steren fonksiyon

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Dosya a��lamad� !! Bir tu�a bas�n...";
		return;
	}
	cout<<"\n\n\t\tHESAP SAH�PLER� L�STES�\n\n";
	cout<<"====================================================\n";
	cout<<"Hesap no.           �S�M          T�R   BAK�YE\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//Para �ekme ve yat�rma fonksiyonu

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Dosya a��lamad� !! Bir tu�a bas�n...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tPARA YATIRMAK ���N ";
				cout<<"\n\nYat�r�lacak miktar� girin.";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tPARA �EKMEK ���N ";
				cout<<"\n\n�ekilecek miktar� girin.";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='V') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Yetersiz bakiye.";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Kay�t g�ncellendi.";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Kay�t bulunamad�. ";
}


//Tan�t�m fonksiyonu


void intro()
{
	account(); setlocale(LC_ALL, "Turkish");
	cout<<"\n\n\n\t  BANKA";
	cout<<"\n\n\tY�NET�M";
	cout<<"\n\n\t  S�STEM�";
	cout<<"\n\n\n\nHAZIRLAYAN : TAYFUN KARAVEL�";
	cout<<"\n\nOKUL : �STANBUL GEL���M �N�VERS�TES�";
	cin.get();
}
