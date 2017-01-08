/**
 * Created by bradfier on 07/01/17.
 */

import org.msgpack.*;
import org.msgpack.template.Templates;
import org.msgpack.type.Value;
import org.msgpack.unpacker.Converter;
import org.zeromq.ZMQ;
import java.util.ArrayList;
import java.util.List;

public class Example {
    public static void main(String[] args) {
        ZMQ.Context context = ZMQ.context(1);

        //  Socket to talk to server
        System.out.println("Connecting to msgpack server");

        ZMQ.Socket socket = context.socket(ZMQ.REQ);
        socket.connect ("tcp://localhost:5555");

        int[] bytes = {0, 1, 2, 3, 4};

        MessagePack mp = new MessagePack();
        try {
            byte[] raw = mp.write(bytes);

            socket.send(raw);

            byte[] reply = socket.recv(0);
            Value dynamic = mp.read(reply);
            String text = new Converter(dynamic).read(Templates.TString).toString();
            System.out.println(text);
        } catch (Exception ex) {
            System.exit(1);
        }

        socket.close();
        context.term();
    }
}
