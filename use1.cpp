#include<iostream>
#include"simvd.cpp"

int main(){
  simvd x;
  
  x.append(-50);
  x.append(75);

  x.printv();
  x.set(25,1);
  x.printv();

  x.insert(1,0);
  x.printv();

  x.append(10);
  x.append(-10);
  x.append(100);
  x.append(5);
  x.printv();
  x.sort();
  x.printv();

  return 0;
}
