#include <bits/stdc++.h>
using namespace std; 

char buffer[CHAR_MAX];
int t=0;

bool areEqual(int arr1[], int arr2[], int n) 
{   
    for (int i=0; i<n; i++) 
         if (arr1[i] != arr2[i]) 
            return false; 
  
    return true; 
}

bool greaterA(int *A,int * B,int N) {
    for(int i=0;i<N;i++) {
        if(A[i] > B[i]) {
            return true;
        }
    }
    return false;
}

bool check(int *A, int *B, int N) {
    if(greaterA(A, B, N)) {
        return false;
    }
    if(areEqual(A, B, N)) {
        return true;
    }
    for(int i=0;i<N-3;i++) {
        int *temp = A;
        for(int j=0;j<3;i++) {
            temp[i+j] += (j+1);
        }
        check(temp, B, N);
    }
}

int main() {
    int T=0;
    cin >> T;
    for(int i=0;i<T;i++) {
        int N = 0;
        cin >> N;
        int *A, *B;
        A = (int *)malloc(sizeof(int)*N);
        B = (int *)malloc(sizeof(int)*N);
        for(int j=0;j<N;j++) {
            cin >> A[j];
        }
        for(int j=0;j<N;j++) {
            cin >> B[j];
        }
        check(A, B, N) ? (t += sprintf(buffer+t, "TAK\n")) : (t += sprintf(buffer+t, "NIE\n"));
        cout << "da";
        
    }
    printf("%s", buffer);
    return 0;
}
