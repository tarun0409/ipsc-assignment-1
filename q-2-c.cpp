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

int get_lower_bandwidth(double ** A, int m, int n)
{
    int bandwidth_bound = (m < n)?m:n;
    int p = bandwidth_bound-1;
    bool found = false;
    for( ; p >= 0; p--)
    {
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(i >= j+p && A[i][j]!=0)
                {
                    found = true;
                    break;
                }
            }
            if(found)
            {
                break;
            }
        }
        if(found)
        {
            break;
        }
    }
    return p;
}

int get_upper_bandwidth(double ** A, int m, int n)
{
    int bandwidth_bound = (m < n)?m:n;
    int q = bandwidth_bound-1;
    bool found = false;
    for( ; q >= 0; q--)
    {
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(j >= i+q && A[i][j]!=0)
                {
                    // cout<<"\ni = "<<i<<" j = "<<j<<" q = "<<q<<endl;
                    found = true;
                    break;
                }
            }
            if(found)
            {
                break;
            }
        }
        if(found)
        {
            break;
        }
    }
    return q;
}

int main()
{
    int m,n;
    cout<<"\nEnter the dimensions of the matrix : ";
    cin>>m>>n;
    double ** matrix = (double **)calloc(m,sizeof(double *));
    cout<<"\nEnter the elements of the matrix in row major order : ";
    for(int i=0; i<m; i++)
    {
        matrix[i] = (double *)calloc(n,sizeof(double));
        for(int j=0; j<n; j++)
        {
            cin>>matrix[i][j];
        }
    }

    int upper_bandwidth = get_upper_bandwidth(matrix,m,n);
    int lower_bandwidth = get_lower_bandwidth(matrix,m,n);

    bool lower_hessenberg = (upper_bandwidth == 1);
    bool upper_hessenberg = (lower_bandwidth == 1);

    double ** L = (double **)calloc(m,sizeof(double *));
    for(int i=0; i<m; i++)
    {
        L[i] = (double *)calloc(m,sizeof(double));
        L[i][i] = 1;
    }
    int start_index = 0;
    for(int j=0; j<m; j++)
    {
        if(matrix[start_index][j]==0)
        {
            continue;
        }
        int main_val = matrix[start_index][j];
        
        int row_ext = upper_hessenberg?((start_index+2 < m)?(start_index+2):m):m;
        
        for(int i=(start_index+1); i<row_ext; i++)
        {
            L[i][j] = matrix[i][j]/main_val;
            
            int curr_val = matrix[i][j];
            int l = lcm(main_val>=0?main_val:(-1*main_val),curr_val>=0?curr_val:(-1*curr_val));
            int main_mul = l/main_val;
            main_mul = main_mul>=0?main_mul:(-1*main_mul);
            int curr_mul = l/curr_val;
            curr_mul = curr_mul>=0?curr_mul:(-1*curr_mul);
            int b = ((main_val>=0 && curr_val>=0)||(main_val<=0 && curr_val<=0))?-1:1;

            int col_ext = lower_hessenberg?((j+3 < n)?(j+3):n):n;

            for(int k=j; k<n; k++)
            {
                matrix[i][k] = (curr_mul*matrix[i][k]) + (b*main_mul*matrix[start_index][k]);
            }
        }
        start_index++;
    }

    cout<<"\nU matrix: \n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<matrix[i][j]<<"\t";
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