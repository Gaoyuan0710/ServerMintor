import java.util.HashMap;
import java.util.Map;

/**
 * Created by gaoyuan on 14-11-15.
 */
public class InfoType {
    private static Map<Integer, String> InfoTypeMap = new HashMap<Integer, String>();
    static {
        InfoTypeMap.put(0, "Notype");
        InfoTypeMap.put(1, "ClientBaseInfo");
        InfoTypeMap.put(2, "CpuInfo");
        InfoTypeMap.put(3, "MemInfo");
        InfoTypeMap.put(4, "CpuRate");
        InfoTypeMap.put(5, "NetWorkInfo");
        InfoTypeMap.put(6, "DiskIOInfo");
    }
    public static String getInfoType(int type){
        return InfoTypeMap.get(type);
    }
}
