import com.mypacket.MyPacket;

import java.io.*;

/**
 * Created by gaoyuan on 14-10-16.
 */
public class TestMain {
    public static void main(String argvs[]){
        MyPacket.Packet.Builder info= MyPacket.Packet.newBuilder();
        File file = new File("");

        try {
            info.mergeFrom(new FileInputStream( file.getAbsolutePath() + "/src/kankan"));
        } catch (IOException e){
            e.printStackTrace();
        }

        System.out.println(info.getLen());
        System.out.println(info.getTypes());
        System.out.println(info.getValue());

    }
}
