//Pair of ('message', 'id') 'message' is sent from 'id'

public class MyPair {
    public String first;
    public int second;
    public MyPair() {
        first = null;
        second = 0;
    }

    public MyPair(String _first, int _second) {
        first = new String(_first);
        second = _second;
    }
}
