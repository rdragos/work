
import java.io.*;

class ClientInput extends Thread {
    
    private DataInputStream socketIn;
    public ClientInput(DataInputStream _socketIn) {
        socketIn = _socketIn;
    }
    public synchronized void run() {
        try {
            while(true) {
                System.out.println(socketIn.readUTF());  
            }
        } catch(IOException e) {
            System.out.println("Adioooo, visul frumos s-a terminat!");
            System.exit(0);
        }
    }
}
