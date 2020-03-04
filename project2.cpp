#include <iostream>

using namespace std;

class Complex
{
	float re, im;
public:
	void setre(float r)
	{
		this->re=r;
	} 
	float getre()
	{
		return this->re;
	}
	void setim(float i)
	{
		this->im=i;
	}
	float getim()
	{
		return this->im;
	}
	Complex(float real=0, float imag=0)
	{
		re=real;
		im=imag;
	}
	~Complex(){};
	Complex(const Complex &nr)
	{
		re=nr.re;
		im=nr.im;
	}
	friend class Vector;
	friend istream& operator>>(istream& i,Complex& c);
  	friend ostream& operator<<(ostream& o,Complex& c);
  	Complex operator=(Complex c);
};

istream& operator>>(istream& i,Complex& c)
{
	i>>c.re;
	cout<<endl;
	i>>c.im;
	cout<<endl;
	return i;
}

ostream& operator<<(ostream& o,Complex& c)
{
 	o<<"Numarul este: "<<c.re<<"+"<<c.im<<"*i\n";
  	return o;
}

Complex Complex::operator=(Complex c)
{
 	re=c.re;
 	im=c.im;
	//return *this;
}

class Vector
{
	int dim;
	Complex *v;
public:
	Vector(int d=0)
	{
		dim=d;
		v=new Complex [d]();
	}
	Complex* getv()
	{
		return this->v;
	}
	void setv(Complex* v)
	{
		this->v=v;
	}
	int getdim()
	{
		return this->dim;
	}
	void setdim(int dim)
	{
		this->dim=dim;
	}
	~Vector(){};
	Vector(const Vector &vect)
	{
		dim=vect.dim;
		v=new Complex[dim];
		for(int i=0;i<dim;i++)
			v[i]=vect.v[i];
	}
	virtual void citire(istream& in)=0;
	virtual void afisare(ostream& out)=0;
	virtual void adaugare(float real, float imag)=0;
	virtual void stergere()=0;
	virtual int verif_imag()=0;
};

istream& operator>>(istream& in, Vector& v)
{
	v.citire(in);
	return in;
}

ostream& operator<<(ostream& out, Vector& v)
{
	v.afisare(out);
	return out;
}

class Stiva: public Vector
{
	int nrelem;
public:
	Stiva(int nr): Vector(nr)
	{
		nrelem=nr;
	}
	void setnr(int nrelem)
	{
		this->nrelem=nrelem;
	}
	int getnr()
	{
		return this->nrelem;
	}
	void adaugarecit(float real, float imag)
	{
		Complex *p;
		p=getv();
		for(int i=nrelem;i>=1;i--)
			p[i]=p[i-1];
		p[0].setre(real);
		p[0].setim(imag);
	}
	void adaugare(float real, float imag)
	{
		Complex *p;
		p=getv();
		for(int i=nrelem;i>=1;i--)
			p[i]=p[i-1];
		p[0].setre(real);
		p[0].setim(imag);
		nrelem++;
	}
	void citire(istream& in)
	{
		int i;
		float x, y;
		cout<<"Introduceti numerele sub forma real-imaginar\n";
		for(i=1;i<=nrelem;i++)
		{
			cout<<"Numarul: ";
			in>>x>>y;
			adaugarecit(x, y);
		}
	}
	void afisare(ostream& out)
	{
		Complex *p;
		p=getv();
		int i;
		for(i=0;i<nrelem;i++)
			out<<p[i];
		out<<endl;
	}
	void stergere()
	{
		Complex *p;
		p=getv();
		for(int i=0;i<nrelem-1;i++)
			p[i]=p[i+1];
		nrelem--;

	}
	int verif_imag()
	{
		Complex *p;
		p=getv();
		for(int i=0;i<nrelem;i++)
			if(p[i].getre()!=0)
				return 0;
		return 1;
	}
	Stiva(const Stiva &stiv): Vector(stiv)
	{
		nrelem=stiv.nrelem;
	}
	~Stiva()
	{
		delete this;
	}
};

class Coada: public Vector
{
	int nrelem;
public:
	Coada(int nr): Vector(nr)
	{
		nrelem=nr;
	}
	void setnr(int nrelem)
	{
		this->nrelem=nrelem;
	}
	int getnr()
	{
		return this->nrelem;
	}
	void adaugare(float real, float imag)
	{
		Complex *p;
		p=getv();
		p[nrelem].setre(real);
		p[nrelem].setim(imag);
		nrelem++;
	}
	void citire(istream& in)
	{
		int i;
		float x, y;
		Complex *p;
		p=getv();
		cout<<"Introduceti numerele sub forma real-imaginar\n";
		for(i=1;i<=nrelem;i++)
		{
			cout<<"Numarul: ";
			in>>x>>y;
			p[i-1].setre(x);
			p[i-1].setim(y);
		}
	}
	void afisare(ostream& out)
	{
		Complex *p;
		p=getv();
		int i;
		for(i=0;i<nrelem;i++)
			out<<p[i];
		out<<endl;
	}
	void stergere()
	{
		Complex *p;
		p=getv();
		for(int i=0;i<nrelem-1;i++)
			p[i]=p[i+1];
		nrelem--;
	}
	int verif_imag()
	{
		Complex *p;
		p=getv();
		for(int i=0;i<this->nrelem;i++)
			if(p[i].getre()!=0)
				return 0;
		return 1;
	}
	Coada(const Coada &cod): Vector(cod)
	{
		nrelem=cod.nrelem;
	}
	~Coada()
	{
		delete this;
	}
};

int main()
{
	int t, dims, dimc, x=1, y=1;
	cout<<"\n";
	cout<<"1. Citire stiva\n";
	cout<<"2. Citire coada\n";
	cout<<"3. Afisare stiva\n";
	cout<<"4. Afisare coada\n";
	cout<<"5. Adaugare element stiva\n";
	cout<<"6. Stergere element stiva\n";
	cout<<"7. Verificare stiva pur imaginara\n";
	cout<<"8. Adaugare element coada\n";
	cout<<"9. Stergere element coada\n";
	cout<<"10. Verificare coada pur imaginara\n";

	cout<<"\nDimensiunea stivei: ";
	cin>>dims;

	cout<<"Dimensiunea cozii: ";
	cin>>dimc;

	Coada C(dimc);
	Stiva S(dims);

	if(dims==0)
		x=0;
	if(dimc==0)
		y=0;

	do
	{
		cout<<"Optiunea: ";
		cin>>t;
		switch(t)
		{
			case 1:
			{
				if(x==0)
					cout<<"Imposibil de citit stiva\n";
				else
				{
					cin>>S;
					x=1;
				}
			}break;
			case 2:
			{
				if(y==0)
					cout<<"Imposibil de citit coada\n";
				else
				{
					cin>>C;
					y=1;
				}
			}break;
			case 3:
			{
				if(x==1)
				{
					cout<<"Stiva:\n";
					cout<<S;
				}
				else
					cout<<"Stiva nu exista\n";
			}break;
			case 4:
			{
				if(y==1)
				{
					cout<<"Coada:\n";
					cout<<C;
				}
				else
					cout<<"Coada nu exista\n";
			}break;
			case 5:
			{
				if(x==1)
				{
					float a, b;
					cout<<"Numarul de adaugat: (re-im): ";
					cin>>a>>b;
					S.adaugare(a,b);
				}
				else
					cout<<"Stiva nu exista\n";
			}break;
			case 6:
			{
				if(x==1)
				{
					S.stergere();
				}
				else
					cout<<"Stiva nu exista\n";
			}break;
			case 7:
			{
				if(x==1)
				{
					if(S.verif_imag()==1)
						cout<<"Stiva este pur imaginara\n";
					else
						cout<<"Stiva nu este pur imaginara\n";
				}
				else
					cout<<"Stiva nu exista\n";
			}break;
			case 8:
			{
				if(y==1)
				{
					float a, b;
					cout<<"Numarul de adaugat: (re-im): ";
					cin>>a>>b;
					C.adaugare(a,b);
				}
				else
					cout<<"Coada nu exista\n";
			}break;
			case 9:
			{
				if(y==1)
				{
					C.stergere();
				}
				else
					cout<<"Coada nu exista\n";
			}break;
			case 10:
			{
				if(y==1)
				{
					if(C.verif_imag()==1)
						cout<<"Coada este pur imaginara\n";
					else
						cout<<"Coada nu este pur imaginara\n";
				}
				else
					cout<<"Coada nu exista\n";
			}break;
			default:
				cout<<"Optiune invalida\n";
			break;
			case 0:
			break;
		}
	}while(t!=0);
	return 0;
}