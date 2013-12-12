import java.net.*;
import java.io.*;


class ClientSocket {
    //Structure of a client  
    Socket link;

    MyReader _Reader;
    public MyWriter _Writer;
    public int id = 0;
    public String nick_name;
    
    public synchronized void disconnect() {
        try {
//            System.out.println("Disconecting...");
            _Writer.terminate = true;
            _Reader.terminate = true;

            GetConnection.ConnectionArray.remove(this);
            link.close();
        } catch(IOException e) {
            System.out.println("Error closing socket: ClientSocket.disconnect()");
        }
    }
    public ClientSocket(Socket _link, int _id) {
        link = _link;
        id = _id;
        try { 
            nick_name = new String();
            _Writer = new MyWriter(link.getOutputStream());
            _Reader = new MyReader(link.getInputStream(), id);

            _Writer.start();
            _Reader.start();
        } catch(IOException e) {
            System.out.println("Error in SetConnection class" + e.getMessage()); 
        }
    }
}

