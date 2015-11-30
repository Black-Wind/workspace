#pragma once

#include "../src/moea.h"
#include <es/eoRealInitBounded.h>
#include <es/eoRealOp.h>

template <class MOEOT,class MOEOT_OBJ,class MOEOT_EVAL>
void runMOEAD(unsigned int POP_SIZE,\
         unsigned int MAX_GEN ,\
         double P_CROSS,\
         double ETA_CROSS,\
         double P_MUT,\
         double ETA_MUT,\
         unsigned int OBJ_SIZE ,\
         unsigned int VEC_SIZE ,\
         unsigned int NICHE_SIZE,\
         unsigned int H)
{
    moeaDebugger<MOEOT>debugger;

    std::vector <bool> bObjectives(OBJ_SIZE);
    //minimum
    for (unsigned int i=0; i<OBJ_SIZE ; i++)
        bObjectives[i]=true;
    //objective param setting
    moeoObjectiveVectorTraits::setup(OBJ_SIZE,bObjectives);
    // objective functions evaluation
    MOEOT_EVAL eval;
    //  generate initial population
    // the genotype (through a genotype initializer)
    //eoRealVectorBounds bounds(VEC_SIZE, 0.0, 1.0);
    vector<double> minBounds(VEC_SIZE,0.0);
    vector<double> maxBounds(VEC_SIZE,1.0);
    eoRealVectorBounds bounds(minBounds,maxBounds);

    eoRealInitBounded < MOEOT> init (bounds);


    eoPop < MOEOT > pop (POP_SIZE, init);

    //Extreme point
    MOEOT_OBJ pUtopian;
    MOEOT_OBJ pNadir;
    MOEOT_OBJ pRef;
    vector<MOEOT_OBJ> pAnchor;



    moeaUtopianPointUpdate<MOEOT> pUtopianUpdate(pUtopian);
    moeaNadirPointUpdate<MOEOT> pNadirUpdate(pNadir);
    moeaReferencePointUpdate<MOEOT> pRefUpdate(pRef,pUtopian);
    moeaAnchorPointsUpdate<MOEOT> pAnchorUpdate(pUtopian,pAnchor);


    moeaExtremePointManager<MOEOT> pExtreme(pUtopianUpdate,pNadirUpdate,pRefUpdate,pAnchorUpdate);


    moeaSubProblemLocate::setup(H,OBJ_SIZE);

    vector<moeaSubProblem> subProblems;
    //init weight for subProblems
    moeaWeightInit weightInit(POP_SIZE,OBJ_SIZE,H);
    weightInit(subProblems);



    //calculate index of neighborhood for subProblems
    moeaNeighborhoodInit neighborhoodInit(NICHE_SIZE);
    neighborhoodInit(subProblems);

    for(unsigned int i=0;i < POP_SIZE;i++)
    {
        cout<<"["<<i<<"] ("<<subProblems[i].weight[0]<<","<<subProblems[i].weight[1]<<")";
        for(unsigned int j =0;j<subProblems[i].neighbor.size();j++)
            cout<<subProblems[i].neighbor[j]<<",";
        cout<<endl;
    }

    moeaNormalized<MOEOT> normalized(pUtopian);
    //moeaAnchorNormalized<MOEOT> normalized(pUtopian,pAnchor);
    //moeaNadirNormalized<MOEOT> normalized(pUtopian,pNadir);

    //fitness
    moeaTCHFitnessAssignment<MOEOT> fitness(eval);
    //moeaPBIFitnessAssignment<MOEOT> fitness(eval);

    moeaNeighborhoodSelect<MOEOT> selection(POP_SIZE,subProblems);
    //moeaDiffSelect selection(POP_SIZE,subProblems);


    // the variation operators
    PolynomialMutation < MOEOT> mutation(bounds, P_MUT, ETA_MUT);

    moeaSBXCrossover < MOEOT > xover(bounds, P_CROSS,ETA_CROSS);

    moeaQuadRecombination<MOEOT> recombination(selection,xover, mutation);

    //moeaDiffXover < MOEOT > xover(bounds,P_CROSS);

    //moeaDiffRecombination<MOEOT> recombination(selection,xover, mutation);


    //replacement
    moeaNeighborReplacement<MOEOT> replacement(fitness,subProblems,normalized);


    // build MOEA/D
    moeaMOEAD < MOEOT > moead(NICHE_SIZE,H,MAX_GEN, eval,pExtreme,recombination,replacement);


    // run the algo
    moead (pop);

    for(unsigned int i =0;i<POP_SIZE;i++)
    {
        cout<<"["<<i<<"] select:"<<selection.de[i]<<"  replace:"<<replacement.de[i]<<endl;
    }


    debugger(pop,GENE);

    moeoUnboundedArchive < MOEOT > arch;
    arch(pop);

    debugger(pop,OBJ);

    debugger(arch,OBJ);
    cout << endl;

};
