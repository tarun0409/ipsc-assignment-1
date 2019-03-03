#include<iostream>
using namespace std;

int gcd(int a, int b)
{
    if(a == 0)
    {
        return b;
    }
    return gcd(b%a, a);
}

int lcm(int a, int b)
{
    if(a==0 || b==0)
    {
        return 0;
    }
    return (a*b)/gcd(a,b);
}

int main()
{
    int m,n;
    cout<<"\nEnter the number of linear equations : ";
    cin>>m;
    cout<<"\nEnter the number of variables : ";
    cin>>n;
    double matrix[m][n];
    double U[m][n];
    double x[n],y[n],b[n];
    cout<<"\nEnter the values of A matrix (coefficients of left side of linear equation) : ";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>matrix[i][j];
            U[i][j] = matrix[i][j];
        }
    }
    cout<<"\nEnter the values of b vector (right side of linear equation) : ";
    for(int i=0; i<n; i++)
    {
        cin>>b[i];
    }
    double ** L = (double **)calloc(m,sizeof(double *));
    for(int i=0; i<m; i++)
    {
        L[i] = (double *)calloc(m,sizeof(double));
        L[i][i] = 1;
    }
    int start_index = 0;
    for(int j=0; j<m; j++)
    {
        if(U[start_index][j]==0)
        {
            continue;
        }
        int main_val = U[start_index][j];
        for(int i=(start_index+1); i<m; i++)
        {
            L[i][j] = U[i][j]/main_val;
            
            int curr_val = U[i][j];
            int l = lcm(main_val>=0?main_val:(-1*main_val),curr_val>=0?curr_val:(-1*curr_val));
            int main_mul = l/main_val;
            main_mul = main_mul>=0?main_mul:(-1*main_mul);
            int curr_mul = l/curr_val;
            curr_mul = curr_mul>=0?curr_mul:(-1*curr_mul);
            int b = ((main_val>=0 && curr_val>=0)||(main_val<=0 && curr_val<=0))?-1:1;
            for(int k=j; k<n; k++)
            {
                U[i][k] = (curr_mul*U[i][k]) + (b*main_mul*U[start_index][k]);
            }
        }
        start_index++;
    }

    cout<<"\nU matrix: \n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<U[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<"\nL matrix: \n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<m; j++)
        {
            cout<<L[i][j]<<"\t";
        }
        cout<<endl;
    }

    //forward sweep
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            b[i] = b[i] - (L[i][j]*y[j]);
        }
        y[i] = b[i]/L[i][i];
    }

    cout<<"\ny = ";
    for(int i=0; i<n; i++)
    {
        cout<<y[i]<<" ";
    }
    cout<<endl;

    for(int i=(n-1); i>=0; i--)
    {
        for(int j=(n-1); j>i; j--)
        {
            y[i] = y[i] - (U[i][j]*x[j]);
        }
        x[i] = y[i]/U[i][i];
    }

    cout<<"\nx = ";
    for(int i=0; i<n; i++)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;


    return 0;
}