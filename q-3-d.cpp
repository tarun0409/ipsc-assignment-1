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

double ** get_q_recursive(double ** A, double ** Q, int m, int n, int j)
{
    if(j < n)
    {
        double * curr_vector = (double *)calloc(m,sizeof(double));
        for(int i=0; i<m; i++)
        {
            curr_vector[i] = A[i][j];
        }
        double * curr_diff =(double *)calloc(m,sizeof(double));
        for(int i=0; i<m; i++)
        {
            curr_diff[i] = A[i][j];
        }

        for(int k=0; k<j; k++)
        {
            double * curr_basis = (double *)calloc(m,sizeof(double));
            for(int i=0; i<m; i++)
            {
                curr_basis[i] = Q[i][k];
            }

            double dot1 = dot_vectors(curr_vector,curr_basis,m);
            double dot2 = dot_vectors(curr_basis,curr_basis,m);

            double scale = dot1/dot2;
            

            curr_diff = subtract_vectors(curr_diff,scalar_vector_multiply(scale,curr_basis,m),m);
        }
        for(int i=0; i<m; i++)
        {
            Q[i][j] = curr_diff[i];
        }
        return get_q_recursive(A, Q, m, n, j+1);
    }
    return Q;
}

double *** recursive_qr(double ** A, int m, int n)
{
    double ** Q = (double **)calloc(m,sizeof(double *));
    for(int i=0; i<m; i++)
    {
        Q[i] = (double *)calloc(n,sizeof(double));
        for(int j=0; j<n; j++)
        {
            Q[i][j] = A[i][j];
        }
    }
    Q = get_q_recursive(A,Q,m,n,1);
    for(int j=0; j<n; j++)
    {
        double * vec = (double *)calloc(m,sizeof(double));
        for(int i=0; i<m; i++)
        {
            vec[i] = Q[i][j];
        }
        double mag = magnitude_vector(vec,m);
        for(int i=0; i<m; i++)
        {
            Q[i][j] = Q[i][j]/mag;
        }
    }
    double ** qt = transpose_matrix(Q,m,n);
    
    double ** R = matrix_multiply(qt, A, n,m,m,n);
    double *** qr = (double ***)calloc(2,sizeof(double **));
    qr[0] = Q;
    qr[1] = R;
    return qr;
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
    for(int i=0; i<m; i++)
    {
        A[i] = (double *)calloc(n,sizeof(double));
        for(int j=0; j<n;j++)
        {
            cin>>A[i][j];
        }
    }
    cout<<"\nEnter the elements of b (RHS) : ";
    double ** b = (double **)calloc(m,sizeof(double *));
    double ** x = (double **)calloc(m,sizeof(double *));
    for(int i=0; i<m; i++)
    {
        b[i] = (double *)calloc(1,sizeof(double));
        x[i] = (double *)calloc(1,sizeof(double));
        cin>>b[i][0];
    }
    cout<<"\nThe A matrix is : \n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nb vector is : ";
    for(int i=0; i<m; i++)
    {
        cout<<b[i][0]<<" ";
    }
    cout<<endl;

    double *** qr = recursive_qr(A, m, n);
    double ** Q = qr[0];
    double ** R = qr[1];

    cout<<"\nQ matrix : \n";
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<Q[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<"\nR matrix is : \n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<R[i][j]<<"\t";
        }
        cout<<endl;
    }

    double ** qt = transpose_matrix(Q, m, n);

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