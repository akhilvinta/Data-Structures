//
//  main.cpp
//  maze
//
//  Created by Akhil Vinta on 2/10/20.
//  Copyright © 2020 Akhil Vinta. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    
    
    if(sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = 'X';
    
        if(maze[sr - 1][sc] == '.' && sr != 0)
             if(pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
                 return true;

        if(maze[sr + 1][sc] == '.' && sr != nRows - 1)
            if(pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
                return true;

        if(maze[sr][sc - 1] == '.' && sc != 0)
             if(pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
                 return true;

        if(maze[sr][sc + 1] == '.' && sc != nCols - 1)
             if(pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
                 return true;

        
    return false;

}
 
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
