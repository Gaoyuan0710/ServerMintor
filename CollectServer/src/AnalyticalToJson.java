import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by gaoyuan on 14-11-1.
 */
public class AnalyticalToJson {
    public static void StringAnalyticalToJson(int id, String string) throws Exception {
        JSONObject json = new JSONObject(string);
        String sqlData = "(\'";
        sqlData += id;
        sqlData += "\',\'";


        System.out.println("Json Start");
        String type = json.names().toString();
        String infoString = type.substring(2, type.length() - 2);

        //   System.out.println(infoString);
        //   System.out.println(json.get(infoString));

        JSONArray infoArray = new JSONArray(json.get(infoString).toString());

        for (int i = 0; i < infoArray.length(); i++) {
            JSONObject jsonObject = infoArray.getJSONObject(i);

            //     System.out.println(jsonObject);
            String infoType = jsonObject.names().toString();
            String infoData = infoType.substring(2, infoType.length() - 2);

            System.out.println("Begin");
            System.out.println(infoData);
            System.out.println(jsonObject.get(infoData));

            TempData tempData = TempData.getInstance();
            tempData.addKeyValue(infoData, jsonObject.get(infoData).toString());
            sqlData += jsonObject.get(infoData).toString() + "','";
            System.out.println("Over");

        }


        sqlData = sqlData.replaceAll("\"", "\\\"");
        sqlData = sqlData.substring(0, sqlData.length() - 2);
        sqlData += ");";
    //    System.out.println(sqlData);

        // System.out.println(json.get("ClientBaseInfo"));


        try {
            if (infoString.equals("MonitorInfo")) {
                StoreToDatabase.insert(sqlData);
            } else if (infoString.equals("BaseInfo")) {
                StoreToDatabase.update(id, sqlData);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
