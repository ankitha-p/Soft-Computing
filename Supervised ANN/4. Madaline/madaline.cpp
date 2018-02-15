#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
/* For madaline neural network
1. only the weights between input layer and hidden layer are adjusted.
2. Weights for output units are fixed,v=1/2
*/
#define foreachInput for(int i=0;i<noInputs;i++)

int activation(float inp)
{
    if(inp>=0) return 1;
    else return -1;
}

int main()
{
    int noInputs,noSTpairs,epochs;
    cout<<"Enter the number of inputs:  ";
    cin>>noInputs;
    cout<<"Enter the number of input output pairs,i.e datasets:  ";
    cin>>noSTpairs;
    cout<<"Enter the input target pairs:\n";
    float x[noSTpairs][noInputs],target[noSTpairs];
    for(int i=0;i<noSTpairs;i++)
    {
        for(int j=0;j<noInputs;j++)
            cin>>x[i][j];
        cin>>target[i];
    }

    cout<<"\nHow many epochs do you wish to see: ";
    cin>>epochs;
    cout<<endl;
    cout<<"Enter learning rate:";

    float weights[noInputs][noInputs],bias[noInputs],zin[noInputs],a;
    cin>>a;
    for(int j=1;j<=noInputs;j++){
        for(int i=1;i<=noInputs;i++)
            cout<<"w"<<i<<j<<"  ";
        cout<<"b"<<j<<" :";
        for(int i=0;i<noInputs;i++)
            cin>>weights[i][j-1];
        cin>>bias[j-1];
        cout<<endl;
    }

    float z[noInputs],v=0.5,b0=0.5,yin,y;
    cout.precision(3);
    cout.fill('-');
    cout<<setw(146)<<"\n";
    cout.fill(' ');
    for(int i=1;i<=noInputs;i++) cout<<"|"<<setw(7)<<"x"<<i;
    cout<<"|"<<setw(8)<<"a"<<"|"<<setw(8)<<"t";
    for(int i=1;i<=noInputs;i++) cout<<"|"<<setw(7)<<"Zin"<<i;
    for(int i=1;i<=noInputs;i++) cout<<"|"<<setw(7)<<"Z"<<i;
    cout<<"|"<<setw(8)<<"yin"<<"|"<<setw(8)<<"y";
    for(int j=1;j<=noInputs;j++){
        for(int i=1;i<=noInputs;i++)
            cout<<"|"<<setw(6)<<"w"<<i<<j;
        cout<<"|"<<setw(7)<<"b"<<j;
    }
    cout<<"|\n";

    int cnt=0,k=0;
    do{ /*for each input target pair:: In x[a][b] a represents the serial number,
        b represents the bth input of that pair*/
        if(k==0)
        {
            cout.fill('-');
            cout<<setw(146)<<"\n";
            cout.fill(' ');
            cout<<"EPOCH no: "<<cnt+1<<endl;
        }
        int j=0;
        do{
            zin[j]=bias[j]; //apply all inputs to zj
            for(int i=0;i<noInputs;i++) zin[j]+=x[k][i]*weights[i][j];
            z[j]=activation(zin[j]);
            j++;
        }while(j!=noInputs);

        yin=b0;
        for(int j=0;j<noInputs;j++) yin+=(v*z[j]);
        y=activation(yin);
        if(target[k]!=y)
        {
            if(target[k]==1)
            {
                //get that zj whose zinj is closest to zero
                float nearest=9999.999;
                int index=noInputs;
                for(int j=0;j<noInputs;j++) if(fabs(zin[j])<nearest) {nearest=fabs(zin[j]);index=j;}
                bias[index]+=(a*(1-zin[index]));
                for(int i=0;i<noInputs;i++) weights[i][index]+=((a*(1-zin[index]))*x[k][i]);
            }
            else
            {
                for(int j=0;j<noInputs;j++)
                {
                    if(zin[j]>0.0) //update weights on units z, which have positive net input
                    {
                        bias[j]+=(a*(-1-zin[j]));
                        for(int i=0;i<noInputs;i++) weights[i][j]+=(a*(-1-zin[j])*x[k][i]);
                    }
                }
            }
        }

        for(int i=0;i<noInputs;i++) cout<<"|"<<setw(8)<<x[k][i];
        cout<<"|"<<setw(8)<<"1"<<"|"<<setw(8)<<target[k];
        for(int i=0;i<noInputs;i++) cout<<"|"<<setw(8)<<zin[i];
        for(int i=0;i<noInputs;i++) cout<<"|"<<setw(8)<<z[i];
        cout<<"|"<<setw(8)<<yin<<"|"<<setw(8)<<y;
        for(int j=0;j<noInputs;j++){
            for(int i=0;i<noInputs;i++)
                cout<<"|"<<setw(8)<<weights[i][j];
            cout<<"|"<<setw(8)<<bias[j];
        }
        cout<<"|\n";
        k++;
        if(k==noSTpairs){ k=0;cnt++;}
    }while(cnt!=epochs);
    cout.fill('-');
    cout<<setw(146)<<"\n";
    cout.fill(' ');

    return 0;
}
