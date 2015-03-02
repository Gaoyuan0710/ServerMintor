package com.xiyou.Monitor.ToJson;

import com.xiyou.Monitor.DatabaseOps.StoreToDatabase;
import com.xiyou.Monitor.Log.ErrorLog;
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


        String type = json.names().toString();
        String infoString = type.substring(2, type.length() - 2);

        JSONArray infoArray = new JSONArray(json.get(infoString).toString());

        for (int i = 0; i < infoArray.length(); i++) {
            JSONObject jsonObject = infoArray.getJSONObject(i);

            String infoType = jsonObject.names().toString();
            String infoData = infoType.substring(2, infoType.length() - 2);

            sqlData += jsonObject.get(infoData).toString() + "','";

        }
        sqlData = sqlData.replaceAll("\"", "\\\"");
        sqlData = sqlData.substring(0, sqlData.length() - 2);
        sqlData += ");";

        try {
            if (infoString.equals("MonitorInfo")) {
                StoreToDatabase.insert(sqlData);
            } else if (infoString.equals("BaseInfo")) {
                StoreToDatabase.update(id, sqlData);
            }

        } catch (Exception e) {
            e.printStackTrace();
            ErrorLog.writeToFile(e.toString());
        }

    }
}
