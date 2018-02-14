#include<iostream>
using namespace std;
float threshold=0.0;
#define foreachInput for(int i=0;i<noInputs;i++)
int activation(float yin)
{
    if(yin>threshold) return 1;
    if(yin>= -threshold && yin<=threshold) return 0;
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
    float input[noSTpairs][noInputs],target[noSTpairs];
    for(int i=0;i<noSTpairs;i++)
    {
        for(int j=0;j<noInputs;j++)
            cin>>input[i][j];
        cin>>target[i];
    }

    cout<<"\nHow many epochs do you wish to see: ";
    cin>>epochs;
    cout<<"\nEnter thetha and alpha(threshold, learning rates): ";
    float weights[noInputs],b=0,a=1,output,t,dw[noInputs],db=0;
    cin>>threshold>>a;

    foreachInput {weights[i]=0;dw[i]=0;}
    foreachInput cout<<"x"<<i+1<<"   ";
    cout<<"t   yin   y   ";
    foreachInput cout<<"dw"<<i+1<<"   ";
    cout<<"db   ";
    foreachInput cout<<"w"<<i+1<<"   ";
    cout<<"b\n";

    int x=0,cnt=0;
    do
    {
        if(x==0) cout<<endl<<"EPOCH no: "<<cnt+1<<endl;
        float y=b;
        foreachInput y+=input[x][i]*weights[i];
        t=target[x];
        output=activation(y);
        foreachInput dw[i]=0;
        db=0;
        if(output!=t)
        {
            foreachInput{
                dw[i]=a*t*input[x][i];
                weights[i]+=dw[i];
            }
            db=a*t;
            b+=db;
        }

        foreachInput cout<<input[x][i]<<"   ";
        cout<<a<<"   "<<target[x]<<"   "<<y<<"   "<<output<<"   ";
        foreachInput cout<<dw[i]<<"   ";
        cout<<db<<"   ";
        foreachInput cout<<weights[i]<<"   ";
        cout<<b<<endl;

        x++;
        if(x==noSTpairs) {x=0;cnt++;}
    }while(cnt!=epochs);

    cout<<"\n\nAfter the training with the "<<epochs<<" epochs we have ended up with:\n";
    foreachInput cout<<endl<<"w"<<i+1<<"  = "<<weights[i];
    cout<<"\nbias, b = "<<b;
    return 0;
}
