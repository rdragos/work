import java.io.*;

class MyReader extends Thread {
    private DataInputStream input;
    private int id;
    public boolean terminate = false;
    public MyReader(InputStream SocketIn, int _id) {
        id = _id;
        input = new DataInputStream(SocketIn);

    }
    public synchronized void run() { 
        String data = "";
        try {
           while(!terminate) {
               data = input.readUTF();
               ResolveConnection.QMessages.add(new MyPair(data, id));
           }
        } catch(IOException e) {
            System.out.println("Client disconnected from server");
        }
    }
};



