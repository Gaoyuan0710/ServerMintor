import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by gaoyuan on 14-11-1.
 */
public class AnalyticalToJson {
    public AnalyticalToJson(String string) throws JSONException {
        JSONArray json = new JSONArray(string);

        for (int i = 0; i < json.length(); i++){
            System.out.println(json.get(i));
        }
    }vim 
}
