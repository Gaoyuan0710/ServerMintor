/**
 * Created by gaoyuan on 14-11-26.
 */

import java.sql.SQLException;

/**
 * Created by gaoyuan on 14-11-25.
 */

public class DealGetRequest {
    public static String getInfo(int clientID, String order) throws SQLException {
        if (order.equals("getBaseInfo")){
            return getClientBaseInfo(clientID);
        }
        else if(order.equals("getCpuInfo")){
            return getCpuInfo(clientID);
        }
        else if(order.equals("getMemInfo")){
            return getMemInfo(clientID);
        }
        else if (order.equals("getCpuRate")){
            return getCpuRate(clientID);
        }
        else if (order.equals("getNetWorkInfo")){
            return getNetWorkInfo(clientID);
        }
        else if(order.equals("getDiskIO")){
            return getDiskIO(clientID);
        }
        else{
            return "No info";
        }
    }
    public static String getClientBaseInfo(int clientID) throws SQLException {
        return StoreToDatabase.findBaseInfo(clientID);
    }
    public static String getCpuInfo(int clientID) throws SQLException {
        return StoreToDatabase.find("CpuInfo", "clientList", clientID);
    }
    public static String getMemInfo(int clientID) throws SQLException{
        return StoreToDatabase.find("MemInfo", "MonitorInformation", clientID);
    }
    public static String getCpuRate(int clientID) throws SQLException{
        return StoreToDatabase.find("Cpurate", "MonitorInformation", clientID);
    }
    public static String getNetWorkInfo(int clientID) throws SQLException{
        return StoreToDatabase.find("NetWorkInfo", "MonitorInformation", clientID);
    }
    public static String getDiskIO(int clientID) throws SQLException{
        return StoreToDatabase.find("IOInfo", "MonitorInformation", clientID);
    }
}

