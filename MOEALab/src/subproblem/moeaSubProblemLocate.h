#pragma once

#include "../global.h"

class moeaSubProblemLocate
{
public:
    /** the objective vector type of the solutions */

    static void setup(unsigned int _nH, unsigned int _nObj)
    {
        nH = _nH;
        nObj = _nObj;
    }

    /// My class name.
    virtual std::string className() const
    {
        return "moeaSubProblemLocate";
    }

    void uniformObservationPoint(vector<double> &_pObservation)
    {
        double sumObj = accumulate(_pObservation.begin(),_pObservation.end(),0.0);
        //transform to super plant
        if (sumObj < TOLERANCE) // equals to 0
        {
            sumObj = nH;
            _pObservation[0] = nH;
            for (unsigned int j =1; j < nObj; j++)
            {
                _pObservation[j] = 0;
            }
        }
        else
        {
            for (unsigned int j = 0; j < nObj; j++)
            {
                _pObservation[j] = _pObservation[j] / sumObj * nH;
            }
        }
    }

    void locateRefObservation(vector<unsigned int>& _refObservation, const vector<double>& _pObservation)
    {
        vector<bool> isCompleteBit(nObj, false);
        unsigned int size = nObj;
        unsigned int min_index = 0;
        double min_value = INF;
        vector<double> lowdif(nObj,0.0);
        vector<double> uppdif(nObj,0.0);
        double fix;
        double selectdata;
        for (unsigned int i = 0; i < nObj; i++)
        {
            lowdif[i] =	(double)floor(_pObservation[i])- _pObservation[i];
            uppdif[i] = 1.0 + lowdif[i];
            selectdata = (-lowdif[i]) < uppdif[i] ? - lowdif[i] : uppdif[i];
            if (min_value > selectdata)
            {
                min_index = i;
                min_value = selectdata;
            }
        }

        while (1)
        {
            selectdata = ((-lowdif[min_index]) < uppdif[min_index] ? lowdif[min_index] : uppdif[min_index]);
            _refObservation[min_index] = selectdata<0 ? floor(_pObservation[min_index]) : ceil(_pObservation[min_index]);

            isCompleteBit[min_index] = true;
            size--;

            if (size == 1)
            {
                unsigned int sum = 0;
                unsigned int left_index;
                for (unsigned int i = 0; i < nObj; i++)
                {
                    if (isCompleteBit[i])
                        sum += _refObservation[i];
                    else
                        left_index = i;
                }
                _refObservation[left_index] = floor(nH - sum + 0.5);
                break;
            }
            fix =  selectdata / size;

            min_value = INF;
            for (unsigned int i = 0; i < nObj; i++)
            {
                if (isCompleteBit[i])continue;

                lowdif[i] += fix;
                uppdif[i] += fix;
                selectdata = (-lowdif[i]) < uppdif[i] ? -lowdif[i] : uppdif[i];
                if (min_value > selectdata)
                {
                    min_index = i;
                    min_value = selectdata;
                }
            }
        }

        isCompleteBit.clear();
        lowdif.clear();
        uppdif.clear();
    }

    unsigned int locateIndex(const vector<unsigned int>& _refObservation)
    {
        //calculate the index of subproblm in pop
        //special case(2/3 dim)
        if (2 == nObj) return _refObservation[0];
        else if (3 == nObj) return (nH - _refObservation[2] + 1)*(nH - _refObservation[2]) / 2 + _refObservation[0];

        //general case
        //transform vector
        vector<unsigned int> h(nObj-1,0);
        h[nObj-2] = nH - _refObservation[nObj-1];
        for (unsigned int i = nObj-3; i > 0; i--)
        {
            h[i] = h[i+1] - _refObservation[i+1];
        }
        h[0] = _refObservation[0];

        unsigned int result_index = 0;
        for (unsigned int i = 0; i < nObj - 1; i++)
        {
            result_index += choose(h[i]+i ,i+1);
        }
        h.clear();
        return result_index;
    }

    unsigned int locate(const vector<double>& _vec){

        // vector<double> pObservation(nObj,0.0);
        //get Observation point
        //uniformObservationPoint(pObservation);

        vector<unsigned int> refObservation(nObj,0);
        //locate the reference Observation vector
        locateRefObservation(refObservation,_vec);

        unsigned int index = locateIndex(refObservation);
        //pObservation.clear();
        refObservation.clear();
        return index;
    }

    unsigned int choose(unsigned int n,unsigned  int m)
    {
        /*
        int numerator = 1;
        int denominator = 1;
        for (int i = n; i > n - m; i--)
            numerator *= i;
        for (int i = m; i > 1; i--)
            denominator *= i;
        return numerator / denominator;
        */
        if (m > n)
        {
            return 0;
        }
        return (unsigned int)floor(0.5 + exp(lnchoose(n, m)));
    }

    double lnchoose(unsigned int n, unsigned int m)
    {
        if (m > n)
        {
            return 0;
        }
        if (m < n/2.0)
        {
            m = n-m;
        }
        double s1 = 0;
        for (unsigned int i=m+1; i<=n; i++)
        {
            s1 += log((double)i);
        }
        double s2 = 0;
        unsigned int ub = n-m;
        for (unsigned int i=2; i<=ub; i++)
        {
            s2 += log((double)i);
        }
        return s1 - s2;
    }

    virtual unsigned int operator()(vector<double>& _vec)
    {
        uniformObservationPoint(_vec);
        return locate(_vec);
    }

    virtual unsigned int operator()(vector<double>&& _vec)
    {
        uniformObservationPoint(_vec);
        return locate(_vec);
    }

    static unsigned int nH;
    static unsigned int nObj;
};


unsigned int moeaSubProblemLocate::nH = 0;
unsigned int moeaSubProblemLocate::nObj = 0;