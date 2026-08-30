#include<stdio.h>
void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
int partition(int a[],int low,int high){
    int pivot=a[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(a[j]<=pivot){
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[high]);
    return i+1;
}
// recursive approach
/*
void quickSort(int a[],int low,int high){
    if(low<high){
        int pi=partition(a,low,high);
        quickSort(a,low,pi-1);
        quickSort(a,pi+1,high);
    }
}
*/
// Non Recursive approach
void quickSort(int a[],int low,int high){
    int stack[7];
    int top=-1;
    stack[++top]=low;
    stack[++top]=high;
    while(top>=0){
        high=stack[top--];
        low=stack[top--];
        int p=partition(a,low,high);
        if(p-1>low){
            stack[++top]=low;
            stack[++top]=p-1;
        }
        if(p+1<high){
            stack[++top]=p+1;
            stack[++top]=high;
        }
    }
}
int main(){
    int a[]={8,7,6,5,4,3,2};
    quickSort(a,0,6);
    for(int i=0;i<7;i++){
        printf("%d ",a[i]);
    }
}