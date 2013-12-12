import java.util.*;
import java.io.*;
class Main {

    
    public static void main(String[] argv) throws Exception {
        Task A = new Task();
        A.solve();
    }

}



class Task {

    int Q, N, NR;
    int[][] Mat;
    int[] Pos, uz, perm;
    PrintWriter out;	
    
    void Mark(int x, int y, int[][] Mat, int val) {
        //left diagonal
        Mat[x][y] += val;
        int i = x - 1, j = y - 1;
        while(i >= 0 && j >= 0) {
            Mat[i][j] += val;
            i -= 1; j -= 1;
        }
        
        i = x + 1; j = y + 1;
        while(i < N && j < N) {
            Mat[i][j] += val;
            i += 1; j += 1;
        }
        //right diagonal
        i = x + 1; j = y - 1;
        while(i < N && j >= 0) {
            Mat[i][j] += val;
            i += 1; j -= 1;
        }
        i = x - 1; j = y + 1;
        while(i >= 0 && j < N) {
            Mat[i][j] += val;
            i -= 1; j += 1;
        }
        for (int k = 0; k < N; ++k) {
            if (k != x) {
                Mat[k][y] += val;
            } 
            if (k != y) {
                Mat[x][k] += val;
            }
        }

    }
    boolean RoutineCheck(int x, int y) {
        return (Mat[x][y] > 0);
    }
    void PrintSolution() {
       
        if(NR < 9) {
            out.print(" ");
        }
        NR += 1;
        out.print(NR + "      ");
        for (int i = 1; i < N; ++i)
            out.print(perm[i] + " ");
        out.println(perm[N]);
/*
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                out.print(Mat[i][j] + " ");
            }
            out.println();
        }
        out.println();
*/
    }
    void back(int k) {
        
        if (Pos[k] > 0) {
            
            if(RoutineCheck(k - 1, Pos[k] - 1)) {
                return ;
            }
             
            uz[Pos[k]] = 1;
            perm[k] = Pos[k];
            Mark(k - 1, Pos[k] - 1, Mat, 1);
            back(k + 1);

            uz[Pos[k]] = 0;
            Mark(k - 1, Pos[k] - 1, Mat, -1);

            return ;
        }        

        if (k > 8) {
            PrintSolution();
        } else {
            for (int i = 1; i <= 8; ++i) {
                if (uz[i] == 1) {
                    continue;
                }
                int x = k - 1;
                int y = i - 1;
 
                if (RoutineCheck(x, y)) {
                    continue;
                }
                
                Mark(x, y, Mat, 1);
                perm[k] = i;
                uz[i] = 1;
                back(k + 1);

                Mark(x, y, Mat, -1);
                uz[i] = 0;

            }
        }
    }
    public void solve() throws Exception{
        
        Scanner in = new Scanner(System.in);
        out = new PrintWriter(System.out);
        
        N = 8;
        Q = in.nextInt();
        
        perm = new int[10];
        uz = new int[10];
        Mat = new int[10][10];
        Pos = new int[10];
/*
        out.println("SOLN       COLUMN");
        out.println(" #      1 2 3 4 5 6 7 8");
        out.println();
*/
        for (int i = 1; i <= Q; ++i) {
            
            out.println("SOLN       COLUMN");
            out.println(" #      1 2 3 4 5 6 7 8");
            out.println();

            int x, y;
            x = in.nextInt();
            y = in.nextInt();

            Pos[y] = x;
            NR = 0;

            back(1);
            Pos[y] = 0;
            
            if (i < Q) {
                out.println();
            }

        }    
          
        out.close();
         
    }
}


