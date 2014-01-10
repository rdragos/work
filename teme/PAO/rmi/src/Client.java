import java.rmi.Naming;
import java.rmi.registry.*;
import java.util.Scanner;
public class Client {

    public static void main(String[] argv) throws Exception {
         

        String url = "//localhost/MyServerClass";
        ServerFactory obj_factory = null;
        MyServerInterface obj_server = null;
        Registry reg;

        try {
            reg = LocateRegistry.getRegistry(8000);
            obj_factory = (ServerFactory)reg.lookup("fact");
        } catch(Exception e) {
            System.out.println("Conectare esuata");
            System.exit(0);
        }
        try {
            obj_server = obj_factory.GiveUniqueServer();
        } catch(Exception e) {
        }
        
        String t1 = "1: add(x y)\n2: mult(x,y)\n3: sub(x,y)\n4: quot(x,y)\n5: pow(x, y)\n";
        String t2 = "6: inverse(x)\n7: sqrt(x)\n8: fact(x)\n";
        String t3 = "9: M+(x)\n10: M-(x)\n11: set()\n12: read(x)\n13: clear()\n";
        String options = t1 + t2 + t3;
        Scanner input = new Scanner(System.in);
        while(true) {
            System.out.println(options);
            int n = input.nextInt();
            if (n == 8) {
                System.out.println("You've selected factorial\n");
                int x = input.nextInt();
                System.out.println(obj_server.factorial(x));
                continue;
            }
            if (n <= 5) {
                if (n == 1) {
                    System.out.println("You've selected: adunare\n"); 
                    double x = input.nextDouble(); double y = input.nextDouble();
                    System.out.println(obj_server.adunare2(x, y));
                } else if(n == 2) {
                    System.out.println("You've selected: multiplaction\n");
                    
                    double x = input.nextDouble(); double y = input.nextDouble();
                    System.out.println(obj_server.multiplication(x, y));
                } else if(n == 3) {
                    System.out.println("You've selected: scadere\n");
                    
                    double x = input.nextDouble(); double y = input.nextDouble();
                    System.out.println(obj_server.scadere2(x, y));
                } else if(n == 4) {
                    System.out.println("You've selected: division\n");
                    
                    double x = input.nextDouble(); double y = input.nextDouble();
                    System.out.println(obj_server.division(x, y));
                } else if (n == 5) {
                    System.out.println("You've selected: raise to pow\n");
                    
                    double x = input.nextDouble(); double y = input.nextDouble();
                    System.out.println(obj_server.raiseToPow(x, y));
                }
            } else if (n <= 11) {
                if (n == 6) { 
                    System.out.println("You've selected: inverse\n");
                    double x = input.nextInt();
                    System.out.println(obj_server.inverse(x));
                } else if(n == 7) {
                    System.out.println("You've selected: square root\n");
                    double x = input.nextInt();
                    System.out.println(obj_server.root(x));
                } else if (n == 9) {
                    System.out.println("You've selected: adding in memory\n");
                    double x = input.nextInt();
                    obj_server.adunare1(x);
                } else if (n == 10) {
                    System.out.println("You've selected: scadere in memory\n");
                    double x = input.nextInt();
                    obj_server.scadere1(x);
                } else if (n == 11) {
                    System.out.println("You've selected: setting in memory\n");
                    double x = input.nextInt();
                    obj_server.set(x);
                } 
            } else if(n <= 13) {
                if (n == 12) { 
                    System.out.println("You've selected: reading in memory\n");
                    obj_server.read();
                } else if (n == 13) {

                    System.out.println("You've selected: reseting the memory\n");
                    obj_server.clear();
                }
            } else {
                if (n == 14) {
                    System.out.println("Peek at memory\n");
                    System.out.println(obj_server.getMem());
                } else {
                  System.out.println("Careful, you are messing with command numbers\n");
                  }
            } 
        }

    }
}

