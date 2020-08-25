#ifndef SIMVD_CPP
#define SIMVD_CPP
#include<iostream>
#include<cassert>

using namespace std;

//compile with g++ -std=c++11 

class simvd{
public:
	//operations
	
	//constructors
	simvd(){
		capacity = INIT_CAPACITY;
		elems = new double[5];
		curr_size = 0;
	}

	//initial cpacity
	simvd(int ic){
		capacity = ic;
		elems = new double[capacity];
		curr_size = 0;
	}
	
	simvd(const simvd& orig){
		capacity = orig.capacity;
		elems = new double[capacity];
		
		//copy data
		for(int i = 0; i < orig.curr_size; i++){
			elems[i] = orig.elems[i];
		}
	
		//this->curr_size = orig.curr_size;
		//curr_size = orig.curr_size; //same things equivalent statements 
		(*this).curr_size = orig.curr_size;
	}	

	simvd(const initializer_list<double>& lst){
		this->curr_size = lst.size();
		this->capacity = curr_size + INCREMENT_SIZE;

		elems = new double[capacity];
		
		initializer_list<double>::iterator it;
		int i = 0;
		for(it = lst.begin(); it != lst.end(); it++){
			elems[i++] = *it;
		}	
	
	}

	//destructor
	~simvd(){
	  //cout<<"Deleting elems..."<<endl;
		delete[] elems;
	}

	int get_capacity() const{ //know that this value isnt getting changed
		return capacity;
	}
	
	int get_curr_size() {
		return curr_size;
	}
	//append
	void append(double e){
		if(curr_size == capacity){
			//get more memory	
			capacity += INCREMENT_SIZE;
			double* sec_elems = new double[capacity];

			for(int i = 0; i < curr_size; i++){
				sec_elems[i] = elems[i];
			}

			sec_elems[curr_size++] = e;
			delete[] elems;
			elems = sec_elems;	//elems now points to sec_elems

		} else
			elems[curr_size++] = e;
	}

	void printv() const{
		cout<< "[";

		for(int i = 0; i < curr_size; i++){
			cout<<elems[i];
			if(i < curr_size -1)
				cout<<", ";
		}
		cout<<"]"<<endl;
	}

	void set(double val, int loc){
		//assert(loc >= 0 && loc < curr_size);
		if(loc >= 0 && loc < curr_size){
			elems[loc] = val;
		}else{
			cout<<"Illegal location."<<endl;
		}
	}

	void insert(double val, int loc){
	  //checks if location is outside of the bounds of elems
	  if(loc >= curr_size || loc < 0){
	    cerr<<"simvd:container value at"<<loc<<"does not exist."<<endl;
	  }else{

	    //increase capacity if needed
	    if(curr_size + 1 > capacity){
	      capacity += INCREMENT_SIZE;
	      double* sec_elems = new double[capacity];
	      for(int i = 0; i < curr_size; i++){
		sec_elems[i] = elems[i];
	      }
	      delete[] elems;
	      elems = sec_elems;
	    }

	    double* sec_elems = new double[capacity];
	  
	    for(int i = loc; i < curr_size; i++){
	      sec_elems[i] = elems[i];
	    }

	    elems[loc] = val;
	    for(int i = loc + 1; i < curr_size; i++){
	      elems[i] = sec_elems[i-1];
	    }
	  }
	}

	double at(int loc) const{
		//assert(loc >= 0 && loc < curr_size);
		if(loc >= curr_size){
			cerr<<"simvd: container value at "<<loc<<" does not exist."<<endl;
			return 0.0;
		}
		
		return elems[loc];
	}
  
  int find(double val) const{
    int ans = -1;

    for(int i = 0; i < curr_size; i++){
      if(elems[i] == val){
	ans = i;
	break;
      }
    }

    return ans;
  }

	//overloaded function
  simvd& operator=(const simvd& original){
		this->curr_size = original.curr_size;
		this->capacity = original.capacity;
			
		this->elems = new double[capacity];
	
		for(int i = 0; i < original.curr_size; i++){
			this->elems[i] = original.elems[i];
		}
		
		return *this;
	}

  //swap function for quicksort
  void swap(double* a, double* b){
    double t = *a;
    *a = *b;
    *b = t;
  }

  //partition function for quicksort with low end pivot
  int partition(int low, int high){
    int pivot = elems[low];
    int i = low;
    
    for(int j = low+1; j <= high; j++){
      if(elems[j] <= pivot){
	i++;
	swap(&elems[i], &elems[j]);
      }
    }
    swap(&elems[low], &elems[i]);
    return i;
    
  }
  //quicksort 
  void quicksort(int low, int high){
    if(low >= high){
      return;
    }
    int pi = partition(low,high);
    
    quicksort(low,(pi - 1));
    quicksort((pi+1),high);
    
  }
	
  //calls quicksort over the entirety of the vector
  void sort(){
    quicksort(0,curr_size-1);
  }
private:
	//data
	double* elems;
	int curr_size;
	int capacity;
	
	unsigned const static int INIT_CAPACITY = 5;	//initial capacity
	unsigned const static int INCREMENT_SIZE = 10;	//capacity increase quantity
};

#endif
