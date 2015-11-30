#pragma once

#include "../global.h"
#include "../extremePoint/extremePoint.h"
#include "../VariationOp/VariationOp.h"
#include "../replacement/replacement.h"

/**
 * MOEA/D
 *
 * */

template < class MOEOT >
class moeaMOEAD: public moeoEA< MOEOT >
{
public:

    /** the objective vector type of the solutions */
    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

	moeaMOEAD(unsigned int _nNiche, unsigned int _nH, unsigned int _maxGen, eoEvalFunc < MOEOT > & _eval, moeaExtremePointManager<MOEOT> &_pExtreme, moeaRecombination<MOEOT> &_recombination, moeaNeighborReplacement<MOEOT> & _replace) :
		nNiche(_nNiche), nH(_nH), defaultGenContinuator(_maxGen), continuator(defaultGenContinuator), eval(_eval), defaultPopEval(_eval), popEval(defaultPopEval), pExtreme(_pExtreme),recombination(_recombination), replace(_replace),repair(defaultRepair)
    {}

    moeaMOEAD(unsigned int _nNiche, unsigned int _nH, unsigned int _maxGen, eoEvalFunc < MOEOT > & _eval, moeaExtremePointManager<MOEOT> &_pExtreme, moeaRecombination<MOEOT> &_recombination, moeaNeighborReplacement<MOEOT> & _replace,moeaRepairOp<MOEOT> &_repair) :
            nNiche(_nNiche), nH(_nH), defaultGenContinuator(_maxGen), continuator(defaultGenContinuator), eval(_eval), defaultPopEval(_eval), popEval(defaultPopEval), pExtreme(_pExtreme),recombination(_recombination), replace(_replace),repair(_repair)
    {}

    /**
     * Apply a the algorithm to the population _pop until the stopping criteria is satified.
     * @param _pop the population
     */
    void operator () (eoPop< MOEOT > &_pop)
    {
        cout<<"MOEAD >>>1"<<endl;
        //decomposition
        //
        unsigned int nPop = _pop.size();
        unsigned int nObj = MOEOT::ObjectiveVector::nObjectives();

        eoPop < MOEOT > empty_pop;
        popEval (empty_pop, _pop);	// a first eval of _pop


        //for(unsigned int i=0;i<nPop;i++)
        {
         /*   cout<<"object ["<<i<<"] :";
            for(unsigned int j=0;j<nObj;j++)
            {
                cout<<_pop[i].objectiveVector(j)<<",";
            }
            cout<<endl;
            */
           // cout<<_pop[i]<<endl;
        }


        cout<<"MOEAD >>>2"<<endl;

		for (unsigned int i = 0; i < nPop; i++)
			repair(_pop[i]);

        cout<<"MOEAD >>>3"<<endl;

        //init extreme points
        pExtreme.init(_pop[0]);

        cout<<"Extreme Point Init"<<endl;
        pExtreme.printOut();

        cout<<"MOEAD >>>4"<<endl;

        //update extreme points
        pExtreme.update(_pop);

        cout<<"Extreme Point Update"<<endl;
        pExtreme.printOut();


        cout<<"MOEAD >>>5"<<endl;

        do
        {
            // generate offspring, worths are recalculated if necessary
            for (unsigned int i = 0; i < nPop; ++i)
            {
               // cout<<"MOEAD loop>>>1"<<endl;

                //MOEOT &&offspring = recombination(_pop , i);

                MOEOT offspring = recombination(_pop,i);

               // cout<<offspring<<endl;
             //   cout<<"MOEAD loop>>>6"<<endl;

                eval(offspring);
                //cout<<"[eval] "<<offspring<<endl;
               // cout<<"new ("<<offspring.objectiveVector()<<")"<<endl;

                //cout<<"MOEAD loop>>>7"<<endl;

                //update extreme points
                pExtreme.update(offspring);
                //cout<<"Extreme Point Update"<<endl;
                //pExtreme.printOut();
               //cout<<"MOEAD loop>>>8"<<endl;

                //replace
                replace(offspring,_pop,i);

                //int tmp;
               // cin>>tmp;
            //    cout<<"MOEAD loop>>>9"<<endl;

            }
        }
        while (continuator (_pop));

        pExtreme.printOut();
       // cout<<"MOEAD >>>end"<<endl;

    }

protected:

    /** a continuator based on the number of generations (used as default) */
    eoGenContinue< MOEOT > defaultGenContinuator;
    /** stopping criteria */
    eoContinue< MOEOT > & continuator;

    /** evaluation function */
    eoEvalFunc< MOEOT > & eval;
    /** default popEval */
    eoPopLoopEval< MOEOT > defaultPopEval;
    /** evaluation function used to evaluate the whole population */
    eoPopEvalFunc< MOEOT > & popEval;

    moeaRecombination<MOEOT> &recombination;

    /** fitness assignment used in MOEA/D */
    moeaNeighborReplacement< MOEOT > &replace;

    moeaRepairOp<MOEOT> defaultRepair;
    moeaRepairOp<MOEOT> &repair;

private:
    unsigned int nNiche;
    unsigned int nH;
    moeaExtremePointManager <MOEOT> &pExtreme;
};
