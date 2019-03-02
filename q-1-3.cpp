#include<iostream>
using namespace std;

int index_of(int * row_indices, int * col_indices, int len, int row_index, int col_index)
{
    for(int i=0; i<len; i++)
    {
        if(row_indices[i]==row_index && col_indices[i]==col_index)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int m1,n1,m2,n2;
    cout<<"Enter the dimension of matrix 1 : "<<endl;
    cin>>m1>>n1;
    int matrix1[m1][n1];
    cout<<"Enter the elements of the matrix 1 : "<<endl;
    int nz1 = 0;
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n1; j++)
        {
            cin>>matrix1[i][j];
            if(matrix1[i][j] != 0)
            {
                nz1++;
            }
        }
    }
    cout<<"Enter the dimension of matrix 2 : "<<endl;
    cin>>m2>>n2;
    int matrix2[m2][n2];
    cout<<"Enter the elements of the matrix 2 : "<<endl;
    int nz2 = 0;
    for(int i=0; i<m2; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cin>>matrix2[i][j];
            if(matrix2[i][j] != 0)
            {
                nz2++;
            }
        }
    }

    cout<<"Matrix 1 is "<<endl;
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n1; j++)
        {
            cout<<matrix1[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"Matrix 2 is "<<endl;
    for(int i=0; i<m2; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cout<<matrix2[i][j]<<"\t";
        }
        cout<<endl;
    }


    int row_indices1[nz1], col_indices1[nz1], val1[nz1];
    int row_indices2[nz2], col_indices2[nz2], val2[nz2];
    int temp_nz1 = nz1;
    int temp_nz2 = nz2;
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n1; j++)
        {
            if(matrix1[i][j]!=0)
            {
                int index = --temp_nz1;
                row_indices1[index] = i;
                col_indices1[index] = j;
                val1[index] = matrix1[i][j];
            }
        }
    }
    for(int i=0; i<m2; i++)
    {
        for(int j=0; j<n2; j++)
        {
            if(matrix2[i][j]!=0)
            {
                int index = --temp_nz2;
                row_indices2[index] = i;
                col_indices2[index] = j;
                val2[index] = matrix2[i][j];
            }
        }
    }
    cout<<endl<<endl;
    cout<<"Row indices of matrix 1 : "<<endl;
    for(int i=0; i<nz1; i++)
    {
        cout<<row_indices1[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Column indices of matrix 1 : "<<endl;
    for(int i=0; i<nz1; i++)
    {
        cout<<col_indices1[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Values of matrix 1 : "<<endl;
    for(int i=0; i<nz1; i++)
    {
        cout<<val1[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Row indices of matrix 2 : "<<endl;
    for(int i=0; i<nz2; i++)
    {
        cout<<row_indices2[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Column indices of matrix 2 : "<<endl;
    for(int i=0; i<nz2; i++)
    {
        cout<<col_indices2[i]<<" ";
    }
    cout<<endl<<endl;
    cout<<"Values of matrix 2 : "<<endl;
    for(int i=0; i<nz2; i++)
    {
        cout<<val2[i]<<" ";
    }
    cout<<endl<<endl;

    //matrix multiplication
    int ** prod = (int **)calloc(m1,sizeof(int *));
    for(int i=0; i<m1; i++)
    {
        prod[i] = (int *)calloc(n2, sizeof(int));
        for(int j=0; j<n2; j++)
        {
            for(int k=0; k<n1; k++)
            {
                int a = 0;
                int b = 0;
                int index1 = index_of(row_indices1, col_indices1, nz1, i, k);
                if(index1 >= 0)
                {
                    a = val1[index1];
                }
                int index2 = index_of(row_indices2, col_indices2, nz2, k, j);
                if(index2 >= 0)
                {
                    b = val2[index2];
                }
                prod[i][j] = prod[i][j] + (a*b);
            }
        }
    }
    cout<<"The product matrix is : \n";
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