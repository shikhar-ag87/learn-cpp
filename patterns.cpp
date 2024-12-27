#include <iostream>

using std::cout;

void squarePattern1(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << (char)(j+65) << " ";
        }
        cout << "\n";
    }
}

void squarePattern2(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << j+n*i+1 << " ";
        }
        cout << "\n";
    }
}

void trianglePattern1(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << "*";
        }
        cout << "\n";
    }
}

void trianglePattern2(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << i+1;
        }
        cout << "\n";
    }
}

void trianglePattern3(int n) {
    int num =1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            // cout << (i*(i+1)/2) + j+1;
            cout << num++;
        }
        cout << "\n";
    }
}

void trianglePattern4(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << ( (j<i) ? " " : std::to_string(i+1) );
        }
        cout << "\n";
    }
}

void pyramidPattern1(int n) {
    for(int i=0; i<n; i++) {
        
        for(int j=0; j<n-i; j++) {
            cout << " ";
        }
        
        for(int j=0; j<i; j++) {
            cout << j+1;
        }
        for(int j=i; j>=0; j--) {
            cout << j+1;
        }

        cout << "\n";
    }
}

void diamondPattern1(int n) {
    
    for(int i=0; i<n; i++) {

        for(int j=0; j<=2*n; j++) {
            cout << ((j==n-i || j==n+i) ? "*" : " ");
        }
        cout << "\n";
    }
    for(int i=n; i>=0; i--) {

        for(int j=0; j<=2*n; j++) {
            cout << ((j==n-i || j==n+i) ? "*" : " ");
        }
        cout << "\n";
    }
    /*
    for(int i=n-1; i>0; i--) {

        for(int j=0; j<n; j++) {
            cout << ((i==j) ? "*" : " ");
        }

        for(int j=n-2; j>=0; j--) {
            cout << ((i==j) ? "*" : " ");
        }
        cout << "\n";
    }
    for(int i=0; i<n; i++) {

        for(int j=0; j<n; j++) {
            cout << ((i==j) ? "*" : " ");
        }

        for(int j=n-2; j>=0; j--) {
            cout << ((i==j) ? "*" : " ");
        }
        cout << "\n";
    }
    */
}

void butterflyPattern1(int n) {
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<2*n; j++) {
            cout << ( (j<=i || j>=2*n-i-1) ? "*" : " " );
        }
        cout << "\n";
    }
    for(int i=n-1; i>=0; i--) {
        for(int j=0; j<2*n; j++) {
            cout << ( (j<=i || j>=2*n-i-1) ? "*" : " " );
        }
        cout << "\n";
    }

}

int main () {
    int n = 4;
    // squarePattern1(n);
    // squarePattern2(n);
    // trianglePattern1(n);
    // trianglePattern2(n);
    // trianglePattern3(n);
    // trianglePattern4(n);
    // pyramidPattern1(n);
    // diamondPattern1(n);
    butterflyPattern1(n);
    return 0;
}

