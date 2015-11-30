#include "../src/moea.h"
#include "runMOEAD.h"
#include "runCAEA.h"
#include "runCHEA.h"



int main (int argc, char *argv[])
{
    eoParser parser(argc, argv);  // for user-parameter reading
    eoState state;                // to keep all things allocated

    /*
    // parameters
    unsigned int POP_SIZE = parser.createParam((unsigned int)(100), "popSize", "Population size",'P',"Param").value();
    unsigned int MAX_GEN = parser.createParam((unsigned int)(100), "maxGen", "Maximum number of generations",'G',"Param").value();
    double P_CROSS = parser.createParam(1.0, "pCross", "Crossover probability",'C',"Param").value();
    double ETA_CROSS = parser.createParam(20.0,"etaCross","Parameter eta in SBXCrossover",'A',"Param").value();
    double P_MUT = parser.createParam(0.1, "pMut", "Mutation probability",'M',"Param").value();
    double ETA_MUT = parser.createParam(20.0,"etaMut","Parameters eta in PolynomialMutation",'B',"Param").value();
    unsigned int OBJ_SIZE = parser.createParam((unsigned int)(2),"objSize","Objective size",'O',"Param").value();
    unsigned int VEC_SIZE = parser.createParam((unsigned int)(30),"varSize","Decision variables size",'V',"Param").value();

    P_MUT = 1.0/VEC_SIZE;

    unsigned int NICHE_SIZE = parser.createParam((unsigned int)(20),"nicheSize","Neighbor Size",'N',"Param").value();
    unsigned int H = parser.createParam((unsigned int)(1),"hyperIntercept","Number of partition in each dimension",'H',"Param").value();
*/

    // parameters
    unsigned int POP_SIZE = 100;
    unsigned int MAX_GEN  = 400;
    double P_CROSS        = 1.0;
    double ETA_CROSS      = 20.0;
    //double P_MUT = 0.1;
    double ETA_MUT = 20.0;
    unsigned int OBJ_SIZE = 2;
    unsigned int VEC_SIZE = 30;

    double P_MUT = 1.0/VEC_SIZE;

    unsigned int NICHE_SIZE = 20;
    unsigned int H = 99;

   runMOEAD<ZDT,ZDTObjectiveVector ,ZDT1Eval>(POP_SIZE,MAX_GEN ,P_CROSS,ETA_CROSS,P_MUT,ETA_MUT,OBJ_SIZE ,VEC_SIZE ,NICHE_SIZE, H);

   //runCAEA<ZDT,ZDTObjectiveVector ,ZDT1Eval>(POP_SIZE,MAX_GEN ,P_CROSS,ETA_CROSS,P_MUT,ETA_MUT,OBJ_SIZE ,VEC_SIZE , H);

   // runCHEA<ZDT,ZDTObjectiveVector ,ZDT1Eval>(POP_SIZE,MAX_GEN ,P_CROSS,ETA_CROSS,P_MUT,ETA_MUT,OBJ_SIZE ,VEC_SIZE , H);

    //VEC_SIZE = 12;
    //runMOEAD<DTLZ,DTLZObjectiveVector ,DTLZ1Eval>(POP_SIZE,MAX_GEN ,P_CROSS,ETA_CROSS,P_MUT,ETA_MUT,OBJ_SIZE ,VEC_SIZE ,NICHE_SIZE, H);

    // help ?
   // make_help(parser);
    return EXIT_SUCCESS;
}
