

//set the TEG//

            Info<< "\nset TEGs "<< endl;

            int TEGlist[solidsNames.size()]={0};
            int TEGEclist[solidsNames.size()]={0};
            int myi;
//variables for R function consts//
            double TEGRavgTCharlist[solidsNames.size()];
            double TEGRDTCharlist[solidsNames.size()];
            double TEGRCrCharlist[solidsNames.size()];
            double TEGRCCharlist[solidsNames.size()];
//variables for V function consts//
            double TEGVDTCharlist[solidsNames.size()];
            double TEGVCCharlist[solidsNames.size()];
//variables for face serial number//
            int TEGhotSideNum[solidsNames.size()]={-1};
            int TEGcoldSideNum[solidsNames.size()]={-1};
//variables for tempValue//
            double sumThot=0.;
            double hotSidefaceV=0.;
            double sumTcold=0.;
            double coldSidefaceV=0.;
            double sumTV=0.;
//variables for R Ve Qe and Output//
            double TEGRlist[solidsNames.size()];
            double TEGVelist[solidsNames.size()];
            double TEGQelist[solidsNames.size()];
            double TEGOutputlist[solidsNames.size()];
//variables for temperature outputs//
            double TEGThotlist[solidsNames.size()];
            double TEGTcoldlist[solidsNames.size()];
            double TEGTvavglist[solidsNames.size()];

//consts file reading//
            forAll(solidRegions, i)
            {

                IOdictionary TemOptions
                 (
                 IOobject
                 (
                 "TemOptions",
                 runTime.constant(),
                 solidRegions[i],
                 IOobject::MUST_READ,
                 IOobject::NO_WRITE
                 )
                 );
                Info<< "\nTemOptions of"
                    << solidsNames[i] <<"="
                  <<TemOptions<< endl;
                scalar TEGjudge = readScalar(TemOptions.lookup("TEGjudge"));

                if (TEGjudge)
                {
//consts reading//
                TEGEclist[i] = readScalar(TemOptions.lookup("TEGEc"));
                TEGRavgTCharlist[i] = readScalar(TemOptions.lookup("TEGRavgTnum"));
                TEGRDTCharlist[i] = readScalar(TemOptions.lookup("TEGRDTnum"));
                TEGRCrCharlist[i] = readScalar(TemOptions.lookup("TEGRCrnum"));
                TEGRCCharlist[i] = readScalar(TemOptions.lookup("TEGRCnum"));
                TEGVDTCharlist[i] = readScalar(TemOptions.lookup("TEGVDTnum"));
                TEGVCCharlist[i] = readScalar(TemOptions.lookup("TEGVCnum"));
                TEGlist[i]=1;
                TEGhotSideNum[i]=readScalar(TemOptions.lookup("HotSidepatchNum"));
                TEGcoldSideNum[i]=readScalar(TemOptions.lookup("ColdSidepatchNum"));
                }
            }

//circuit file reading//
                IOdictionary EcOptions
                 (
                 IOobject
                 (
                 "EcOptions",
                 runTime.constant(),
                 runTime,
                 IOobject::MUST_READ,
                 IOobject::NO_WRITE
                 )
                 );
            int nEc=readScalar(EcOptions.lookup("nEc"));

            Info<< "\nCircuit Number="<< nEc << endl;


            scalarList TEGloadRlist;
            TEGloadRlist.setSize(nEc);
            TEGloadRlist= readScalar(EcOptions.lookup("loadR"));

//variables for circuit//
           double sumR[nEc]={0};
           double sumVe[nEc]={0};
           double Ilist[nEc]={0};
           double Poutputlist[nEc]={0};
                  
//output files//
            PtrList<IOdictionary> IOutputs(solidRegions.size());
            PtrList<IOdictionary> ROutputs(solidRegions.size());
            PtrList<IOdictionary> POutputs(solidRegions.size());
            PtrList<IOdictionary> PinOutputs(solidRegions.size());
            PtrList<IOdictionary> ThotavgOutputs(solidRegions.size());
            PtrList<IOdictionary> TcoldavgOutputs(solidRegions.size());
            PtrList<IOdictionary> TVavgOutputs(solidRegions.size());
            PtrList<IOdictionary> VeOutputs(solidRegions.size());
//output files set//
            forAll(solidRegions, i)
            {
             IOutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "IOutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             ROutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "ROutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             POutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "POutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             PinOutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "PinOutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             ThotavgOutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "ThotavgOutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             TcoldavgOutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "TcoldavgOutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             TVavgOutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "TVavgOutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
             VeOutputs.set
                (
                 i,
                new IOdictionary
                 (
                 IOobject
                 (
                 "VeOutput",
                 runTime.timeName(),
                 solidRegions[i],
                 IOobject::NO_READ,
                 IOobject::AUTO_WRITE
                 )
                 )
               );
            }
            

