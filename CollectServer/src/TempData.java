import java.util.concurrent.ConcurrentHashMap;

/**
 * Created by gaoyuan on 14-11-17.
 */
public class TempData {
    private static TempData data = new TempData();

    public static TempData getInstance() {
        return data;
    }

    private ConcurrentHashMap<String, String> demoMap;

    private TempData() {
        demoMap = new ConcurrentHashMap<String, String>();
    }

    public void addKeyValue(String key, String value) {
        demoMap.put(key, value);
    }

    public String getValue(String key) {
        return demoMap.get(key);
    }
}
