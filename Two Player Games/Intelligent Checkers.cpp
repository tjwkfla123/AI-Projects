#include <iostream>
#include <utility>
#include <tuple>
#include <chrono>

auto start = std::chrono::high_resolution_clock::now();

// global variable path to save which path is the best path and value
std::tuple<int, int, int, int> bestPath;
int bestValue;
std::tuple<int, int, int, int> bestPathAB;
int bestValueAB;
int bestValueABP2;
bool gameFin = false;
int totalMoveGen1 = 0;
int totalMoveGen2 = 0;
int globalDepth1 = 0;
int globalDepth2 = 0;

int min(int val1, int val2)
{
  if(val1 < val2)
  {
    return val1;
  }
  else if(val2 < val1)
  {
    return val2;
  }
  else
  {
    return val1;
  }
}


int max(int val1, int val2)
{
  if(val1 > val2)
  {
    return val1;
  }
  else if(val2 > val1)
  {
    return val2;
  }
  else
  {
    return val1;
  }
}

std::tuple<int, int, int, int>* movegen(int** board, int player, int** king)
{
  // first two int inital position of checker. second two int: position after the checker move
  std::tuple<int, int, int, int>* movable = new std::tuple<int, int, int, int> [100];

  int count = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      // red player's turn. Check all the player and put all the possible moves to path array.
      if (player == 2 && board[i][j] == 2) {
	      // pawn diagnal move
        if ((j != 0) && (i != 7) && (board[i + 1][j - 1] == 0)) {
      	  movable[count] = std::make_tuple(i, j, i + 1, j - 1);
      	  count++;
        }
      	if ((j != 7) && (i != 7) && (board[i + 1][j + 1] == 0)) {
      	  movable[count] = std::make_tuple(i, j, i + 1, j + 1);
      	  count++;
      	}
      	// pawn taking other player's pawn
      	if ((j > 1) && (i < 6) && (board[i + 1][j - 1] == 1) && (board[i + 2][j - 2] == 0)) {
          movable[count] = std::make_tuple(i, j, i + 2, j - 2);
      	  count++;
      	}
      	if ((j < 6) && (i < 6) && (board[i + 1][j + 1] == 1) && (board[i + 2][j + 2] == 0)) {
      	  movable[count] = std::make_tuple(i, j, i + 2, j + 2);
      	  count++;
      	}
      	// king move backwards
      	if ((i != 0) && (j != 0) && (board[i - 1][j - 1] == 0) && (king[i][j] == 1)) {
      	  movable[count] = std::make_tuple(i, j, i - 1, j - 1);
      	  count++;
      	}
      	if ((i != 0) && (j != 7) && (board[i - 1][j + 1] == 0) && (king[i][j] == 1)) {
          movable[count] = std::make_tuple(i, j, i - 1, j + 1);
      	  count++;
        }
	// king move backwarkward and take pawn
        if ((i > 1) && (j < 6) && (board[i - 2][j + 2] == 0) && (king[i][j] == 1) && board[i - 1][i + 1] == 2) {
          movable[count] = std::make_tuple(i, j, i - 2, j + 2);
          count++;
        }
        if ((i > 1) && (j > 1) && (board[i - 2][j - 2] == 0) && (king[i][j] == 1) && board[i - 1][j - 1] == 2) {
          movable[count] = std::make_tuple(i, j, i - 2, j - 2);
          count++;
        }

      }

      // black player's turn. Check all the player and put all the possible moves to path array.
      if (player == 1 && board[i][j] == 1) {
        // pawn diagnal move
        if ((j != 0) && (i != 0) && (board[i - 1][j - 1] == 0)) {
          movable[count] = std::make_tuple(i, j, i - 1, j -1);
          count++;
        }
        if ((j != 7) && (i != 0) && (board[i - 1][j + 1] == 0)) {
          movable[count] = std::make_tuple(i, j, i - 1, j + 1);
          count++;
        }
        // pawn taking other player's pawn
        if ((j > 1) && (i > 1) && (board[i - 1][j - 1] == 2) && (board[i - 2][j - 2] == 0)) {
          movable[count] = std::make_tuple(i, j, i - 2, j - 2);
          count++;
        }
        if ((j != 6) && (j != 7) && (i > 1) && (board[i - 1][j + 1] == 2) && (board[i - 2][j + 2] == 0) ) {
          movable[count] = std::make_tuple(i, j, i - 2, j + 2);
          count++;
        }
        // king move backwards
        if ((i != 7) && (j != 0) && (board[i + 1][j - 1] == 0) && (king[i][j] == 1)) {
          movable[count] = std::make_tuple(i, j, i + 1, j - 1);
          count++;
        }
        if ((i != 7) && (j != 7) && (board[i + 1][j + 1] == 0) && (king[i][j] == 1)) {
          movable[count] = std::make_tuple(i, j, i + 1, j + 1);
          count++;
        }
        if ((king[i][j] == 1) && (board[i+1][j+1] == 2)){
          movable[count] = std::make_tuple(i, j, i + 2, j + 2);
          count++;
        }
        // king take pawn by moving back
	if ((i < 6) && (j > 1) && (board[i + 2][j - 2] == 0) && (king[i][j] == 1) && board[i + 1][i - 1] == 1) {
          movable[count] = std::make_tuple(i, j, i + 2, j - 2);
          count++;
        }
        if ((i < 6) && (j < 6) && (board[i + 2][j + 2] == 0) && (king[i][j] == 1) && board[i + 1][j + 1] == 1) {
          movable[count] = std::make_tuple(i, j, i + 2, j + 2);
          count++;
        }

      }
    }
  }

  if (player == 1) {
    totalMoveGen1 += count;
  } else {
    totalMoveGen2 += count;
  }
  return movable;
}

bool deepenough(int depth)
{
  if (depth < 2) return false;
  else return true;
}

bool deepenoughpruning(int depth)
{
  if (depth < 3) return false;
  else return true;
}

int evalJarim(int** board, int** king, int player){
  int redVal = 0, blackVal = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((board[i][j] == 2) && (king[i][j] == 0) && (i > 3)) {
        redVal = redVal + 6;
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
      }
      else if ((board[i][j] == 2) && (king[i][j] == 0)) {
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
        redVal = redVal + 4;
      }
      else if ((board[i][j] == 2) && (king[i][j] == 1)) {
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
        redVal = redVal + 10;
      }
      else if ((board[i][j] == 1) && (king[i][j] == 0) && (i < 4)) {
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
        blackVal = blackVal + 6;
      }
      else if ((board[i][j] == 1) && (king[i][j] == 0)) {
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
        blackVal = blackVal + 4;
      }
      else if ((board[i][j] == 1) && (king[i][j] == 1)) {
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
        blackVal = blackVal + 10;
      }
    }
  }

  if (player == 2) return redVal - blackVal;
  else return (redVal - blackVal) * -1;
}

int evalMorgan(int** board, int** king, int player) {
  int redVal = 0, blackVal = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if ((board[i][j] == 2) && (king[i][j] == 0)){
        redVal = redVal + 1;
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
      }
      else if ((board[i][j] == 2) && (king[i][j] == 1)) {
        redVal = redVal + 2;
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
      }
      else if ((board[i][j] == 1) && (king[i][j] == 0)) {
        blackVal = blackVal + 1;
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
      }
      else if ((board[i][j] == 1) && (king[i][j] == 1)) {
        blackVal = blackVal + 2;
        if (player == 2) {
          totalMoveGen2++ ;
        } else {
          totalMoveGen1++;
        }
      }
    }
  }

  if (player == 2) return redVal - blackVal;
  else return (redVal - blackVal) * -1;
}

int evalCody(int** board, int** king, int player)
{
  int redVal = 0, blackVal = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if(board[i][j] == 2)
      {
        if(king[i][j] == 0)
        {
          if(i+2 < 8 && j+2 < 8)
          {
            if(board[i+2][j+2] == 0 && board[i+1][i+1] == 1)
            {
              if(king[i+1][j+1] == 0)
              {
                redVal = redVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                redVal = redVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i+2 < 8 && j-2 >= 0)
          {
            if(board[i+2][j-2] == 0 && board[i+1][i-1] == 1)
            {
              if(king[i+1][j-1] == 0)
              {
                redVal = redVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                redVal = redVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          if(i > 3)
          {
            redVal = redVal + 2;
            if (player == 2) {
              totalMoveGen2++ ;
            } else {
              totalMoveGen1++;
            }
          }
          else
          {
            redVal = redVal + 1;
            if (player == 2) {
              totalMoveGen2++ ;
            } else {
              totalMoveGen1++;
            }
          }
        }
        else if(king[i][j] == 1)
        {
          if(i+2 < 8 && j+2 < 8)
          {
            if(board[i+2][j+2] == 0 && board[i+1][i+1] == 1)
            {
              if(king[i+1][j+1] == 0)
              {
                redVal = redVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                redVal = redVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i+2 < 8 && j-2 >= 0)
          {
            if(board[i+2][j-2] == 0 && board[i+1][i-1] == 1)
            {
              if(king[i+1][j-1] == 0)
              {
                redVal = redVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                redVal = redVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i-2 >= 0 && j-2 >= 0)
          {
            if(board[i-2][j-2] == 0 && board[i-1][i-1] == 1)
            {
              if(king[i-1][j-1] == 0)
              {
                redVal = redVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                redVal = redVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i-2 >= 0 && j+2 < 8)
          {
            if(board[i-2][j+2] == 0 && board[i-1][i+1] == 1)
            {
              if(king[i-1][j+1] == 0)
              {
                redVal = redVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                redVal = redVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }

          redVal = redVal + 3;
        }
      }
      else if(board[i][j] == 1)
      {
        if(king[i][j] == 0)
        {
          if(i-2 >= 0 && j+2 < 8)
          {
            if(board[i-2][j+2] == 0 && board[i-1][i+1] == 2)
            {
              if(king[i-1][j+1] == 0)
              {
                blackVal = blackVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                blackVal = blackVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i-2 >= 0 && j-2 >= 0)
          {
            if(board[i-2][j-2] == 0 && board[i-1][i-1] == 2)
            {
              if(king[i-1][j-1] == 0)
              {
                blackVal = blackVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                blackVal = blackVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          if(i < 4)
          {
            blackVal = blackVal + 2;
            if (player == 2) {
              totalMoveGen2++ ;
            } else {
              totalMoveGen1++;
            }
          }
          else
          {
            blackVal = blackVal + 1;
            if (player == 2) {
              totalMoveGen2++ ;
            } else {
              totalMoveGen1++;
            }
          }
        }
        else if(king[i][j] == 1)
        {
          if(i+2 < 8 && j+2 < 8)
          {
            if(board[i+2][j+2] == 0 && board[i+1][i+1] == 1)
            {
              if(king[i+1][j+1] == 0)
              {
                blackVal = blackVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                blackVal = blackVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i+2 < 8 && j-2 >= 0)
          {
            if(board[i+2][j-2] == 0 && board[i+1][i-1] == 1)
            {
              if(king[i+1][j-1] == 0)
              {
                blackVal = blackVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                blackVal = blackVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
            }
          }
          else if(i-2 >= 0 && j-2 >= 0)
          {
            if(board[i-2][j-2] == 0 && board[i-1][i-1] == 1)
            {
              if(king[i-1][j-1] == 0)
              {
                blackVal = blackVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                blackVal = blackVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }
          else if(i-2 >= 0 && j+2 < 8)
          {
            if(board[i-2][j+2] == 0 && board[i-1][i+1] == 1)
            {
              if(king[i-1][j+1] == 0)
              {
                blackVal = blackVal + 4;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
              else
              {
                blackVal = blackVal + 5;
                if (player == 2) {
                  totalMoveGen2++ ;
                } else {
                  totalMoveGen1++;
                }
              }
            }
          }

          blackVal = blackVal + 3;
        }
      }
    }
    }
  }

  if (player == 2) {
    return redVal - blackVal;
  }
  else {
    return (redVal - blackVal) * -1;
  }
}

int minmax(int depth, int **board, int player, int **king, int function)
{
  // initialize
  if (player == 1) {
    globalDepth1 = depth;
  } else {
    globalDepth2 = depth;
  }

  bool didChange = false;
  std::tuple<int, int, int, int>* sucessor = new std::tuple<int, int, int, int> [50];
  int** sampleBoard = new int* [8];
  for (int i = 0; i < 8; ++i) sampleBoard[i] = new int [8];
  int** sampleKing = new int* [8];
  for (int i = 0; i < 8; ++i) sampleKing[i] = new int [8];
  for (int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      sampleBoard[i][j] = board[i][j];
      sampleKing[i][j] = king[i][j];
    }
  }

  // check the depth
  if (deepenough(depth)) {
    if (function == 1) return evalJarim(board, king, player);
    else if (function == 2) return evalMorgan(board, king, player);
    else return evalCody(board, king, player);
    return 0;
  }

  // get all possible moves
  sucessor = movegen(board, player, king);
  int newVal = 0;
  int count = 0;
  while (count < (sizeof(sucessor) -1)) {
    // set board according to sucessor move
    sampleBoard[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] = 0;
    sampleBoard[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = player;

    if (king[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] == 1) {
      sampleKing[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] == 1;
    }

    // run MinMax recursively
    int oppPlayer;
    if (player == 1) oppPlayer = 2;
    else oppPlayer = 1;
    newVal = minmax(depth + 1, sampleBoard, player, sampleKing, function);
    newVal = newVal * -1;
    // return board to previous
    sampleBoard[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] = player;
    sampleBoard[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = 0;
    if (king[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] == 1) {
      sampleKing[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = 0;
    }

    // if better value is found, update the path and the value.
    if (newVal > bestValue) {
      didChange = true;
      bestValue = newVal;
      bestPath = std::make_tuple(std::get<0>(sucessor[count]), std::get<1>(sucessor[count]), std::get<2>(sucessor[count]), std::get<3>(sucessor[count]));
    }
    count++;
  }
  // if the values are all the same, make any move.
  if (!didChange) {
  if (function == 1) {
        bestPath = std::make_tuple(std::get<0>(sucessor[0]), std::get<1>(sucessor[0]), std::get<2>(sucessor[0]), std::get<3>(sucessor[0]));

       }
       if (function == 2) {
         bestPath = std::make_tuple(std::get<0>(sucessor[3]), std::get<1>(sucessor[3]), std::get<2>(sucessor[3]), std::get<3>(sucessor[3]));
       }
       else{
         bestPath = std::make_tuple(std::get<0>(sucessor[4]), std::get<1>(sucessor[4]), std::get<2>(sucessor[4]), std::get<3>(sucessor[4]));
       }

  }

  delete[] sucessor;
  for (int i = 0; i < 8; ++i) delete[] sampleKing[i];
  delete[] sampleKing;
  for (int i = 0; i < 8; ++i) delete[] sampleBoard[i];
  delete[] sampleBoard;

  return bestValue;
}

int alphaBetaPruning(int **board, int **king, int depth, int alpha, int beta, int player, int function)
{
  if (player == 1) {
    globalDepth1 = depth;
  } else {
    globalDepth2 = depth;
  }

  if(deepenoughpruning(depth))
  {
    if(function == 1)
    {
      return evalJarim(board, king, player);
    }
    else if(function == 2)
    {
      return evalMorgan(board, king, player);
    }
    else
    {
      return evalCody(board, king, player);
    }
  }

  bool didChange = false;
  std::tuple<int, int, int, int>* sucessor = new std::tuple<int, int, int, int> [50];

  int** sampleBoard = new int* [8];
  for(int i = 0; i < 8; ++i)
    sampleBoard[i] = new int [8];

  int** sampleKing = new int* [8];
  for(int i = 0; i < 8; ++i)
    sampleKing[i] = new int [8];

  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      sampleBoard[i][j] = board[i][j];
      sampleKing[i][j] = king[i][j];
    }
  }
  int val;
  if(player == 1)
  {
    sucessor = movegen(board, player, king);
    bestValueAB = -9999;
    int count = 0;
    while(count < (sizeof(sucessor)-1))
    {
      sampleBoard[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] = 0;
      sampleBoard[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = player;

      val = alphaBetaPruning(sampleBoard, sampleKing, depth+1, alpha, beta, 2, function);

      sampleBoard[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] = player;
      sampleBoard[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = 0;
      count++;

      if(val < bestValueAB)
      {
        didChange = true;
        bestValueAB = val;
        bestPathAB = std::make_tuple(std::get<0>(sucessor[count]), std::get<1>(sucessor[count]), std::get<2>(sucessor[count]), std::get<3>(sucessor[count]));
      }
      alpha = max(alpha, bestValueAB);

      if(alpha >= beta)
      {
        break;
      }
    }

    if(!didChange)
    {
	if (function == 1) {
        bestPathAB = std::make_tuple(std::get<0>(sucessor[2]), std::get<1>(sucessor[2]), std::get<2>(sucessor[2]), std::get<3>(sucessor[2]));

       }
       if (function == 2) {
         bestPathAB = std::make_tuple(std::get<0>(sucessor[0]), std::get<1>(sucessor[0]), std::get<2>(sucessor[0]), std::get<3>(sucessor[0]));
       }
       else{
         bestPathAB = std::make_tuple(std::get<0>(sucessor[5]), std::get<1>(sucessor[5]), std::get<2>(sucessor[5]), std::get<3>(sucessor[5]));
       }
    }
  }
  else
  {
    sucessor = movegen(board, player, king);
    bestValueABP2 = 9999;
    int count = 0;
    while(count < (sizeof(sucessor)-1))
    {
      sampleBoard[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] = 0;
      sampleBoard[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = player;
      if (king[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] == 1) {
        sampleKing[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] == 1;
      }
      val = alphaBetaPruning(sampleBoard, sampleKing, depth+1, alpha, beta, 1, function);
      if (king[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] == 1) {
        sampleKing[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] == 0;
      }
      sampleBoard[std::get<0>(sucessor[count])][std::get<1>(sucessor[count])] = player;
      sampleBoard[std::get<2>(sucessor[count])][std::get<3>(sucessor[count])] = 0;
      count++;

      if(val > bestValueABP2)
      {
        didChange = true;
        bestValueABP2 = val;
        bestPathAB = std::make_tuple(std::get<0>(sucessor[count]), std::get<1>(sucessor[count]), std::get<2>(sucessor[count]), std::get<3>(sucessor[count]));
      }
      beta = min(beta, val);
      if(alpha >= beta)
      {
        break;
      }
    }

    if(!didChange)
    {
       if (function == 1) {
        bestPathAB = std::make_tuple(std::get<0>(sucessor[2]), std::get<1>(sucessor[2]), std::get<2>(sucessor[2]), std::get<3>(sucessor[2]));

       }
       if (function == 2) {
         bestPathAB = std::make_tuple(std::get<0>(sucessor[0]), std::get<1>(sucessor[0]), std::get<2>(sucessor[0]), std::get<3>(sucessor[0]));
       }
       else {
         bestPathAB = std::make_tuple(std::get<0>(sucessor[5]), std::get<1>(sucessor[5]), std::get<2>(sucessor[5]), std::get<3>(sucessor[5]));
       }
     }
  }

  for (int i = 0; i < 8; ++i) delete[] sampleBoard[i];
  delete[] sampleBoard;
  for (int i = 0; i < 8; ++i) delete[] sampleKing[i];
  delete[] sampleKing;
  delete[] sucessor;

  return val;
}

bool makeMove(int** board, std::pair<int, int> position, std::pair<int, int> move, int player, int** king) {
  //current position
  int initX = position.first;
  int initY = position.second;

  // moving position
  int x = move.first;
  int y = move.second;

  // No checker in the selected position
  if(board[initX][initY] == 0){
    printf("No checker in the selected position!");
    gameFin = true;
    return false;
  }

  // makes invalid move (same color checker there)
  if (board[x][y] != 0 && player == board[x][y]) {
    printf("Invalid move: already a same-color checker there!\n");
    gameFin = true;
    return false;
  }

  // makes invalid move (back)
  if (((initX > x) && player == 2) && king[initX][initY] == 0) {
    printf("Invalid move: cannot move back!\n");
    gameFin = true;
    return false;
  }

  if (((initX < x) && player == 1) && king[initX][initY] == 0) {
    printf("Invalid move: cannot move back!\n");
    gameFin = true;
    return false;
  }

  // makes invalid move (straight)
  if (initY == y ) {
    printf("Invalid move: cannot move straight!\n");
    gameFin = true;
    return false;
  }

  // takes another player's checker
  if ((initX + 2 == x) && (initY - 2 == y) && (board[x + 1][y - 1] != player)) {
    board[x + 1][y - 1] = 0;
    board[x][y] = player;
    board[initX][initY] = 0;
    printf("Took other player's checker!\n");
    return true;
  }

  if ((initX + 2 == x) && (initY + 2 == y) && (board[x + 1][y + 1] != player)) {
    board[x + 1][y + 1] = 0;
    board[x][y] = player;
    board[initX][initY] = 0;
    printf("Took other player's checker!\n");
    return true;
  }

  // makes valid move (diagonal)
  if (king[initX][initY] == 0) {
    board[x][y] = player;
    board[initX][initY] = 0;

    // make the player king if necessary
    if ((player == 2 && x == 7) || (player == 1 && x == 0)) {
      king[x][y] = 1;
    }
    printf("Valid diagonal move!");
    return true;
  }

  // player is king and move multiple squares
  if (x - initX > 0) {
    int kingmove = x - initX;
    if (initY + kingmove == y) {
      king[x][y] = 1;
      king[initX][initY] = 0;
      board[initX][initY] = 0;
      board[x][y] = player;
      printf("Valid move: king moves backward!\n");
      return true;
    }
  }

  if (initX - x > 0) {
    int kingmove = initX - x;
    if (initY - kingmove == y) {
      king[x][y] = 1;
      king[initX][initY] = 0;
      board[initX][initY] = 0;
      board[x][y] = player;
      printf("Valid move: king moves forward!\n");
      return true;
    }
  }

  return false;
}

int main()
{
  printf("-----------------------------------------------------------------------\nWelcome to checkers! You will be playing against the computer in an effort to win. \n Directions: The first prompt will ask for the location of the checker you wish to move. Enter its location in the form xy where x is the row number and y is the column number. For instance, if you want to move the piece in the first row, third column, enter 13. The next prompt will ask for the location that you would like to move your piece to. Enter the new location in the same format as above.\n YOU ARE PLAYER 2. 2 indicate your checkers, 1 indicates your opponent's checkers.\n-----------------------------------------------------------------------\n\n\n");

  int moveCount = 0;
  int moveCount1 = 0;
  int moveCount2 = 0;
  int humanGame = 2; // computer v. computer by default
  int player = 2; // Player 2 by default
  int evalFunction1 = 1; // Jarim's by default
  int evalFunction2 = 1; // Jarim's by default
  int algorithm = 1; // Minmax by default
  int algorithm1 = 1; // Minmax by default
  int algorithm2 = 1; // Minmax by default

  printf("Game Mode:\n");
  printf("1. Human v. Computer\n");
  printf("2. Computer v. Computer\n");
  printf("Select 1 or 2: ");
  std::cin >> humanGame;

  // If computer vs computer select algorithm for both
  if (humanGame == 2) {
    printf("\n\nSelect Player 1's evaluation function:\n");
    printf("1. Jarim's\n");
    printf("2. Morgan's\n");
    printf("3. Cody's\n");
    std::cin >> evalFunction1;

    printf("\n\nSelect Player 1's algorithm:\n");
    printf("1. Minmax-A-B\n");
    printf("2. Alpha-Beta-Search\n");
    std::cin >> algorithm1;

    printf("\n\nSelect Player 2's evaluation function:\n");
    printf("1. Jarim's\n");
    printf("2. Morgan's\n");
    printf("3. Cody's\n");
    std::cin >> evalFunction2;

    printf("\n\nSelect Player 2's algorithm:\n");
    printf("1. Minmax-A-B\n");
    printf("2. Alpha-Beta-Search\n");
    std::cin >> algorithm2;
  } else { // If human v. computer, human doesn't heed their own algorithm
    printf("\n\nSelect the Computer's evaluation function: \n");
    printf("1. Jarim's\n");
    printf("2. Morgan's\n");
    printf("3. Cody's\n");
    std::cin >> evalFunction1;

    printf("\n\nSelect the Computer's algorithm:\n");
    printf("1. Minmax-A-B\n");
    printf("2. Alpha-Beta-Search\n");
    std::cin >> algorithm1;
  }

  // initialize board
  int** board = new int* [8];
  for (int i = 0; i < 8; ++i) board[i] = new int [8];

  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      board[i][j] = 0;
    }
  }

  // set red players
  for (int i = 0; i < 3; i++) {
    if (i == 0 || i == 2) {
      for (int j = 0; j < 8; j += 2) {
        board[i][j] = 2;
      }
    }
    if (i == 1) {
      for (int j = 1; j < 8; j += 2) {
        board[i][j] = 2;
      }
    }
  }
  // set black players
  for (int i = 5; i < 8; i++) {
    if (i == 6) {
      for (int j = 0; j < 8; j += 2) {
        board[i][j] = 1;
      }
    }
    if (i == 5 || i == 7) {
      for (int j = 1; j < 8; j += 2) {
        board[i][j] = 1;
       }
    }
  }

  // initialize king array
  int** king = new int* [8];
  for (int i = 0; i < 8; ++i) king[i] = new int [8];

  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    {
      king[i][j] = 0;
    }
  }

  // print the board
  printf("\n-----------------------PLAYER 2-----------------------");
  printf("\n------------------------------------------------------\n");
  printf("COLUMNS | 0     1     2     3     4     5     6     7");
  printf("\n------------------------------------------------------\n");
  for (int i = 0 ; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (j == 0 ) {
        printf("ROW %d   |", i);
      }
      if( j < 7 ){
        printf(" %d  | ", board[i][j]);
      } else {
        printf(" %d", board[i][j]);
      }
    }
    printf("\n------------------------------------------------------\n");
  }
  printf("-----------------------PLAYER 1-----------------------\n");

  // Human v. Computer game
  while (gameFin == false && humanGame == 1) {
    int checker1Count = 0;
    int checker2Count = 0;
    // if no more checkers on the board, game is over
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (board[i][j] == 2) {
            checker2Count++;
          } else if (board[i][j] == 1){
            checker1Count++;
          }
        }
    }

    if(checker2Count == 0 || checker1Count == 0) {
      gameFin = true;
      return 0;
    }

    if (player == 2) {
      int fromRow;
      int fromColumn;
      printf("\nEnter the row of the checker you would like to move: ");
      std::cin >> fromRow;
      printf("\nEnter the column of the checker you would like to move: ");
      std::cin >> fromColumn;
      printf("\nYou entered row %d and column %d \n", fromRow, fromColumn);

      int toRow;
      int toColumn;
      printf("\nEnter the row where you would like to move the checker to: ");
      std::cin >> toRow;
      printf("\nEnter the column where you would like to move the checker to: ");
      std::cin >> toColumn;
      printf("\nYou entered row %d and column %d \n", toRow, toColumn);

      // mark current positon of the checker
      std::pair<int, int> position;
      // mark position where checker wants to move to
      std::pair<int, int> move;

      position = std::make_pair(fromRow, fromColumn);
      move = std::make_pair(toRow, toColumn);

      // If false, re-prompt the user for a path that will work
      makeMove(board, position, move, player, king);
      moveCount++;
      moveCount2++;

      player = 1;
    }

    if (player == 1) {
      // start MinMax Algorithm (Initialize bestValue, which is global variable, to 0 before running the Algorithm)
      bestValue = 0;

      // This marks which person's function to use; 1 = Jarim, 2 = Morgan, 3 = Cody
      int function = evalFunction1;
      // Minmax is 1, Alpha-Beta Pruning is 2
      if(algorithm1 == 1) {
        int value = minmax(0, board, player, king, function);
      } else {
        int value = alphaBetaPruning(board, king, 0, -9999, 9999, player, function);
      }

      printf("Player 1 will move from %d %d to %d %d\n", std::get<0>(bestPath), std::get<1>(bestPath), std::get<2>(bestPath), std::get<3>(bestPath));

      std::pair<int, int> position = std::make_pair(std::get<0>(bestPath), std::get<1>(bestPath));
      std::pair<int, int> move = std::make_pair(std::get<2>(bestPath), std::get<3>(bestPath));

      makeMove(board, position, move, player, king);
      moveCount++;
      moveCount1++;

      player = 2;
    }

    // print the board
    printf("\n\n******************* BOARD STATE #%d *******************\n", moveCount);
    printf("\n------------------------------------------------------\n");
    printf("COLUMNS | 0     1     2     3     4     5     6     7");
    printf("\n------------------------------------------------------\n");
    for (int i = 0 ; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (j == 0 ) {
          printf("ROW %d   |", i);
        }
        if( j < 7 ){
          printf(" %d  | ", board[i][j]);
        } else {
          printf(" %d", board[i][j]);
        }
      }
      printf("\n-------------------------------------------------------\n");
    }
    printf("\n******************************************************\n");
  }

  // Computer v. Computer game
  while (gameFin == false && humanGame == 2) {
    // if no more checkers on the board, game is over
    int checker1Count = 0;
    int checker2Count = 0;
    // if no more checkers on the board, game is over
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          if (board[i][j] == 2) {
            checker2Count++;
          } else if (board[i][j] == 1){
            checker1Count++;
          }
        }
    }

    if(checker2Count == 0 || checker1Count == 0) {
      gameFin = true;
      return 0;
    }

    // start MinMax Algorithm (Initialize bestValue, which is global variable, to 0 before running the Algorithm)
    bestValue = 0;
    int function = 1; // Default to minmax

    // Assign the function and algorithm based on current player and their previous selection
    if(player == 1) {
      function = evalFunction1;
      algorithm = algorithm1;
    } else {
      function = evalFunction2;
      algorithm = algorithm2;
    }

    // Select the algorithm according to the user input
    if(algorithm == 1) {
      int value = minmax(0, board, player, king, function);
    } else {
      int value = alphaBetaPruning(board, king, 0, -9999, 9999, player, function);
    }
    std::pair<int, int> position;
    std::pair<int, int> move;
    std::tuple<int, int, int, int>* sucessor = new std::tuple<int, int, int, int> [50];

    if(algorithm == 1) {
      printf("Player %d: BEST PATH From %d %d to %d %d\n", player, std::get<0>(bestPath), std::get<1>(bestPath), std::get<2>(bestPath), std::get<3>(bestPath));
      position = std::make_pair(std::get<0>(bestPath), std::get<1>(bestPath));
      move = std::make_pair(std::get<2>(bestPath), std::get<3>(bestPath));

    } else {
      printf("Player %d: BEST PATH From %d %d to %d %d\n", player, std::get<0>(bestPathAB), std::get<1>(bestPathAB), std::get<2>(bestPathAB), std::get<3>(bestPathAB));
      position = std::make_pair(std::get<0>(bestPathAB), std::get<1>(bestPathAB));
      move = std::make_pair(std::get<2>(bestPathAB), std::get<3>(bestPathAB));


    }


    makeMove(board, position, move, player, king);
    if(player == 1) {
      moveCount1++;
    } else {
      moveCount2++;
    }
    moveCount++;

    if(moveCount%2 == 0) {
      player = 2;
    } else {
      player = 1;
    }

    // print the board
    printf("\n\n******************* BOARD STATE #%d *******************\n", moveCount);
    printf("\n------------------------------------------------------\n");
    printf("COLUMNS | 0     1     2     3     4     5     6     7");
    printf("\n------------------------------------------------------\n");
    for (int i = 0 ; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (j == 0 ) {
          printf("ROW %d   |", i);
        }
        if( j < 7 ){
          printf(" %d  | ", board[i][j]);
        } else {
          printf(" %d", board[i][j]);
        }
      }
      printf("\n-------------------------------------------------------\n");
    }
    printf("\n******************************************************\n");
  }

  if (gameFin == true) {
    auto stop = std::chrono:: high_resolution_clock::now();
    if (player == 1) {
      printf("\nPlayer 1 is the winner!\n");
    } else {
      printf("\nPlayer 2 is the winner!\n");
    }
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "\nThis program completed in: "
         << duration.count() << " milliseconds";

    printf("\nPlayer 1 stats:");
    printf("\nLength of path: %d", moveCount1);
    printf("\nNumber of nodes generated: %d", totalMoveGen1);
    printf("\nNumber of nodes expanded: %d\n\n", globalDepth1);

    printf("\nPlayer 2 stats:");
    printf("\nLength of path: %d", moveCount2);
    printf("\nNumber of nodes generated: %d", totalMoveGen2);
    printf("\nNumber of nodes expanded: %d\n\n", globalDepth2);
  }

  return 0;
}
