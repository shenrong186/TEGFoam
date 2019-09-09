

//-------------------getIP---------------------------------//

for(myi=1; myi<=nEc;myi++)
{
Ilist[myi]=sumVe[myi]/(sumR[myi]+TEGloadRlist[myi-1]);
Poutputlist[myi]=Ilist[myi]*Ilist[myi]*TEGloadRlist[myi-1];
}

