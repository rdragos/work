import java.io.*;
import java.util.*;

//TO DO: implement pairs of (Nick, Message) - Nick wrote Message for you

class MyWriter extends Thread{
    
    private DataOutputStream out;
    private Queue <String> Q;

    public boolean terminate = false;

    public MyWriter(OutputStream SocketOut) {
        out = new DataOutputStream(SocketOut);
        Q = new LinkedList<String>(); 
    } 
    public synchronized void sendData(String s) {
        Q.add(s);
    }
    public void run() {
        while(!terminate) {
            try {
                Thread.sleep(5);
            } catch(InterruptedException e) {
                System.out.println("Erorr at waiting in MyWriter " + e.getMessage());
            }
            while(!Q.isEmpty()) {
                String x = Q.poll();
                try {
                    out.writeUTF(x); 
                    out.flush();
                } catch(IOException e) {
                    System.out.println("Error ar writing in sockets: MyWriter.java" + e.getMessage());
                }
            }
            //send data
        }
    }
}

    

