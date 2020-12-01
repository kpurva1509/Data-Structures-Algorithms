#include "headers.hpp"

/* Basic framework to follow for backtracking: 
 * function backtrack(path, selection list):
 * 
 *      if end condition is satisfied
 *              return
 * 
 *      for item in the selection list
 *          select item
 *          (remove from selection list and put into path)
 *          backtrack(path, selection list) --> DFS Approach
 *          deselect item
 *          (remove from path and put back into selection list)
 * end backtrack
 */

/* 1. Subset of the given input */

template<typename T>
void subsetsUtil(std::vector<T>& input, int start, 
                 std::vector<T>& track, std::vector<std::vector<T> > result) {
    
    /* terminating recursion */
    if(start == input.size()) return;

    result.push_back(track);

    for(int i = start; i < input.size(); i++) {
        track.push_back(input[i]);
        subsetsUtil<T>(input,i + 1, track, result);
        track.pop_back();
    }
}

template<typename T>
std::vector<std::vector<T> > subsets(std::vector<T>& input) {

    std::vector<std::vector<T> > result;
    std::vector<T> track;
    subsetsUtil<T>(input, 0, track, result);
    return result;
}

/* 2. Combinations of given input */
void combineUtil(std::vector<int> &input, int position,
                std::vector<int>& track, std::vector<std::vector<int> >& result) {

    /* terminating condition  */
    if(track.size() == input.size()) {
        result.push_back(track);
        return;
    }

    for(int i=position; i<input.size(); i++) {

        // if(auto iter = std::find(track.begin(), track.end(), input[i]); iter != track.end()) continue;

        track.push_back(input[i]);
        combineUtil(input, i+1, track, result);
        track.pop_back();
    }
}

std::vector<std::vector<int> > combine(std::vector<int>& input)  {

    std::vector<std::vector<int> > result;
    std::vector<int> track;
    combineUtil(input, 1, track, result);
    return result;
}

/* 3. Permutations of a given input */
void permuteUtil(std::vector<int>& input, 
                std::vector<int>& track, std::vector<std::vector<int> > result) {

    /* terminating condition */
    if(track.size() == input.size()){
        result.push_back(std::vector<int>(track));
        return;
    }

    for(int i=0; i<input.size(); i++) {
        if (auto iter = std::find(track.begin(), track.end(), input[i]); iter != track.end())
            continue;
        track.push_back(input[i]);
        permuteUtil(input, track, result);
        track.pop_back();
    }
  }

std::vector<std::vector<int> > permute(std::vector<int>& input) {

    std::vector<std::vector<int> > result;
    std::vector<int> mylist;
    permuteUtil(input, mylist, result);
    return result;
}

/* 4. N - Queens Problem */

bool underAttack(std::vector<std::vector<int> > &board, const int& row, const int& column){

    for(int i=0; i<column; i++) {
        if(board[row][i]) return true;
    }

    int i,j;
    for(i=row, j=column; i>=0,j>=0; i--,j--){
        if(board[i][j]) return true;
    }

    for(i=row, j=0; i>=0, j<board.size(); i--,j++) {
        if(board[i][j]) return true;
    }

}

void solveUtil(int column, std::vector<std::vector<int> >& board) {

    if(column >= board.size()){
        return;
    }

    // for every column, we choose which row will be safe for the queen
    for(int row=0; row < board.size(); row++) {

        if(!underAttack(board, row, column)){
            board[row][column] = 1;
            solveUtil(column+1, board);
            board[row][column] = 0;
        }

    }

}

std::vector<std::vector<int> > nQueens(const int& gridSize) {

    std::vector<std::vector<int> > board(gridSize, std::vector<int>(gridSize, 0));
    solveUtil(0, board);
    return board;

}


int main() {

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (auto&& entry : subsets<int>(vec)) {
        std::cout << "{";
        for(auto&& element : entry) {
            std::cout << element << " ";
        }
        std::cout << "}\n";
    }

        return 0;
}