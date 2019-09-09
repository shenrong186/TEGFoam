
     Info << "Calculate TEG module R for" << solidsNames[i] << " "
            << nl << endl;

//-------------------Ve---------------------------------//

TEGRlist[i]=calculatetemR(TEGTvavglist[i],TEGThotlist[i],TEGTcoldlist[i],TEGRavgTCharlist[i],TEGRDTCharlist[i],TEGRCrCharlist[i],TEGRCCharlist[i]);

    Info<< "R of = " << TEGRlist[i] << " om in" << solidsNames[i] << " "
            << nl << endl;


