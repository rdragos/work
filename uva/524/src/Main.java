import java.util.*;
import java.io.*;


class Main {
    public static void main(String[] argv) throws Exception{
        Task A = new Task();
        A.solve();
    }
}

class Task {
    int N; 
    int[] prime, sol, viz;
    PrintWriter out;
    private void ciur() {
        
        prime = new int[40];
        for (int i = 2; i < 40; ++i)
            prime[i] = 1;

        for (int i = 2; i < 40; ++i) {
            if (prime[i] == 0){
                continue;
            }
            for (int j = i * i; j < 40; j += i) {
                prime[j] = 0;
            }
        }
    }

    
    private void back(int k) {
        if (k > N) {

            if (prime[sol[N] + 1] == 0) {
                return ;
            }             
            for (int i = 1; i < N; ++i) {
                out.print(sol[i] + " ");
            }   
            out.println(sol[N]);
        } else {
            for (int i = 1; i <= N; ++i) {
                if (viz[i] == 0) {
                    if (k >= 2) {
                        if (prime[sol[k - 1] + i] == 0) {
                            continue;
                        }
                    }
                    sol[k] = i;
                    viz[i] = 1;
                    back(k + 1);
                    viz[i] = 0;
                }
            }
        }
    } 

    public void solve() throws Exception{
        
        Scanner in = new Scanner(System.in);
        out = new PrintWriter(System.out);
        
        sol = new int[20];
        viz = new int[20];
        ciur();
        int t = 1;
        viz[1] = 1;
        sol[1] = 1;
        while(in.hasNextInt()) {
            N = in.nextInt();
            if (t > 1) {
                out.println();
            }
            out.println("Case " + t + ":");            
             
            back(2);
            t += 1;
        }
        out.close();
    }
}
