#include <iostream>
#include <vector>
#include "Instrument.h"
#include "Brass.h"
#include "Strings.h"
#include "Keys.h"

using namespace std;

int main()
{
  // Create an array of instruments
  vector<Instrument> instruments = vector<Instrument>();
  instruments.push_back(Brass("Trumpet 1","Toet!","1-99"));
  instruments.push_back(Brass("Trumpet 2","Pwaap!","1-99"));
  instruments.push_back(Brass("Trumpet 3","Zoem!","1-99"));
  instruments.push_back(Strings("Guitar 1","Ploink!","1-99"));
  instruments.push_back(Strings("Guitar 2","Tok!","1-99"));
  instruments.push_back(Keys("Piano","Doeng!","1-99"));

  // Iterate and make sounds
  for (int i = 0; i < instruments.size(); i ++)
  {
    instruments[i].makeSound();
  }

  return 0;
}
