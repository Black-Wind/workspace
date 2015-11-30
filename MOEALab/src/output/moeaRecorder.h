#pragma once

#include "../global.h"
#include "output.h"

template <class MOEOT>
class moeaRecorder
{
public:
	moeaRecorder(string _filePath):filePath(_filePath)
	{
		output.open(filePath.c_str());
	}
	void setPath(string _filePath)
	{
		filePath=_filePath;
		output.close();
		output.open(filePath.c_str());
	}
	~moeaRecorder()
	{
		output.close();
	}
	virtual void operator()(const string _message)
	{
		output<<_message<<endl;
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
        		output<<"["<<i<<"] "<<_pop[i]<<endl;
        	break;
		case OBJ:
			for (unsigned int i=0 ; i < POP_SIZE; i++)
    		{
        		for (unsigned int j=0 ; j<OBJ_SIZE; j++)
        		{
            		output <<_pop[i].objectiveVector()[j];
            		if (j != OBJ_SIZE -1)
                		output << " ";
        		}
       		output <<endl;
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
	       		output<<"["<<i<<"] "<<_arch[i]<<endl;
	       	break;
		case OBJ:
			for (unsigned int i=0 ; i < POP_SIZE; i++)
	   		{
	       		for (unsigned int j=0 ; j<OBJ_SIZE; j++)
	       		{
	           		output <<_arch[i].objectiveVector()[j];
	           		if (j != OBJ_SIZE -1)
	               		output << " ";
	       		}
	       		output <<endl;
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

private:
	ofstream output;
	string filePath;
};