import java.rmi.*;
import java.rmi.server.*;

public class Factory extends UnicastRemoteObject
        implements ServerFactory {
    public Factory() throws RemoteException {}
    public MyServerInterface GiveUniqueServer() throws Exception {
        return new MyServerClass();
    }
}


