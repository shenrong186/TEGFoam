

if (TEGlist[i])

{
     Info << "Creat Heat Tinput for" << solidsNames[i] << " "
            << nl << endl;

     fvMesh& mesh = solidRegions[i];
     solidThermo& thermo = thermos[i];

//-------------------Qe---------------------------------//
TEGQelist[i]=Ilist[TEGEclist[i]]*TEGVelist[i];
//-------------------output---------------------------------//
TEGOutputlist[i]=TEGQelist[i]-Ilist[TEGEclist[i]]*Ilist[TEGEclist[i]]*TEGRlist[i];

     double qhe=(TEGQelist[i]-TEGOutputlist[i])/TEGvolumes[i];

     scalarField& TCells  = thermo.T();
     forAll(TCells, celli)
     {
     Heats[i][celli]=qhe;
     }
     double tempV=0;
     const labelList& Thotfaces = mesh.boundary()[TEGhotSideNum[i]].faceCells();
     forAll(Thotfaces,celli)
     {
       tempV+=mesh.V()[Thotfaces[celli]];
     }
     double tempPc=TEGQelist[i]/tempV;
     forAll(Thotfaces,celli)
     {
     Heats[i][Thotfaces[celli]] = Heats[i][Thotfaces[celli]]-tempPc*thermo.T()[Thotfaces[celli]]/TEGThotlist[i];
     }

IOutputs[i].set("I",Ilist[TEGEclist[i]]);
ROutputs[i].set("R",TEGRlist[i]);
POutputs[i].set("TEGPOutput",TEGOutputlist[i]);
PinOutputs[i].set("TEGPin",TEGQelist[i]-TEGOutputlist[i]);
ThotavgOutputs[i].set("TEGThotavg",TEGThotlist[i]);
TcoldavgOutputs[i].set("TEGTcoldavg",TEGTcoldlist[i]);
TVavgOutputs[i].set("TEGTVavg",TEGTvavglist[i]);
VeOutputs[i].set("Ve",TEGVelist[i]);
}
