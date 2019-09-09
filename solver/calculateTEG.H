

//R function//

double calculatetemR
(const double Tvavg,const double Thot,const double Tcold,const double TEGRavgTChar,const double TEGRDTChar,const double TEGRCrChar,const double TEGRCChar)
{
	double Rtem;
	Rtem=TEGRavgTChar*Tvavg+TEGRDTChar*(Thot-Tcold)/(2*Tvavg-TEGRCrChar)+TEGRCChar;
	return (Rtem);
}
//V function//
double calculatetemV
(const double Thot,const double Tcold,const double TEGVDTChar,const double TEGVCChar)
{
	double Vtem;
	Vtem=TEGVDTChar*(Thot-Tcold)+TEGVCChar;
        if (Vtem<0)
        {
        return 0;
        }
        else
        {       
	return (Vtem);
        }
}
