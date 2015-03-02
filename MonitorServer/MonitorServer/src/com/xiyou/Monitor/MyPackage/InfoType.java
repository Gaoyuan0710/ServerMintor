package com.xiyou.Monitor.MyPackage;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by gaoyuan on 14-11-15.
 */
public class InfoType {
    private static Map<Integer, String> ClientListMap = new HashMap<Integer, String>();

    static {
        ClientListMap.put(0, "Notype");
        ClientListMap.put(1, "No.1");
        ClientListMap.put(2, "No.2");
        ClientListMap.put(3, "No.3");
        ClientListMap.put(4, "No.4");
        ClientListMap.put(5, "No.5");
        ClientListMap.put(6, "No.6");
    }

    public static String getInfoType(int type) {
        return ClientListMap.get(type);
    }
}

