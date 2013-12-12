import java.net.*;
import java.io.*;

class Server extends Thread{
    

    public static ServerSocket myServer;
    private int port;
    GetConnection Getter;
    ResolveConnection Solver;

    public Server(int _port){
        try {   
            port = _port;
            myServer = new ServerSocket(port); 
            Getter = new GetConnection(myServer);
            Solver = new ResolveConnection();
        } catch(IOException e) {
            System.out.println(e.getMessage());
        }
           
    }

    public void action() {
        //Getter gets me messages
        
        Getter.start();
        //Solver assures that everything is smooth between clients 
        Solver.start();
    }
    public static void main(String[] argv) {
        if (argv.length != 1) {
            System.out.println("Se foloseste comanda java Server nume_port");
        } else {
            System.out.println("Hello from Server");
            Server S = new Server(Integer.parseInt(argv[0]));
            S.action();
        }
    }
}
