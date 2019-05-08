#include<iostream>
#include<cmath>

using namespace std;

double dot_vectors(double * a, double * b, int n)
{
    double c = 0;
    for(int i=0; i<n; i++)
    {
        c += a[i]*b[i];
    }
    return c;
}

double magnitude_vector(double * a, int n)
{
    double m;
    for(int i=0; i<n; i++)
    {
        m += (a[i]*a[i]);
    }
    m = sqrt(m);
    return m;
}

double * scalar_vector_multiply(double scalar, double * vector, int n)
{
    for(int i=0; i<n; i++)
    {
        vector[i] = vector[i]*scalar;
    }
    return vector;
}

double * subtract_vectors(double * a, double * b, int n)
{
    double * diff = (double *)calloc(n,sizeof(double));
    for(int i=0; i<n; i++)
    {
        diff[i] = a[i]-b[i];
    }
    return diff;
}

double ** transpose_matrix(double ** A, int m, int n)
{
    double ** T = (double **)calloc(n,sizeof(double *));
    for(int i=0; i<n; i++)
    {
        T[i] = (double *)calloc(m,sizeof(double));
        for(int j=0; j<m; j++)
        {
            T[i][j] = A[j][i];
        }
    }
    return T;
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
double ** matrix_multiply(double ** A, double * row, double * col, double * val, int nz, int m1, int n1, int m2, int n2)
{
    if(n1!=m2)
    {
        cout<<"\nDimensions of matrices "<<m1<<"x"<<n1<<" and "<<m2<<"x"<<n2<<" do not comply for multiplication";
        exit(1);
    }
    double ** C = (double **)calloc(m1,sizeof(double *));
    for(int i=0; i<m1; i++)
    {
        C[i] = (double *)calloc(n2,sizeof(double));
        for(int j=0; j<n2; j++)
        {
            for(int k=0; k<n1; k++)
            {
                C[i][j] = C[i][j] + (A[i][k]*val_at(k, j, row, col, val, m2, nz));
            }
            if((C[i][j]>0 && C[i][j]<0.00001) || (C[i][j]<0 && C[i][j]>-0.00001))
            {
                C[i][j] = 0;
            }
        }
    }
    return C;
}

double ** matrix_multiply(double ** A, double ** B, int m1, int n1, int m2, int n2)
{
    if(n1!=m2)
    {
        cout<<"\nDimensions of matrices "<<m1<<"x"<<n1<<" and "<<m2<<"x"<<n2<<" do not comply for multiplication";
        exit(1);
    }
    double ** C = (double **)calloc(m1,sizeof(double *));
    for(int i=0; i<m1; i++)
    {
        C[i] = (double *)calloc(n2,sizeof(double));
        for(int j=0; j<n2; j++)
        {
            for(int k=0; k<n1; k++)
            {
                C[i][j] = C[i][j] + (A[i][k]*B[k][j]);
            }
            if((C[i][j]>0 && C[i][j]<0.00001) || (C[i][j]<0 && C[i][j]>-0.00001))
            {
                C[i][j] = 0;
            }
        }
    }
    return C;
}



int main()
{
    int m,n;
    cout<<"\nEnter the number of linear equations : ";
    cin>>m;
    cout<<"\nEnter the number of variables : ";
    cin>>n;
    cout<<"\nEnter the elements of the matrix A in row major order :";
    double ** A = (double **)calloc(m,sizeof(double *));
    double ** orth = (double **)calloc(m,sizeof(double *));
    int nz = 0;
    for(int i=0; i<m; i++)
    {
        A[i] = (double *)calloc(n,sizeof(double));
        orth[i] = (double *)calloc(n,sizeof(double));
        for(int j=0; j<n;j++)
        {
            cin>>A[i][j];
            if(A[i][j] != 0)
            {
                nz++;
            }
            orth[i][j] = A[i][j];
        }
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
            if(A[i][j]!=0)
            {
                int index = nz_i++;
                val[index] = A[i][j];
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

    cout<<"\nEnter the elements of b (RHS) : ";
    double ** b = (double **)calloc(m,sizeof(double *));
    double ** x = (double **)calloc(m,sizeof(double *));
    for(int i=0; i<m; i++)
    {
        b[i] = (double *)calloc(1,sizeof(double));
        x[i] = (double *)calloc(1,sizeof(double));
        cin>>b[i][0];
    }

    cout<<"\nCSR of A : \n";
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

    cout<<"\nb vector is : ";
    for(int i=0; i<m; i++)
    {
        cout<<b[i][0]<<" ";
    }
    cout<<endl;

    for(int j=1; j<n; j++)
    {
        double * curr_vector = (double *)calloc(m,sizeof(double));
        for(int i=0; i<m; i++)
        {
            curr_vector[i] = val_at(i,j,row,col,val,m,nz);
        }
        double * curr_diff =(double *)calloc(m,sizeof(double));
        for(int i=0; i<m; i++)
        {
            curr_diff[i] = val_at(i,j,row,col,val,m,nz);
        }

        for(int k=0; k<j; k++)
        {
            double * curr_basis = (double *)calloc(m,sizeof(double));
            for(int i=0; i<m; i++)
            {
                curr_basis[i] = orth[i][k];
            }

            double dot1 = dot_vectors(curr_vector,curr_basis,m);
            double dot2 = dot_vectors(curr_basis,curr_basis,m);

            double scale = dot1/dot2;
            

            curr_diff = subtract_vectors(curr_diff,scalar_vector_multiply(scale,curr_basis,m),m);
        }
        for(int i=0; i<m; i++)
        {
            orth[i][j] = curr_diff[i];
        }
    }


    for(int j=0; j<n; j++)
    {
        double * vec = (double *)calloc(m,sizeof(double));
        for(int i=0; i<m; i++)
        {
            vec[i] = orth[i][j];
        }
        double mag = magnitude_vector(vec,m);
        for(int i=0; i<m; i++)
        {
            orth[i][j] = orth[i][j]/mag;
        }
    }

    cout<<"\nQ matrix : \n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<orth[i][j]<<"\t";
        }
        cout<<endl;
    }

    double ** qt = transpose_matrix(orth,m,n);
    
    double ** R = matrix_multiply(qt, row, col, val, nz, n,m,m,n);

    cout<<"\nR matrix is : \n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<R[i][j]<<"\t";
        }
        cout<<endl;
    }

    double ** y = matrix_multiply(qt,b, n,m,m,1);
    

    for(int i=(n-1); i>=0; i--)
    {
        for(int j=(n-1); j>i; j--)
        {
            y[i][0] = y[i][0] - (R[i][j]*x[j][0]);
        }
        x[i][0] = y[i][0]/R[i][i];
    }

    cout<<"\nx vector is : ";
    for(int i=0; i<m; i++)
    {
        cout<<x[i][0]<<"  ";
    }
    cout<<endl;

    return 0;
}