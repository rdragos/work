import java.util.*;


class ResolveConnection extends Thread{
    
    boolean terminate;
    static Queue<MyPair> QMessages; 
    public ResolveConnection() {
        terminate = true;
        QMessages = new LinkedList<MyPair>();
    }
    
    private void BCAST(int _id, String toSend) {
       
        
        String name = new String();

        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.id == _id) {
                name = client.nick_name;
            }
        }
        if(name.length() == 0) {
            name = new String("Anonymous");
        }

        for (ClientSocket client : GetConnection.ConnectionArray) {
           client._Writer.sendData("(" + name + ")" + " " + toSend + "\n"); 
       }
    }

    private void NICK(int temp_id, String _nick) {
        int ok = 0;
        for (ClientSocket client : GetConnection.ConnectionArray) {        
            if(client.nick_name.equals(_nick) && temp_id != client.id) {
                ok += 1;
            }
        }

        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.id == temp_id) {
                if(ok > 0) {
                    client._Writer.sendData("Another name already exists\n");
                    continue;
                }
                client.nick_name = new String(_nick);
                client._Writer.sendData("Nick Name succesfully changed into " + _nick + "\n");
            }
        }
            
    }
    private void LIST(int _id) {
        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.id == _id) {
                ClientSocket current_client = client;
                current_client._Writer.sendData("List of connected clients\n");

                for (ClientSocket client2 : GetConnection.ConnectionArray) {
                    if(client2.nick_name.length() > 0) {
                        current_client._Writer.sendData(client2.nick_name);
                    } else {
                        current_client._Writer.sendData(new String("Anonymous"));
                    }
                }
                current_client._Writer.sendData("End of connected clients list\n");
                
                break;
            }
        }
    }
    private void MSG(int _id, String message) {
        
        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.id == _id) {
                client._Writer.sendData(message);
                return ;
            }
        }
    }
    private int MSG(int _id, String where, String message) {
        String _name = new String();

        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.id == _id) {
                _name = client.nick_name;
                break;
            }
        }
        if(_name.length() == 0) {
            _name = new String("Anonymous");
        }

        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.nick_name.equals(where)) {
                client._Writer.sendData("(" + _name + ")" + " " + message);
                return 1;
            }
        }
        return 0;
    }
    private void quit_client(int _id) {
        for (ClientSocket client : GetConnection.ConnectionArray) {
            if(client.id == _id) {
                client.disconnect();
                return ;
            }

        }
    }
    public void run() {
        while(terminate){
            //actually, iterate over messages to send
            
            try {
                while(QMessages.isEmpty()) {
                    Thread.sleep(30);
                }
            }catch(InterruptedException e) {
                System.out.println("Erorr at waiting in ResolveConnection");
            }            
            
            MyPair val = QMessages.poll();
            int temp_id = val.second;
            String[] text = val.first.split(" ");
            
            if(val.first.length() == 0) {
                continue;
            }

            if(text[0].equals("BCAST")) {
                if(val.first.length() > 6) {
                    BCAST(temp_id, val.first.substring(6));
                    continue;
                } 
            }

            if(text[0].equals("LIST")) { 
                LIST(temp_id);
                continue;
            } 
            if(text[0].equals("NICK")) {
                if(val.first.length() > 5) {
                    NICK(temp_id, val.first.substring(5));
                    continue;
                }
            }
            if(text[0].equals("MSG")) {
                //sending message text[2] to text[1]
                if(text[1].length() != 0 && val.first.length() > text[0].length() + text[1].length() + 2) {
                    String temp = val.first.substring(text[0].length() + text[1].length() + 2);
                    if(MSG(temp_id, text[1], temp) == 0) {
                        MSG(temp_id, "Sorry, no such user: " + text[1]);
                    }                       
                    continue;
                }
            }
            if(text[0].equals("QUIT")) {
                quit_client(temp_id);
                continue;
            }
           MSG(temp_id, "kimpossibru command");
        }        
    }
    
}

