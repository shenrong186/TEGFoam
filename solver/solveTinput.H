
     Info << "Calculate TEG module Tinput for" << solidsNames[i] << " "
            << nl << endl;

     fvMesh& mesh = solidRegions[i];
     solidThermo& thermo = thermos[i];

//-------------------HotsideT---------------------------------//

     const labelList& Thotfaces = mesh.boundary()[TEGhotSideNum[i]].faceCells();
     forAll(Thotfaces,celli)
     {
       sumThot=sumThot+mesh.V()[Thotfaces[celli]]*thermo.T()[Thotfaces[celli]];
       hotSidefaceV=hotSidefaceV+mesh.V()[Thotfaces[celli]];
     }
     TEGThotlist[i]=sumThot/hotSidefaceV;

        Info<< "Mean temperature of hot side = " << TEGThotlist[i] << " K in" << solidsNames[i] << " "
            << nl << endl;
//-------------------ColdsideT---------------------------------//
     const labelList& Tcoldfaces  = mesh.boundary()[TEGcoldSideNum[i]].faceCells();
     
     forAll(Tcoldfaces,celli)
     {
       sumTcold=sumTcold+mesh.V()[Tcoldfaces[celli]]*thermo.T()[Tcoldfaces[celli]];
       coldSidefaceV=coldSidefaceV+mesh.V()[Tcoldfaces[celli]];
     }
     TEGTcoldlist[i]=sumTcold/coldSidefaceV;

        Info<< "Mean temperature of cold side = " << TEGTcoldlist[i] << " K in" << solidsNames[i] << " "
            << nl << endl;
//-------------------VavgT---------------------------------//
     forAll(thermo.T(),celli)
     {
       sumTV=sumTV+mesh.V()[celli]*thermo.T()[celli];
     }
     TEGTvavglist[i]=sumTV/TEGvolumes[i];

        Info<< "Mean temperature of V = " << TEGTvavglist[i] << " K in" << solidsNames[i] << " "
            << nl << endl;


