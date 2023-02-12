

#ifndef RNDSET_H
#define	RNDSET_H


class RndSet{
 public:
   unsigned long int num;
   bool pass;

    RndSet(): num(0){
        //num=0;
        pass=false;
         }

    bool isEven(){
      return (this->num % 2 ==0);
    }
    bool isOdd(){
      return (this->num % 2 ==1);
    }
    ~RndSet() {};
};

#endif