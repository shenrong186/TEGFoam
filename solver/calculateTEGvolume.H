    
//calculate TEG volumes for source terms//
    Info<< "    Adding to volumes\n" << endl;
    double TEGvolumes[solidsNames.size()];
    

    forAll(solidsNames,i)
    {
       if (TEGlist[i])
       {
       double sumVoltemp=0.;
       const scalarField& Voltemp = solidRegions[i].V();
       forAll(Voltemp,celli)
       {
          sumVoltemp=sumVoltemp+Voltemp[celli];
       }
       TEGvolumes[i]=sumVoltemp;
       }
     }

