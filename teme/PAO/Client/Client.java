import java.io.*;
import java.net.*;
import java.util.*;


public class Client {
    
    private DataInputStream socketIn;
    private Scanner console;
    private DataOutputStream socketOut;
    private Socket socket;
    public static boolean terminate = false;

    private ClientOutput socketOutputParalel;
    private ClientInput socketInputParalel;
    
    public Client(String Hostname, int port) {
        try {
            socket = new Socket(Hostname, port);
            System.out.println("Connection started!");
            this.getInput();
            socketInputParalel = new ClientInput(socketIn);
            socketOutputParalel = new ClientOutput(socketOut, console); 
        } catch(UnknownHostException e){
            System.out.println("Sorry, no connection for you :(");
        } catch(IOException e) {
            System.out.println("IO exception for you :( reading from sockets");
        }
    }   
    public void multi() {
            socketInputParalel.start();
            socketOutputParalel.start();        
    }
    public void getInput() throws IOException {
        console = new Scanner(System.in);
        socketOut = new DataOutputStream(socket.getOutputStream());
        socketIn = new DataInputStream(socket.getInputStream());
    }
    public void stopme2() {
        try {
            if (console != null) console.close();
            if (socketOut != null) socketOut.close();
            if (socket != null) socket.close();
            System.out.println("Succesfully disconnected from Server");
            System.exit(0);
        } catch(IOException e) {
            System.out.println("Error closing files");
        }
    }

    public static void main(String argv[]) {
        Client client = null;
        
        if(argv.length != 2) {
            System.out.println("Se foloseste comanda: java Client host port");
        } else {
            client = new Client(argv[0], Integer.parseInt(argv[1])); 
            client.multi();
        }
    }
}
