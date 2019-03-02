#include<iostream>

using namespace std;

int get_upper_bandwidth(int ** A, int m, int n)
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

int get_lower_bandwidth(int ** A, int m, int n)
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

int ** get_band_stored_matrix(int ** matrix, int m, int n, int upper_bandwidth, int lower_bandwidth)
{
    int q = upper_bandwidth;
    int p = lower_bandwidth;
    int M = p + q + 1;
    int N = n;
    int ** band_store = (int **)calloc(M,sizeof(int *));
    for(int i=0; i<M; i++)
    {
        band_store[i] = (int *)calloc(N,sizeof(int));
    }
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            int new_i = i - j + q;
            if(new_i < 0 || new_i >= M)
            {
                continue;
            }
            band_store[new_i][j] = matrix[i][j];
        }
    }
    return band_store;
}

int main()
{
    int m1,n1;
    cout<<"Enter the dimensions of matrix 1 : ";
    cin>>m1>>n1;
    cout<<"Enter the elements of matrix 1 : ";
    int ** matrix1 = (int **)malloc(m1*sizeof(int *));
    for(int i=0; i<m1; i++)
    {
        matrix1[i] = (int *)malloc(n1*sizeof(int));
        for(int j=0; j<n1; j++)
        {
            cin>>matrix1[i][j];
        }
    }
    cout<<"The matrix is : "<<endl;
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j < n1; j++)
        {
            cout<<matrix1[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    // cout<<"Upper bandwidth of the matrix is : "<<get_upper_bandwidth(matrix1, m1,n1)<<endl;
    // cout<<"Lower bandwidth of the matrix is : "<<get_lower_bandwidth(matrix1, m1,n1)<<endl;
    int p = get_lower_bandwidth(matrix1, m1,n1);
    int q = get_upper_bandwidth(matrix1, m1,n1);
    int ** band_stored_matrix = get_band_stored_matrix(matrix1, m1, n1, q, p);
    int M1 = p + q + 1;
    cout<<"The band stored matrix is : "<<endl;
    for(int i=0; i<M1; i++)
    {
        for(int j=0; j < n1; j++)
        {
            cout<<band_stored_matrix[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    return 0;
}