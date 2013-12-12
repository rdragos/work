import java.util.*;
import java.io.*;

class Main {

    public static void main(String[] argv) throws Exception {
        
//        System.out.println("DASDDSAD");
        Task A = new Task();

//        System.out.println("DASDDSAD");
        A.solve();
//        System.out.println("DASDDSAD");
    }
}


class Task {


    int N;
    int[][] A;
    int[] B;
    int cnt_rook;
    int ans;


    int max(int a, int b) {
        if (a > b) {
            return a;
        } 
        return b;
    }
    
    boolean can(int i, int j) {
        if (A[i][j] > 0) {
            return false;
        }
        int ok = 0;
        // see on columns
        for (int k = i - 1; k >= 0; --k) {
            if ((B[k] & (1 << j)) > 0) {
                ok |= 1;
                break;
            }
            if (A[k][j] > 0) {
                break;
            }
        }
        //see on the same row
        for (int k = j - 1; k >= 0; --k) { 
            if ((B[i] & (1 << k)) > 0) {
                ok |= 1;
                break;
            }
            if (A[i][k] > 0) {
                break;
            }
        }
        return (ok == 0);
    }
    void back(int L) {
        if (L >= N) {
            ans = max(ans, cnt_rook);
        } else {
            for (int conf = 0; conf < (1 << N) ; ++conf) {
                int ok = 1;
                int b = 0;
                B[L] = conf;
                
                for (int i = 0; i < N; ++i) {
                     if ((conf & (1 << i)) > 0) {
                        b += 1;  
                        if (!can(L, i)) { 
                            ok = 0;
                            break;
                     }
                  }
               }

               if (ok > 0) {
                   cnt_rook += b;
                   back(L + 1);
                   cnt_rook -= b;
               }
               B[L] = 0;
            }
        }
    }
                   
    public void solve() throws Exception {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        
        N = in.nextInt();
        A = new int[10][10];    
        B = new int[10];    
        while(N != 0) {
            in.nextLine();

            ans = 0;    
            for (int i = 0; i < N; ++i) {
                String s = in.nextLine();
                for (int j = 0; j < N; ++j) {
                    if (s.charAt(j) == 'X')
                        A[i][j] = 1;
                    else {
                        A[i][j] = 0;
                    }
                }

            }
            
            back(0); 
            N = in.nextInt();
            out.println(ans);
        }
        
        out.close();        
    }
}
