#include "sigslot.h"
#include <iostream>
#include <string>


using namespace sigslot;

class O {
	public:
O(const char *p) :s_(p){}
  virtual ~O(){}
  std::string name() const {return s_;}
protected:
  std::string s_;
};

class A :public O {
public:
     A(const char*p): O(p) {}

  signal2<std::string,int> sig;

void run(){
     for(int i=1;i<10;i++){
	sig.emit(name(),i);
    }
}

};

class B :public O,
public has_slots<>
{
public:
    B(const char *p):O(p){
      
    }
  void test(std::string s,int d){
    std::cout<<name()<<" received "<<d<<" from "<<s<<std::endl;
   }
};

int main(){
    A a("A");
    B b("B");
    a.sig.connect(&b,&B::test);
    a.run();
    return 0;

}
