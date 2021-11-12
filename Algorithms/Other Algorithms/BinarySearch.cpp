//
//  main.cpp
//  recursion_practice
//
//  Created by Akhil Vinta on 2/12/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include <iostream>
using namespace std;

static int runs = 0;

int binarySearch(int a[], int n, int find){

    if(n == 1) return 0;
    
    if(a[n/2] == find) return (n/2);
    
    return (a[n/2] < find) ? (n/2 + binarySearch(a + n/2, n - n/2, find)) : binarySearch(a, n - n/2, find);
    
}



int main(int argc, const char * argv[]) {
   
    int arr[] = {7,8,9,10,11,12,12,13,14,15};
    cout << binarySearch(arr,10,15) << endl;
}
