import java.rmi.*;

public interface MyServerInterface extends Remote {
    public double adunare2(double x , double y) throws RemoteException;
    public void adunare1(double x) throws RemoteException;

    public double scadere2(double x, double y) throws RemoteException;
    public void scadere1(double x) throws RemoteException;
    
    public void set(double x) throws RemoteException;
    public double inverse(double x) throws RemoteException;
    public double division(double x, double y) throws RemoteException;
    public double multiplication(double x, double y) throws RemoteException;
    public double raiseToPow(double x, double y) throws RemoteException;
    public double factorial(int x) throws RemoteException;
    public double root(double x) throws RemoteException;
    public void read() throws RemoteException;
    public void clear() throws RemoteException;
    public double getMem() throws RemoteException;
}
