#pragma once

#include "../src/moea.h"
#include <es/eoRealInitBounded.h>
#include <es/eoRealOp.h>

template <class MOEOT,class MOEOT_OBJ,class MOEOT_EVAL>
void runCAEA(unsigned int POP_SIZE,\
         unsigned int MAX_GEN ,\
         double P_CROSS,\
         double ETA_CROSS,\
         double P_MUT,\
         double ETA_MUT,\
         unsigned int OBJ_SIZE ,\
         unsigned int VEC_SIZE ,\
         unsigned int H)
{
    cout<<">>>1"<<endl;
    std::vector <bool> bObjectives(OBJ_SIZE);
    //minimum
    for (unsigned int i=0; i<OBJ_SIZE ; i++)
        bObjectives[i]=true;
    //objective param setting
    moeoObjectiveVectorTraits::setup(OBJ_SIZE,bObjectives);

    // objective functions evaluation
    MOEOT_EVAL eval;

    // generate initial population
    // the genotype (through a genotype initializer)
    //eoRealVectorBounds bounds(VEC_SIZE, 0.0, 1.0);
    vector<double> minBounds(VEC_SIZE,0.0);
    vector<double> maxBounds(VEC_SIZE,1.0);
    eoRealVectorBounds bounds(minBounds,maxBounds);

    eoRealInitBounded < MOEOT> init (bounds);

    cout<<">>>2"<<endl;

    eoPop < MOEOT > pop (POP_SIZE, init);

    //Extreme point
    MOEOT_OBJ pUtopian;
    MOEOT_OBJ pNadir;
    MOEOT_OBJ pRef;
    vector<MOEOT_OBJ> pAnchor;

    cout<<">>>3"<<endl;

    moeaUtopianPointUpdate<MOEOT> pUtopianUpdate(pUtopian);
    moeaNadirPointUpdate<MOEOT> pNadirUpdate(pNadir);
    moeaReferencePointUpdate<MOEOT> pRefUpdate(pRef,pUtopian);
    moeaAnchorPointsUpdate<MOEOT> pAnchorUpdate(pUtopian,pAnchor);

    cout<<">>>4"<<endl;

    moeaExtremePointManager<MOEOT> pExtreme(pUtopianUpdate,pNadirUpdate,pRefUpdate,pAnchorUpdate);

    cout<<">>>5"<<endl;

    moeaSubProblemLocate::setup(H,OBJ_SIZE);

    vector<moeaSubProblem> subProblems;
    //init weight for subProblems
    moeaWeightInit weightInit(POP_SIZE,OBJ_SIZE,H);
    weightInit(subProblems);

    cout<<">>>6"<<endl;

    //calculate index of neighborhood for subProblems
    //moeaVicinityInit vicinityInit(H);
    //vicinityInit(subProblems);
    moeaNeighborhoodInit neighborhoodInit(20);
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
    moeaCaFitnessAssignment<MOEOT> fitness(pRef,POP_SIZE,eval);

    moeaSubProblemMapping mapSubProblem(POP_SIZE,pExtreme.updateVersion());

    moeaConicalAreaComparator<MOEOT> comparator(pop,subProblems,mapSubProblem,normalized,pRef,fitness);

    moeaSubProblemMappingUpdate<MOEOT> mapSubProblemUpdate(subProblems,mapSubProblem,normalized,comparator);

    cout<<">>>7"<<endl;
    moeaConicalTournamentSelect<MOEOT> baseSelection(POP_SIZE,comparator);
    //moeaNeighborhoodSelect<MOEOT> selection(POP_SIZE,subProblems);
   // moeaDiffSelect baseSelection(POP_SIZE,subProblems);

   // cout<<"special "<<endl;
    moeaConicalSpecialSelect selection(baseSelection,POP_SIZE,OBJ_SIZE,H,POP_SIZE/10);

    cout<<">>>8"<<endl;

    // the variation operators
    PolynomialMutation < MOEOT> mutation(bounds, P_MUT, ETA_MUT);

    moeaSBXCrossover < MOEOT > xover(bounds, P_CROSS,ETA_CROSS);

    moeaQuadRecombination<MOEOT> recombination(selection,xover, mutation);


    //moeaDiffXover < MOEOT > xover(bounds,P_CROSS);

    //moeaDiffRecombination<MOEOT> recombination(selection,xover, mutation);

    cout<<">>>9"<<endl;

    cout<<">>>10"<<endl;

    //replacement
    //moeaNeighborReplacement<MOEOT> neighborReplacement(normalizedTCHFitness,subProblems);
    moeaConicalReplacement<MOEOT> replacement(comparator,mapSubProblem,normalized);

    cout<<">>>11"<<endl;

    // build MOEA/D
    moeaConicalEA < MOEOT > caea(mapSubProblem,POP_SIZE,MAX_GEN, eval,mapSubProblemUpdate,pExtreme,recombination,replacement);

    cout<<">>>12"<<endl;

    // run the algo
    caea (pop);

    cout<<">>>13"<<endl;
    for(unsigned int i =0;i<POP_SIZE;i++)
    {
        cout<<"["<<i<<"] select:"<<selection.de[i]<<"  replace:"<<replacement.de[i]<<endl;
    }
    //for(int i=0;i<POP_SIZE;i++)
    {
    //    cout<<"["<<i<<"] "<<pop[i]<<endl;
    }

    moeoUnboundedArchive < MOEOT > arch;
    arch(pop);

    cout<<">>>14"<<endl;

    // printing of the final archive
    cout << "Final Archive" << endl;
    arch.sortedPrintOn (cout);
    cout << endl;
};