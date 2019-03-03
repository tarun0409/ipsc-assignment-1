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
    cout<<"\nEnter the dimensions of the matrix : ";
    cin>>m>>n;
    double matrix[m][n];
    double U[m][n];
    cout<<"\nEnter the elements of the matrix in row major order : ";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cin>>matrix[i][j];
            U[i][j] = matrix[i][j];
        }
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


    return 0;
}