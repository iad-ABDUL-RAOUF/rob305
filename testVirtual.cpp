#include <iostream>

class Mother
{
public:
  void print() const;
  virtual void vprint() const;
};

void Mother::print() const
{
  std::cout << "Mother simple print" << std::endl;
}

void Mother::vprint() const
{
  std::cout << "Mother virtual print" << std::endl;
}

class Daugther : public Mother // daugther derivie de mother et on dit aussi que c'est une specialisatio de mother
{
public:
  void print() const;
  void vprint() const override; //override semble juste etre un 'test'. pas besoin pour reecrire une fonction virtuelle mais si la fonction n'est pas virtuelle alors renvois une erreur
  // Daughter herite de mother et donc cette fonction est automatiquement virtuelle. on ne peux pas devirtualiser des fonctions
};

void Daugther::print() const
{
  std::cout << "Daugther simple print" << std::endl;
}

void Daugther::vprint() const
{
  std::cout << "Daugther virtual print" << std::endl;
}

int main()
{
  Mother mother;
  Daugther daugther;

  Mother* pmother[2];

  pmother[0] = &mother;
  pmother[1] = &daugther;

  pmother[0]->print();
  pmother[0]->vprint();
  pmother[1]->print();
  pmother[1]->vprint();

  daugther.print();
  daugther.vprint();

}