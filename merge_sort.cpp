#include<iostream>
#include<bits/stdc++.h>

using namespace std;

void merge(int a[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = 0;

    int b[ub - lb + 1];

    while(i <= mid && j <= ub)
    {
        if(a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }

    while(i <= mid)
        b[k++] = a[i++];

    while(j <= ub)
        b[k++] = a[j++];

    for(int s = 0; s < k; s++)
        a[lb + s] = b[s];
}



void merge_sort(int *a, int lb, int ub)
{
    if(lb>=ub) return;
    int mid = (lb+ub)/2;
    merge_sort(a,lb,mid);
    merge_sort(a,mid+1,ub);
    merge(a,lb,mid,ub);
}

int main()
{
    int a[]={34,12,55,67,90,44};
    int n = sizeof(a)/sizeof(a[0]);
    merge_sort(a,0,n-1);
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}