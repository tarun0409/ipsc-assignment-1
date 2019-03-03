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

int val_at(int i, int j, double * row_vec, double * col_vec, double * val_vec, int m, int nz)
{
    int nz_col = row_vec[i];
    int nxt_nz_col = nz;
    if(nz_col < 0)
    {
        return 0;
    }
    if(i<(m-1))
    {
        nxt_nz_col = row_vec[i+1];
    }
    for(int k = nz_col; k<nxt_nz_col; k++)
    {
        if(col_vec[k]==j)
        {
            return val_vec[k];
        }
    }
    return 0;
}

double * foreward(double ** L, double * b, int n)
{
    double * y = (double *)calloc(n,sizeof(double));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<i; j++)
        {
            b[i] = b[i] - (L[i][j]*y[j]);
        }
        y[i] = b[i]/L[i][i];
    }
    return y;
}

double * back(double ** U, double * y, int n)
{
    double * x = (double *)calloc(n,sizeof(double));
    for(int i=(n-1); i>=0; i--)
    {
        for(int j=(n-1); j>i; j--)
        {
            y[i] = y[i] - (U[i][j]*x[j]);
        }
        x[i] = y[i]/U[i][i];
    }
    return x;
}

double * lu_solve(double * row, double * col, double * val, int nz, double * b, int m, int n)
{
    double ** U = (double **)calloc(m,sizeof(double *));
    for(int i=0; i<m; i++)
    {
        U[i] = (double *)calloc(n,sizeof(double));
        for(int j=0; j<n; j++)
        {
            U[i][j] = val_at(i,j,row,val,val,m,nz);
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

    //forward sweep
    double * y = foreward(L,b,n);

    //backward sweep
    double * x = back(U,y,n);
}


int main()
{
    int m,n;
    cout<<"\nEnter the number of linear equations : ";
    cin>>m;
    cout<<"\nEnter the number of variables : ";
    cin>>n;
    double ** matrix = (double **)calloc(m,sizeof(double *));
    double * b = (double *)calloc(n,sizeof(double));
    cout<<"\nEnter the values of A matrix (coefficients of left side of linear equation) : ";
    int nz = 0;
    for(int i=0; i<m; i++)
    {
        matrix[i] = (double *)calloc(n,sizeof(double));
        for(int j=0; j<n; j++)
        {
            cin>>matrix[i][j];
            if(matrix[i][j]!=0)
            {
                nz++;
            }
        }
    }
    cout<<"\nEnter the values of b vector (right side of linear equation) : ";
    for(int i=0; i<n; i++)
    {
        cin>>b[i];
    }
    
    double * row = (double *)calloc((m+1),sizeof(double));
    double * col = (double *)calloc(nz,sizeof(double));
    double * val = (double *)calloc(nz,sizeof(double));

    int nz_i = 0;
    int nz_r = 0;
    for(int i=0; i<m; i++)
    {
        bool found = false;
        for(int j=0; j<n; j++)
        {
            if(matrix[i][j]!=0)
            {
                int index = nz_i++;
                val[index] = matrix[i][j];
                col[index] = j;
                if(!found)
                {
                    found = true;
                    row[nz_r++] = index;
                }
            }
        }
    }
    row[nz_r] = nz+1;

    cout<<"\nCSR of matrix 1 : \n";
    cout<<"Values : ";
    for(int i=0; i<nz; i++)
    {
        cout<<val[i]<<" ";
    }
    cout<<endl;
    cout<<"Cols : ";
    for(int i=0; i<nz; i++)
    {
        cout<<col[i]<<" ";
    }
    cout<<endl;
    cout<<"Rows : ";
    for(int i=0; i<(m+1); i++)
    {
        cout<<row[i]<<" ";
    }
    cout<<endl;

    double * x = lu_solve(row,col,val,nz,b,m,n);

    cout<<"\nx = ";
    for(int i=0; i<n; i++)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;


    return 0;
}