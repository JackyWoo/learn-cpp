//
// Created by wujianchao5 on 2024/1/10.
//

#include <iostream>
#include <vector>

using namespace std;

using Board = vector<vector<int>>;
vector<Board> result;

bool valid(int row, int col, Board & board)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[row][i] == 1)
            return false;
    }
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i][col] == 1)
            return false;
    }
    for (int i = row, j = col; i < board.size() && j < board.size(); i++, j++)
    {
        if (board[i][j] == 1)
            return false;
    }
    for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++)
    {
        if (board[i][j] == 1)
            return false;
    }
    for (int i = row, j = col; i < board.size() && j >= 0; i++, j--)
    {
        if (board[i][j] == 1)
            return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

void backTrack(Board & board, int row, int n)
{
    if (row == n)
    {
        result.push_back(board);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (valid(row, i, board))
        {
            board[row][i] = 1;
            backTrack(board, row + 1, n);
            board[row][i] = 0;
        }
    }
}

void nQueue(int n)
{
    Board board;
    for (int i = 0; i < n; i++)
    {
        board.push_back(std::move(vector(4, 0)));
    }
    backTrack(board, 0, n);
}

int main()
{
    int n = 4;
    nQueue(n);

    /// print result
    for (const auto & board : result)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << (board[i][j] == 0 ? '.' : 'Q');
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}