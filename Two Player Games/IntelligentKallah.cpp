#include <string>
#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <unistd.h>

using namespace std;

int* bestPathMinmax = new int [14];
int* bestPathAB = new int [14];
int gamePath, nodeNum;
int pathCount;
int bestValueAB;
int bestValueABP2;

struct gameStat
{
  int value;
  int path[10];
};

/* From: https://gist.github.com/thirdwing/da4621eb163a886a03c5
to calculate the total memory used by the program */

void process_mem_usage(double& vm_usage, double& resident_set)
{
    vm_usage     = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}

int jarimEval (int* board, int player)
{
  int current = board[6];
  int opponent = board[13];

  if (player == 2) {
    current = board[13];
    opponent = board[6];
  }
  return current * 10 + opponent * 5;
}

int navyaEval (int* board, int player)
{
  int value1 = 0, value2= 0;
  for (int i = 0; i < 7; i++) value1 += board[i];
  for (int i = 8; i < 14; i++) value2 += board[i];

  if (player == 1) return value1 * 20;
  else return value2 * 20;
}

bool deep_enough (int depth, int set_depth)
{
  if (depth == set_depth) return true;
  else return false;
}

int** gen_move(int* board, int player)
{
  int** sucessor = new int* [20];
  for (int i = 0; i < 20; i++) {
    sucessor[i] = new int [14];
    for (int j = 0; j < 14; j++) sucessor[i][j] = INT_MIN;
  }
  int succ_count = 0;
  int temp_board[14];

  // player 1 gen-move
  if (player == 1) {
    for (int i = 0; i < 6; i++) {
	    for (int i = 0; i < 14; i++) temp_board[i] = board[i];
      if (temp_board[i] != 0) {
        int stones = temp_board[i];
        int count = i;
        temp_board[i] = 0;
        for (int j = 0; j < stones; j++) {
          count = count + 1;
          if (count >= 14) count = 0;
          if (count != 13) temp_board[count]++;
          else j--;
        }
        // if last landed on player's kallah
        if (count == 6) {
          bool repeat = true;
          while (repeat) {
            int pick = 0;
            for (int j = 0; j < 6; j++) {
              if (temp_board[j] != 0) pick = j;
             }
            int stones = temp_board[pick];
            int count = pick;
            temp_board[pick] = 0;
            for (int j = 0; j < stones; j++) {
              count = count + 1;
              if (count >= 14) count = 0;
              if (count != 13) temp_board[count]++;
              else j--;
            }
            if (count != 6) repeat = false;
          }
        }
        // if there is only one stone
        if (count < 6 && temp_board[count] == 1) {
          int opponent = 12 - count;
          int add = temp_board[opponent] + 1;
          temp_board[6] += add;
          temp_board[opponent] = 0;
          temp_board[count] = 0;
        }
        // else just finish
        for (int j = 0; j < 14; j++) sucessor[succ_count][j] = temp_board[j];
        succ_count++;
      }
    }
  }

  // player 2 gen-move
  if (player == 2) {
    for (int i = 7; i < 13; i++) {
      for (int i = 0; i < 14; i++) temp_board[i] = board[i];
      if (temp_board[i] != 0) {
        int stones = temp_board[i];
        int count = i;
        temp_board[i] = 0;
        for (int j = 0; j < stones; j++) {
          count = count + 1;
          if (count >= 14) count = 0;
          if (count != 6) temp_board[count]++;
          else j--;
        }
        // if last landed on player's kallah
        if (count == 13) {
          bool repeat = true;
          while (repeat) {
            int pick = 0;
            for (int j = 7; j < 13; j++) {
              if (temp_board[j] != 0) pick = j;
             }
            int stones = temp_board[pick];
            int count = pick;
            temp_board[pick] = 0;
            for (int j = 0; j < stones; j++) {
              count = count + 1;
              if (count >= 14) count = 0;
              if (count != 7) temp_board[count]++;
              else j--;
            }
            if (count != 6) repeat = false;
          }
        }
        // if there is only one stone
        if (count > 6 && temp_board[count] == 1 && count != 13) {
          int opponent = 12 - count;
          int add = temp_board[opponent] + 1;
          temp_board[6] += add;
          temp_board[opponent] = 0;
          temp_board[count] = 0;
        }
        // else just finish
        for (int j = 0; j < 14; j++) sucessor[succ_count][j] = temp_board[j];
        succ_count++;
      }
    }
  }

  return sucessor;
}

gameStat minmaxAB(int* board, const int set_depth, int depth, int use_tresh, int pass_tresh, int player, const int eval1, const int eval2)
{
  gamePath++;
  // check if the depth is deep enough
  gameStat current;
  if (deep_enough(depth, set_depth)) {
    if ((player == 1 && eval1 == 1) || (player == 2 && eval2 == 1)) {
      current.value = jarimEval(board, player);
      return current;
    } else if ((player == 1 && eval1 == 2) || (player == 2 && eval2 == 2)) {
      current.value = navyaEval(board, player);
      return current;
    }
  }

  // get sucessors by calling gen-move
  int** sucessor = gen_move(board, player);

  // sucssor is empty, treat it same as deep-enough
  if (sucessor[0][0] == INT_MIN) {
    if ((player == 1 && eval1 == 1) || (player == 2 && eval2 == 1)) {
      current.value = jarimEval(board, player);
      return current;
    } else if((player == 1 && eval1 == 2) || (player == 2 && eval2 == 2)) {
      current.value = navyaEval(board, player);
      return current;
    }
  }

  int succ_num = 0;
  for (int i = 0; i < 20; i++) {
    if (sucessor[i][0] != INT_MIN) succ_num++;
  }
  nodeNum += succ_num;
  // if sucessor is not empty
  gameStat result;
  bool didChange = false;
  for (int i = 0; i < succ_num; i++) {
    int opposite = 0;
    if (player == 1) opposite  = 2;
    else opposite = 1;
    result = minmaxAB(sucessor[i], set_depth, depth + 1, use_tresh, pass_tresh, opposite, eval1, eval2);
    int result_succ = result.value;
    int new_value = result_succ * -1;
    if (new_value > pass_tresh) {
      pass_tresh = new_value;
      result.path[pathCount] = i;
      pathCount++;
      for (int j = 0; j < 14; j++)  bestPathMinmax[j] = sucessor[i][j];
      didChange = true;
    }
    if (pass_tresh >= use_tresh) {
      result.value = pass_tresh;
      return result;
    }
  }
  return result;
}

int max_value(int val1, int val2){
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

int min_value(int val1, int val2){
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

gameStat alpha_beta_search(int* board, const int set_depth, int depth, int alpha, int beta, int player, const int eval1, const int eval2){

  // check if the depth is deep enough
  gameStat current;

  gamePath++;
  if (deep_enough(depth, set_depth)) {
    if ((player == 1 && eval1 == 1) || (player == 2 && eval2 == 1)) {
      current.value = jarimEval(board, player);
      return current;
    } else if ((player == 1 && eval1 == 2) || (player == 2 && eval2 == 2)) {
      current.value = navyaEval(board, player);
      return current;
    }
  }

  gameStat result;
  bool didChange = false;
  int val ;

  if(player == 1){
    // get sucessors by calling gen-move
    int** sucessor = gen_move(board, player);

    // sucssor is empty, treat it same as deep-enough
    if (sucessor[0][0] == INT_MIN) {
      if ((player == 1 && eval1 == 1) || (player == 2 && eval2 == 1)) {
        current.value = jarimEval(board, player);
        return current;
      } else if((player == 1 && eval1 == 2) || (player == 2 && eval2 == 2)) {
        current.value = navyaEval(board, player);
        return current;
      }
    }


    int succ_num = 0;
    for (int i = 0; i < 20; i++) {
      if (sucessor[i][0] != INT_MIN) succ_num++;
    }
  nodeNum += succ_num;
    bestValueAB = INT_MIN;
    for (int i = 0; i < succ_num; i++) {
      result = alpha_beta_search(sucessor[i], set_depth, depth + 1, alpha, beta, 2, eval1, eval2);
      val = result.value;

      if(val > bestValueAB){
        didChange = true;
        bestValueAB = val;
        result.path[pathCount] = i;
        pathCount++;
        for (int j = 0; j < 14; j++)  bestPathAB[j] = sucessor[i][j];
      }
      alpha = max_value(alpha, bestValueAB);

      if(alpha >= beta){
        break;
      }
    }
  }
  else{
    // get sucessors by calling gen-move
    int** sucessor = gen_move(board, player);

    // sucssor is empty, treat it same as deep-enough
    if (sucessor[0][0] == INT_MIN) {
      if ((player == 1 && eval1 == 1) || (player == 2 && eval2 == 1)) {
        current.value = jarimEval(board, player);
        return current;
      } else if((player == 1 && eval1 == 2) || (player == 2 && eval2 == 2)) {
        current.value = navyaEval(board, player);
        return current;
      }
    }


    int succ_num = 0;
    for (int i = 0; i < 20; i++) {
      if (sucessor[i][0] != INT_MIN) succ_num++;
    }

    bestValueABP2 = INT_MAX;
    for (int i = 0; i < succ_num; i++) {
      result = alpha_beta_search(sucessor[i], set_depth, depth + 1, alpha, beta, 1, eval1, eval2);
      val = result.value;

      if(val < bestValueABP2){
        didChange = true;
        bestValueABP2 = val;
        result.path[pathCount] = i;
        pathCount++;
        for (int j = 0; j < 14; j++)  bestPathAB[j] = sucessor[i][j];
      }
      beta = min_value(beta, val);

      if(alpha >= beta){
        break;
      }
    }
  }
  return result;
}

int main ()
{
  int algorithm1, algorithm2, evaluation1, evaluation2, set_depth;
  printf("*****WELCOME TO KALLAH***** (Input numbers for choices)\n");
  printf("Choose the Algorithm for Player 1.\n1. MINMAX\n2. Alpha-Beta\n");
  cin >> algorithm1;
  printf("Choose the evaluation function for Player 1.\n1. Jarim\n2. Navya\n");
  cin >> evaluation1;
  printf("Choose the Algorithm for Player 2.\n1. MINMAX\n2. Alpha-Beta\n");
  cin >> algorithm2;
  printf("Choose the evaluation function for Player 2.\n1. Jarim\n2. Navya\n");
  cin >> evaluation2;
  printf("Choose the depth. \n1. 2\n2. 4\n");
  int i;
  cin >> set_depth;

  /* Set up the game:
     player1 holes: board[0] - board[5]
             kallah: board[6]
     player2 holes: board[7] - board[12]
             kallah: board[13]           */
  timeval start, end;
  gettimeofday(&start, NULL);
  gamePath = 0, nodeNum = 0;
  int* board = new int [14];
  for (int i = 0; i < 14; i++) board[i] = 6;
  board[6] = 0;
  board[13] = 0;
  int use_tresh = INT_MAX;
  int pass_tresh = INT_MIN;
  gameStat result;
  int player = 1;
  int turn = 1;
  int winner;
  bool stillPlaying = true;
  printf("Initial Board: \n");
  printf("Player 1   Kallah: %d stones\n", board[6]);
  printf("           Holes: A-%d B-%d C-%d D-%d E-%d F-%d\n", board[5], board[4], board[3], board[2], board[1], board[0]);
  printf("Player 2   Kallah: %d stones\n", board[13]);
  printf("           Holes: f-%d e-%d d-%d c-%d b-%d a-%d\n\n", board[7], board[8], board[9], board[10], board[11], board[12]);

  while (stillPlaying) {
    printf("Play Number = %d, Player %d makes move.\n", turn, player);
    // run MinMax AB
    if (algorithm1 == 1 || algorithm2 == 1) {
      pathCount = 0;
      result = minmaxAB(board, set_depth, 0, use_tresh, pass_tresh, player, evaluation1, evaluation2);
      // transfer result
      for (int i = 0; i < 14; i++) board[i] = bestPathMinmax[i];
    }
    // run Alpha Beta Pruning
    if (algorithm1 == 2 || algorithm2 == 2) {
      pathCount = 0;
      result = alpha_beta_search(board, set_depth, 0, pass_tresh, use_tresh, player, evaluation1, evaluation2);
      //transfer result
      for (int i = 0; i < 14; i++) board[i] = bestPathAB[i];
    }
    // print the board
    printf("Path: ");
    for (int i = 0; i < 10; i++) {
      if (result.path[i] > 0 && result.path[i] < 13) printf("%d ", result.path[i]);
      else continue;
    }
    printf("\nThe board after the move: \n");
    printf("Player 1   Kallah: %d stones\n", board[6]);
    printf("           Holes: A-%d B-%d C-%d D-%d E-%d F-%d\n", board[5], board[4], board[3], board[2], board[1], board[0]);
    printf("Player 2   Kallah: %d stones\n", board[13]);
    printf("           Holes: f-%d e-%d d-%d c-%d b-%d a-%d\n\n", board[7], board[8], board[9], board[10], board[11], board[12]);

    // CAN GAME END?
    //check if half of the stone is in one kallah
    if (board[6] >= 36 || board[13] >= 36) {
      stillPlaying = false;
      winner = player;
    }
    // check if one side of hole is empty
    int empty1 = 0;
    int empty2 = 0;
    for (int i = 0; i < 6; i++) {
      if (board[i] == 0) empty1++;
    }
    for (int i = 7; i < 13; i++) {
      if (board[i] == 0) empty2++;
    }
    if (empty1 == 6 || empty2 == 6) {
      if (empty1 == 6) {
        int total = 0;
        for (int i = 7; i < 13; i++) {
          total += board[i];
          board[i] = 0;
        }
        board[13] += total;
      }
      if (empty2 == 6) {
        int total = 0;
        for (int i = 0; i < 6; i++) {
          total += board[i];
          board[i] = 0;
        }
        board[6] += total;
      }
      if (board[6] > board[13]) {
        winner = player;
        stillPlaying = false;
      } else {
        if (player == 1) winner = 2;
        else winner == 1;
        stillPlaying = false;
      }
    }
    //change the player
    if (player == 1) player = 2;
    else player = 1;
    turn++;
  }

  // Display Final Result
  printf("The Final Board: \n");
  printf("Player 1   Kallah: %d stones\n", board[6]);
  printf("           Holes: A-%d B-%d C-%d D-%d E-%d F-%d\n", board[5], board[4], board[3], board[2], board[1], board[0]);
  printf("Player 2   Kallah: %d stones\n", board[13]);
  printf("           Holes: f-%d e-%d d-%d c-%d b-%d a-%d\n\n", board[7], board[8], board[9], board[10], board[11], board[12]);

  printf("THE WINNER IS Player %d\n", winner);

  gettimeofday(&end, NULL);
  const double runtime = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
  printf("\n******STATISTICS*****\n");
  printf("Execution Time: %.4f s\n", runtime);
  printf("Length of game path: %d\n", gamePath);
  printf("Node generated: %d\n", nodeNum);
  printf("Node expanded: %d\n", turn);
   double vm, rss;
   process_mem_usage(vm, rss);
   cout << "Resident Memory Used: " << rss << endl;
}
