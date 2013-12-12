import java.util.*;
import java.io.*;



class Main {
    public static void main(String[] argv) throws Exception {
        Task A = new Task();
        A.solve();
    }
}


class Task {

    int[] A, sol;
    int N, T;
    int s = 0;
    boolean pass;

    int LastPrintedConf;
    PrintWriter out;
    
    
    private void WriteSolution(int k) {
        pass = true;
        for (int i = 1; i < k; ++i) {
            out.print(A[sol[i]] + "+");
        }
        out.println(A[sol[k]]);
    }
    private void back(int _k, int S) {
        
        if (S == T && _k > 1) {
            WriteSolution(_k - 1);
        }
     
        if (_k > N || S > T) {
            return ;
        }
        sol[_k] = 0;
        for (int i = sol[_k - 1] + 1; i <= N; ++i) {
            if (A[sol[_k]] == A[i]) {
                continue;
            }
            sol[_k] = i;
            back(_k + 1, S + A[i]);
        }
    }

    public void solve() throws Exception {
        Scanner in = new Scanner(System.in);
        out = new PrintWriter(System.out);

        T = in.nextInt();
        N = in.nextInt();
        A = new int[20];
        sol = new int[20];
        A[0] = -1;
        while(N != 0) {
            
            out.println("Sums of " + T + ":");
            for (int i = 1; i <= N; ++i) {
                A[i] = in.nextInt();
            }
            for (int i = 1; i <= N; ++i) {
                for (int j = i + 1; j <= N; ++j)
                    if (A[i] < A[j]) {
                        int aux = A[i] ;
                        A[i] = A[j];
                        A[j] = aux;
                    }
            }

            pass = false;
            back(1, 0);

            if (!pass) {
                out.println("NONE");
            }
            T = in.nextInt();
            N = in.nextInt();
        }
        out.close();
    }
}


                        

