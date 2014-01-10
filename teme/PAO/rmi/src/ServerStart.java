import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.UnicastRemoteObject;
public class ServerStart implements Remote {

    private static Registry reg = null;
    private static Factory fact;

    public static void main(String[] argv) throws Exception {
        System.out.println("RMI Server has started");
        try {
            reg = LocateRegistry.createRegistry(8000);
            fact = new Factory();
            System.out.println("RMI registry has been created");
        } catch(RemoteException e) {
            System.out.println("java RMI registry already exists.");
        }
        reg.rebind("fact", fact);
        System.out.println("PeerServer bound in registry");
    }
}

