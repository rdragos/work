import java.util.*;
import java.net.*;
import java.io.*;

class GetConnection extends Thread {
    
    static ArrayList<ClientSocket> ConnectionArray;
    static Queue<String> QMessages;
    static int NR_CONNECTIONS;

    private ServerSocket myServer;    
    private static int SocketNumber;
    private boolean terminate;
    
    public GetConnection(ServerSocket _myServer) {
        ConnectionArray = new ArrayList<ClientSocket>();

        SocketNumber = 0;
        myServer = _myServer;
        terminate = true;
    }
    public static int getSize() {
        return SocketNumber;
    }   
    public void setNumber(int _t) {
        SocketNumber = _t;
    }

    public void run() {
        try {
            while(terminate) {
                Socket link = myServer.accept();
                System.out.println("Just accepted a client");
                //Adding a socket 
                
                NR_CONNECTIONS++;
                //Let's open some threads for I/O operations
                ConnectionArray.add(new ClientSocket(link, NR_CONNECTIONS));               
            }
        }
        catch(IOException e) {
            System.out.println("Error accepting data from Server Socket");
        }
    }
}

