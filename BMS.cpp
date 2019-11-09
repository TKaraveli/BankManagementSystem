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
    void create_account();	//Kullanýcýdan veri alan fonksiyon.
	void show_account() const;	//Kullanýcýya veri gösteren fonksiyon.
	void modify();	//Veriyi düzenlemeye yarayan fonksiyon.
	void dep(int);	//Para yatýrmak için kullandýðýmýz fonksiyon.
	void draw(int);	//Para çekmek için kullandýðýmýz fonksiyon.
	void report() const;	//Veriyi çizelge halinde gösteren fonksiyon.
	int retacno() const;	//Hesap numarasýna dönmek için kullandýðýmýz fonksiyon.
	int retdeposit() const;	//Hesap bakiyesini görmek için kullandýðýmýz fonksiyon.
	char rettype() const;	//Hesap türünü ayarlamak için kullandýðýmýz fonksiyon
};         

void account::create_account()
{
	account(); setlocale(LC_ALL, "Turkish");
	cout<<"\nHesap numarasýný giriniz. :";
	cin>>acno;
	cout<<"\n\nHesap sahibinin adýný giriniz. : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nHesap türünü giriniz.Vadeli veya Câri hesap (V/C) : "; //C harfi Câri hesap açmak için , V harfi ise Vadeli hesap açmak için kullanýlýr.
	cin>>type;
	type=toupper(type);
	cout<<"\nBaþlangýç tutarýný giriniz.(Vadeli hesap için >=500 ve Câri hesap için >=1000 ) : ";
	cin>>deposit;
	cout<<"\n\n\nHesabýnýz oluþturuldu..";
}

void account::show_account() const
{
	cout<<"\nHesap numarasý : "<<acno;
	cout<<"\nHesap sahibi : ";
	cout<<name;
	cout<<"\nHesap türü : "<<type;
	cout<<"\nHesap bakiyesi : "<<deposit;
}


void account::modify()
{
	cout<<"\nHesap numarasý : "<<acno;
	cout<<"\nHesap sahibinin adýný düzenle : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nHesap bakiyesini düzenle : ";
	cin>>deposit;
	type=toupper(type);
	cout<<"\nHesap türünü düzenle : ";
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


void write_account();	//Ýkili sayý sisteminde kayýt tutan fonksiyon.
void display_sp(int);	//Kullanýcýnýn girdiði hesap detaylarýný gösteren fonksiyon.
void modify_account(int);	//Hesabý düzenleyen fonksiyon.
void delete_account(int);	//Hesap numarasýný silen fonksiyon
void display_all();		//Bütün hesaplarýn detaylarýný gösteren fonksiyon.
void deposit_withdraw(int, int); //Para çekmek veya yatýrmak için kullanacaðýmýz fonksiyon.
void intro();	//Tanýtým ekranýmýz.

//PROGRAMIMIZIN ANA FONKSÝYONU

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		account(); setlocale(LC_ALL, "Turkish");
		system("cls");
		cout<<"\n\n\n\tANA MENÜ";
		cout<<"\n\n\t01. YENÝ HESAP";
		cout<<"\n\n\t02. PARA YATIR";
		cout<<"\n\n\t03. PARA ÇEK";
		cout<<"\n\n\t04. BAKÝYE SORGULAMA";
		cout<<"\n\n\t05. BÜTÜN HESAP SAHÝPLERÝ";
		cout<<"\n\n\t06. BÝR HESABI KAPAT";
		cout<<"\n\n\t07. BÝR HESABI DÜZENLE";
		cout<<"\n\n\t08. ÇIKIÞ";
		cout<<"\n\n\tSeçeneðinizi belirtin. (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tHesap numarasýný girin. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tHesap numarasýný girin. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tHesap numarasýný girin. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tHesap numarasýný girin. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tHesap numarasýný girin. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tBanka yönetim sistemimizi kullandýðýnýz için teþekkür ederiz.";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

//Kayýt tutma fonksiyonu
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//Kiþisel kayýtlarý okuyan fonksiyon
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Dosya açýlamadý !! Bir tuþa basýn...";
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
		cout<<"\n\nHesap numarasý mevcut deðil.";
}


//Hesap kaydýný düzenleyen fonksiyon

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Dosya açýlamadý !! Bir tuþa basýn...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nYeni hesap detaylarýný girin."<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Kayýt güncellendi.";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Kayýt bulunamadý. ";
}

//Hesap kaydýný silen fonksiyon


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Dosya açýlamadý !! Bir tuþa basýn...";
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
	cout<<"\n\n\tKayýt silindi ..";
}

//Bütün hesaplarýn detaylarýný gösteren fonksiyon

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"Dosya açýlamadý !! Bir tuþa basýn...";
		return;
	}
	cout<<"\n\n\t\tHESAP SAHÝPLERÝ LÝSTESÝ\n\n";
	cout<<"====================================================\n";
	cout<<"Hesap no.           ÝSÝM          TÜR   BAKÝYE\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//Para çekme ve yatýrma fonksiyonu

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"Dosya açýlamadý !! Bir tuþa basýn...";
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
				cout<<"\n\n\tPARA YATIRMAK ÝÇÝN ";
				cout<<"\n\nYatýrýlacak miktarý girin.";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tPARA ÇEKMEK ÝÇÝN ";
				cout<<"\n\nÇekilecek miktarý girin.";
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
			cout<<"\n\n\t Kayýt güncellendi.";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Kayýt bulunamadý. ";
}


//Tanýtým fonksiyonu


void intro()
{
	account(); setlocale(LC_ALL, "Turkish");
	cout<<"\n\n\n\t  BANKA";
	cout<<"\n\n\tYÖNETÝM";
	cout<<"\n\n\t  SÝSTEMÝ";
	cout<<"\n\n\n\nHAZIRLAYAN : TAYFUN KARAVELÝ";
	cout<<"\n\nOKUL : ÝSTANBUL GELÝÞÝM ÜNÝVERSÝTESÝ";
	cin.get();
}
