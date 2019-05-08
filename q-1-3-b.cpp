#include<iostream>
using namespace std;

int val_at(int i, int j, int * row_vec, int * col_vec, int * val_vec, int m, int nz)
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

    int * row1 = (int *)calloc((m1+1),sizeof(int));
    int * col1 = (int *)calloc(nz1,sizeof(int));
    int * val1 = (int *)calloc(nz1,sizeof(int));

    int * row2 = (int *)calloc((m2+1),sizeof(int));
    int * col2 = (int *)calloc(nz2,sizeof(int));
    int * val2 = (int *)calloc(nz2,sizeof(int));

    int nz_i = 0;
    int nz_r = 0;
    for(int i=0; i<m1; i++)
    {
        bool found = false;
        for(int j=0; j<n1; j++)
        {
            if(matrix1[i][j]!=0)
            {
                int index = nz_i++;
                val1[index] = matrix1[i][j];
                col1[index] = j;
                if(!found)
                {
                    found = true;
                    row1[nz_r++] = index;
                }
            }
        }
    }
    row1[nz_r] = nz1+1;

    nz_i = 0;
    nz_r = 0;
    for(int i=0; i<m2; i++)
    {
        bool found = false;
        for(int j=0; j<n2; j++)
        {
            if(matrix2[i][j]!=0)
            {
                int index = nz_i++;
                val2[index] = matrix2[i][j];
                col2[index] = j;
                if(!found)
                {
                    found = true;
                    row2[nz_r++] = index;
                }
            }
        }
    }
    row2[nz_r] = nz2+1;

    cout<<"\nCSR of matrix 1 : \n";
    cout<<"Values : ";
    for(int i=0; i<nz1; i++)
    {
        cout<<val1[i]<<" ";
    }
    cout<<endl;
    cout<<"Cols : ";
    for(int i=0; i<nz1; i++)
    {
        cout<<col1[i]<<" ";
    }
    cout<<endl;
    cout<<"Rows : ";
    for(int i=0; i<(m1+1); i++)
    {
        cout<<row1[i]<<" ";
    }
    cout<<endl;
    cout<<"\nCSR of matrix 2 : \n";
    cout<<"Values : ";
    for(int i=0; i<nz2; i++)
    {
        cout<<val2[i]<<" ";
    }
    cout<<endl;
    cout<<"Cols : ";
    for(int i=0; i<nz2; i++)
    {
        cout<<col2[i]<<" ";
    }
    cout<<endl;
    cout<<"Rows : ";
    for(int i=0; i<(m2+1); i++)
    {
        cout<<row2[i]<<" ";
    }
    cout<<endl;

    int ** prod = (int **)calloc(m1, sizeof(int *));

    for(int i=0; i<m1; i++)
    {
        prod[i] = (int *)calloc(n2, sizeof(int));
        for(int j=0; j<n2; j++)
        {
            for(int k=0; k<n1; k++)
            {
                prod[i][j] = prod[i][j] + (val_at(i,k,row1,col1,val1,m1,nz1)*val_at(k,j,row2,col2,val2,m2,nz2));
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