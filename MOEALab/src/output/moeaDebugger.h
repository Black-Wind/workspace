#pragma once

#include "../global.h"
#include "output.h"

// // #define  GENE 0;
// // #define  OBJ  1;
// enum Instruction{GENE,OBJ};

template <class MOEOT>
class moeaDebugger:public moeaOutputer<MOEOT>
{
public:
	virtual void operator()(const string _message)
	{
		cout<<_message<<endl;
	}
	virtual void operator()(const eoPop<MOEOT> & _pop,\
							Instruction ins)
	{
		unsigned int OBJ_SIZE = MOEOT::ObjectiveVector::nObjectives();
		unsigned int POP_SIZE=_pop.size();
		switch(ins)
		{
		case GENE:
		    for(unsigned int i=0;i<POP_SIZE;i++)
        		cout<<"["<<i<<"] "<<_pop[i]<<endl;
        	break;
		case OBJ:
			for (unsigned int i=0 ; i < POP_SIZE; i++)
    		{
        		for (unsigned int j=0 ; j<OBJ_SIZE; j++)
        		{
            		cout <<_pop[i].objectiveVector()[j];
            		if (j != OBJ_SIZE -1)
                		cout << " ";
        		}
       		cout <<endl;
    		}
    		break;
		}
	}
	//////output
	virtual void operator()(const moeoArchive < MOEOT > & _arch,\
							Instruction ins)
	{
		unsigned int OBJ_SIZE = MOEOT::ObjectiveVector::nObjectives();
		unsigned int POP_SIZE=_arch.size();
		switch(ins)
		{
		case GENE:
		    for(unsigned int i=0;i<POP_SIZE;i++)
	       		cout<<"["<<i<<"] "<<_arch[i]<<endl;
	       	break;
		case OBJ:
			for (unsigned int i=0 ; i < POP_SIZE; i++)
	   		{
	       		for (unsigned int j=0 ; j<OBJ_SIZE; j++)
	       		{
	           		cout <<_arch[i].objectiveVector()[j];
	           		if (j != OBJ_SIZE -1)
	               		cout << " ";
	       		}
	       		cout <<endl;
	   		}
	   		break;
		}

	}
	virtual void operator()(const Timer &timer)
	{

	}
	virtual void operator()(const moeaMeasurer &_measurer)
	{

	}

} ;