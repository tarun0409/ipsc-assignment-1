#include<iostream>
using namespace std;

int main()
{
    int m1, n1, m2, n2;
    cout << "Enter the dimensions of the matrix 1 m, n : ";
    cin>>m1>>n1;
    cout << "Enter the dimensions of the matrix 2 m, n : ";
    cin>>m2>>n2;
    if(n1 != m2)
    {
        cout<<"Matrices not compatible for multiplication!";
        return 1;
    }
    cout << "Enter the elements of the matrix 1: ";
    int matrix1[m1][n1];
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n1; j++)
        {
            cin >> matrix1[i][j];
        }
    }
    cout << "Enter the elements of the matrix 2: ";
    int matrix2[m2][n2];
    for(int i=0; i<m2; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cin >> matrix2[i][j];
        }
    }
    cout<<"\nMatrix 1: \n";
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n1; j++)
        {
            cout<<matrix1[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nMatrix 2: \n";
    for(int i=0; i<m2; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cout<<matrix2[i][j]<<"\t";
        }
        cout<<endl;
    }
    int product[m1][n2];
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n2; j++)
        {
            product[i][j] = 0;
            for(int k = 0; k<n1; k++)
            {
                product[i][j] = product[i][j] + matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    cout<<"\nProduct matrix: \n";
    for(int i=0; i<m1; i++)
    {
        for(int j=0; j<n2; j++)
        {
            cout<<product[i][j]<<"\t";
        }
        cout<<endl;
    }

    return 0;
}