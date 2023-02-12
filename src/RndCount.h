

#ifndef RNDCOUNT_H
#define	RNDCOUNT_H


class RndCount{
 public:
   unsigned long int count;
   long int sum;
   unsigned long int barrier;
   unsigned int globalsum;      // n'th global sum this thread has updated
   unsigned int maxglobalsum;   // total number of global sums
   
   bool pass;

    RndCount(){}

    void init(unsigned long int _max, unsigned int _totalsums ) {
        //num=0;
        count =0; sum =0;
        barrier = _max;
        globalsum=0;
        maxglobalsum = _totalsums;
        
    }

    void add_sum(uint64_t next_rn){
      count++;
      sum+= next_rn;
    }
    unsigned long int get_count(){
      return count;
    }

    unsigned int get_sumcount(){
      return globalsum;
    }
    void reset_both(){
      count =0; sum=0;
    }

    void reset_count(){
      count =0; 
    }
    bool count_max(){
      return (count >= barrier);
    }
    long int get_sum() {
     return sum;

    }

    bool update_globalsum() {
     globalsum++;

    }
    bool max_globalsum() {
     return (globalsum == maxglobalsum);
    }

    int get_maxglobalsum() {
     return maxglobalsum;
    }

    bool complete() {
     return (globalsum == maxglobalsum);
    }

    ~RndCount() {};
};

#endif