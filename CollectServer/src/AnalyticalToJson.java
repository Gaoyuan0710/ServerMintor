import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by gaoyuan on 14-11-1.
 */
public class AnalyticalToJson {
    public static void StringAnalyticalToJson(String string) throws Exception {
        JSONObject json = new JSONObject(string);

        for (int i = 0; i < json.length(); i++) {
            System.out.println(json.get("NetWorkInfo"));
            try {
                StoreToDatabase.insert( 10 , json.get("NetWorkInfo").toString());
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
