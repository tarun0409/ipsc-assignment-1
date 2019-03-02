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

    int m2,n2;
    cout<<"Enter the dimensions of matrix 2 : ";
    cin>>m2>>n2;
    cout<<"Enter the elements of matrix 2 : ";
    int ** matrix2 = (int **)malloc(m2*sizeof(int *));
    for(int i=0; i<m2; i++)
    {
        matrix2[i] = (int *)malloc(n2*sizeof(int));
        for(int j=0; j<n2; j++)
        {
            cin>>matrix2[i][j];
        }
    }



    cout<<"Matrix 1 is : "<<endl;
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n1; j++)
        {
            cout<<matrix1[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<"Matrix 2 is : "<<endl;
    for(int i=0; i<m2; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cout<<matrix2[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<endl<<endl;
    
    int p1 = get_lower_bandwidth(matrix1, m1,n1);
    int q1 = get_upper_bandwidth(matrix1, m1,n1);
    int p2 = get_lower_bandwidth(matrix2, m2,n2);
    int q2 = get_upper_bandwidth(matrix2, m2,n2);
    int ** bsm1 = get_band_stored_matrix(matrix1, m1, n1, q1, p1);
    int ** bsm2 = get_band_stored_matrix(matrix2, m2, n2, q2, p2);    
    int M1 = p1 + q1 + 1;
    int M2 = p2 + q2 + 1;
    cout<<"The band stored matrix 1 is : "<<endl;
    for(int i=0; i<M1; i++)
    {
        for(int j=0; j < n1; j++)
        {
            cout<<bsm1[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    cout<<"The band stored matrix 2 is : "<<endl;
    for(int i=0; i<M2; i++)
    {
        for(int j=0; j < n2; j++)
        {
            cout<<bsm2[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl<<endl;

    int ** prod = (int **)calloc(m1,sizeof(int *));
    
    for(int i=0; i<m1; i++)
    {
        prod[i] = (int *)calloc(n2,sizeof(int));
        for(int j=0; j<n2; j++)
        {
            for(int k=0; k<n1; k++)
            {
                int a = 0;
                int b = 0;
            
                int new_i = i - k + q1;
                if(new_i >=0 && new_i < M1)
                {
                    a = bsm1[new_i][k];
                }
                int new_k = k - j + q2;
                if(new_k >=0 && new_k < M2)
                {
                    b = bsm2[new_k][j];
                }
                prod[i][j] = prod[i][j] + (a*b);
            }
        }
    }
    cout<<"\n\nThe product matrix is : \n";
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cout<<prod[i][j]<<"\t";
        }
        cout<<endl;
    }
    
    return 0;
}