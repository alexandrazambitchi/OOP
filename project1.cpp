#include <iostream>

using namespace std;

class Nod
{
	int val;
	Nod *urm;
public:
	Nod(int val = 0)
	{
		this->val=val;
		this->urm = NULL;
	}
	void setVal(int x) {
        this->val = x;
	}
	void setUrm(Nod *n) {
	    this->urm = n;
	}
	Nod* getUrm() {
        return this->urm;
	}
	int getVal() {
        return this->val;
	}
	friend class Lista;
};

class Lista
{
	int nrElem;
	Nod *prim;

public:
	Lista(int nrElem=0)
	{
		this->nrElem=nrElem;
		this->prim=NULL;
	}
	Nod* getPrim() {
        return this->prim;
	}
	void setPrim(Nod* prim)
	{
		this->prim=prim;
	}
	int getNr()
	{
		return nrElem;
	}
	void setNr()
	{
		this->nrElem=nrElem;
	}
	friend istream& operator>>(istream& i, Lista &lista);
	friend ostream& operator<<(ostream& o, Lista &lista);
	void addLast(int val);
	void deleteLast();
	void reverseLeg();
	void eliminare(int k);
	Lista& operator+(Lista& prim1);
};

void Lista::addLast(int val)
{
	Nod *p = new Nod;
	p->setVal(val);
	if(prim == NULL){
		prim=p;
		prim->setUrm(prim);
	}
	else{
		
		Nod *s = prim;
		while(s->getUrm() != prim) s=s->getUrm();
		s->setUrm(p);
		p->setUrm(prim);
	}
}

void Lista::deleteLast()
{
	Nod* s = prim;
	if(s->getUrm() == prim)
		delete prim;
	else
	{
		while(s->getUrm()->getUrm() != prim) s=s->getUrm();
		Nod* p = s->getUrm();
		s->setUrm(prim);
		delete p;
	}
}

istream& operator>>(istream& i, Lista &lista)
{
	int j;
	for(j=1; j<=lista.getNr(); j++)
	{

			cout<<"Introduceti un element: ";
			int x;
			i>>x;
			lista.addLast(x);
	}
	return i;
}

ostream& operator<<(ostream& o, Lista &lista)
{
	Nod *p;
	p = lista.getPrim();
	do
	{
		o<<p->getVal()<<" ";
		p=p->getUrm();
	}while(p != lista.getPrim());
	return o;
}

Lista& Lista::operator+(Lista& prim1)
{
	Lista *temp;
	temp=this;
	Nod *s=prim1.getPrim();
	do
	{
		temp->addLast(s->val);
		s=s->getUrm();
	}while(s!=prim1.getPrim());
	return *temp;
}

void Lista::eliminare(int k)
{
	int cnt=1;
	Nod *p, *s, *aux;
	p=this->getPrim();
	while(this->getPrim()->getUrm() != this->getPrim())
	{
		while(cnt%k!=0)
		{
			cnt++;
			s=p;
			p=p->getUrm();
		}
		aux=p;
		cnt++;
		p=p->getUrm();
		s->setUrm(p);
		cout<<aux->getVal()<<" ";
		delete aux;
	}
}

void Lista::reverseLeg()
{
	Nod *prev, *next, *act;
	prev=this->getPrim();
	while(prev->getUrm() != this->getPrim())
		prev=prev->getUrm();
	act=this->getPrim();
	do
	{
		next=act->getUrm();
		act->setUrm(prev);
		prev=act;
		act=next;
	}while(act!= this->getPrim());
}

int main()
{
	int t, nrElem;
	cout<<"Citire lista\n";
	cout<<"Numarul de elemente pe care doriti sa le introduceti este: "; cin>>nrElem;
	Lista L(nrElem);
	cin>>L;
	cout<<"1. Afisare lista\n";
	cout<<"2. Inversare legaturi\n";
	cout<<"3. Eliminare din k in k\n";
	cout<<"4. Concatenare \n";
	cout<<"5. Adaugare la final\n";
	cout<<"6. Stergere ultim\n";
	do
	{
		cout<<"Optiunea: ";
		cin>>t;
		switch(t)
		{
			case 1:
			{	
				cout<<"Lista este: ";
				cout<<L;
			}break;
			case 2:
			{
				L.reverseLeg();
			}break;
			case 3:
			{
				int k;
				cin>>k;
				L.eliminare(k);
			}break;
			case 4:
			{
				int nr2;
				cout<<"Numarul de elemente pe care doriti sa le introduceti este: "; cin>>nr2;
				Lista L2(nr2);
				cin>>L2;
				cout<<"Listele dupa concatenare: ";
				cout<<L+L2;
			}break;
			case 5:
			{
				int val;
				cout<<"Valoarea de adaugat: ";
				cin>>val;
				L.addLast(val);
			}break;
			case 6:
				L.deleteLast();
			break;
			default:
				cout<<"Optiune invalida.";
			break;
			case 0:
			break;
			cout<<endl;
		}
		cout<<endl;
	}while(t!=0);
}