import java.rmi.RemoteException;
import java.rmi.server.*;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

public class MyServerClass extends UnicastRemoteObject implements MyServerInterface{
    private double stored;
    private double last;

    MyServerClass()throws RemoteException {
       super(0);
       stored = 0;
       last = 0;
    }     
    public void scadere1(double x) throws RemoteException {
        stored -= x;
    }
    public void set(double x)  throws RemoteException {
        stored = x;
    }
    public void adunare1(double x) throws RemoteException {
        stored += x;
    }
    public void read() throws RemoteException {
        stored = last;
    }
    public void clear() throws RemoteException {
        stored = 0;
    }
    public double adunare2(double x, double y) throws RemoteException{
        last = x + y;
        return last;
    }
    public double scadere2(double x, double y) throws RemoteException {
        last = x - y;
        return last;
    }
    public double inverse(double x) throws RemoteException {
        last = 1.0 / x;
        return last;
    }
    public double division(double x, double y) throws RemoteException {
        last = x / y;
        return last;
    }
    public double multiplication(double x, double y)  throws RemoteException {
        last = x * y;
        return last;
    }
    public double raiseToPow(double x, double y) throws RemoteException {
        last = pow(x, y);
        return last;
    }
    public double factorial(int x) throws RemoteException {
        double last = 1;
        for (int i = 1; i <= x; ++i) {
            last *= i;
        }
        return last;
    }
    public double root(double x) throws RemoteException {
        last = sqrt(x);
        return last;
    }
    public double getMem() throws RemoteException {
        return stored; 
    }
}
