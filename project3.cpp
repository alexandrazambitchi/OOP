//Zambitchi Alexandra 133 
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define MAX 1000
class statie
{
private:
	char strada[MAX];
	int nr_strada;
	int sector;
	int nr_transp;
	int transp[MAX];
	static int cod_statie;
	char nume[MAX];
public:
	statie(char strada=NULL, int nr_strada=0, int sector=0, int nr_transp=0, int transp[]=0, char nume=NULL)
	{
		strcpy(this->strada, strada);
		this->nr_strada=nr_strada;
		this->sector=sector;
		for(int i=0;i<(this->transp.size());i++)
			this->transp[i]=transp[i];
		strcpy(this->nume, nume);
		cod_statie++;
	}
	char *getStrada()
	{
		return this->strada;
	}
	void setStrada(char strada[MAX])
	{
		strcpy(this->strada,strada);
	}
	int getNr_strada()
	{
		return this->nr_strada;
	}
	void setNr_strada(int nr)
	{
		nr_strada=nr;
	}
	int getSector()
	{
		return this->sector;
	}
	void setSector(int sect)
	{
		sector=sect;
	}
	int getNr_transp()
	{
		return this->nr_transp;
	}
	void setNr_strada(int nr)
	{
		nr_transp=nr;
	}
	int *getTransp()
	{
		return this->transp;
	}
	static int getCod_statie()
	{
		return this->cod_statie;
	}
	char* getNume()
	{
		return this->nume;
	}
	void setNume(char nume[MAX])
	{
		strcpy(this->nume, nume);
	}
	virtual void afisare()
	{
		cout<<"Numele statiei: "<<nume<<"\n";
		cout<<"Adresa: "<<strada<<" "<<nr_strada<<" "<<sector<<"\n";
		cout<<"Mijloace de transport care opresc: ";
		for(int i=0;i<nr_transp;i++)
			cout<<transp[i]<<" ";
		cout<<"\n";
	}
	friend istream& operator>>(istream&, statie&);
};

istream& operator>>(istream& in, statie& st)
{
	cout<<"Introduceti numele statiei: ";
	in>>nume;
	cout<<"Adresa statiei (strada, numar, sector; ex: Unirii 20 3): ";
	in>>strada>>nr_strada>>sector;
	cout<<"Numarul de mijloace de transport care opresc in aceasta statie: ";
	in>>nr_transp;
	cout<<"Mijloacele de transport (ex 123, 66, 1): "
	for(int i=0;i<nr_transp;i++)
		in>>transp[i];
	return in;
}

class statie_urbana: public class statie
{
private:
	int punct_achizitie;
	int obiective;
public:
	statie_urbana(int punct_achizitie=0, int obiective=0, char strada=NULL, int nr_strada=0, int sector=0, int nr_transp, int transp[]=0, char nume=NULL): statie(char strada=NULL, int nr_strada=0, int sector=0, int nr_transp, int transp[]=0, char nume=NULL)
	{
		this->punct_achizitie=punct_achizitie;
		this->obiective=obiective;
	}
	int getPunct()
	{
		return this->punct_achizitie;
	}
	void setPunct(int info)
	{
		punct_achizitie=info;
	}
	int getObiective()
	{
		return this->obiective;
	}
	void setPunct(int obiective)
	{
		this->obiective=obiective;
	}
	void afisare()
	{
		statie::afisare();
		if(punct_achizitie==0)
			cout<<"Statia nu are punct de achizitionare al legitimatiilor.\n";
		else
			cout<<"Statia are punct de achizitionare al legitimatiilor.\n";
		if(obiective==0)
			cout<<"Statia nu are in apropiere obiective de interes pentru turisti.\n";
		else
			cout<<"Statia are in apropiere obiective de interes pentru turisti.\n";
	}
	friend istream& operator>>(istream&, statie_urbana&);
};

istream& operator>>(istream& in, statie_urbana& su)
{
	in>>statie& su;
	cout<<"Statia are punct de achizitionare? 1-da 0-nu\n";
	in>>punct_achizitie;
	cout<<"Statia are prin apropiere vreun obiectiv de interes? 1-da 0-nu\n";
	in>>obiective;
	return in;
}

class statie_extraurbana: public class statie
{
private:
	int obiective;
public:
	statie_extraurbana(int obiective, char strada=NULL, int nr_strada=0, int sector=0, int nr_transp, int transp[]=0, char nume=NULL): statie(char strada=NULL, int nr_strada=0, int sector=0, int nr_transp, int transp[]=0, char nume=NULL)
	{
		this->obiective=obiective;
	}
	int getObiective()
	{
		return this->obiective;
	}
	void setPunct(int obiective)
	{
		this->obiective=obiective;
	}
	void afisare()
	{
		statie::afisare();
		if(obiective==0)
			cout<<"Statia nu are in apropiere obiective de interes pentru turisti.\n";
		else
			cout<<"Statia are in apropiere obiective de interes pentru turisti.\n";
	}
	friend istream& operator>>(istream&, statie_extraurbana&);
};

istream& operator>>(istream& in, statie_extraurbana& se)
{
	in>>statie& se;
	cout<<"Statia are prin apropiere vreun obiectiv de interes? 1-da 0-nu\n";
	in>>obiective;
	return in;
}




