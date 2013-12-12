
import java.io.*;
import java.util.*;

class ClientOutput extends Thread {
    private DataOutputStream socketOut;
    private Scanner console;
    
    public ClientOutput(DataOutputStream _socketOut,Scanner _console) {
        socketOut = _socketOut;
        console = _console;
    }
    public synchronized void run() {
        try {
            
            String text;
            while(Client.terminate == false) {        
                text = console.nextLine();
                socketOut.writeUTF(text);
                socketOut.flush();
            }

        }
        catch(IOException e) {
            System.out.println("Error from ClientOuput : " + e.getMessage()); 
            System.exit(0);
        }
    }
}
