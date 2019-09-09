
     Info << "Calculate TEG module Ve for" << solidsNames[i] << " "
            << nl << endl;

//-------------------Ve---------------------------------//

TEGVelist[i]=calculatetemV(TEGThotlist[i],TEGTcoldlist[i],TEGVDTCharlist[i],TEGVCCharlist[i]);

    Info<< "Ve of= " << TEGVelist[i] << " V in" << solidsNames[i] << " "
            << nl << endl;

