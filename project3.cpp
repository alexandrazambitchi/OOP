#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>
using namespace std;

class Examen
{
	static int nr_exam;
	char den_materie[10];
	float nota_partial, nota_quiz;
public:
	Examen(char denumire[], float nota_partial=0, float nota_quiz=0)
	{
		strcpy(den_materie,denumire);
		this->nota_partial=nota_partial;
		this->nota_quiz=nota_quiz;
		nr_exam++;
	}
	~Examen()
	{
		nr_exam--;
		strcpy(den_materie,"");
		nota_partial=0;
		nota_quiz=0;
	}
	void setMaterie(char denumire[])
	{
		strcpy(this->den_materie, denumire);
	}
	void setNota_partial(float nota_partial)
	{
		this->nota_partial=nota_partial;
	}
	void setNota_quiz(float nota_quiz)
	{
		this->nota_quiz=nota_quiz;
	}
	char* getMaterie()
	{
		return this->den_materie;
	}
	float getNota_partial()
	{
		return this->nota_partial;
	}
	float getNota_quiz()
	{
		return this->nota_quiz;
	}
	static int getNr()
	{
		return nr_exam;
	}
	virtual void afisare()
	{
		float x;
		cout<<"\nExamenul la materia: "<<den_materie<<endl;
		cout<<"Nota la partial este "<<nota_partial<<endl;
		if(nota_quiz!=0)
			cout<<"A fost dat si quiz-ul si s-a obtinut punctajul: "<<nota_quiz<<endl;
		else
			cout<<"Nu a fost dat quiz.\n";
		cout<<"Nota partial+quiz este: ";
		x=nota_partial+nota_quiz;
		if(x>5)
			cout<<5<<endl;
		else
			cout<<x<<endl;
	}
	friend istream& operator >>(istream&, Examen&);
	friend ostream& operator <<(ostream&, Examen&);
	Examen& operator =(const Examen& ex)
	{
		strcpy(den_materie, ex.den_materie);
		nota_partial=ex.nota_partial;
		nota_quiz=ex.nota_quiz;
		return *this;
	}
};

istream& operator >>(istream& in, Examen& ex)
{
	cout<<"Materia: ";
	in>>ex.den_materie;
	cout<<"Nota partial (0-5): ";
	float intrare1, intrare2;
	int opt;
	try
	{
		in>>intrare1;
		if(intrare1<0 || intrare1>5)
			throw intrare1;
		ex.nota_partial=intrare1;
	}
	catch (float intrare1)
	{
		cout<<"Nota invalida.\n";
		return in;
	}
	cout<<"Se doreste quiz? 1.Da 2.Nu\n";
	in>>opt;
	if(opt==1)
	{
		cout<<"Nota quiz (0-2): ";
		try
		{
			in>>intrare2;
			if(intrare2<0 || intrare2>2)
				throw intrare2;
			ex.nota_quiz=intrare2;
		}
		catch (float intrare2)
		{
			cout<<"Nota invalida.\n ";
			return in;
		}
	}
	
	return in;
}

int Examen::nr_exam=0;

class Examen_final: public Examen
{
	char den_materie[10];
	float puncte, nota_scris;
	int proiect;
public:
	Examen_final(char denumire[10]=NULL, float puncte_bonus=0, float nota_scris=0, float partial=0, float quiz=0): Examen(denumire, partial, quiz)
	{
		puncte=puncte_bonus;
		this->nota_scris=nota_scris;
	}
	void setpct(float puncte)
	{
		this->puncte=puncte;
	}
	float getpct()
	{
		return this->puncte;
	}
	void setnota_scris(float nota_scris)
	{
		this->nota_scris=nota_scris;
	}
	float getnota_scris()
	{
		return this->nota_scris;
	}
	void setMaterie(char denumire[])
	{
		strcpy(this->den_materie, denumire);
	}
	char* getMaterie()
	{
		return this->den_materie;
	}
	~Examen_final()
	{
		puncte=0;
		strcpy(den_materie,"");
		nota_scris=0;
	}
	unsigned int calcul_notafin()
	{
		int opt;
		float final=Examen::getNota_partial()+nota_scris+puncte;
		cout<<"\nSe doreste quiz? 1.Da 2.Nu\n";
		cin>>opt;
		if(opt==1)
		{	
			final=final+Examen::getNota_quiz();
			cout<<"Nota dupa adaugarea quiz-ului: "<<final<<endl;
		}
		else
			cout<<"Nota finala (fara quiz): "<<final<<endl;
		return round(final);
	}
	void afisare()
	{
		float auxp, final;
		int opt, ok=0;
		Examen::afisare();
		cout<<"Nota la scris este: "<<nota_scris<<endl;
		cout<<"Punctaj proiect: "<<puncte<<endl;
		if(Examen::getNota_partial()<2.5)
		{
			cout<<"Introduceti noua nota la partial: ";
			cin>>auxp;
			setNota_partial(auxp);
			ok=1;
		}
		if(Examen::getNota_partial()>2.5 || ok==1)
		{
			unsigned int nota_fin=calcul_notafin();
			if(nota_fin>=10)
				cout<<"Nota se va rotunji la 10.\n";
			else
				cout<<"Nota finala este: "<<nota_fin<<endl;
		}

	}
	friend istream& operator >>(istream&, Examen_final&);
	Examen_final& operator =(Examen_final& ex)
	{
		strcpy(den_materie, ex.den_materie);
		puncte=ex.puncte;
		nota_scris=ex.nota_scris;
		return *this;
	} 
};

istream& operator >>(istream& in, Examen_final& ex)
{
	in>>(Examen&)ex;
	cout<<"Proiectul a fost facut?\n1.Da 2.Nu\n";
	int opt;
	float intrare2, intrare3;
	in>>opt;
	if(opt==1)
	{
		cout<<"Punctele din proiect (0-1): ";
		try 
		{
			in>>intrare2;
			if(intrare2 <0 || intrare2>1)
				throw intrare2;
			ex.puncte=intrare2;
		}
		catch (float intrare2)
		{
			cout<<"Numar de puncte invalid.\n";
			return in;
		}
	}
	else
		ex.puncte=0;
	cout<<"Nota la examenul scris este (0-5): ";
	try
	{
		in>>intrare3;
		if(intrare3<0 || intrare3>5)
			throw intrare3;
		ex.nota_scris=intrare3;
	}
	catch(float intrare3)
	{
		cout<<"Nota invalida.\n";
		return in;
	}
	return in;
}

template <class T> 
class CatalogIndividual
{
	static int nr_matricol;
	int nr_examene;
	vector<T*> examene;
public:
	CatalogIndividual (int nr_examene=0)
	{
		this->nr_examene=nr_examene;
		nr_matricol++;
	}
	~CatalogIndividual()
	{
		int i;
		for(i=0;i<examene.size();i++)
			delete examene[i];
		nr_matricol--;
	}
	CatalogIndividual(const CatalogIndividual<T> &ex)
	{
		examene=ex.examene;
		nr_matricol=ex.nr_matricol;
		nr_examene=ex.nr_examene;
	}
	CatalogIndividual<T>& operator +=(T &ex)
	{
		examene.push_back(&ex);
		return *this;
	}
	static int getNr_matricol()
	{
		return nr_matricol;
	}
	int getNr_exam()
	{
		return this->nr_examene;
	}
	void setNr_exam(int nr)
	{
		this->nr_examene=nr;
	}
	void afisare()
	{
		if(Examen::getNr()!=0)
			cout<<"Studentul cu numarul matricol "<<nr_matricol<<" are notele:\n";
		for(int i=0;i<Examen::getNr();i++)
			if(Examen_final *s1 = dynamic_cast<Examen_final*>(examene[i]))
				s1->afisare();
	}

};

template <class T>
int CatalogIndividual<T>::nr_matricol=0;

template <>
class CatalogIndividual<unsigned>
{
	unsigned int suma;
public:
	CatalogIndividual()
	{
		suma=0;
	}
	~CatalogIndividual(){}
	*CatalogIndividual(CatalogIndividual<unsigned> &m)
	{
		suma=m.suma;
	}
	CatalogIndividual <unsigned>& operator +=(unsigned int m)
	{
		suma=suma+m;
		return *this;
	}
	void calcul_medie()
	{
		cout<<"Medii finale: "<<(unsigned int)suma/Examen::getNr()<<"\n";
	}
};

int main()
{
	int t, nr;
	cout<<"\nNumarul de examene pentru fiecare student: ";
	cin>>nr;
	cout<<"\n1. Introducere note.\n";
	cout<<"2. Afisare catalog.\n";
	cout<<"0. Iesire program.\n";

	CatalogIndividual<Examen> student(nr);
	CatalogIndividual<unsigned> Med;
	do
	{
		Examen_final *Ef;
		cout<<"Optiunea: ";
		cin>>t;
		switch(t)
		{
			case 1:
			{
				if(Examen::getNr()==student.getNr_exam())
					cout<<"Nu se mai pot adauga examene.\n";
				else
				{
					Ef=new Examen_final("", 0, 0, 0, 0);
					cin>>(*Ef);
					student += (*Ef);
					Med += Ef->calcul_notafin();
				}
			}break;
			case 2:
			{
				student.afisare();
			}break;
			case 0:
			break;
		}
	}while(t==1 || t==2);
	Med.calcul_medie();
	return 0;
}
